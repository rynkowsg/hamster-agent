#include <boost/filesystem.hpp> // exists, path
#include <iostream>             // cout
#include "ParserXML.h"    // parse
#include "Data.h"         // Data, DataListPtr
#include "Storage.h"
#include "Daemon.hpp"
#include "config.h"

void test_code();
void processForMethod1();
void processForMethod2(bool (*exit)(), int sleep_seconds);

int main(int argc, char* argv[])
{
//    test_code();

//    Daemon(PROGRAM_NAME).demonize(processForMethod2);
    Daemon(PROGRAM_NAME).demonize(processForMethod1);

    return 0;
}


//-----------
using boost::filesystem::path;
using boost::filesystem::exists;

const path XML_PATH("/home/grzecho/Projects/hamster-service/example/sample.xml");

void test_code() {
    Storage::instance().AddCategory("Nowa kategoria 2");

    std::cout << "XML_PATH='" << XML_PATH << "'\n\n"; 

    if ( !exists( XML_PATH ) ) {
          std::cerr << "Can't find xml file!" << std::endl;
          // TODO: create/copy database file
          exit(1);
    }

    Model::DataPtr list;
    try {
        list = Model::ParserXML::parse(XML_PATH);
    }
    catch(std::exception const &e) {
        std::cerr << "Oh, exception: " << e.what() << std::endl;
        exit(1);
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

void processForMethod1() {
    // staff to do
    printf("I am working [method 1]\n");
}

void processForMethod2(bool (*exit)(), int sleep_seconds) {
    if(!exit)
        throw std::runtime_error("exit() method equals null it causes infinite loop");
    else
        while(!exit()) {
            printf("I am working [method 2]\n");
            sleep(sleep_seconds);    //Sleep for 60 seconds
        }
}
