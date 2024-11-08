#include "Dictionary.h"
#include <iostream>
#include <string>
#include <algorithm>

Dictionary::Dictionary(string file_path) 
{
    this->file_path = file_path;
}

bool Dictionary::lookupWord(string word)
{
    ifstream dictionary_file(file_path);

    if (!dictionary_file.is_open())
    {
        cerr << "Błąd otwierania pliku" << endl;
        return false;
    }

    string line;

    while (getline(dictionary_file, line))
    {

        // Wywolanie erase() sluzy do obciecia znaku '\r' ('\n' obcial juz getline)
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        if (line == word)
        {
            dictionary_file.close();
            return true;
        }
    }

    dictionary_file.close();
    return false;
}