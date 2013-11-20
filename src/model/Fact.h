#ifndef FACT_H
#define FACT_H

#include <boost/date_time/posix_time/posix_time.hpp>    // ptime, to_simple_string
#include <memory>       // shared_ptr
#include <sstream>      // stringstream
#include <string>       // string
#include <vector>       // vector
#include "../Utils.h"

using boost::posix_time::ptime;
using boost::posix_time::to_simple_string;
using std::string;
using std::stringstream;
using std::vector;


namespace Model {

typedef string Activity;
typedef string Category;
typedef string Tag;
typedef string Description;
typedef ptime Time;

struct TagsList
{
    TagsList() : mTags() {}
    TagsList(string const& s, const char delim = ',') {
        Utils::split(s, delim, mTags);
    }
    void fill(string const& s, const char delim = ',') {
        Utils::split(s, delim, mTags);
    }
    string toString(char separator = ',') const {
        return Utils::toString(mTags, separator);
    }
  private:
    vector<Tag> mTags;
};

struct Fact {
    Activity activity;
    Category category;
    Time start_time;
    Time end_time;
    TagsList tags;
    Description description;

    string toString() const {
        stringstream x;
        x << "|" <<  activity << "|" << category << "|"
            << to_simple_string(start_time) << "|"
            << to_simple_string(end_time) << "|"
            << tags.toString(',') << "|"
            << description << "|";
        return x.str();
    }
};
typedef vector<Fact> FactsList;
typedef std::shared_ptr<FactsList> FactsListPtr;

} // namepspace Model

#endif  // FACT_H
