#include <boost/filesystem.hpp> // exists, path
#include <iostream>             // cout
#include "ParserXML.h"    // parse
#include "Data.h"         // Data, DataListPtr
#include "Storage.h"
#include "Deamon.h"

void test_code();

int main(int argc, char* argv[])
{
    test_code();
    return 0;
}

//-----------
using boost::filesystem::path;
using boost::filesystem::exists;

<<<<<<< HEAD
const path XML_PATH("/home/grzecho/Projects/hamster-service/example/sample.xml");
=======
>>>>>>> 7d278c0... Isolated tested code in main.cpp

const path XML_PATH("/home/grzecho/Projects/hamster-service/example/sample.xml");

void test_code() {
    Storage::instance().AddCategory("Nowa kategoria 2");

    std::cout << "XML_PATH='" << XML_PATH << "'\n\n"; 

    if ( !exists( XML_PATH ) ) {
          std::cerr << "Can't find xml file!" << std::endl;
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

    // serialize
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, *list);

    // deserialize
    msgpack::unpacked msg;
    msgpack::unpack(&msg, sbuf.data(), sbuf.size());

    msgpack::object obj = msg.get();

    // you can convert object to myclass directly
    Model::Data rvec;
    obj.convert(&rvec);

    std::cout << "Count = " << rvec.size() << ". Parsed data:\n";
    for(Model::Fact const& element : rvec) {
        std::cout << element.toString() << "\n";
        std::cout << "serialized:  " << element.serializeToString() << "\n";
        Storage::instance().AddFact(element.serializeToString(), element.start_time, element.end_time, false);
    }
    std::cout << std::endl;
}
