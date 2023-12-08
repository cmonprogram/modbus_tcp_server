# tcp_server
Моя реализация многопоточного tcp-сервера на основе boost::asio

## Использование

Установить порт и количество потоков
```
int main()
{
  Server server(9000, 10);
  server.Start();
}
```
Собрать и запустить
```
cmake . && cmake --build .
./best_tcp_server
```
Подключиться
```
nc localhost 9000
```
Вывод:
```
Fri Dec  8 05:16:08 2023
>Hello
Hello,127.0.0.1 now its: Fri Dec  8 05:16:12 2023
```
