#include <boost/date_time/posix_time/posix_time.hpp>    // time_from_string
#include <boost/filesystem.hpp>                         // path
#include <boost/property_tree/ptree.hpp>                // ptree
#include <boost/property_tree/xml_parser.hpp>           // read_xml
#include <memory>                                       // make_shared
#include <fstream>                                      // ifstream
#include "Data.h"
#include "ParserXML.h"

using boost::filesystem::path;
using boost::posix_time::time_from_string;
using boost::property_tree::ptree;

namespace Model {

DataPtr ParserXML::parse( path const& filepath ) {
    ptree pt;
    std::ifstream is( filepath.string() );
    read_xml(is, pt);

    DataPtr ans = std::make_shared<Data>();
    for( ptree::value_type const& v : pt.get_child("data") ) {
        if( v.first == "row" ) {
            Row row;
            row.fact.activity = v.second.get<Activity>("activity");
            row.fact.category = v.second.get<Category>("category");
            row.fact.start_time = time_from_string(
                    v.second.get<std::string>("start_time") );
            row.fact.end_time = time_from_string(
                    v.second.get<std::string>("end_time") );
            row.fact.description = v.second.get<Description>("description");
            row.tags.fill( v.second.get<Tag>("tags") );
            ans->push_back(row);
        }
    }
    return ans;
}

} //namespace Model
