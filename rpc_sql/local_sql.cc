#include "local_sql.h"
#include "mylog.h"

string getMySQLIp(){
	return "tcp://127.0.0.1:3306";
}
string getUsername(){
	return "root";
}
string getPassword(){
	return "root";
}


bool localExecute(string sql_statement){
	cout << "sql_statement " << sql_statement << endl;
	cout << "localExecute(string sql_statement)" << endl;
	MySQL_Driver *driver;
	Connection *con;
	Statement *stmt;
	driver = sql::mysql::get_mysql_driver_instance();
	cout << "	driver = sql::mysql::get_mysql_driver_instance();" << endl;
	con = driver->connect(getMySQLIp(), getUsername(), getPassword());
	con->setSchema("test");
	stmt = con->createStatement();
	cout << "stmt = con->createStatement();" << endl;
	bool ok = false;
	cout << "bool ok = false;" << endl;
	assert(sql_statement.size() > 0);
	ok = stmt->execute(sql_statement);
	cout << "ok " << ok << endl;
	delete con;
	delete stmt;
	cout << "delete stmt;" << endl;
	return ok;
}

int localExecuteUpdate(string sql_statement){
	MySQL_Driver *driver;
	Connection *con;
	Statement *stmt;
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect(getMySQLIp(), getUsername(), getPassword());
	con->setSchema("test");
	stmt = con->createStatement();
	int cnt = false;
	assert(sql_statement.size() > 0);
	cnt = stmt->executeUpdate(sql_statement);
	delete con;
	delete stmt;
	return cnt;
}



string localExecuteQuery(string sql_statement){
	MySQL_Driver *driver;
	Connection *con;
	Statement *stmt;
	ResultSet  *res;
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect(getMySQLIp(), getUsername(), getPassword());
	con->setSchema("test");
	stmt = con->createStatement();
	res = stmt->executeQuery(sql_statement);
	int columnCnt = res->getMetaData()->getColumnCount();
	string result;
	while (res->next()){
		for (int i=1;i<=columnCnt;++i){
			result.append(res->getString(i));
			result.append(",");
		}
		result.append("\n");
	}
	return result;
}


bool localInsertFileToTable(string sql_file, string table_name){
	string file_name = "tmp";
	ofstream tmp(file_name, std::ios::out);
	tmp << sql_file;
	tmp.close();
	string sql_statement = 
	string("LOAD DATA LOCAL INFILE ") +
	"'" + file_name + "'" +
	" INTO TABLE " + table_name +
	" FIELDS TERMINATED BY \t " +
	"LINES TERMINATED BY '\n'";

	MySQL_Driver *driver;
	Connection *con;
	Statement *stmt;
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect(getMySQLIp(), getUsername(), getPassword());
	con->setSchema("test");
	stmt = con->createStatement();
	bool ok = false;
	assert(sql_statement.size() > 0);
	ok = stmt->execute(sql_statement);
	delete con;
	delete stmt;
	return ok;
}