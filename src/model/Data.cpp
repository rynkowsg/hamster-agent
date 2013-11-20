#include <boost/date_time/posix_time/posix_time.hpp>    // to_simple_string
#include <sstream>      // stringstream
#include <string>       // string
#include "../Utils.h"   // split, toString
#include "Data.h"

using boost::posix_time::to_simple_string;

namespace Model {

TagsList::TagsList(string const& s, char delim) {
    Utils::split(s, delim, mTags);
}

void TagsList::fill(string const& s, char delim) {
    Utils::split(s, delim, mTags);
}

string TagsList::toString(char delim) const {
    return Utils::toString(mTags, delim);
}

string Row::toString(char delim) const {
    std::stringstream x;
    x << delim <<  fact.activity << delim
        << fact.category << delim
        << to_simple_string(fact.start_time) << delim
        << to_simple_string(fact.end_time) << delim
        << tags.toString(',') << delim
        << fact.description << delim;
    return x.str();
}

} // namepspace Model
