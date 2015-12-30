#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>

// using namespace just for convenience in this example
using namespace std;

namespace Example {

const char Delimiter = '|';

struct Entry {
    int id;
    string value;
};

// operator < is required by set
bool operator < (const Entry &e1, const Entry &e2)
{
    return e1.id < e2.id;
}


vector<string> split_string(string str, char delimiter)
{
    stringstream input(str);

    vector<string> substrings;
    string substring;
    while (getline(input, substring, delimiter)) {
        substrings.push_back(substring);
    }
    return substrings;
}

Entry create_entry(const string &str)
{
    auto substrings = split_string(str, Delimiter);

    // we might want to handle exeptions for stoi function
    // in order to not crash if input data is corrupted
    int id = stoi(substrings[0]);
    string value = substrings[1];

    // this one is C99 syntax for structs initialization, not C++ specific
    return Entry{.id = id, .value = value};
}

// this function works with string
vector<Entry> create_entries(const string &str)
{
    auto lines = split_string(str, '\n');

    vector<Entry> entries;
    for (auto line: lines) {
        Entry entry = create_entry(line);
        entries.push_back(entry);
    }

    return entries;
}

// this function works with input file stream
vector<Entry> create_entries(ifstream &input)
{
    vector<Entry> entries;

    string line;
    while(getline(input, line)) {
        Entry entry = create_entry(line);
        entries.push_back(entry);
    }

    return entries;
}

void print_entries(const vector<Entry> &entries, const set<Entry> &selected)
{
    int i = 1;
    for (auto e: entries) {
        string prefix = selected.count(e) ? "* " : "  ";
        cout << prefix << i << "." << " " << e.id << " | " << e.value << endl;
        ++i;
    }
}

const string Prompt = ">";

void run_ui(const vector<Entry> &entries)
{
    set<Entry> selected_entries;
    while(true) {
        print_entries(entries, selected_entries);

        string command;
        cout << Prompt << " ";
        cin >> command;

        if (command == "exit" ||
            command == "quit")
        {
            break;
        } else {
            // TODO: check stoi for exeptions
            int index = stoi(command) - 1;
            Entry entry = entries[index];

            if (selected_entries.count(entry)) {
                selected_entries.erase(entry);
            } else {
                selected_entries.insert(entries[index]);
            }
        }
    }
}

}

const string DataFilename = "data";

int main()
{
    using namespace Example;

    ifstream input(DataFilename);
    vector<Entry> entries = create_entries(input);

    run_ui(entries);

    return 0;
}

