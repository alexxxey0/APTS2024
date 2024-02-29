#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Guard {
public:
    int id;
    int time;
    bool busy;
    int available_at;

    Guard(int id, int time) {
        this->id = id;
        this->time = time;
        this->busy = false;
        this->available_at = 0;
    }

    Guard () {};
};

class Person_out {
public:
    int id;
    int time;
    int checking_guard;

    Person_out(int id, int time, int checking_guard) {
        this->id = id;
        this->time = time;
        this->checking_guard = checking_guard;
    }

    Person_out () {};
};

// Returns the id of the first free guard. If all guards are busy, returns 0.
int first_free_guard(vector<Guard> guards, int guards_count) {
    for (int i = 0; i < guards_count; i++) {
        if (!guards[i].busy) return guards[i].id;
    }
    return 0;
}

int get_guard_time(vector<Guard> guards, int guards_count, int id) {
    for (int i = 0; i < guards_count; i++) {
        if (guards[i].id == id) return guards[i].time;
    }
    return 0;
}

int get_guard_available_at(vector<Guard> guards, int guards_count, int id) {
    for (int i = 0; i < guards_count; i++) {
        if (guards[i].id == id) return guards[i].available_at;
    }
    return 0;
}

int get_soonest_guard (vector<Guard> guards, int guards_count) {
    int min_time = guards[0].available_at;
    int guard_id = guards[0].id;
    for (int i = 0; i < guards_count; i++) {
        //cout << guards[i].available_at << " " << min_time << endl;
        if (guards[i].available_at < min_time) {
            guard_id = guards[i].id;
            min_time = guards[i].available_at;
        }
    }
    cout << endl;
    return guard_id;
}

vector<Person_out> sorted_output(vector<Person_out> output) {
    //for (Person_out p: output) cout << p.id << " ";
    cout << endl;
    vector<int> order;
    vector<int> guard_nums;
    vector<Person_out> result;
    int min_num = output[0].time;

    for (Person_out p: output) {
        order.push_back(p.time);
    }

    sort(order.begin(), order.end());
    auto it = unique(order.begin(), order.end());
    order.erase(it, order.end());

    //for (int n: order) cout << n << endl;

    // Check if there ar multiple people exiting at the same point in times
    map<int, int> exiting; // time, num of people exiting
    for (Person_out p: output) {
        exiting[p.time]++;
    }

    //for (auto n: exiting) cout << n.first << " " << n.second << endl;
    //for (Person_out p: output) cout << p.id << " ";

    for (int n: order) {
        if (exiting[n] == 1) {
            for (Person_out p: output) {
                if (p.time == n) {
                    result.push_back(p);
                }
            }
        } else {
            for (Person_out p: output) {
                if (p.time == n) guard_nums.push_back(p.checking_guard);
            }
            sort(guard_nums.begin(), guard_nums.end());

            for (int g: guard_nums) {
                for (Person_out p: output) {
                    if (p.time == n && p.checking_guard == g) {
                        result.push_back(p);
                        continue;
                    }
                }
            }
        }
    }

    return result;
}

int main() {
    ifstream cin("customs.in");
    ofstream cout("customs.out");

    int p_guards_count, n_guards_count, p_time, n_time, id, time, available_guard, soonest_guard, waiting_time;
    char letter1, letter2;
    vector<Person_out> output_p;
    vector<Person_out> output_n;


    cin >> p_guards_count;
    cin >> n_guards_count;
    cin >> p_time;
    cin >> n_time;

    vector<Guard> p_guards;
    vector<Guard> n_guards;

    for (int i = 1; i <= p_guards_count; i++) {
        Guard guard(i, p_time);
        p_guards.push_back(guard);
    }
    for (int i = 1; i <= n_guards_count; i++) {
        Guard guard(i, n_time);
        n_guards.push_back(guard);
    }

    do {
        cin >> letter1;

        if (letter1 == 'T') {
            cin >> letter2;
            cin >> id;
            cin >> time;
            if (letter2 == 'P') p_guards[id - 1].time = time;
            else n_guards[id - 1].time = time;
        }
    } while (letter1 == 'T');

    while (letter1 == 'P' || letter1 == 'N') {
        cin >> id;
        waiting_time = 0;

        if (letter1 == 'P') {
            for (Guard &g: p_guards) {
                if (g.available_at <= id) g.busy = false;
            }
            available_guard = first_free_guard(p_guards, p_guards_count);

            if (available_guard != 0) {
                p_guards[available_guard - 1].busy = true;
                p_guards[available_guard - 1].available_at = id + p_guards[available_guard - 1].time;
                Person_out person_out(id, id + p_guards[available_guard - 1].time, available_guard);
                output_p.push_back(person_out);
            } else {
                soonest_guard = get_soonest_guard(p_guards, p_guards_count);
                p_guards[soonest_guard - 1].available_at = p_guards[soonest_guard - 1].available_at + p_guards[soonest_guard - 1].time;
                Person_out person_out(id, get_guard_available_at(p_guards, p_guards_count, soonest_guard), soonest_guard);
                output_p.push_back(person_out);
            }

        } else if (letter1 == 'N') {
            for (Guard &g: n_guards) {
                if (g.available_at <= id) g.busy = false;
            }
            available_guard = first_free_guard(n_guards, n_guards_count);
            if (available_guard != 0) {
                n_guards[available_guard - 1].busy = true;
                n_guards[available_guard - 1].available_at = id + n_guards[available_guard - 1].time;
                Person_out person_out(id, id + n_guards[available_guard - 1].time, available_guard);
                output_n.push_back(person_out);
            } else {
                soonest_guard = get_soonest_guard(n_guards, n_guards_count);
                n_guards[soonest_guard - 1].available_at = n_guards[soonest_guard - 1].available_at + n_guards[soonest_guard - 1].time;
                Person_out person_out(id, get_guard_available_at(n_guards, n_guards_count, soonest_guard), soonest_guard);
                output_n.push_back(person_out);
            }
        }
        cin >> letter1;
    }

    output_p.insert(output_p.end(), output_n.begin(), output_n.end());


    vector<Person_out> result;
    //for (Person_out p: output_p) cout << p.id << " ";

    result = sorted_output(output_p);

    vector<Person_out> unique_result;
    vector<int> unique_nums;

    for (Person_out p: result) {
        if (find(unique_nums.begin(), unique_nums.end(), p.id) == unique_nums.end()) {
            unique_nums.push_back(p.id);
            unique_result.push_back(p);
        }
    }

    for (Person_out p: unique_result) {
        cout << p.id << " " << p.time << endl;
    }

}
