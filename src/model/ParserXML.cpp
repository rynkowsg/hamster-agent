#include <boost/filesystem.hpp>                         // path
#include <boost/property_tree/ptree.hpp>                // ptree
#include <boost/property_tree/xml_parser.hpp>           // read_xml
#include <ctime>                                        // tm, strptime
#include <fstream>                                      // ifstream
#include <memory>                                       // make_shared
#include "Data.h"
#include "ParserXML.h"

using boost::filesystem::path;
using boost::property_tree::ptree;

const char* time_format = "%Y-%m-%d %H:%M:%S";

namespace Model {

DataPtr ParserXML::parse( path const& filepath ) {
    ptree pt;
    std::ifstream is( filepath.string() );
    read_xml(is, pt);

    DataPtr ans = std::make_shared<Data>();
    for( ptree::value_type const& v : pt.get_child("data") ) {
        if( v.first == "row" ) {
            Row row;
            row.fact.activity = v.second.get<std::string>("activity");
            row.fact.category = v.second.get<std::string>("category");
            strptime(v.second.get<std::string>("start_time").c_str(),
                    time_format, &row.fact.start_time);
            strptime(v.second.get<std::string>("end_time").c_str(),
                    time_format, &row.fact.end_time);
            row.fact.description = v.second.get<std::string>("description");
            stringToTags(v.second.get<std::string>("tags"), ',', row.tags);
            ans->push_back(row);
        }
    }
    return ans;
}

} //namespace Model
