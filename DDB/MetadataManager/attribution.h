#ifndef ATTRIBUTION_H
#define ATTRIBUTION_H

#include "../global.h"
#include <string>


class Attribution
{
public:
    Attribution();
    Attribution(const Attribution &Attr);

    void set_attr_name(std::string name){attr_name = name;}
    std::string get_attr_name(){return attr_name;}

    void set_attr_datatype(DataType datatype){attr_datatype = datatype;}
    DataType get_attr_datatype(){return attr_datatype;}

    void set_attr_length(int length){attr_length = length;}
    int get_attr_length(){return attr_length;}

    void set_attr_rulestype(RulesType rulestype){attr_rulestype = rulestype;}
    RulesType get_attr_rulestype(){return attr_rulestype;}

private:
    std::string attr_name;
    DataType attr_datatype;
    int attr_length;
    RulesType attr_rulestype;




};

#endif // ATTRIBUTION_H
