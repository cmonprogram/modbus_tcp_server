# tcp_server
Моя реализация многопоточного tcp-сервера на основе boost::asio

## Использование
Собрать и запустить
```
cmake . -DBOOST_ROOT=<path to boost folder>
cmake --build .
./best_tcp_server <port> <threads num>
```
Подключиться
```
nc localhost 9000
```
Вывод:
```
Fri Dec  8 05:16:08 2023
>Hello
Hello, 127.0.0.1 now its: Fri Dec  8 05:16:12 2023
```
