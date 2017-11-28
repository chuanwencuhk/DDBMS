%{
#include <stdio.h>
#include <stdlib.h>
#include "tinySQL_test.tab.h"

int lineno = 1;
void yyerror(char *s);
char *strdupxy(char *s);

int lex_init();
%}
%%

	/* reserved keywords */
CREATE	|
create		return CREATE;
TABLE	|
table		return TABLE;
DROP	|
drop		return DROP;
INDEX	|
index		return INDEX;
SELECT	|
select		return SELECT;
FROM	|
from		return FROM;
WHERE	|
where		return WHERE;
ORDER	|
order		return ORDER;
BY	|
by		return BY;
ASC	|
asc		return ASC;
DESC	|
desc		return DESC;
UNIQUE	|
unique		return UNIQUE;
ALL	|
all		return ALL;
DISTINCT |
distinct	return DISTINCT;
INSERT	|
insert		return INSERT;
INTO	|
into		return INTO;
VALUES	|
values		return VALUES;
DELETE	|
delete		return DELETE;
AND	|
and		return AND;
INT(EGER)? |
int(eger)?	return INTEGER;
CHAR(ACTER)? |
char(acter)?	return CHARACTER;
varchar |
VARCHAR		return VARCHAR;
EXIT	|
exit	|
QUIT	|
quit		return EXIT;
DATE	|
date		return DATE;
SHOW	|
show		return SHOW;
TABLES	|
tables		return TABLES;

	/* punctation */
"="	|
"<>"	|
"<"	|
">"	|
"<="	|
">="			yylval.strval = strdupxy(yytext);	return COMPARISION;
[-+*/:(),.;]							return yytext[0];

'[^'\n]*'	yylval.strval = strdupxy(yytext); 	return STRING;
	/* names */
[a-zA-Z][a-zA-Z0-9_]*		yylval.strval = strdupxy(yytext);	return NAME;
	/* numbers */
[0-9]+		yylval.strval = strdupxy(yytext);	return NUMBER;



	/* whitespace */
\n	lineno++;
[ \t\r]+	;

	
	/* anything else */
.		yyerror("invalid character");
%%

int main(){
	
	while(1)
    {
       parser_init();
       int rnt = yyparse();
       if(rnt==-1)
            break;
    }
	printf("# of lines = %d\n",lineno);
	return 0;
}
void yyerror(char *s)
{
	printf("> %s at ==> %s\n", s, yytext);
	printf("SQL syntax error....\n");
}

int yywrap()
{
	extern int ctb;
	if (yyin == stdin) {
		return 1;
	} else {
		fclose(yyin);
		printf("stdDBMS> ");
		yyin = stdin;
		return 0;
	}
}
/* make a duplicate of s */
char *strdupxy(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}
int lex_init()
{
	lineno = 1;
	return 0;
}

