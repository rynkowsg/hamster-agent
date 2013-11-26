#include <boost/filesystem.hpp> // exists, path
#include <iostream>             // cout
#include "model/Database.h"
#include "model/ParserXML.h"    // parse
#include "model/Data.h"         // Data, DataListPtr

using boost::filesystem::path;
using boost::filesystem::exists;

const path XML_PATH("example/sample.xml");
const path DB_PATH("example/hamster.db");


int main(int argc, char* argv[])
{
    std::cout << "XML_PATH='" << XML_PATH << "'\n\n"; 

    if ( !exists( XML_PATH ) ) {
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
    std::cout << std::endl;

    Model::Database(DB_PATH.string()).test();


    return 0;
}
