#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <string>

class StringBuilder {
public:
    template<typename Type> StringBuilder(Type& arg) {
        ss << arg;
    }
    template<typename Type> StringBuilder(Type* arg) {
        ss << arg;
    }
    template<typename Type> StringBuilder& add(Type& arg) {
        ss << arg;
        return *this;
    }
    template<typename Type> StringBuilder& add(Type* arg) {
        ss << arg;
        return *this;
    }
    std::string str() const {
        return ss.str();
    }
    const char* c_str() const {
        return ss.str().c_str();
    }
private:
    std::stringstream ss;
};

#endif // UTILS_H
