#ifndef MEMBERCOUNTRY_H
#define MEMBERCOUNTRY_H

#include <string>
#include <vector>
using namespace std;

void loadXML();

class MemberCountry
{
public:
    MemberCountry();

    string id;
    string name;
    string capital;
    int size;
    int population;
    vector<string> languages;

    string toXml();


};

#endif // MEMBERCOUNTRY_H
