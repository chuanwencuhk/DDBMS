  #include "metadatamanager.h"

#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "tableMetadataInfo.h"
#include <unistd.h>//for access() fuction
using namespace std;
using namespace libconfig;

MetadataManager* MetadataManager::pmtr = NULL;
MetadataManager::MetadataManager()
{
    //string str = METADATA_CONFIG_FILE;
    initialize_from_config_file(METADATA_CONFIG_FILE);//initialize the MetadataManager

    initialize_database();//initialize DDB segment
    load_tablemetadata_fromcfg();

    initialize_siteinfo();//initialzie site_info segment
    initialize_fragment();//initialize fragment segment
    load_fragmentmetadata_fromcfg();

    //initialize_tablemetadata();//initialize the tablemetadata
    //read_config_file(str);
    //ptablemetadata = NULL;
    //ptablemetadata = tablemetadata;
    //printf("ptablemetadata is %p\n",ptablemetadata);

    cout<<"MetadataManager() is starting"<<endl;

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


//    try
//    {
//      int num_of_tables = cfg.lookup("db1.table_num");

//      this->num_of_tables = num_of_tables;//get tables' num
//      cout << "num_of_tables: " << this->num_of_tables << endl;
//    }
//    catch(const SettingNotFoundException &nfex)
//    {
//      cerr << "No 'table_num' setting in configuration file." << endl;
//    }


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

//not to use anymore
void MetadataManager::initialize_tablemetadata()
{


      try
        {
        cfg.setOptions(Config::OptionFsync
                       | Config::OptionSemicolonSeparators
                       | Config::OptionColonAssignmentForGroups
                       | Config::OptionOpenBraceOnSeparateLine);
        Setting &root = cfg.getRoot();

                if(! root.exists(CONFIG_NAME_DATABASE))
                {
                  root.add(CONFIG_NAME_DATABASE, Setting::TypeGroup);
                  cout<<"initialize_tablemetadata no database"<<endl;
                }


//          //const Setting &tables = database["db1"]["supplier"];
//          const Setting &tables = database["db1"]["SUPPLIER"];
//          int count = tables.getLength();
//          cout<<"the table own attr num is "<<count<<endl;
//          string str_table_name;
//          string str_path;
//          int attr_num = 0;

//          string attr_name;
//          string attr_datatype;
//          int attr_length;
//          string attr_rulestype;

//          tables[0].lookupValue("table_attr_num",attr_num);
//          tables[0].lookupValue("table_name",str_table_name);
//          tables[0].lookupValue("table_path",str_path);
//          cout<<"tables[0].table_name is: "<<str_table_name<<endl;
//          cout<<"tables[0].table_attr_num is: "<<attr_num<<endl;
//          cout<<"tables[0].table_path is: "<<str_path<<endl<<endl;
//          for(int i =1;i < count;i++)
//          {
//           tables[i].lookupValue("attr_name",attr_name);
//           tables[i].lookupValue("attr_datatype",attr_datatype);
//           tables[i].lookupValue("attr_length",attr_length);
//           tables[i].lookupValue("attr_rulestype",attr_rulestype);
//           cout<<i<<" attr_name is: "<<attr_name<<endl;
//           cout<<i<<" attr_datatype is: "<<attr_datatype<<endl;
//           cout<<i<<" attr_length is: "<<attr_length<<endl;
//           cout<<i<<" attr_rulestype is: "<<attr_rulestype<<endl<<endl;


          }

        catch(const SettingNotFoundException &nfex)
        {
          //Ignore.
          cout<<"initialize_tablemetadata() error"<<endl;
        }



}


void MetadataManager::set_tablemetadata(TableMedata &Tbm)
{



    string str = Tbm.table_name;
    tableMetadataInfo.set_table_metadata(Tbm);

    add_tablename_intolist(str);

    Setting& root = cfg.getRoot();
    Setting& ddb_cfg = root[CONFIG_NAME_DATABASE];
    if(ddb_cfg.exists(str.c_str()))
        ddb_cfg.remove(str.c_str());

    ddb_cfg.add(str.c_str(),Setting::TypeGroup);
    Setting& tb_cfg = ddb_cfg[str.c_str()];

    //int pos = tableMetadataInfo.get_tablemetadata_pos_bystr(str);
    //TableMedata tmp =tableMetadataInfo.get_tablemetadata_bypos(pos);
    TableMedata tmp =tableMetadataInfo.get_tablemetadata_bystr(str);
     tb_cfg.add(CONFIG_NAME_TALBE_ATTR_NUM,Setting::TypeInt) = tmp.table_attr_num;

    for(int i = 0; i<tmp.table_attr_num; i++)
    {
        tb_cfg.add(CONFIG_NAME_TABLE_ATTR_SLICE+to_string(i), Setting::TypeGroup);
        Setting& attr_cfg = tb_cfg[CONFIG_NAME_TABLE_ATTR_SLICE+to_string(i)];

        attr_cfg.add(CONFIG_NAME_TABLE_ATTR_NAME, Setting::TypeString) = tmp.Attr[i].attr_name;
        attr_cfg.add(CONFIG_NAME_TABLE_ATTR_DATATYPE,Setting::Setting::TypeInt) \
                = (int)tmp.Attr[i].attr_datatype;
        attr_cfg.add(CONFIG_NAME_TABLE_ATTR_LENGTH,Setting::TypeInt) = tmp.Attr[i].attr_length;
        attr_cfg.add(CONFIG_NAME_TABLE_ATTR_RULESTYPE,Setting::TypeInt) = (int)tmp.Attr[i].attr_rulestype;


    }

    write_to_config_file(METADATA_CONFIG_FILE);

}
//2017-12-30 addby yfchai
void MetadataManager::delete_tablemetadata(string str)
{
    tableMetadataInfo.delete_tablemetadata_inmap(str);

    delete_tablename_formlist(str);

    Setting& root = cfg.getRoot();
    Setting& ddb_cfg = root[CONFIG_NAME_DATABASE];
    if(ddb_cfg.exists(str.c_str()))
    {
        ddb_cfg.remove(str.c_str());
        cout<<"delete_tablemetadata: "<<str<<endl;
        write_to_config_file(METADATA_CONFIG_FILE);
        return;
    }
    cout<<"delete_tablemetadata: "<<str<<" table not exist, no need to delete!"<<endl;
}

//2017-12-30 addby yfchai
void MetadataManager::add_tablename_intolist(string str)
{


    Setting& root = cfg.getRoot();
    Setting& db_cfg = root[CONFIG_NAME_DATABASE];
    Setting& tb_namelist = db_cfg[CONFIG_NAME_TABLE_LIST];
    bool b = true;
    int len = tb_namelist.getLength();
    for(int i=0;i<len;i++)
    {
        string s = tb_namelist[i];
        if(str == s) b = false;
    }

    if(b)
    {

        tb_namelist.add(Setting::TypeString) = str;
        write_to_config_file(METADATA_CONFIG_FILE);
    }

}
//2017-12-30 addby yfchai
void MetadataManager::delete_tablename_formlist(string str)
{

    Setting& root = cfg.getRoot();
    Setting& db_cfg = root[CONFIG_NAME_DATABASE];
    Setting& tbname_list = db_cfg[CONFIG_NAME_TABLE_LIST];

    bool b = false;
    int len = tbname_list.getLength();
    int pos;
    for(int i=0;i<len;i++)
    {
        string s = tbname_list[i];
        if(str == s)
        {
            b = true;
            pos = i;
            break;
        }
    }

    if(b)
    {

        tbname_list.remove((unsigned)pos);
        write_to_config_file(METADATA_CONFIG_FILE);
    }

}

void MetadataManager::load_tablemetadata_fromcfg()
{
    Setting& root = cfg.getRoot();
    Setting& db_cfg = root[CONFIG_NAME_DATABASE];
    Setting& tb_namelist = db_cfg[CONFIG_NAME_TABLE_LIST];
    int len = tb_namelist.getLength();
    if(len == 0) return;//len==0 means no table in GDD

    for(int i=0;i<len;i++)
    {
        TableMedata tmp;
        string tbname = tb_namelist[i];
        Setting& table_cfg = db_cfg[tbname];
        int attr_num;
        table_cfg.lookupValue(CONFIG_NAME_TALBE_ATTR_NUM,attr_num);

        tmp.table_name = tbname;
        tmp.table_attr_num = attr_num;

           for(int j=0;j<attr_num;j++)
           {
               Setting& attr_cfg = table_cfg[CONFIG_NAME_TABLE_ATTR_SLICE+to_string(j)];

               attr_cfg.lookupValue(CONFIG_NAME_TABLE_ATTR_NAME, tmp.Attr[j].attr_name);
               attr_cfg.lookupValue(CONFIG_NAME_TABLE_ATTR_DATATYPE,tmp.Attr[j].attr_datatype);
               attr_cfg.lookupValue(CONFIG_NAME_TABLE_ATTR_LENGTH,tmp.Attr[j].attr_length);
               attr_cfg.lookupValue(CONFIG_NAME_TABLE_ATTR_RULESTYPE,tmp.Attr[j].attr_rulestype);
            }

           tableMetadataInfo.set_table_metadata(tmp);
    }




}

void MetadataManager::add_fragment_name_intolist(string str)
{
    Setting& root = cfg.getRoot();
    Setting& frg_cfg = root[CONFIG_NAME_FRAGMENT];
    Setting& frg_namelist = frg_cfg[CONFIG_NAME_FRAGMENT_LIST];
    bool b = true;
    int len = frg_namelist.getLength();
    for(int i=0;i<len;i++)
    {
        string s = frg_namelist[i];
        if(str == s) b = false;
    }

    if(b)
    {

        frg_namelist.add(Setting::TypeString) = str;
        write_to_config_file(METADATA_CONFIG_FILE);
    }

}

void MetadataManager::delete_fragment_name_fromlist(string str)
{
    Setting& root = cfg.getRoot();
    Setting& frg_cfg = root[CONFIG_NAME_FRAGMENT];
    Setting& frg_list = frg_cfg[CONFIG_NAME_FRAGMENT_LIST];

    bool b = false;
    int len = frg_list.getLength();
    int pos;
    for(int i=0;i<len;i++)
    {
        string s = frg_list[i];
        if(str == s)
        {
            b = true;
            pos = i;
            break;
        }
    }

    if(b)
    {

        frg_list.remove((unsigned)pos);
        write_to_config_file(METADATA_CONFIG_FILE);
    }


}

void MetadataManager::load_fragmentmetadata_fromcfg()
{
    Setting& root = cfg.getRoot();
    Setting& frg_cfg = root[CONFIG_NAME_FRAGMENT];
    Setting& frg_list = frg_cfg[CONFIG_NAME_FRAGMENT_LIST];
    int len = frg_list.getLength();
    if(len == 0) return;//len==0 means no fragment in GDD

    for(int i=0;i<len;i++)
    {
        Fragment tmp;
        string frg_name = frg_list[i];
        Setting& frg_info = frg_cfg[frg_name];
        tmp.frag_talbe_name = frg_name;
        for(int j = 0; j<MAX_FRAGMENT_NUM;j++)
        {
            Setting& frgi_cfg = frg_info[CONFIG_NAME_FRAGMENT_SLICE+to_string(j)];
            frgi_cfg.lookupValue(CONFIG_NAME_FRAGMENT_ISVALID,tmp.condtion_slice[j].isValid);

            {//for con_H1
                Setting& frg_conH1 = frgi_cfg[CONFIG_NAME_FRAGMENT_CON_H1];
                frg_conH1.lookupValue(CONFIG_NAME_FRAGMENT_ISVALID, tmp.condtion_slice[j].con_H1.isValid);
                frg_conH1.lookupValue(CONFIG_NAME_FRAGMENT_ATTR_NAME, tmp.condtion_slice[j].con_H1.attr_name);
                frg_conH1.lookupValue(CONFIG_NAME_FRAGMENT_ATTR_CONDITION, tmp.condtion_slice[j].con_H1.attr_condition);
                frg_conH1.lookupValue(CONFIG_NAME_FRAGMENT_ATTR_VALUE, tmp.condtion_slice[j].con_H1.attr_value);

            }

            {//for con_H2
                Setting& frg_conH2 = frgi_cfg[CONFIG_NAME_FRAGMENT_CON_H2];
                frg_conH2.lookupValue(CONFIG_NAME_FRAGMENT_ISVALID, tmp.condtion_slice[j].con_H2.isValid);
                frg_conH2.lookupValue(CONFIG_NAME_FRAGMENT_ATTR_NAME, tmp.condtion_slice[j].con_H2.attr_name);
                frg_conH2.lookupValue(CONFIG_NAME_FRAGMENT_ATTR_CONDITION, tmp.condtion_slice[j].con_H2.attr_condition);
                frg_conH2.lookupValue(CONFIG_NAME_FRAGMENT_ATTR_VALUE, tmp.condtion_slice[j].con_H2.attr_value);

            }

            {//for con_V1
                 Setting& frg_conV1 = frgi_cfg[CONFIG_NAME_FRAGMENT_CON_V1];
                 frg_conV1.lookupValue(CONFIG_NAME_FRAGMENT_ISVALID, tmp.condtion_slice[j].con_V1.isValid);
                 frg_conV1.lookupValue(CONFIG_NAME_FRAGMENT_V_ATTR_NUM, tmp.condtion_slice[j].con_V1.attr_num);
                 frg_conV1.lookupValue(CONFIG_NAME_FRAGMENT_ATTR_PRIKEY, tmp.condtion_slice[j].con_V1.attr_prikey);

                 Setting& list_cfg = frg_conV1[CONFIG_NAME_FRAGMENT_ATTR_FRAG_STRLIST];
                 int num = list_cfg.getLength();
                 for(int k=0;k<num;k++)
                 {
                     string s = list_cfg[k];
                     tmp.condtion_slice[j].con_V1.attr_frag_strlist[k] = s;
                 }


            }
        }
        fragInfo.set_fragment_info(tmp);

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

MetadataManager *MetadataManager::getInstance()
{
    if(pmtr == NULL )
        pmtr = new MetadataManager();

    return pmtr;
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
      root.add(CONFIG_NAME_SITEINFO, Setting::TypeGroup);
      cout<<"initialize_siteinfo no site_info"<<endl;
    }

    write_to_config_file(METADATA_CONFIG_FILE);
    cout << "initialize_siteinfo is ok! "  << endl;

}

void MetadataManager::initialize_database()
{
    cfg.setOptions(Config::OptionFsync
                   | Config::OptionSemicolonSeparators
                   | Config::OptionColonAssignmentForGroups
                   | Config::OptionOpenBraceOnSeparateLine);

    Setting &root = cfg.getRoot();
    if(! root.exists(CONFIG_NAME_DATABASE))
    {
      root.add(CONFIG_NAME_DATABASE, Setting::TypeGroup);
      Setting& db_cfg = root[CONFIG_NAME_DATABASE];

      db_cfg.add(CONFIG_NAME_TABLE_LIST, Setting::TypeArray);
      //Setting& array_cfg = db_cfg[CONFIG_NAME_TABLE_LIST];

//      array_cfg.add(Setting::TypeString) = "EMP";
//      array_cfg.add(Setting::TypeString) = "ASG";
//      array_cfg.add(Setting::TypeString) = "SAL";
//      if(!array_cfg.exists("ASG"))
//          cout<<"ASG is in table name list"<<endl;
//      array_cfg.remove((unsigned)0);
//      string ss = array_cfg[0];
//      cout<<"ss is: "<<ss<<endl;

      write_to_config_file(METADATA_CONFIG_FILE);
      cout<<"initialize_database:"<<CONFIG_NAME_DATABASE<<endl;
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
      Setting& frag_list = root[CONFIG_NAME_FRAGMENT];
      frag_list.add(CONFIG_NAME_FRAGMENT_LIST,Setting::TypeArray);
      cout<<"initialize_fragment no fragment"<<endl;
      write_to_config_file(METADATA_CONFIG_FILE);
    }

    cout << "initialize_fragment  is ok! "  << endl;

}

void MetadataManager::set_fargment_info(Fragment &frg)
{
    string str = frg.frag_talbe_name;
    fragInfo.set_fragment_info(frg);

    add_fragment_name_intolist(str);

    Setting &root = cfg.getRoot();
    Setting& frg_tb_cfg = root[CONFIG_NAME_FRAGMENT];
    if(frg_tb_cfg.exists(str.c_str()))
        frg_tb_cfg.remove(str.c_str());//delete it then update it

    frg_tb_cfg.add(str.c_str(),Setting::TypeGroup);
    Setting& frg_slc_cfg = frg_tb_cfg[str.c_str()];

    //int pos = fragInfo.get_fragment_pos(str);
    //Fragment tmp = fragInfo.get_frag_bypos(pos);
    Fragment tmp = fragInfo.get_frag_bystr(str);

    for(int i =0;i<MAX_FRAGMENT_NUM;i++)
    {
        //if(!tmp.condtion_slice[i].isValid )
        {
            //continue;
        }

        frg_slc_cfg.add(CONFIG_NAME_FRAGMENT_SLICE+to_string(i),Setting::TypeGroup);
        Setting& frg_i_cfg = frg_slc_cfg[CONFIG_NAME_FRAGMENT_SLICE+to_string(i)];
        frg_i_cfg.add(CONFIG_NAME_FRAGMENT_ISVALID,Setting::TypeBoolean) = frg.condtion_slice[i].isValid;


          //if(frg.condtion_slice[i].con_H1.isValid)
          {
              frg_i_cfg.add(CONFIG_NAME_FRAGMENT_CON_H1,Setting::TypeGroup);
              Setting& frg_conH1_cfg = frg_i_cfg[CONFIG_NAME_FRAGMENT_CON_H1];
              frg_conH1_cfg.add(CONFIG_NAME_FRAGMENT_ISVALID,Setting::TypeBoolean) \
                      = frg.condtion_slice[i].con_H1.isValid;

              frg_conH1_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_NAME,Setting::TypeString) \
                      = frg.condtion_slice[i].con_H1.attr_name;

              frg_conH1_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_CONDITION,Setting::TypeString)\
                      =frg.condtion_slice[i].con_H1.attr_condition;

              frg_conH1_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_VALUE,Setting::TypeString)\
                      =frg.condtion_slice[i].con_H1.attr_value;
              //write_to_config_file(METADATA_CONFIG_FILE);

          }

          //if(frg.condtion_slice[i].con_H2.isValid)
          {
              frg_i_cfg.add(CONFIG_NAME_FRAGMENT_CON_H2,Setting::TypeGroup);
              Setting& frg_conH2_cfg = frg_i_cfg[CONFIG_NAME_FRAGMENT_CON_H2];
              frg_conH2_cfg.add(CONFIG_NAME_FRAGMENT_ISVALID,Setting::TypeBoolean) \
                      = frg.condtion_slice[i].con_H2.isValid;

              frg_conH2_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_NAME,Setting::TypeString) \
                      = frg.condtion_slice[i].con_H2.attr_name;

              frg_conH2_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_CONDITION,Setting::TypeString)\
                      =frg.condtion_slice[i].con_H2.attr_condition;

              frg_conH2_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_VALUE,Setting::TypeString)\
                      =frg.condtion_slice[i].con_H2.attr_value;

              //write_to_config_file(METADATA_CONFIG_FILE);

          }
          //for vertical fragment slice metadata store
          {
            frg_i_cfg.add(CONFIG_NAME_FRAGMENT_CON_V1,Setting::TypeGroup);
            Setting& frg_conV1_cfg = frg_i_cfg[CONFIG_NAME_FRAGMENT_CON_V1];

            frg_conV1_cfg.add(CONFIG_NAME_FRAGMENT_ISVALID,Setting::TypeBoolean) \
                    = frg.condtion_slice[i].con_V1.isValid;

            frg_conV1_cfg.add(CONFIG_NAME_FRAGMENT_V_ATTR_NUM,Setting::TypeInt) \
                    = frg.condtion_slice[i].con_V1.attr_num;

            frg_conV1_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_PRIKEY,Setting::TypeString) \
                    = frg.condtion_slice[i].con_V1.attr_prikey;
            frg_conV1_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_FRAG_STRLIST,Setting::TypeArray);

            Setting& list_cfg = frg_conV1_cfg[CONFIG_NAME_FRAGMENT_ATTR_FRAG_STRLIST];
            for(int j=0;j<frg.condtion_slice[i].con_V1.attr_num;j++)
                list_cfg.add(Setting::TypeString) = frg.condtion_slice[i].con_V1.attr_frag_strlist[j];
          }

