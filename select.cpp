#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>

// using namespace just for simplicity
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
    while (getline(input, substring, Delimiter)) {
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

}

const string Text = "123|Belgrad";

int main()
{
    using namespace Example;

    Entry e = create_entry(Text);

    cout << "id=" << e.id << endl;
    cout << "val=" << e.value << endl;

    return 0;
}



