#include <boost/filesystem.hpp> // exists
#include <iostream>             // cout
#include "model/DatabaseOperation.h"
#include "model/ParserXML.h"    // parse
#include "model/Data.h"         // Data, DataListPtr

namespace fs = boost::filesystem;

const fs::path XML_PATH("example/sample.xml");

int main(int argc, char* argv[])
{
    std::cout << "XML_PATH='" << XML_PATH << "'\n\n"; 

    if ( !fs::exists( XML_PATH ) ) {
          std::cerr << "Can't find my file!" << std::endl;
    }

    Model::DataPtr list;
    try {
        list = Model::ParserXML::parse(XML_PATH);
    }
    catch(std::exception const &e) {
        std::cerr << "Parser ERROR: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Count = " << list->size() << ". Parsed data:\n";
    for(Model::Row const& element : *list) {
        std::cout << element.toString() << "\n";
    }

    return 0;
}
