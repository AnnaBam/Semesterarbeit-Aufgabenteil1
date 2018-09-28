#include "europa.h"
#include <string>
#include "membercountry.h"

Europa::Europa(){
}

string Europa::toXml(){
    string tempE = "";
    tempE += "<Europa>\n";
    for(MemberCountry member : memberCountries){
        tempE += member.toXml();
    }
    tempE += "\n</Europa>";
    return tempE;
}


void Europa::addCountry(MemberCountry& country){
         this->memberCountries.push_back(country);
}


// POSITION
int Europa::searchName (string name){
    for(int i= 0; i< this->memberCountries.size(); i++){
        MemberCountry country = this->memberCountries.at(i);


        if(country.name.compare(name) == 0){
            return i;
        }
    }
    return -1;
};
