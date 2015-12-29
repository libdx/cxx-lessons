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

}

const string Text = "123|Belgrad\n42|Odessa";
const string DataFilename = "data";

void print_entries(const vector<Example::Entry> &entries)
{
    for (auto e: entries) {
        cout << e.id << "|" << e.value << endl;
    }
}

int main()
{
    using namespace Example;

    vector<Entry> entries = create_entries(Text);
    print_entries(entries);

    cout << endl;

    ifstream input("data");
    vector<Entry> entries_from_file = create_entries(input);
    print_entries(entries_from_file);

    return 0;
}

