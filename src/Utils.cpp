#include <algorithm>    // for_each
#include <sstream>      // stringstream
#include <string>       // string
#include <vector>       // vector

using std::string;
using std::stringstream;
using std::vector;

namespace Utils {

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

string toString(const vector<string>& vec, const char separator) {
    stringstream x;
    x << *(vec.begin());
    std::for_each(vec.begin()+1, vec.end(),
            [&x,separator](string const& e) { x << separator << e; } );
    return x.str();
}

} // namespace Utils
