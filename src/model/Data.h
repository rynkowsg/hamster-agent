#ifndef FACT_H
#define FACT_H

#include <ctime>        // time_t
#include <memory>       // shared_ptr
#include <string>       // string
#include <vector>       // vector

using std::string;
using std::vector;

namespace Model {

typedef vector<string> TagsList;

struct Fact {
    string activity;
    string category;
    vector<string> tags;
    std::time_t start_time;
    std::time_t end_time;
    string description;

    string toString(char delim = '|') const;
};

typedef vector<Fact> Data;
typedef std::shared_ptr<Data> DataPtr;


string tagstoString(const TagsList& vec, const char delim);
TagsList& stringToTags(const string& s, const char delim, TagsList& elems);

} // namepspace Model

#endif  // FACT_H
