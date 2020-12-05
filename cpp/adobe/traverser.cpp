#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

string generate_hash(string word) {
    map<char, bool> hash;
    for (string::iterator it=word.begin(); it!=word.end(); ++it) {
        hash.insert(pair<char, bool>(*it, true));
    }
    string result = "";
    for (map<char, bool>::iterator itr = hash.begin(); itr != hash.end(); ++itr) {
        result += itr->first;
    }
    return result;
}

int main(int argc, char *argv[]) {
    map<string, int> frecv;
    string word;

    ifstream in("data.txt");
    while (in >> word) {
        word.erase(remove(word.begin(), word.end(), ','), word.end());
        string hash = generate_hash(word);
        map<string, int>::iterator it = frecv.find(hash);
        if (it == frecv.end()) {
            frecv.insert(pair<string, int>(hash, 1));
        } else {
            it->second++;
        }
    }
 
    for (map<string, int>::iterator itr = frecv.begin(); itr != frecv.end(); ++itr) {
        cout << itr->first << " -> " << itr->second << "\n";
    }
   
    in.close();
    return 0;
}
