  #include "../include/metadatamanager.h"

#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <unistd.h>//for access() fuction
using namespace std;
using namespace libconfig;

MetadataManager::MetadataManager()
{
    //string str = METADATA_CONFIG_FILE;
    initialize_from_config_file(METADATA_CONFIG_FILE);//initialize the MetadataManager
    initialize_database();//initialize DDB segment
    initialize_siteinfo();//initialzie site_info segment
    initialize_fragment();//initialize fragment segment


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

    Setting& root = cfg.getRoot();
    Setting& ddb_cfg = root[CONFIG_NAME_DATABASE];
    if(ddb_cfg.exists(str.c_str()))
        ddb_cfg.remove(str.c_str());

    ddb_cfg.add(str.c_str(),Setting::TypeGroup);
    Setting& tb_cfg = ddb_cfg[str.c_str()];

    //int pos = tableMetadataInfo.get_tablemetadata_pos_bystr(str);
    //TableMedata tmp =tableMetadataInfo.get_tablemetadata_bypos(pos);
    TableMedata tmp =tableMetadataInfo.get_tablemetadata_bystr(str);

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
      cout<<"initialize_fragment no fragment"<<endl;
      write_to_config_file(METADATA_CONFIG_FILE);
    }

    cout << "initialize_fragment  is ok! "  << endl;

}

void MetadataManager::set_fargment_info(Fragment &frg)
{
    string str = frg.frag_talbe_name;
    fragInfo.set_fragment_info(frg);
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
        if(!tmp.condtion_slice[i].isValid )
        {
            continue;
        }

        frg_slc_cfg.add(CONFIG_NAME_FRAGMENT_SLICE+to_string(i),Setting::TypeGroup);
        Setting& frg_i_cfg = frg_slc_cfg[CONFIG_NAME_FRAGMENT_SLICE+to_string(i)];
        frg_i_cfg.add(CONFIG_NAME_FRAGMENT_ISVALID,Setting::TypeBoolean) = frg.condtion_slice[i].isValid;


          if(frg.condtion_slice[i].con_A.isValid)
          {
              frg_i_cfg.add(CONFIG_NAME_FRAGMENT_CON_A,Setting::TypeGroup);
              Setting& frg_conA_cfg = frg_i_cfg[CONFIG_NAME_FRAGMENT_CON_A];
              frg_conA_cfg.add(CONFIG_NAME_FRAGMENT_ISVALID,Setting::TypeBoolean) \
                      = frg.condtion_slice[i].con_A.isValid;

              frg_conA_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_NAME,Setting::TypeString) \
                      = frg.condtion_slice[i].con_A.attr_name;

              frg_conA_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_CONDITION,Setting::TypeString)\
                      =frg.condtion_slice[i].con_A.attr_condition;

              frg_conA_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_VALUE,Setting::TypeString)\
                      =frg.condtion_slice[i].con_A.attr_value;
              //write_to_config_file(METADATA_CONFIG_FILE);

          }

          if(frg.condtion_slice[i].con_B.isValid)
          {
              frg_i_cfg.add(CONFIG_NAME_FRAGMENT_CON_B,Setting::TypeGroup);
              Setting& frg_conB_cfg = frg_i_cfg[CONFIG_NAME_FRAGMENT_CON_B];
              frg_conB_cfg.add(CONFIG_NAME_FRAGMENT_ISVALID,Setting::TypeBoolean) \
                      = frg.condtion_slice[i].con_B.isValid;

              frg_conB_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_NAME,Setting::TypeString) \
                      = frg.condtion_slice[i].con_B.attr_name;

              frg_conB_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_CONDITION,Setting::TypeString)\
                      =frg.condtion_slice[i].con_B.attr_condition;

              frg_conB_cfg.add(CONFIG_NAME_FRAGMENT_ATTR_VALUE,Setting::TypeString)\
                      =frg.condtion_slice[i].con_B.attr_value;

              //write_to_config_file(METADATA_CONFIG_FILE);

          }
      }
             write_to_config_file(METADATA_CONFIG_FILE);





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

bool MetadataManager::delete_tablemetadata(std::string str){
     Setting& root = cfg.getRoot();
     Setting& ddb_cfg = root[CONFIG_NAME_DATABASE];
     if(ddb_cfg.exists(str.c_str())){
      ddb_cfg.remove(str.c_str());
      cout<<str<<" removed."<<endl;
     } 
    return true;
}
bool MetadataManager::delete_fragment_info(std::string str){
    Setting &root = cfg.getRoot();
    Setting& frg_tb_cfg = root[CONFIG_NAME_FRAGMENT];
    if(frg_tb_cfg.exists(str.c_str()))
        frg_tb_cfg.remove(str.c_str());//delete it then update it
    return true;
}