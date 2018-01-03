  #include "metadatamanager.h"

#include <iomanip>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace libconfig;
MetadataManager::MetadataManager()
{
    string str = METADATA_CONFIG_FILE;
    initialize_from_config_file(str);//initialize the MetadataManager
    initialize_tablemetadata();//initialize the tablemetadata
    //read_config_file(str);
    cout<<"MetadataManager() is starting"<<endl;
    ptablemetadata = NULL;
    ptablemetadata = tablemetadata;
    printf("ptablemetadata is %p\n",ptablemetadata);

}


MetadataManager::~MetadataManager()
{

}

void MetadataManager::read_config_file( const string& filename)
{
    //try-catch block from libconfig manual
    // Read the file. If there is an error, report it and exit.
    try
    {
      cfg.readFile(filename.c_str());
    }
    catch(const FileIOException &fioex)
    {
      std::cerr << "I/O error while reading file." << std::endl;
      //return(EXIT_FAILURE);
    }
    catch(const ParseException &pex)
    {
      std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                << " - " << pex.getError() << std::endl;
      //return(EXIT_FAILURE);
    }


}

void MetadataManager::initialize_from_config_file(const string &str)
{
    read_config_file(str);//open and read metadata.cfg

    try
    {
      string version = cfg.lookup("version");
      cout << "version: " << version << endl;
      this->version = version;//get version info
    }
    catch(const SettingNotFoundException &nfex)
    {
      cerr << "No 'version' setting in configuration file." << endl;
    }


    try
    {
      string database_path = cfg.lookup("db1.database_path");

      this->database_path = database_path;//get database path info
      cout << "database_path: " << this->database_path << endl;
    }
    catch(const SettingNotFoundException &nfex)
    {
      cerr << "No 'database_path' setting in configuration file." << endl;
    }


    try
    {
      string database_name = cfg.lookup("db1.database");

      this->database_name = database_name;//get database name info
      cout << "database_name: " << this->database_name << endl;
    }
    catch(const SettingNotFoundException &nfex)
    {
      cerr << "No 'database_name' setting in configuration file." << endl;
    }


    try
    {
      int num_of_tables = cfg.lookup("db1.table_num");

      this->num_of_tables = num_of_tables;//get tables' num
      cout << "num_of_tables: " << this->num_of_tables << endl;
    }
    catch(const SettingNotFoundException &nfex)
    {
      cerr << "No 'table_num' setting in configuration file." << endl;
    }


//    const Setting& database = cfg.getRoot();
//    try
//    {
//      //const Setting &tables = database["database"]["supplier"];
//      const Setting &tables = database["database"]["supplier"];
//      int count = tables.getLength();
//      cout<<"the tables'num is "<<count<<endl;

//    }
//    catch(const SettingNotFoundException &nfex)
//    {
//      //Ignore.
//      cout<<"error"<<endl;
//    }

}

void MetadataManager::initialize_tablemetadata()
{
        const Setting& database = cfg.getRoot();
        try
        {
          //const Setting &tables = database["db1"]["supplier"];
          const Setting &tables = database["db1"]["SUPPLIER"];
          int count = tables.getLength();
          cout<<"the table own attr num is "<<count<<endl;
          string str_table_name;
          string str_path;
          int attr_num = 0;

          string attr_name;
          string attr_datatype;
          int attr_length;
          string attr_rulestype;

          tables[0].lookupValue("table_attr_num",attr_num);
          tables[0].lookupValue("table_name",str_table_name);
          tables[0].lookupValue("table_path",str_path);
          cout<<"tables[0].table_name is: "<<str_table_name<<endl;
          cout<<"tables[0].table_attr_num is: "<<attr_num<<endl;
          cout<<"tables[0].table_path is: "<<str_path<<endl<<endl;
          for(int i =1;i < count;i++)
          {
           tables[i].lookupValue("attr_name",attr_name);
           tables[i].lookupValue("attr_datatype",attr_datatype);
           tables[i].lookupValue("attr_length",attr_length);
           tables[i].lookupValue("attr_rulestype",attr_rulestype);
           cout<<i<<" attr_name is: "<<attr_name<<endl;
           cout<<i<<" attr_datatype is: "<<attr_datatype<<endl;
           cout<<i<<" attr_length is: "<<attr_length<<endl;
           cout<<i<<" attr_rulestype is: "<<attr_rulestype<<endl<<endl;


          }
        }
        catch(const SettingNotFoundException &nfex)
        {
          //Ignore.
          cout<<"initialize_tablemetadata() error"<<endl;
        }



}
