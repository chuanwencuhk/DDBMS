LEX=flex
YACC=bison
CC=g++
OBJECT=parser			

$(OBJECT): lex.yy.o  yacc.tab.o parser.o conn_mysql.o main.o
	$(CC)  lex.yy.o yacc.tab.o parser.o conn_mysql.o main.o -I/usr/include/mysql/ -lmysqlclient -lrpc_sql -pthread -lrpc -lmysqlcppconn -o $(OBJECT)

main.o: yacc.tab.h main.cpp
	$(CC) -c main.cpp

conn_mysql.o: parser.h parser.cpp lex.yy.c yacc.tab.c  yacc.tab.h conn_mysql.cpp
	$(CC) -c conn_mysql.cpp 

parser.o: parser.h parser.cpp lex.yy.c yacc.tab.c  yacc.tab.h
	$(CC) -c  parser.cpp

lex.yy.o: lex.yy.c  yacc.tab.h  parser.h
	$(CC) -c  lex.yy.c

yacc.tab.o: yacc.tab.c  parser.h
	$(CC) -c  yacc.tab.c
yacc.tab.c  yacc.tab.h: yacc.y
	$(YACC) -d yacc.y

lex.yy.c: lex.l
	$(LEX) lex.l

.PHONY:prepare
clean:
	rm -rf yacc.tab.* lex.yy.*
	@rm -f $(OBJECT)  *.o
prepare:
	cd /home/wcw/ddb_parser/rpc_sql
	g++ -c local_sql.cc rpc_server.cc rpc_sql.cc
	ar -crv librpc_sql.a local_sql.o rpc_server.o rpc_sql.o
	sudo cp librpc_sql.a /usr/local/lib/
	g++ -o myserver rpc_server_test.cc -lrpc_sql -pthread -lrpc -lmysqlcppconn
