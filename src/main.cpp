#include <boost/filesystem.hpp>
#include <iostream>
#include "model/ParserXML.h"
#include <algorithm>

namespace fs = boost::filesystem;
using std::for_each;

const fs::path XML_PATH("../example/sample.xml");

int main(int argc, char* argv[])
{
    std::cout << "It's the beginning of this project ;)" << std::endl;

    if ( !fs::exists( XML_PATH ) )
    {
          std::cerr << "Can't find my file!" << std::endl;
    }
    Model::FactsListPtr list = Model::ParserXML::parse(XML_PATH);
    for(Model::Fact f : *list) {
        std::cout << f.activity << "\n";
    }
    std::cout << "length = " << list->size() << std::endl;


    return 0;
}
