#!/bin/bash
g++ -c local_sql.cc rpc_server.cc rpc_sql.cc 
ar -crv librpc_sql.a local_sql.o rpc_server.o rpc_sql.o 
sudo cp librpc_sql.a /usr/local/lib/
g++ -o myserver rpc_server_test.cc -lrpc_sql -pthread -lrpc -lmysqlcppconn

