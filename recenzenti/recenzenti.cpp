#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

class Person {
public:
    string name;
    vector<int> nicknames;

    Person (string name, vector<int> nicknames) {
        this->name = name;
        this->nicknames = nicknames;
    }
};

string find_person(vector<Person> &persons, int nickname) {
    for (Person p: persons) {
        for (int person_nickname: p.nicknames) {
            if (person_nickname == nickname) {
                return p.name;
            }
        }
    }
    return "";
}

bool nickname_belongs(vector<Person> &persons, int nickname, string name) {
    for (Person p: persons) {
        for (int person_nickname: p.nicknames) {
            if (person_nickname == nickname && p.name == name) return true;
        }
    }

    return false;
}

int main() {
    ifstream cin("reviewers.in");
    ofstream cout("reviewers.out");

    string command, name;
    int nickname_count, nickname;
    char command_type;
    vector<Person> persons;
    vector<int> nicknames;
    vector<string> names;
    vector<int> nicknames_temp;
    bool success;

    while (getline(cin, command)) {
        nicknames_temp.clear();
        istringstream iss(command);

        iss >> command_type;
        if (command_type == 'I') {
            success = true;
            iss >> name;
            if (find(names.begin(), names.end(), name) == names.end()) { // Adding a new person
                iss >> nickname_count;
                if (nickname_count > 50) success = false;

                for (int i = 0; i < nickname_count; i++) {
                    iss >> nickname;
                    if (find(nicknames.begin(), nicknames.end(), nickname) == nicknames.end() || find(nicknames_temp.begin(), nicknames_temp.end(), nickname) != nicknames_temp.end()) { // Nickname doesn't exist
                        nicknames.push_back(nickname);
                        nicknames_temp.push_back(nickname);
                        names.push_back(name);
                        success = true;
                    } else success = false;
                }

                if (success) {
                    Person person(name, nicknames_temp);
                    persons.push_back(person);
                    cout << "ok" << endl;
                } else cout << "no" << endl;

            } else { // Adding extra nicknames for an existing person
                iss >> nickname_count;
                if (nickname_count > 50) success = false;

                for (int i = 0; i < nickname_count; i++) {
                    iss >> nickname;
                    if (find(nicknames.begin(), nicknames.end(), nickname) == nicknames.end()) {
                        nicknames_temp.push_back(nickname);
                    } else if (!nickname_belongs(persons, nickname, name)) {
                        success = false;
                        break;
                    }
                }

                for (Person p: persons) {
                    if (p.name == name) {
                        if (p.nicknames.size() + nicknames_temp.size() > 50) success = false;
                    }
                }

                if (success) {
                    for (Person &p: persons) {
                        if (p.name == name) {
                            for (int person_nickname: nicknames_temp) {
                                p.nicknames.push_back(person_nickname);
                                nicknames.push_back(person_nickname);
                            }
                        }
                    }
                }

                if (success) cout << "ok" << endl;
                else cout << "no" << endl;
            }


        } else if (command_type == 'D') {
            iss >> nickname;
            if (find(nicknames.begin(), nicknames.end(), nickname) != nicknames.end()) {
                name = find_person(persons, nickname);
                for (Person p: persons) {
                    if (p.name == name) {
                        for (int person_nickname: p.nicknames) {
                            nicknames.erase(remove(nicknames.begin(), nicknames.end(), person_nickname), nicknames.end());
                        }
                    }
                }

                for (vector<Person>::iterator it = persons.begin(); it != persons.end(); ++it) {
                    if (it->name == name) {
                        persons.erase(it);
                        break;
                    }
                }

                success = true;
            } else success = false;

            if (success) cout << "ok" << endl;
            else cout << "no" << endl;
        } else if (command_type == 'L') {
            success = false;
            iss >> nickname;

            name = find_person(persons, nickname);
            if (name != "") success = true;

            if (success) cout << name << endl;
            else cout << "no" << endl;
        }
    }

}
