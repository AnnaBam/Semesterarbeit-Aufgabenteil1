#include <iostream>
using namespace std;
#include <string.h>
#include "element.h"

Element::Element(char *string)
{
    zahl=0;
    zahlAttribute=0;
    strcpy(name,string);
    status=frei;
    naechstes=NULL;
}

void Element::addTag(char *string){
    strcpy(tags[zahl],string);
    zahl++;
}

void Element::addAttribute(char *string){
    strcpy(attributes[zahlAttribute],string);
    zahlAttribute++;
}

void Element::druckeElement(int ebene,Element *wurzel){
    int j,i;
    Element *abhaengig;

    status=inBearbeitung;
    for (j=0;j<ebene;j++) cout << "|   ";
    cout << "Element " << name << " erlaubt die Attribute: " << endl;
    for (i=0;i<zahlAttribute;i++){
        for (j=0;j<ebene;j++) cout << "|   ";
        cout << "  -" << attributes[i] << endl;
    }
    for (j=0;j<ebene;j++) cout << "|   ";
    cout << "und enth�lt die Tags: " << endl;
    for (i=0;i<zahl;i++){
        for (j=0;j<ebene;j++) cout << "|   ";
        cout << "   " << tags[i] << endl;
        abhaengig=sucheElement(tags[i],wurzel);
        if (abhaengig != NULL) abhaengig->druckeElement(ebene+1,wurzel);
    }
    status=frei;
}

Element *Element::sucheElement(char *suche, Element *element){
    Element *resultat;

    if (element==NULL) return NULL;
    if (!strcmp(suche,element->name))
        if (element->status==frei) return element;
        else return NULL;
    return sucheElement(suche,element->naechstes);
}


int Element::elementIstErlaubt(char *name){
    for (int i=0;i<zahl;i++){
        string s = "";
                s+=name;

        if (s.find(tags[i])) return i;
    }
    return -1;
}

int Element::attributeIstErlaubt(char *name){
    for (int i=0;i<zahlAttribute;i++)
        if (!strcmp(name,attributes[i])) return i;

    return -1;
}

