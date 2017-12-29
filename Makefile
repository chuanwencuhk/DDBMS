DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin
LEX		= flex
YACC 	= bison
CC 		= g++
SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC}))

#yacc.tab.c -> yacc.tab.o 
#lex.yy.c -> lex.yy.o

TARGET = main
BIN_TARGET = ${DIR_BIN}/${TARGET}
CFLAGSs =  -g -I/usr/include/mysql/ -lmysqlclient -lrpc_sql -pthread -lrpc -lmysqlcppconn -lconfig++

${BIN_TARGET}: ${DIR_OBJ}/yacc.tab.o ${DIR_OBJ}/lex.yy.o ${OBJ}
	$(CC) $(DIR_OBJ)/yacc.tab.o $(DIR_OBJ)/lex.yy.o $(OBJ) -o $@ $(CFLAGSs)

${DIR_SRC}/yacc.tab.c ${DIR_SRC}/yacc.tab.h: yacc.y
	$(YACC) -d yacc.y && mv yacc.tab.h ${DIR_INC} && mv yacc.tab.c ${DIR_SRC}

${DIR_SRC}/lex.yy.c:lex.l
	$(LEX) lex.l && mv lex.yy.c ${DIR_SRC}

${DIR_OBJ}/lex.yy.o: ${DIR_SRC}/lex.yy.c
	$(CC) -c $< -o $@
${DIR_OBJ}/yacc.tab.o:${DIR_SRC}/yacc.tab.c ${DIR_SRC}/yacc.tab.h
	$(CC) -c $< -o $@
${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) -c $< -o $@ -I/usr/include/mysql/ $(CFLAGSs)

.PHONY:clean
clean:
	cd ${DIR_SRC} && rm -rf yacc.tab.* lex.yy.*
	cd ${DIR_INC} && rm -rf yacc.tab.*
	cd ${DIR_OBJ} && rm -rf *