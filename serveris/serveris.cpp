#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Computer {
public:
    int num;
    vector<int> adjacent_computers;
    int furthest_computer; // Distance to the furthest computer

    Computer() {};

    Computer(int num) {
        this->num = num;
        this->furthest_computer = 0;
    }
};

vector<int> get_adjacent_computers (vector<Computer> computers, int num) {
    return computers[num-1].adjacent_computers;
}


int main() {
    ifstream cin("server.in");
    ofstream cout("server.out");

    int computer_count, computer1_num, computer2_num;
    Computer computer1, computer2;
    vector<Computer> computers;

    cin >> computer_count;

    for (int i = 1; i <= computer_count; i++) {
        Computer new_computer(i);
        computers.push_back(new_computer);
    }

    do {
        cin >> computer1_num;
        cin >> computer2_num;

        if (computer1_num != 0 && computer2_num != 0) {
            computers[computer1_num - 1].adjacent_computers.push_back(computer2_num);
            computers[computer2_num - 1].adjacent_computers.push_back(computer1_num);
        }
    } while (computer1_num != 0 && computer2_num != 0);

    /*
    for (Computer c: computers) {
        cout << c.num << " ";
        for (int n: c.adjacent_computers) cout << n << " ";
        cout << endl;
    }
    */

    for (Computer &c: computers) {
        unordered_map<int, vector<int>> levels;
        vector<int> visited_nodes;
        vector<int> current_level_nodes;
        int current_level = 1;
        vector<int> adjacent_nodes;
        visited_nodes.push_back(c.num);

        adjacent_nodes = get_adjacent_computers(computers, c.num);
        for (int n: adjacent_nodes) {
            if (find(visited_nodes.begin(), visited_nodes.end(), n) == visited_nodes.end()) {
                current_level_nodes.push_back(n);
                visited_nodes.push_back(n);
            }
        }
        levels[current_level] = current_level_nodes;

        while (visited_nodes.size() < computers.size()) {
            for (int n: levels[current_level]) {
                adjacent_nodes = get_adjacent_computers(computers, n);

                for (int n: adjacent_nodes) {
                    if (find(visited_nodes.begin(), visited_nodes.end(), n) == visited_nodes.end()) {
                        current_level_nodes.push_back(n);
                        visited_nodes.push_back(n);
                    }
                }
            }
            levels[current_level + 1] = current_level_nodes;
            current_level++;

        }
        c.furthest_computer = current_level;
    }

    int min_dist = computers[0].furthest_computer;
    for (Computer c: computers) {
        if (c.furthest_computer < min_dist) min_dist = c.furthest_computer;
    }

    vector<int> servers;

    for (Computer c: computers) {
        if (c.furthest_computer == min_dist) servers.push_back(c.num);
    }

    cout << min_dist << endl;
    for (int n: servers) cout << n << " ";

}