//        {
//          frg_i_cfg.add(CONFIG_NAME_FRAGMENT_CON_V2,Setting::TypeGroup);
//          Setting& frg_conV2_cfg = frg_i_cfg[CONFIG_NAME_FRAGMENT_CON_V2];

//          frg_conV2_cfg.add(CONFIG_NAME_FRAGMENT_ISVALID,Setting::TypeBoolean) \
//                  = frg.condtion_slice[i].con_V2.isValid;

//          frg_conV2_cfg.add(CONFIG_NAME_FRAGMENT_V_ATTR_NUM,Setting::TypeInt) \
//                  = frg.condtion_slice[i].con_V2.attr_num;

//          frg_conV2_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_PRIKEY,Setting::TypeString) \
//                  = frg.condtion_slice[i].con_V2.attr_prikey;
//          frg_conV2_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_FRAG_STRLIST,Setting::TypeArray);
//          for(int j=0;j<frg.condtion_slice[i].con_V2.attr_num;j++)
//              frg_conV2_cfg.add(Setting::TypeString) = frg.condtion_slice[i].con_V2.attr_frag_strlist[j];
//        }
      }


             write_to_config_file(METADATA_CONFIG_FILE);





}
//2017-12-30 addby yfchai
void MetadataManager::delete_fragmemt_info(string str)
{
        Setting& root = cfg.getRoot();
        Setting& ddb_cfg = root[CONFIG_NAME_FRAGMENT];
        if(ddb_cfg.exists(str.c_str()))
        {
            ddb_cfg.remove(str.c_str());
            cout<<"delete_fragmemt_info: "<<str<<endl;
            write_to_config_file(METADATA_CONFIG_FILE);
            return;
        }
        cout<<"delete_fragmemt_info: "<<str<<" table fragment info not exist, no need to delete!"<<endl;
}



