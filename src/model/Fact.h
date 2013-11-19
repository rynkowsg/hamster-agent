#ifndef FACT_H
#define FACT_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <memory>
#include <string>
#include <vector>

namespace Model {

struct Fact {
    std::string activity;
    std::string category;
    boost::posix_time::ptime start_time;
    boost::posix_time::ptime end_time;
    std::string tags;
    std::string description;
};
typedef std::vector<Fact> FactsList;
typedef std::shared_ptr<FactsList> FactsListPtr;

} // namepspace Model

#endif  // FACT_H
