#ifndef PARSER_H
#define PARSER_H

#include <boost/filesystem.hpp>     // path
#include "Data.h"

namespace Model {

class Parser {
  public:
    static DataPtr parse( boost::filesystem::path const& filepath );
};
    
} // namespace Model

#endif  // PARSER_H
