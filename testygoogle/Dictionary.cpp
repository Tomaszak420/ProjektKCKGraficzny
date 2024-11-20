#include <fstream>
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Dictionary {
public:
    Dictionary(string file_path);

    bool loadWordList(string file_path);

    int findWord(string word);

    int findWordThatStartsWith(string prefix);

    string getWord(int index);

    bool hasWord(string word);

    vector<string> word_list;
private:
    string file_path= "test_dictionary.txt";
};

Dictionary::Dictionary(string file_path) : file_path(file_path) {
    loadWordList(file_path);
}

bool Dictionary::loadWordList(string file_path) {
    ifstream dictionary_file(file_path);
    if (!dictionary_file.is_open()) {
        cerr << "Błąd otwierania pliku" << endl;
        return false;
    }

    string line;
    while (getline(dictionary_file, line)) {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        word_list.push_back(line);
    }

    dictionary_file.close();
    return true;
}

int Dictionary::findWord(string word) {
    int l = 0;
    int r = word_list.size() - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        int helper = word_list[m].compare(word);
        if (helper < 0) {
            l = m + 1;
        } else if (helper > 0) {
            r = m - 1;
        } else {
            return m;
        }
    }
    return -1;
}

int Dictionary::findWordThatStartsWith(string prefix) {
    int l = 0;
    int r = word_list.size() - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (word_list[m].compare(0, prefix.size(), prefix) < 0) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    if (l < word_list.size() && word_list[l].find(prefix) == 0) {
        return l;
    }
    return -1;
}

string Dictionary::getWord(int index) {
    if (index >= 0 && index < word_list.size()) {
        return word_list[index];
    }
    return "";
}

bool Dictionary::hasWord(string word) {
    return findWord(word) != -1;
}

void testLoadWordList() {
    Dictionary dict("test_dictionary.txt");
    assert(dict.loadWordList("test_dictionary.txt") == true);
}

void testFindWord() {
    Dictionary dict("test_dictionary.txt");
    dict.loadWordList("test_dictionary.txt");
    assert(dict.findWord("apple") != -1);
    assert(dict.findWord("not_in_dictionary") == -1);
}

void testFindWordThatStartsWith() {
    Dictionary dict("test_dictionary.txt");
    dict.loadWordList("test_dictionary.txt");
    int index = dict.findWordThatStartsWith("app");
    assert(index != -1 && dict.getWord(index).find("app") == 0);
}

void testGetWord() {
    Dictionary dict("test_dictionary.txt");
    dict.loadWordList("test_dictionary.txt");
    assert(dict.getWord(0) != "");
    assert(dict.getWord(-1) == "");
    assert(dict.getWord(dict.word_list.size()) == "");
}

void testHasWord() {
    Dictionary dict("test_dictionary.txt");
    dict.loadWordList("test_dictionary.txt");
    assert(dict.hasWord("apple") == true);
    assert(dict.hasWord("not_in_dictionary") == false);
}

int main() {
    testLoadWordList();
    testFindWord();
    testFindWordThatStartsWith();
    testGetWord();
    testHasWord();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}