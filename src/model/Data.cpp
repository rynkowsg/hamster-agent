#include <algorithm>                                    // for_each
#include "boost/date_time/posix_time/posix_time.hpp"    // ptime_from_tm, to_simple_string
#include <sstream>                                      // stringstream
#include "Data.h"

using boost::posix_time::from_time_t;
using boost::posix_time::to_simple_string;
using std::stringstream;

namespace Model {

string Fact::toString(char delim) const {
    stringstream x;
    x << delim <<  activity << delim
        << category << delim
        << to_simple_string(from_time_t(start_time)) << delim
        << (end_time==0 ? "now"
                : to_simple_string(from_time_t(end_time))) << delim
        << tagstoString(tags,',') << delim
        << description << delim;
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

string Fact::serializeToString() const {
    stringstream ss;
    ss << activity << "@" << category;
    if(!description.empty() || !tags.empty())
        ss << "," << description << " #" << tagstoString(tags, '#');

    return ss.str();
}

} // namepspace Model
