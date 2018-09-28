#ifndef ATTTOKEN_H
#define ATTTOKEN_H

#include "element.h"
class AttToken
{
private:
    int anzahlAtt;
    char *attName[10];
    char *attValue[10];
public:





    int getAttList(char *eingabe,Element *element);
    char *zeigeAttName(int id) {return attName[id];}
    char *zeigeAttWert(int id) {return attValue[id];}
    int zahlAtt() {return anzahlAtt;}
};



#endif // ATTTOKEN_H
