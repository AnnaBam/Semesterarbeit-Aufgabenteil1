#ifndef TOKEN_H
#define TOKEN_H

#include "atttoken.h"
#include <fstream>
using namespace std;
class Token
{
    public:
       Token();
       char *name() { return tokenName; }
       Token *child() { return tokenChild; }
       char *inhalt() { return tokenInhalt; }
       Token *sibling() { return tokenSibling; }
       void druckeToken(int ebene);
       int getToken(ifstream &datei,Element *element,Element *wurzel);
       AttToken att;
    private:
       void cleanToken();
       void druckeTokenEbene(int ebene);
       int fillToken(int mode);
       char tokenName[64];
       Token *tokenChild;
       Token *tokenSibling;
       char *tokenInhalt;
};
enum zustand { istStartTag, istEndTag } ;
#endif // TOKEN_H
