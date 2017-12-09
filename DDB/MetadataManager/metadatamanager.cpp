  #include "metadatamanager.h"

#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <unistd.h>//for access() fuction
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
    if(-1 == access(filename.c_str(),F_OK))//whether the metadata.cfg exist
    {
        ofstream of;
        of.open(filename.c_str());
        of.close();
        cout<<"file not exist create it"<<endl;
    }
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
        Setting &root = cfg.getRoot();

        if(! root.exists(CONFIG_NAME_VERSION))
          {
            root.add(CONFIG_NAME_VERSION, Setting::TypeString);
            this->version = "";
            cout<<"initialize_from_config_file no version\n";
          }
        else
        {
            string version = cfg.lookup(CONFIG_NAME_VERSION);
            cout << "version: " << version << endl;
            this->version = version;//get version info
        }


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

void MetadataManager::setMetadataVer(string str)
{


    cfg.setOptions(Config::OptionFsync
                   | Config::OptionSemicolonSeparators
                   | Config::OptionColonAssignmentForGroups
                   | Config::OptionOpenBraceOnSeparateLine);

    Setting &root = cfg.getRoot();

    if(! root.exists(CONFIG_NAME_VERSION))
    {
      root.add(CONFIG_NAME_VERSION, Setting::TypeString);
      cout<<"setMetadataVer no version\n";
    }

    Setting &version = root[CONFIG_NAME_VERSION];
    version = str;



    // Write out the updated configuration.
    try
    {
      cfg.writeFile(METADATA_CONFIG_FILE);
      cerr << "Updated configuration successfully written to: " << METADATA_CONFIG_FILE
           << endl;

    }
    catch(const FileIOException &fioex)
    {
      cerr << "I/O error while writing file: " << METADATA_CONFIG_FILE << endl;
      //return(EXIT_FAILURE);
    }
    //read_config_file(METADATA_CONFIG_FILE);
    //return(EXIT_SUCCESS);
    string s = cfg.lookup(CONFIG_NAME_VERSION);
    cout << "the update version is: " << s << endl;
    this->version = s;
}




void MetadataManager::initialize_siteinfo()
{
    cfg.setOptions(Config::OptionFsync
                   | Config::OptionSemicolonSeparators
                   | Config::OptionColonAssignmentForGroups
                   | Config::OptionOpenBraceOnSeparateLine);

    Setting &root = cfg.getRoot();
    if(! root.exists(CONFIG_NAME_SITEINFO))
    {
      root.add("site_info", Setting::TypeList);
      cout<<"initialize_siteinfo no site_info"<<endl;
    }
//      Setting& siteInfolist = root["site_info"];

//    Setting& infoItem = siteInfolist.add(Setting::TypeGroup);
//    infoItem.add("site_name",Setting::TypeString) = "site4";
//    infoItem.add("site_ip",Setting::TypeString) = "123.123.123.123";
//    infoItem.add("site_port",Setting::TypeInt) = 3389;

    // Write out the updated configuration.

    //read_config_file(METADATA_CONFIG_FILE);
    //return(EXIT_SUCCESS);
    //Setting& item = root["site_info"];

    //string s ;
    //item[0].lookupValue("site_ip", s);
    write_to_config_file(METADATA_CONFIG_FILE);
    cout << "initialize_siteinfo is ok! "  << endl;

}

void MetadataManager::initialize_database(std::string db_name)
{
    cfg.setOptions(Config::OptionFsync
                   | Config::OptionSemicolonSeparators
                   | Config::OptionColonAssignmentForGroups
                   | Config::OptionOpenBraceOnSeparateLine);

    Setting &root = cfg.getRoot();
    if(! root.exists(db_name))
    {
      root.add(db_name, Setting::TypeGroup);
      write_to_config_file(METADATA_CONFIG_FILE);
      cout<<"initialize_database:"<<db_name<<endl;
    }


    cout << "initialize_siteinfo is ok! "  << endl;


}

void MetadataManager::initialize_fragment()
{
    cfg.setOptions(Config::OptionFsync
                   | Config::OptionSemicolonSeparators
                   | Config::OptionColonAssignmentForGroups
                   | Config::OptionOpenBraceOnSeparateLine);

    Setting &root = cfg.getRoot();
    if(! root.exists(CONFIG_NAME_FRAGMENT))
    {
      root.add(CONFIG_NAME_FRAGMENT, Setting::TypeGroup);
      cout<<"initialize_fragment no fragment"<<endl;
      write_to_config_file(METADATA_CONFIG_FILE);
    }

    cout << "initialize_fragment is ok! "  << endl;

}

void MetadataManager::write_to_config_file(std::string filename)
{
    try
    {
      cfg.writeFile(filename.c_str());
      cerr << "Updated configuration successfully written to: " << filename
           << endl;

    }
    catch(const FileIOException &fioex)
    {
      cerr << "I/O error while writing file: " << filename << endl;
      //return(EXIT_FAILURE);
    }
    cout<<"write_to_config file:"<<filename;

}
