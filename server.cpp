
#include <ctime>
#include <string>
#include <iostream>
#include <future>
#include <vector>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/thread.hpp>



using namespace boost;
using namespace boost::asio;
using boost::asio::ip::tcp;

class Server
{

public:
  Server(int socket_num, int threads_num) : threads_num(threads_num), acceptor(io_context, tcp::endpoint(tcp::v4(), socket_num))
  {
    for (int i = 0; i < threads_num; ++i)
    {
      threads.push_back(async(std::launch::async, []() {}));
    }
  }

  std::string make_daytime_string()
  {
    time_t now = std::time(0);
    return std::ctime(&now);
  }

  void Start()
  {

    for (int i = 0; i <= threads_num; ++i)
    {
      if (i == threads_num)
      {
        i = 0;
      }

      std::future_status status = threads[i].wait_for(std::chrono::microseconds(10));
      if (status == std::future_status::ready)
      {
        threads[i] = async(std::launch::async, [this]()
                           {
      tcp::socket socket(io_context);
      acceptor.accept(socket);
      accept_handler(socket); });
      }
    }
  }

  void accept_handler(tcp::socket &socket)
  {
    std::string message = make_daytime_string();

    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    std::cout << "Peer IP: " << socket.remote_endpoint().address().to_string() << std::endl;

    while (true)
    {
      std::string buff;
      auto bytes = read_until(socket, boost::asio::dynamic_buffer(buff), "\n");
      std::cout << buff.substr(0, bytes) << std::flush;
      boost::asio::write(socket, boost::asio::buffer("Hello," + socket.remote_endpoint().address().to_string() + " now its: " + make_daytime_string()));
    }
    return;
  }

private:
  boost::asio::io_context io_context;
  tcp::acceptor acceptor;
  int threads_num = 1;
  std::vector<std::future<void>> threads;
};

int main()
{
  Server server(9000, 10);
  server.Start();
}
