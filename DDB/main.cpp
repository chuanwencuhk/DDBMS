
#include <QApplication>
#include <string>
#include <iostream>
#include <fstream>

#include "global.h"
#include "MetadataManager/metadatamanager.h"
#include "MetadataManager/ddbmainwin.h"

//below for testing
#include "MetadataManager/siteinfo.h"
#include "MetadataManager/fragmentinfo.h"
#include "MetadataManager/tableMetadataInfo.h"
#include "QueryTree/query_tree.h"
#include "Dispather/dispather.h"

#define TEST_SWITCH 1
#include <stdlib.h>
using namespace std;
using namespace libconfig;
void queryTree();
extern struct schema sch;
int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
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

if(TEST_SWITCH ==1)
{
//emulated input table metadata info enum TYPE{I=1,C,V,F,D};
         TableMedata SAL;
         SAL.table_name = "sal";
         SAL.table_attr_num = 2;

         SAL.Attr[0].attr_name = "title";
         SAL.Attr[0].attr_length = 20;
         SAL.Attr[0].attr_datatype = 2;

         SAL.Attr[1].attr_name = "sal";
         SAL.Attr[1].attr_length = 4;
         SAL.Attr[1].attr_datatype = 4;

         TableMedata EMP;
         EMP.table_name = "emp";
         EMP.table_attr_num = 3;

         EMP.Attr[0].attr_name = "eno";
         EMP.Attr[0].attr_length = 20;
         EMP.Attr[0].attr_datatype = 2;

         EMP.Attr[1].attr_name = "ename";
         EMP.Attr[1].attr_length = 20;
         EMP.Attr[1].attr_datatype = 2;

         EMP.Attr[2].attr_name = "title";
         EMP.Attr[2].attr_length = 20;
         EMP.Attr[2].attr_datatype = 2;

         TableMedata JOB;
         JOB.table_name = "job";
         JOB.table_attr_num = 4;

         JOB.Attr[0].attr_name = "jno";
         JOB.Attr[0].attr_length = 20;
         JOB.Attr[0].attr_datatype = 2;

         JOB.Attr[1].attr_name = "jname";
         JOB.Attr[1].attr_length = 20;
         JOB.Attr[1].attr_datatype = 2;

         JOB.Attr[2].attr_name = "budget";
         JOB.Attr[2].attr_length = 4;
         JOB.Attr[2].attr_datatype = 4;

         JOB.Attr[3].attr_name = "loc";
         JOB.Attr[3].attr_length = 20;
         JOB.Attr[3].attr_datatype = 2;

         TableMedata ASG;
         ASG.table_name = "asg";
         ASG.table_attr_num = 4;

         ASG.Attr[0].attr_name = "eno";
         ASG.Attr[0].attr_length = 20;
         ASG.Attr[0].attr_datatype = 2;

         ASG.Attr[1].attr_name = "jno";
         ASG.Attr[1].attr_length = 20;
         ASG.Attr[1].attr_datatype = 2;

         ASG.Attr[2].attr_name = "resp";
         ASG.Attr[2].attr_length = 20;
         ASG.Attr[2].attr_datatype = 2;

         ASG.Attr[3].attr_name = "dur";
         ASG.Attr[3].attr_length = 4;
         ASG.Attr[3].attr_datatype = 1;
//set emulation table metadata
         dm.mtr->set_tablemetadata(SAL);
         dm.mtr->set_tablemetadata(EMP);
         dm.mtr->set_tablemetadata(JOB);
         dm.mtr->set_tablemetadata(ASG);
//emulated input table metadata info enum TYPE{I=1,C,V,F,D};

//emulated input fragment metadata
//////////////////////////////////////////////////////////////EMP///////////////////////
         Fragment FRAG_EMP;
         FRAG_EMP.frag_talbe_name = "emp";
//db1
         FRAG_EMP.condtion_slice[0].isValid =true;
         FRAG_EMP.condtion_slice[0].con_H1.isValid =true;
         FRAG_EMP.condtion_slice[0].con_H1.attr_name ="eno";
         FRAG_EMP.condtion_slice[0].con_H1.attr_condition = "<";
         FRAG_EMP.condtion_slice[0].con_H1.attr_value = "'E1000'";

         FRAG_EMP.condtion_slice[0].con_H2.isValid =true;
         FRAG_EMP.condtion_slice[0].con_H2.attr_name ="title";
         FRAG_EMP.condtion_slice[0].con_H2.attr_condition = "<";
         FRAG_EMP.condtion_slice[0].con_H2.attr_value = "'N'";

         FRAG_EMP.condtion_slice[0].con_V1.isValid =false;
//db2
         FRAG_EMP.condtion_slice[1].isValid =true;
         FRAG_EMP.condtion_slice[1].con_H1.isValid =true;
         FRAG_EMP.condtion_slice[1].con_H1.attr_name ="eno";
         FRAG_EMP.condtion_slice[1].con_H1.attr_condition = "<";
         FRAG_EMP.condtion_slice[1].con_H1.attr_value = "'E1000'";

         FRAG_EMP.condtion_slice[1].con_H2.isValid =true;
         FRAG_EMP.condtion_slice[1].con_H2.attr_name ="title";
         FRAG_EMP.condtion_slice[1].con_H2.attr_condition = ">=";
         FRAG_EMP.condtion_slice[1].con_H2.attr_value = "'N'";

         FRAG_EMP.condtion_slice[1].con_V1.isValid =false;
//db3
         FRAG_EMP.condtion_slice[2].isValid =true;
         FRAG_EMP.condtion_slice[2].con_H1.isValid =true;
         FRAG_EMP.condtion_slice[2].con_H1.attr_name ="eno";
         FRAG_EMP.condtion_slice[2].con_H1.attr_condition = ">=";
         FRAG_EMP.condtion_slice[2].con_H1.attr_value = "'E1000'";

         FRAG_EMP.condtion_slice[2].con_H2.isValid =true;
         FRAG_EMP.condtion_slice[2].con_H2.attr_name ="title";
         FRAG_EMP.condtion_slice[2].con_H2.attr_condition = "<";
         FRAG_EMP.condtion_slice[2].con_H2.attr_value = "'N'";

         FRAG_EMP.condtion_slice[2].con_V1.isValid =false;
//db4
         FRAG_EMP.condtion_slice[3].isValid =true;
         FRAG_EMP.condtion_slice[3].con_H1.isValid =true;
         FRAG_EMP.condtion_slice[3].con_H1.attr_name ="eno";
         FRAG_EMP.condtion_slice[3].con_H1.attr_condition = ">=";
         FRAG_EMP.condtion_slice[3].con_H1.attr_value = "'E1000'";

         FRAG_EMP.condtion_slice[3].con_H2.isValid =true;
         FRAG_EMP.condtion_slice[3].con_H2.attr_name ="title";
         FRAG_EMP.condtion_slice[3].con_H2.attr_condition = ">=";
         FRAG_EMP.condtion_slice[3].con_H2.attr_value = "'N'";

         FRAG_EMP.condtion_slice[3].con_V1.isValid =false;
//////////////////////////////////////////////////////////////ASG///////////////////////
         Fragment FRAG_ASG;
         FRAG_ASG.frag_talbe_name = "asg";
//db1
         FRAG_ASG.condtion_slice[0].isValid =true;
         FRAG_ASG.condtion_slice[0].con_H1.isValid =true;
         FRAG_ASG.condtion_slice[0].con_H1.attr_name ="eno";
         FRAG_ASG.condtion_slice[0].con_H1.attr_condition = "<";
         FRAG_ASG.condtion_slice[0].con_H1.attr_value = "'E1000'";

         FRAG_ASG.condtion_slice[0].con_H2.isValid =true;
         FRAG_ASG.condtion_slice[0].con_H2.attr_name ="jno";
         FRAG_ASG.condtion_slice[0].con_H2.attr_condition = "<";
         FRAG_ASG.condtion_slice[0].con_H2.attr_value = "'J0500'";

         FRAG_ASG.condtion_slice[0].con_V1.isValid =false;
//db2
         FRAG_ASG.condtion_slice[1].isValid =true;
         FRAG_ASG.condtion_slice[1].con_H1.isValid =true;
         FRAG_ASG.condtion_slice[1].con_H1.attr_name ="eno";
         FRAG_ASG.condtion_slice[1].con_H1.attr_condition = "<";
         FRAG_ASG.condtion_slice[1].con_H1.attr_value = "'E1000'";

         FRAG_ASG.condtion_slice[1].con_H2.isValid =true;
         FRAG_ASG.condtion_slice[1].con_H2.attr_name ="jno";
         FRAG_ASG.condtion_slice[1].con_H2.attr_condition = ">=";
         FRAG_ASG.condtion_slice[1].con_H2.attr_value = "'J0500'";

         FRAG_ASG.condtion_slice[1].con_V1.isValid =false;
//db3
         FRAG_ASG.condtion_slice[2].isValid =true;
         FRAG_ASG.condtion_slice[2].con_H1.isValid =true;
         FRAG_ASG.condtion_slice[2].con_H1.attr_name ="eno";
         FRAG_ASG.condtion_slice[2].con_H1.attr_condition = ">=";
         FRAG_ASG.condtion_slice[2].con_H1.attr_value = "'E1000'";

         FRAG_ASG.condtion_slice[2].con_H2.isValid =true;
         FRAG_ASG.condtion_slice[2].con_H2.attr_name ="jno";
         FRAG_ASG.condtion_slice[2].con_H2.attr_condition = "<";
         FRAG_ASG.condtion_slice[2].con_H2.attr_value = "'J0500'";

         FRAG_ASG.condtion_slice[2].con_V1.isValid =false;
//db4
         FRAG_ASG.condtion_slice[3].isValid =true;
         FRAG_ASG.condtion_slice[3].con_H1.isValid =true;
         FRAG_ASG.condtion_slice[3].con_H1.attr_name ="eno";
         FRAG_ASG.condtion_slice[3].con_H1.attr_condition = ">=";
         FRAG_ASG.condtion_slice[3].con_H1.attr_value = "'E1000'";

         FRAG_ASG.condtion_slice[3].con_H2.isValid =true;
         FRAG_ASG.condtion_slice[3].con_H2.attr_name ="jno";
         FRAG_ASG.condtion_slice[3].con_H2.attr_condition = ">=";
         FRAG_ASG.condtion_slice[3].con_H2.attr_value = "'J0500'";

         FRAG_ASG.condtion_slice[3].con_V1.isValid =false;

//////////////////////////////////////////////////////////////JOB///////////////////////
                  Fragment FRAG_JOB;
                  FRAG_JOB.frag_talbe_name = "job";
//db1
                  FRAG_JOB.condtion_slice[0].isValid =true;
                  FRAG_JOB.condtion_slice[0].con_H1.isValid =true;
                  FRAG_JOB.condtion_slice[0].con_H1.attr_name ="jno";
                  FRAG_JOB.condtion_slice[0].con_H1.attr_condition = "<";
                  FRAG_JOB.condtion_slice[0].con_H1.attr_value = "'J0500'";

                  FRAG_JOB.condtion_slice[0].con_H2.isValid =false;

                  FRAG_JOB.condtion_slice[0].con_V1.isValid =true;
                  FRAG_JOB.condtion_slice[0].con_V1.attr_num =3;
                  FRAG_JOB.condtion_slice[0].con_V1.attr_frag_strlist[0] = "jno";
                  FRAG_JOB.condtion_slice[0].con_V1.attr_frag_strlist[1] = "jname";
                  FRAG_JOB.condtion_slice[0].con_V1.attr_frag_strlist[2] = "budget";


//db2
                  FRAG_JOB.condtion_slice[1].isValid =true;
                  FRAG_JOB.condtion_slice[1].con_H1.isValid =true;
                  FRAG_JOB.condtion_slice[1].con_H1.attr_name ="jno";
                  FRAG_JOB.condtion_slice[1].con_H1.attr_condition = "<";
                  FRAG_JOB.condtion_slice[1].con_H1.attr_value = "'J0500'";

                  FRAG_JOB.condtion_slice[1].con_H2.isValid =false;

                  FRAG_JOB.condtion_slice[1].con_V1.isValid =true;
                  FRAG_JOB.condtion_slice[1].con_V1.attr_num =2;
                  FRAG_JOB.condtion_slice[1].con_V1.attr_frag_strlist[0] = "jno";
                  FRAG_JOB.condtion_slice[1].con_V1.attr_frag_strlist[1] = "loc";
//db3
                  FRAG_JOB.condtion_slice[2].isValid =true;
                  FRAG_JOB.condtion_slice[2].con_H1.isValid =true;
                  FRAG_JOB.condtion_slice[2].con_H1.attr_name ="jno";
                  FRAG_JOB.condtion_slice[2].con_H1.attr_condition = ">=";
                  FRAG_JOB.condtion_slice[2].con_H1.attr_value = "'J0500'";

                  FRAG_JOB.condtion_slice[2].con_H2.isValid =false;

                  FRAG_JOB.condtion_slice[2].con_V1.isValid =true;
                  FRAG_JOB.condtion_slice[2].con_V1.attr_num =3;
                  FRAG_JOB.condtion_slice[2].con_V1.attr_frag_strlist[0] = "jno";
                  FRAG_JOB.condtion_slice[2].con_V1.attr_frag_strlist[1] = "jname";
                  FRAG_JOB.condtion_slice[2].con_V1.attr_frag_strlist[2] = "budget";

         //db4
                  FRAG_JOB.condtion_slice[3].isValid =true;
                  FRAG_JOB.condtion_slice[3].con_H1.isValid =true;
                  FRAG_JOB.condtion_slice[3].con_H1.attr_name ="jno";
                  FRAG_JOB.condtion_slice[3].con_H1.attr_condition = ">=";
                  FRAG_JOB.condtion_slice[3].con_H1.attr_value = "'J0500'";

                  FRAG_JOB.condtion_slice[3].con_H2.isValid =false;

                  FRAG_JOB.condtion_slice[3].con_V1.isValid =true;
                  FRAG_JOB.condtion_slice[3].con_V1.attr_num =2;
                  FRAG_JOB.condtion_slice[3].con_V1.attr_frag_strlist[0] = "jno";
                  FRAG_JOB.condtion_slice[3].con_V1.attr_frag_strlist[1] = "loc";

//////////////////////////////////////////////////////////////SAL///////////////////////
                  Fragment FRAG_SAL;
                  FRAG_SAL.frag_talbe_name = "sal";
                  FRAG_SAL.condtion_slice[0].isValid =false;
                  FRAG_SAL.condtion_slice[1].isValid =false;
                  FRAG_SAL.condtion_slice[2].isValid =false;
                  FRAG_SAL.condtion_slice[3].isValid =false;

                  dm.mtr->set_fargment_info(FRAG_SAL);
                  dm.mtr->set_fargment_info(FRAG_EMP);
                  dm.mtr->set_fargment_info(FRAG_JOB);
                  dm.mtr->set_fargment_info(FRAG_ASG);

                  dm.mtr->set_table_metadata_toquerytree();
                  dm.mtr->set_fragment_metadata_toquerytree();


}

//emulated input fragment metadata

    dm.mtr->setMetadataVer("0.0.1");
    queryTree();
    struct schema* p = NULL;
    p = &sch;
    printf("the sch's address is: %p\n",p);
    dm.show();
    //generate querytree to tree.txt


    return app.exec();
    return 0;
}



void queryTree()
{
    //string input = "select eno,jno,title,loc from emp,job,sal,asg where (emp.title=sal.title) and (emp.eno=asg.eno) and (job.jno=asg.jno) and (jno<='J0400') and (title<'N')";
    string input = "select * from emp,asg where (emp.eno=asg.eno)";
    //string input = "select * from emp,sal where (emp.title=sal.title)";
    //string input = "select * from emp where (eno<'E1000') and (title>='N')";
    //string input = "select * from asg";
    //init_schema();
    query_tree original_tree = get_original_tree(input);
    Dispather dis;
    dis.set_treevector_from_querytree(original_tree);
    cout << "original tree build complete\n";
    get_basic_opt_tree(original_tree, 3);//使用前3种优化
    cout << "basic optimize tree complete\n";
    print_tree(original_tree);
}


