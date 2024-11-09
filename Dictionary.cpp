#include "Dictionary.h"
#include <iostream>
#include <string>
#include <algorithm>

Dictionary::Dictionary(string file_path) 
{
    this->file_path = file_path;
    loadWordList(file_path);
}

// Wczytuje listę słów z pliku do wektora "word_list". Zwraca false w przypadku niepowodzenia, w przeciwnym razie true.
bool Dictionary::loadWordList(string file_path) 
{
    // Otwarcie pliku
    ifstream dictionary_file(file_path);

    if (!dictionary_file.is_open())
    {
        cerr << "Błąd otwierania pliku" << endl;
        return false;
    }

    // Wczytujemy plik linia po linii
    string line;

    while (getline(dictionary_file, line)) 
    {
        // getline usunie z końca znak '\n', ale nie pozbedzie sie '\r'. Trzeba to zrobic 'recznie':
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());

        word_list.push_back(line);
    }

    // Zamkniecie pliku
    dictionary_file.close();
    return true;
}

// Jesli slowo jest w slowniku, zwraca jego indeks. Jesli nie ma, zwraca -1.
int Dictionary::findWord(string word)
{
    int l = 0;
    int r = word_list.size() - 1;
    int m;
    int helper;

    while (l <= r)
    {
        m = (l + r) / 2;
        helper = word_list[m].compare(word);

        if (helper < 0)
        {
            l = m + 1;
        }
        else if (helper > 0)
        {
            r = m - 1;
        }
        else
        {
            return m;
        }
    }

    return -1;
}

// Szuka pierwszego slowa w slowniku rozpoczynajacego sie danym prefiksem
// (Zakladamy, ze kazde slowo jest tez swoim wlasnym prefiksem, wiec jesli 'prefix' jest slowem w slowniku, to wlasnie ono zostanie zwrocone).
int Dictionary::findWordThatStartsWith(string prefix)
{
    int l = 0;
    int r = word_list.size();
    int m;

    while (l < r) {
        m = (l + r) / 2;

        if (word_list[m].compare(prefix) < 0) {
            l = m + 1;
        }
        else {
            r = m;
        }
    }

    return l;
}

// Zwraca slowo znajdujace sie w slowniku pod danym indeksem. Jesli indeks wychodzi poza zakres, zwraca pusty string.
string Dictionary::getWord(int index) 
{
    if (index >= 0 && index < word_list.size()) 
    {
        return word_list[index];
    }
    return "";
}

// Jesli slowo jest w slowniku, zwraca true. Jesli nie, zwraca false.
bool Dictionary::hasWord(string word)
{
    int l = 0;
    int r = word_list.size() - 1;
    int m;
    int helper;

    while (l <= r)
    {
        m = (l + r) / 2;
        helper = word_list[m].compare(word);

        if (helper < 0)
        {
            l = m + 1;
        }
        else if (helper > 0)
        {
            r = m - 1;
        }
        else
        {
            return true;
        }
    }

    return false;
}
