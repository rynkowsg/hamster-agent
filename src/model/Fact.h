#ifndef FACT_H
#define FACT_H

#include <boost/date_time/posix_time/posix_time.hpp>    // ptime, to_simple_string
#include <memory>       // shared_ptr
#include <sstream>      // stringstream
#include <string>       // string
#include <vector>       // vector

using boost::posix_time::ptime;
using boost::posix_time::to_simple_string;

namespace Model {

struct Fact {
    std::string activity;
    std::string category;
    ptime start_time;
    ptime end_time;
    std::string tags;
    std::string description;

    std::string toString() const {
        std::stringstream x;
        x << "|" <<  activity << "|" << category << "|"
            << to_simple_string(start_time) << "|"
            << to_simple_string(end_time) << "|"
            << tags << "|" << description << "|";
        return x.str();
    }
};
typedef std::vector<Fact> FactsList;
typedef std::shared_ptr<FactsList> FactsListPtr;

} // namepspace Model

#endif  // FACT_H
