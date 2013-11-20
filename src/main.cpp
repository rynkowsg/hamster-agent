#include <boost/filesystem.hpp>
#include <iostream>
#include "model/ParserXML.h"
#include <algorithm>

namespace fs = boost::filesystem;
using std::for_each;

const fs::path XML_PATH("../example/sample.xml");

int main(int argc, char* argv[])
{
    std::cout << "XML_PATH='" << XML_PATH << "'\n\n"; 

    if ( !fs::exists( XML_PATH ) ) {
          std::cerr << "Can't find my file!" << std::endl;
    }
    Model::FactsListPtr list = Model::ParserXML::parse(XML_PATH);

    std::cout << "Count = " << list->size() << ". List of facts:\n";
    for(Model::Fact const& f : *list) {
        std::cout << f.toString() << "\n";
    }


    return 0;
}
