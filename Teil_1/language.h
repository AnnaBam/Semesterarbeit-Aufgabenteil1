#include <string>
#include <vector>

using namespace std;

void loadCSVLanguages();

class language
{
private:

public:
    language();
    string languageName;
    vector<string> countries;
    language(string, vector<string>);

};
