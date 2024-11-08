#include <string>
#include <fstream>

using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary
{
    ifstream dictionary_file;
    string file_path;
    int dictionary_size;

    int findDictionarySize();
public:
    Dictionary(string file_path);
    bool hasWord(string word);
    bool hasWordsThatStartWith(string word);
};

#endif