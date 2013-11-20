#ifndef UTILS_H
#define UTILS_H

#include <string>       // string
#include <vector>       // vector

using std::string;
using std::vector;

namespace Utils {

vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);
string toString(const vector<string>& vec, const char separator);

} // namespace Utils

#endif  // UTILS_H
