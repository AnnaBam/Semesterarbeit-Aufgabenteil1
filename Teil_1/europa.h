#include <string>
#include <vector>
#include "membercountry.h"

using namespace std;



class Europa
{
public:
    Europa();

    vector<MemberCountry> memberCountries;
    void addCountry(MemberCountry&);
    string toXml();
    int searchName(string name);

};
