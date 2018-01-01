
#include <QApplication>

#include "global.h"
#include "MetadataManager/metadatamanager.h"
#include "MetadataManager/ddbmainwin.h"

//below for testing
#include "MetadataManager/siteinfo.h"
#include "MetadataManager/fragmentinfo.h"
#include "MetadataManager/tableMetadataInfo.h"


#include <stdlib.h>
using namespace std;
using namespace libconfig;

int test_code();
int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    DDBMainWin dm;
    dm.mtr = MetadataManager::getInstance();
//emulated input site info
    SiteInfo sf;
    for(int i=0;i<4;i++)
    {
    sf.set_site_ID(i);
    sf.set_site_name("site"+to_string(i));
    sf.set_site_ip("192.168.1."+to_string(i+1));
    sf.set_site_port(3367+i);
    sf.set_control_site(true);
    //dm.mtr.set_siteinfo(sf);
    }
//emulated input fragment info
    Fragment frg;
     frg.frag_talbe_name = "EMP";
     for(int i=0;i<4;i++)
     {
     frg.condtion_slice[i].isValid =true;
     frg.condtion_slice[i].con_H1.isValid =true;
     frg.condtion_slice[i].con_H1.attr_name ="attr"+to_string(i);
     frg.condtion_slice[i].con_H2.isValid =true;
     frg.condtion_slice[i].con_H2.attr_name ="attr"+to_string(i);

     frg.condtion_slice[i].con_V1.isValid =true;

     frg.condtion_slice[i].con_V1.attr_num =3;
     frg.condtion_slice[i].con_V1.attr_prikey = to_string(i);
     for(int j=0;j<3;j++)
        frg.condtion_slice[i].con_V1.attr_frag_strlist[j] = "hello"+to_string(j);
     }
   //dm.mtr->set_fargment_info(frg);
   //dm.mtr.delete_fragment_name_fromlist("EMP");

//emulated input table metadata
     TableMedata tmd;
     tmd.table_name = "ASG";
     tmd.table_attr_num = 5;
     for(int i =0; i<tmd.table_attr_num;i++)
     {
         tmd.Attr[i].attr_name = "attr"+to_string(i);
         tmd.Attr[i].attr_length = i;
         //tmd.Attr[i].attr_datatype = ( enum TYPE)1;
         //tmd.Attr[i].attr_rulestype = (RulesType)0;
     }

    //dm.mtr.set_tablemetadata(tmd);
    //dm.mtr.delete_tablename_formlist("ASG");
    //dm.mtr.load_tablemetadata_fromcfg();

    dm.mtr->setMetadataVer("0.0.1");
    //dm.mtr.delete_tablemetadata("ASG");
    //dm.mtr.delete_fragmemt_info("EMP");

    //dm.show();
    cout<<endl<<rand()%100<<"the random num is"<<endl;
    return app.exec();


     //MetadataManager mtr;
     //cout<<sizeof(int)<<" int,"<<sizeof(float)<<" float,"<<sizeof(DATE)<<" is DATE";
     cout << "Hello World!" << endl;
     //mtr.setMetadataVer("0.0.2");
     //mtr.initialize_siteinfo();
     //mtr.initialize_database("my_db");
     //getchar();
     //test_code();
    return 0;
}

int test_code()
{

    libconfig::Config cfg;
     //cfg.readFile("my.conf");

     try
     {
       //cfg.readFile("my.conf");
       cfg.readFile("metadata.cfg");
     }
     catch(const FileIOException &fioex)
     {
       std::cerr << "I/O error while reading file." << std::endl;
       return(EXIT_FAILURE);
     }
     catch(const ParseException &pex)
     {
       std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                 << " - " << pex.getError() << std::endl;
       return(EXIT_FAILURE);
     }

     string str = cfg.lookup("version");
     cout << str << endl;

     //const Setting& set = cfg.lookup("table");
     const Setting& set = cfg.lookup("database");
     string str1 = "";
     set.lookupValue("database",str1);
     cout << str1<< endl;

     string str2 = "";
     const Setting& set2 = cfg.lookup("database.supplier");
     set2[1].lookupValue("attr_name",str2);
     cout << str2<< endl;
     set2[1].lookupValue("attr_datatype",str2);
     cout << str2<< endl;

     return 0;
}
