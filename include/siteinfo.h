#ifndef SITEINFO_H
#define SITEINFO_H

#include "../include/global.h"



typedef struct _SiteMetadata
{
    int site_ID = 0;
    int site_port = 0;
    bool isControlSite = false;
    std::string site_name = "";
    std::string site_ip = "";


}SiteMetadata;


class SiteInfo
{
public:
    SiteInfo();
    SiteInfo(SiteInfo &sti);
    void set_site_name(std::string name){site_name = name;}
    std::string get_site_name(){return site_name;}

    void set_site_ip(std::string ip){site_ip = ip;}
    std::string get_site_ip(){return site_ip;}

    void set_site_port(int port){site_port = port;}
    int get_site_port(){return site_port;}

    void set_site_ID(int ID){site_ID = ID;}
    int get_site_ID(){return site_ID;}

    void set_control_site(bool iscontrol){isControlSite = iscontrol;}
    bool get_isControlSite(){return isControlSite;}


private:
    int site_ID;//site ID number
    std::string site_name;//site n's name
    std::string site_ip;//ip address
    int site_port;//port number for connection
    bool isControlSite;//whether this site is a control site
};

#endif // SITEINFO_H

