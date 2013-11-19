#ifndef PARSER_H
#define PARSER_H

#include "Fact.h"
#include <boost/filesystem.hpp>

namespace Model {

class Parser {
  public:
    static FactsListPtr parse( boost::filesystem::path const& filepath );
};
    
} // namespace Model

#endif  // PARSER_H
