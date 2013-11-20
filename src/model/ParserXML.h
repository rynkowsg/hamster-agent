#ifndef PARSERXML_H
#define PARSERXML_H

#include <boost/filesystem.hpp>     // path
#include "Data.h"
#include "Parser.h"

namespace Model {

class ParserXML {
  public:
    static DataPtr parse( boost::filesystem::path const& filepath );
};
    
} // namespace Model

#endif // PARSERXML_H
