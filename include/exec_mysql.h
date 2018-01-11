#include <string>
#include <vector>
#include <mysql/mysql.h>
using std::string;

extern MYSQL *mysql_conn;
extern MYSQL_RES *res;

extern vector<string> ip_vec;
void finish_with_error(const char* msg);
int exe_sql(const char *sql);
int init_mysql();
int get_frag_data();
void load_data();
int load_data_into_local_db(string tb_name);
string readFileIntoString(string filename);

void exec_select_stmt();
void exec_drop_table_stmt();
void exec_show_table_stmt();
void exec_create_stmt();
void exec_delete_stmt();
void exec_update_stmt();