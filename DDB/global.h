#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <libconfig.h++>
#include <string>

#define MAX_ATTRIBUTION_NUM 100 // max numbers of attributin in a table
#define MAX_TABLE_NUM 100 //max numbers of table in a database

#define CONFIG_NAME_DATABASE "DDB"
#define BASE_DATABASE_PATH "./database/" //database path
#define METADATA_CONFIG_FILE "data.cfg" //config file name

#define MAX_SITE_NUM 4 //max site number of DDB

#define CONFIG_NAME_SITEINFO "site_info"
#define CONFIG_NAME_SITEINFO_SITE_ID "site_ID"
#define CONFIG_NAME_SITEINFO_SITE_NAME "site_name"
#define CONFIG_NAME_SITEINFO_SITE_IP "site_ip"
#define CONFIG_NAME_SITEINFO_STIE_PORT "site_port"
#define CONFIG_NAME_SITEINFO_SITE_IS_CONTROL_SITE "is_control_site"

#define MAX_FRAGMENT_NUM 4
#define MAX_VERTICAL_FRAGMENT_NUM 20
#define CONFIG_NAME_FRAGMENT "fragment"
#define CONFIG_NAME_FRAGMENT_ISVALID "isvalid"
#define CONFIG_NAME_FRAGMENT_SLICE "db"
#define CONFIG_NAME_FRAGMENT_CON_H1 "con_H1"
#define CONFIG_NAME_FRAGMENT_CON_H2 "con_H2"
#define CONFIG_NAME_FRAGMENT_CON_V1 "con_V1"
#define CONFIG_NAME_FRAGMENT_CON_V2 "con_V2"
#define CONFIG_NAME_FRAGMENT_ATTR_NAME "attr_name"
#define CONFIG_NAME_FRAGMENT_ATTR_CONDITION "attr_condition"
#define CONFIG_NAME_FRAGMENT_ATTR_VALUE "attr_value"
#define CONFIG_NAME_FRAGMENT_LIST "fragment_name_list"
#define CONFIG_NAME_FRAGMENT_V_ATTR_NUM "attr_num"
#define CONFIG_NAME_FRAGMENT_ATTR_PRIKEY "attr_prikey"
#define CONFIG_NAME_FRAGMENT_ATTR_FRAG_STRLIST "attr_frag_strlist"

#define CONFIG_NAME_VERSION "version"

#define CONFIG_NAME_TABLE_LIST "table_name_list"
#define CONFIG_NAME_TALBE_ATTR_NUM "attr_num"
#define CONFIG_NAME_TABLE_ATTR_NAME "attr_name"
#define CONFIG_NAME_TABLE_ATTR_DATATYPE "attr_datatype"
#define CONFIG_NAME_TABLE_ATTR_LENGTH "attr_length"
#define CONFIG_NAME_TABLE_ATTR_RULESTYPE "attr_rulestype"
#define CONFIG_NAME_TABLE_ATTR_SLICE "ATTR"

#define CONFIG_TEMPFILE_PATH "./tmp/"
#define LOCALHOST "127.0.0.1"


 enum TYPE
{
     I=1,C,V,F,D
};



typedef enum _RulesType
{
    PRIMARY_KEY = 0,
    NOT_NULL,
    FOREIGN_KEY,
    RULES_NULL

}RulesType;
#endif // GLOBAL_H
