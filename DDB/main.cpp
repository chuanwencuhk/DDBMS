
#include <QApplication>

#include "global.h"
#include "MetadataManager/metadatamanager.h"
#include "MetadataManager/ddbmainwin.h"

//below for testing
#include "MetadataManager/siteinfo.h"
#include "MetadataManager/fragmentinfo.h"
#include <stdlib.h>
using namespace std;
using namespace libconfig;

int test_code();
int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    DDBMainWin dm;
    //dm.mtr.initialize_fragment();
    SiteInfo sf;
    sf.set_site_ID(1);
    sf.set_site_name("site1");
    sf.set_site_ip("192.168.1.3");
    sf.set_site_port(3367);
    sf.set_control_site(true);

     Fragment frg;
     frg.frag_talbe_name = "EMP";
     for(int i=0;i<4;i++)
     {
     frg.condtion_slice[i].isValid =true;
     frg.condtion_slice[i].con_A.isValid =true;
     frg.condtion_slice[i].con_B.isValid =true;
     }
    //dm.mtr.initialize_siteinfo();
    dm.mtr.initialize_fragment();
    dm.mtr.set_fargment_info(frg);
    //dm.mtr.set_siteinfo(sf);

    //dm.show();
    cout<<endl<<rand()%100<<"the random num is"<<endl;
    return app.exec();


     //MetadataManager mtr;
     cout<<sizeof(int)<<" int,"<<sizeof(float)<<" float,"<<sizeof(DATE)<<" is DATE";
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
