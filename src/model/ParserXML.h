#ifndef PARSERXML_H
#define PARSERXML_H

#include <boost/filesystem.hpp>
#include "Fact.h"
#include "Parser.h"

namespace Model {

class ParserXML {
  public:
        static FactsListPtr parse(const boost::filesystem::path& filepath);
};
    
} // namespace Model

#endif // PARSERXML_H
