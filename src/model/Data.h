#ifndef FACT_H
#define FACT_H

#include <boost/date_time/posix_time/posix_time.hpp>    // ptime
#include <memory>       // shared_ptr
#include <string>       // string
#include <vector>       // vector

using boost::posix_time::ptime;
using std::string;
using std::vector;

namespace Model {

typedef string Activity;
typedef string Category;
typedef string Description;
typedef ptime Time;

struct Fact {
    Activity activity;
    Category category;
    Time start_time;
    Time end_time;
    Description description;
};

typedef string Tag;
class TagsList
{
  public:
    TagsList() : mTags() {}
    TagsList(string const& s, char delim = ',');

    void fill(string const& s, char delim = ',');
    inline string toString(char delim = ',') const;

  private:
    vector<Tag> mTags;
};

struct Row {
    Fact fact;
    TagsList tags;

    string toString(char delim = '|') const;
};
typedef vector<Row> Data;
typedef std::shared_ptr<Data> DataPtr;

} // namepspace Model

#endif  // FACT_H
