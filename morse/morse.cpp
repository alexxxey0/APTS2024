#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector<string> split_string(string str, char delimiter) {
    string word = "";
    vector<string> result;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != delimiter) {
            word += str[i];
            if (i == str.size() - 1) result.push_back("!");
        }
        else {
            if (word != "") {
                result.push_back(word);
                word = "";
            }
        }
    }
    return result;
}

int main() {
    ifstream cin("morse.in");
    ofstream cout("morse.out");

    unordered_map<string, char> morse_code;

    morse_code[".-"] = 'A';
    morse_code["-..."] = 'B';
    morse_code["-.-."] = 'C';
    morse_code["-.."] = 'D';
    morse_code["."] = 'E';
    morse_code["..-."] = 'F';
    morse_code["--."] = 'G';
    morse_code["...."] = 'H';
    morse_code[".."] = 'I';
    morse_code[".---"] = 'J';
    morse_code["-.-"] = 'K';
    morse_code[".-.."] = 'L';
    morse_code["--"] = 'M';
    morse_code["-."] = 'N';
    morse_code["---"] = 'O';
    morse_code[".--."] = 'P';
    morse_code["--.-"] = 'Q';
    morse_code[".-."] = 'R';
    morse_code["..."] = 'S';
    morse_code["-"] = 'T';
    morse_code["..-"] = 'U';
    morse_code["...-"] = 'V';
    morse_code[".--"] = 'W';
    morse_code["-..-"] = 'X';
    morse_code["-.--"] = 'Y';
    morse_code["--.."] = 'Z';

    morse_code["-----"] = '0';
    morse_code[".----"] = '1';
    morse_code["..---"] = '2';
    morse_code["...--"] = '3';
    morse_code["....-"] = '4';
    morse_code["....."] = '5';
    morse_code["-...."] = '6';
    morse_code["--..."] = '7';
    morse_code["---.."] = '8';
    morse_code["----."] = '9';

    morse_code[".-.-.-"] = '.';
    morse_code["--..--"] = ',';
    morse_code["---..."] = ':';
    morse_code["..--.."] = '?';
    morse_code["-....-"] = '-';
    morse_code["-..-."] = '/';
    morse_code[".----."] = ' ';


    string morse_text, morse_letter;
    vector<string> morse_letters;

    cin >> morse_text;
    morse_letters = split_string(morse_text, '|');

    for (string s: morse_letters) {
        if (morse_code.find(s) != morse_code.end()) cout << morse_code[s];
        else cout << '!';
    }
}
