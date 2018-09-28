#include "language.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

language::language(){
}

language::language(string languageName, vector<string> countries)
{
    this->languageName = languageName;
    this->countries = countries;
}


