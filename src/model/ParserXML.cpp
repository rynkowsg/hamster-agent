#include <boost/date_time/posix_time/posix_time.hpp>    // time_from_string
#include <boost/filesystem.hpp>                         // path
#include <boost/property_tree/ptree.hpp>                // ptree
#include <boost/property_tree/xml_parser.hpp>           // read_xml
#include <boost/foreach.hpp>                            // BOOST_FOREACH
#include <memory>                                       // make_shared
#include <fstream>                                      // ifstream
#include "Fact.h"
#include "ParserXML.h"

using boost::property_tree::ptree;
using boost::posix_time::time_from_string;

namespace Model {

FactsListPtr ParserXML::parse(const boost::filesystem::path& filepath) {
    ptree pt;
    std::ifstream is(filepath.string());
    read_xml(is, pt);

    //FactsListPtr ans = std::make_shared<FactsList>();
    //FactsListPtr ans(new FactsList());
    FactsList* ans = new FactsList(); 
    BOOST_FOREACH( ptree::value_type const& v, pt.get_child("facts") ) {
        if( v.first == "fact" ) {
            Fact f;
            f.activity = v.second.get<std::string>("activity");
            f.category = v.second.get<std::string>("category");
            f.tags = v.second.get<std::string>("tags");
            f.start_time = time_from_string( v.second.get<std::string>("start_time") );
            f.end_time = time_from_string( v.second.get<std::string>("end_time") );
            f.description = v.second.get<std::string>("description");
            std::cout << "activity = " << f.activity << "\n";
            ans->push_back(f);
        }
    }
    std::cout << "size=" << ans->size() << std::endl;
    //return ans;
    return FactsListPtr(ans);
}

} //namespace Model
