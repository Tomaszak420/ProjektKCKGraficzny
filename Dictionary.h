#include <string>
#include <fstream>

using namespace std;

class Dictionary
{
    ifstream dictionary_file;
    string file_path;

public:
    Dictionary(string file_path);
    bool lookupWord(string word);
};