#include <string>
#include <fstream>
#include <vector>

using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary
{
    ifstream dictionary_file;
    string file_path;

public:
    Dictionary(string file_path);
    int findWord(string word);
    int findWordThatStartsWith(string prefix);
    string getWord(int index);
    bool hasWord(string word);

    bool loadWordList(string file_path);

    vector<string> word_list;
};

#endif