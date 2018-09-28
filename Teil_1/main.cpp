#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "language.h"
#include "membercountry.h"
#include "europa.h"
#include "element.h"
#include "string.h"
#include "token.h"

using namespace std;

Element *verarbeite(ifstream& datei);
Token* xmlEinlesen(ifstream& xml, ifstream& dtd);
Europa* tokenToEuropa(Token* token);
Token* findToken(vector<Token*> list, string tagName);
vector<language> ladeCSVLanguages();
void menu(Europa&);




int main()
{
    ifstream dtdinput;
    dtdinput.open("countries.dtd");
    ifstream xmlinput;
    xmlinput.open("EU-countries.xml");

    Token* token= xmlEinlesen(xmlinput, dtdinput);
    if(token == NULL){
        return 0;
    }
    Europa* europa = tokenToEuropa(token);


    menu(*europa);
    return 0;
}





//Europa speichern
Europa* tokenToEuropa(Token* token){
    Europa* europa = new Europa;

    Token* tokenCountry = token->child();

    while(tokenCountry != NULL){
        MemberCountry* country = new MemberCountry;
        country->id = tokenCountry->att.zeigeAttWert(0);
        vector<Token*> tokenList;
        Token* child = tokenCountry->child();
        tokenList.push_back(child);
        while (child != NULL) {
            child = child->sibling();
            if(child != NULL){
                tokenList.push_back(child);
            }
        }

        Token* current = findToken(tokenList,"name");
        if(current != NULL){
            country->name = current->inhalt();
        }
        current = findToken(tokenList, "capital");
        if(current != NULL){
            country->capital = current->inhalt();
        }
        current = findToken(tokenList, "size");
        if(current != NULL){
            string sizeString = current->inhalt();
            if(sizeString.size() > 3){
                sizeString.erase(sizeString.find('.'),1);
            }
            country->size = stoi(sizeString);
        }
        current = findToken(tokenList, "population");
        if(current != NULL){
            country->population = stoi(current->inhalt());
        }
        current = findToken(tokenList, "languages");
        if(current != NULL){
            current = current->child();
            country->languages.push_back(current->inhalt());
            while (current != NULL) {
                current = current->sibling();
                country->languages.push_back(current->inhalt());
            }
        }

        europa->addCountry(*country);

        tokenCountry = tokenCountry->sibling();
    }
    return europa;
}



Token* findToken(vector<Token*> list, string tagName){

    for(Token* token : list){
        if(tagName.compare(token->name()) == 0) {
            return token;
        }
    }
    return NULL;
}

Token* xmlEinlesen(ifstream& xml, ifstream& dtd){
    Element * root = verarbeite(dtd);
    Token* token = new Token;
    token->getToken(xml,NULL,root);
    return token;
}

enum ezustand {direktive, element, attribute, abhaengigElement,
               abhaengigAttribute, noise};

Element *verarbeite(ifstream& datei)
{
    char zeichen, letztes;
    char puffer[100];
    int zaehler;
    enum ezustand zustand = noise;
    Element *jetzt=NULL, *wurzel=NULL, *neu;

    for (datei.get(zeichen);!datei.eof();datei.get(zeichen))
    {
        switch(zeichen)
        {
        case '<':
            zustand=direktive;
            zaehler=0;
            break;
        case '>':
            if (letztes!=' ')
            {
                puffer[zaehler]='\0';
                switch(zustand)
                {
                case abhaengigElement:
                    jetzt->addTag(puffer);
                    break;
                case abhaengigAttribute:
                    jetzt->addAttribute(puffer);
                    break;
                case element:
                    neu=new Element(puffer);
                    if (jetzt!=NULL) jetzt->setNext(neu);
                    else wurzel=neu;
                    jetzt=neu;
                    zustand=abhaengigElement;
                    break;
                }
            }
            zustand=noise;
            break;
        case ' ':
            if (letztes==' ') continue;
            puffer[zaehler]='\0';
            zaehler=0;
            switch(zustand)
            {
            case direktive:
                if (!strcmp(puffer,"!ELEMENT")) zustand=element;
                else if (!strcmp(puffer,"!ATTLIST")) zustand=attribute;
                else
                {
                    cout << endl << "Diese Direktive verstehe ich nicht: " << puffer;
                    zustand=noise;
                }
                break;
            case element:
                neu=new Element(puffer);
                if (jetzt!=NULL) jetzt->setNext(neu);
                else wurzel=neu;
                jetzt=neu;
                zustand=abhaengigElement;
                break;
            case attribute:
                if (wurzel==NULL) neu=NULL;
                else neu=wurzel->sucheElement(puffer,wurzel);
                if (neu==NULL)
                {
                    cout << endl << "Es gibt kein Element mit dem Namen: " << puffer << endl;
                    zustand=noise;
                }
                else
                {
                    zustand=abhaengigAttribute;
                    jetzt=neu;
                }
                break;
            case abhaengigElement:
                jetzt->addTag(puffer);
                break;
            case abhaengigAttribute:
                jetzt->addAttribute(puffer);
                break;
            }
            break;
        default:
            if (zustand!=noise) puffer[zaehler] = zeichen;
            zaehler++;
            break;
        }
        letztes=zeichen;
    }

    return wurzel;
}


vector<language> ladeCSVLanguages(){

    vector<language> languages;
    ifstream input;
    input.open("Language.csv");
    string line;

    for(string zeile; getline(input,zeile);) {
        if(zeile.find(';') == -1){
            break;
        }
        int position = zeile.find(';');
        int oldPos = position;
        string langName = zeile.substr(0,position);
        language tempLang;
        tempLang.languageName = langName;
        while((position = zeile.find(';',oldPos+1)) != -1){
            string countryName = zeile.substr(oldPos+1,position-oldPos-1);
            oldPos = position;
            tempLang.countries.push_back(countryName);

        }
        languages.push_back(tempLang);
    }
    return languages;
}

void packLanguagesInEuropa(Europa& europa){

    vector<language> languages = ladeCSVLanguages();
    for (language l : languages){
        for(string name : l.countries){
            int position;
            position = europa.searchName(name);

            if(position != -1){

            MemberCountry& member = europa.memberCountries.at(position);
            member.languages.push_back(l.languageName);
            }
        }
    }


}


//Menüführung
void menu(Europa& europa){
    char task;
    string searchRequest;

    cout << "Press 's' for search" << endl << "Press 'c' to convert data" << endl;
    cin >> task;
    if (task == 's'){
        cout << "What are you searching for? (search by name)" << endl;
        cin >> searchRequest;
        int i = europa.searchName(searchRequest);
        MemberCountry country = europa.memberCountries.at(i);
        cout << "Country: " << country.name << endl;
        cout << "Capital: " << country.capital << endl;
        cout << "Size: " << country.size << endl;
        cout << "Population: " << country.population << endl;

    }
    else if (task == 'c'){
        cout << "Converting..." << endl;
        packLanguagesInEuropa(europa);
        ofstream out("EU.xml");
        out << europa.toXml();
        out.close();

    }
    else {
        cout << "Invalid input" << endl;
    }
}
