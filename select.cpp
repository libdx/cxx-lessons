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

}

const string Text = "123|Belgrad\n42|Odessa";

int main()
{
    using namespace Example;

    vector<Entry> entries = create_entries(Text);

    for (auto e: entries) {
        cout << "id=" << e.id << endl;
        cout << "val=" << e.value << endl;
    }

    return 0;
}



