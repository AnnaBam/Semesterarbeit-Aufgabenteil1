#include "membercountry.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

MemberCountry::MemberCountry()
{
}

//XML-Format ausgeben
string MemberCountry::toXml(){
    string temp = "";
    temp += "<country id=\"";
    temp += id;
    temp += "\">\n";

    temp += "<name>";
    temp += name;
    temp += "</name>\n";

    temp += "<captial>";
    temp += capital;
    temp += "</captial>\n";



    temp += "<size>";
    temp += to_string(size/1000);
    temp += ".";
    temp += to_string(size%1000);

    temp += "</size>\n";

    temp += "<population>";
    temp += to_string(population);
    temp += "</population>\n";

    //wenn Sprache vorhanden, LanguagesTag mit einer oder mehreren Sprachen
    if(languages.size() != 0){
        temp += "<languages>\n";

        for(string l : languages){
            temp += "<language>";
            temp += l;
            temp += "</language>\n";
        }

        temp += "</languages>\n";
    }

    temp += "</country>\n";

    return temp;
}

//XML-Datei laden
vector<MemberCountry> member;
void loadXML2(){
    ifstream input;
    input.open("EU-countries.xml");

    string test;    
    int counter = 1;
    while (counter < 14){
        getline(input, test);
        counter ++;
    }

    for(string line; getline(input,line);) {

        MemberCountry tempMember;
        if(line.find("<country>")){
            int startPos = line.find("=\"");
            int endPos = line.find('\">');
            string id = line.substr(startPos+2, endPos-startPos-3);
            tempMember.id = id;
        }
        if(line.find("<name>")){
            int startPos = line.find('>');
            int endPos = line.find('/');
            string countryName = line.substr(startPos+1, endPos-startPos-2);
            tempMember.name = countryName;
        }
        if(line.find("<capital>")){
            int startPos = line.find('>');
            int endPos = line.find('/');
            string capital = line.substr(startPos+1, endPos-startPos-2);
            tempMember.capital = capital;
        }
        if(line.find("<size>")){
            int startPos = line.find('>');
            int endPos = line.find('/');
            int size = stoi(line.substr(startPos+1, endPos-startPos-2));
            tempMember.size = size;
        }
        if(line.find("<population>")){
            int startPos = line.find('>');
            int endPos = line.find('/');
            int population = stoi(line.substr(startPos+1, endPos-startPos-2));
            tempMember.population = population;
        }
        member.push_back((tempMember));
    }
}




void loadXML(){
    ifstream input;
    input.open("EU-countries.xml");

    string test ;
    string fullxml;
    int counter = 1;


    while (counter < 14){
        getline(input, test);
        fullxml += test;
        counter ++;
    }

    for(string line; getline(input,line);) {
        fullxml +=line;
    }
    int i = 0;
    while (i < fullxml.length()) {
        i = fullxml.find('\n', i);
        if (i == -1) {
            break;
        }
        fullxml.erase(i);

    }


    vector<MemberCountry> countries;
    MemberCountry country;



  cout << fullxml;

}