void MetadataManager::set_siteinfo(SiteInfo& sti)
{
    int i = sti.get_site_ID();
    this->siteinfo[i] = sti;

    Setting &root = cfg.getRoot();
//    if(!root.exists(CONFIG_NAME_SITEINFO))
//        root.add(CONFIG_NAME_SITEINFO,Setting::TypeGroup);
   string str = sti.get_site_name();
    Setting& sf = root[CONFIG_NAME_SITEINFO];
    if(sf.exists(str.c_str()))//if exist site_i info then delete it and rebuild it to update siteinfo
        sf.remove(str.c_str());

    sf.add(str.c_str(),Setting::TypeGroup);
    Setting& info = sf[str.c_str()];
    info.add(CONFIG_NAME_SITEINFO_SITE_ID, Setting::TypeInt) = sti.get_site_ID();
    info.add(CONFIG_NAME_SITEINFO_SITE_IP,Setting::TypeString) = sti.get_site_ip().c_str();
    info.add(CONFIG_NAME_SITEINFO_SITE_NAME,Setting::TypeString) = sti.get_site_name().c_str();
    info.add(CONFIG_NAME_SITEINFO_STIE_PORT,Setting::TypeInt) = sti.get_site_port();
    info.add(CONFIG_NAME_SITEINFO_SITE_IS_CONTROL_SITE,Setting::TypeBoolean) = sti.get_isControlSite();

    write_to_config_file(METADATA_CONFIG_FILE);
    cout<<"set_siteinfo() ok"<<endl;


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
