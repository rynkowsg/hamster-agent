#include <algorithm>                                    // for_each
#include "boost/date_time/posix_time/posix_time.hpp"    // ptime_from_tm
#include <sstream>                                      // stringstream
#include "Data.h"

using boost::posix_time::ptime_from_tm;
using boost::posix_time::to_simple_string;
using std::stringstream;

namespace Model {

string Row::toString(char delim) const {
    stringstream x;
    x << delim <<  fact.activity << delim
        << fact.category << delim
        << boost::posix_time::ptime_from_tm(fact.start_time) << delim
        << ( ( fact.end_time.is_initialized()==false ) ? "now"
                : to_simple_string( ptime_from_tm(fact.end_time.get()) ) )
        << delim << tagstoString(tags,',') << delim
        << fact.description << delim;
    return x.str();
}

string tagstoString(const TagsList& vec, const char delim) {
    stringstream x;
    std::for_each(vec.begin(), vec.end()-1,
            [&x,delim](string const& e) { x << e << delim; } );
    x << *(vec.end()-1);
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
