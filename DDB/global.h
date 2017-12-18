#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <libconfig.h++>
#include <string>

#define MAX_ATTRIBUTION_NUM 100 // max numbers of attributin in a table
#define MAX_TABLE_NUM 100 //max numbers of table in a database

#define BASE_DATABASE_PATH "./database/" //database path
#define METADATA_CONFIG_FILE "etadata.cfg" //config file name

#define MAX_SITE_NUM 4 //max site number of DDB

#define CONFIG_NAME_SITEINFO "site_info"
#define CONFIG_NAME_SITEINFO_SITE_ID "site_ID"
#define CONFIG_NAME_SITEINFO_SITE_NAME "site_name"
#define CONFIG_NAME_SITEINFO_SITE_IP "site_ip"
#define CONFIG_NAME_SITEINFO_STIE_PORT "site_port"
#define CONFIG_NAME_SITEINFO_SITE_IS_CONTROL_SITE "is_control_site"

#define CONFIG_NAME_FRAGMENT "fragment"

#define CONFIG_NAME_VERSION "version"
typedef enum _DataTYpe
{
    INTEGER, CHAR, VARCHAR, LONG, FLOAT, DOUBLE, DATE, TYPE_NULL

}DataType;


typedef enum _RulesType
{
    PRIMARY_KEY,
    NOT_NULL,
    FOREIGN_KEY,
    RULES_NULL

}RulesType;
#endif // GLOBAL_H
