#include <boost/filesystem.hpp> // exists, path
#include <iostream>             // cout
#include "model/Database.h"
#include "model/ParserXML.h"    // parse
#include "model/Data.h"         // Data, DataListPtr
#include "model/db/Storage.h"

using boost::filesystem::path;
using boost::filesystem::exists;

const path XML_PATH("example/sample.xml");
const path DB_PATH("example/hamster.db");


int main(int argc, char* argv[])
{
    Storage::instance().AddCategory("Nowa kategoria 2");


    std::cout << "XML_PATH='" << XML_PATH << "'\n\n"; 

    if ( !exists( XML_PATH ) ) {
          std::cerr << "Can't find database file!" << std::endl;
          // TODO: create/copy database file
          return 1;
    }

    Model::DataPtr list;
    try {
        list = Model::ParserXML::parse(XML_PATH);
    }
    catch(std::exception const &e) {
        std::cerr << "Oh, exception: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Count = " << list->size() << ". Parsed data:\n";
    for(Model::Fact const& element : *list) {
        std::cout << element.toString() << "\n";
        std::cout << "serialized:  " << element.serializeToString() << "\n";
        Storage::instance().AddFact(element.serializeToString(), element.start_time, element.end_time, false);
    }
    std::cout << std::endl;

    Model::Database(DB_PATH.string()).test();


    return 0;
}
