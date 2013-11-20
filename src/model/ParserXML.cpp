#include <boost/date_time/posix_time/posix_time.hpp>    // time_from_string
#include <boost/filesystem.hpp>                         // path
#include <boost/property_tree/ptree.hpp>                // ptree
#include <boost/property_tree/xml_parser.hpp>           // read_xml
#include <boost/foreach.hpp>                            // BOOST_FOREACH
#include <memory>                                       // make_shared
#include <fstream>                                      // ifstream
#include "Fact.h"
#include "ParserXML.h"

using boost::filesystem::path;
using boost::posix_time::time_from_string;
using boost::property_tree::ptree;

namespace Model {

FactsListPtr ParserXML::parse( path const& filepath ) {
    ptree pt;
    std::ifstream is( filepath.string() );
    read_xml(is, pt);

    FactsListPtr ans = std::make_shared<FactsList>();
    BOOST_FOREACH( ptree::value_type const& v, pt.get_child("facts") ) {
        if( v.first == "fact" ) {
            Fact f;
            f.activity = v.second.get<Activity>("activity");
            f.category = v.second.get<Category>("category");
            f.tags.fill( v.second.get<Tag>("tags") );
            f.start_time = time_from_string( v.second.get<std::string>("start_time") );
            f.end_time = time_from_string( v.second.get<std::string>("end_time") );
            f.description = v.second.get<Description>("description");
            ans->push_back(f);
        }
    }
    return ans;
}

} //namespace Model
