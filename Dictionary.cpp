#include "Dictionary.h"
#include <iostream>
#include <string>
#include <algorithm>

Dictionary::Dictionary(string file_path) 
{
    this->file_path = file_path;
    dictionary_size = findDictionarySize();
}

int Dictionary::findDictionarySize() {
    ifstream dictionary_file(file_path);

    if (!dictionary_file.is_open())
    {
        cerr << "Błąd otwierania pliku" << endl;
        return -1;
    }

    string line;
    int counter = 0;

    while (getline(dictionary_file, line)) {
        counter++;
    }

    dictionary_file.close();

    return counter;
}

bool Dictionary::hasWord(string word)
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

bool Dictionary::hasWordsThatStartWith(string word)
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

        if (line.length() >= word.length())
        {

            if (line.compare(0, word.size(), word) == 0)
            {
                dictionary_file.close();
                return true;
            }
        }
    }

    dictionary_file.close();
    return false;
}