#include "siteinfo.h"

SiteInfo::SiteInfo()
{
    site_ID = 0;
    site_ip = "";
    site_name = "";
    site_port = 0;
    isControlSite = false;

}

SiteInfo::SiteInfo(SiteInfo &sti)
{
    this->site_ID = sti.get_site_ID();
    this->site_ip = sti.get_site_ip();
    this->site_name = sti.get_site_name();
    this->site_port = sti.get_site_port();
    this->isControlSite = sti.get_isControlSite();

}
