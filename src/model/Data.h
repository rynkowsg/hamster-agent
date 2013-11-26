#ifndef FACT_H
#define FACT_H

#include <boost/optional/optional.hpp>  // optional
#include <ctime>        // tm
#include <memory>       // shared_ptr
#include <string>       // string
#include <vector>       // vector

using std::string;
using std::vector;

namespace Model {

struct Fact {
    string activity;
    string category;
    std::tm start_time;
    boost::optional<std::tm> end_time;
    string description;
};
typedef vector<string> TagsList;

struct Row {
    Fact fact;
    TagsList tags;

    string toString(char delim = '|') const;
};
typedef vector<Row> Data;
typedef std::shared_ptr<Data> DataPtr;


string tagstoString(const TagsList& vec, const char delim);
TagsList& stringToTags(const string& s, const char delim, TagsList& elems);

} // namepspace Model

#endif  // FACT_H
