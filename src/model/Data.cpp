#include <algorithm>                                    // for_each
#include "boost/date_time/posix_time/posix_time.hpp"    // ptime_from_tm
#include <sstream>                                      // stringstream
#include "Data.h"

using std::stringstream;

namespace Model {

string Row::toString(char delim) const {
    stringstream x;
    x << delim <<  fact.activity << delim
        << fact.category << delim
        << boost::posix_time::ptime_from_tm(fact.start_time) << delim
        << boost::posix_time::ptime_from_tm(fact.end_time) << delim
        << tagstoString(tags,',') << delim
        << fact.description << delim;
    return x.str();
}

string tagstoString(const TagsList& vec, const char delim) {
    stringstream x;
    x << *(vec.begin());
    std::for_each(vec.begin()+1, vec.end(),
            [&x,delim](string const& e) { x << delim << e; } );
    return x.str();
}

TagsList& stringToTags(const string& s, const char delim, TagsList& elems) {
    stringstream ss(s);
    string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

} // namepspace Model
