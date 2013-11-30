#include <boost/filesystem.hpp>                         // path
#include <boost/optional/optional.hpp>                  // optional
#include <boost/property_tree/ptree.hpp>                // ptree
#include <boost/property_tree/xml_parser.hpp>           // read_xml
#include <ctime>                                        // tm, strptime
#include <fstream>                                      // ifstream
#include <memory>                                       // make_shared
#include "Data.h"
#include "ParserXML.h"

using boost::filesystem::path;
using boost::property_tree::ptree;

namespace Model {

DataPtr ParserXML::parse( path const& filepath ) {
    ptree pt;
    std::ifstream is( filepath.string() );

    try {
        read_xml(is, pt);
    }
    catch (const boost::property_tree::ptree_bad_data& e) { // doesn't work
        std::cerr << "Exception 'ptree_bad_data': " << e.what() << std::endl;
        throw;
    }
    catch (const boost::property_tree::ptree_bad_path& e) { // doesn't work
        std::cerr << "Exception 'ptree_bad_path': " << e.what() << std::endl;
        throw;
    }
    catch (const boost::property_tree::xml_parser::xml_parser_error& ex) { // works
        std::cerr << "Error in xml file " << ex.filename() << " line " << ex.line() << std::endl;
        throw;
    }
    catch (const boost::property_tree::ptree_error& e) { // works
        std::cerr << "Exception 'ptree_error': " << e.what() << std::endl;
        throw;
    }

    DataPtr ans = std::make_shared<Data>();
    for( ptree::value_type const& v : pt.get_child("data") ) {
        if( v.first == "row" ) {
            Fact fact;
            for( ptree::value_type const& t : v.second )
            {
                if( t.first == "<xmlattr>" )
                {
                    fact.start_time = v.second.get<int>("<xmlattr>.start_time");
                    boost::optional<int> end = v.second.get_optional<int>("<xmlattr>.end_time");
                    fact.end_time = end.is_initialized() ? end.get() : 0;
                }
                else if( t.first == "activity" ) {
                    fact.activity = t.second.get<std::string>("<xmlattr>.name");
                }
                else if( t.first == "category" ) {
                    fact.category = t.second.get<std::string>("<xmlattr>.name");
                }
                else if( t.first == "tag" ) {
                    fact.tags.push_back(t.second.get<std::string>("<xmlattr>.name"));
                }
                else if( t.first == "description" ) {
                    fact.description = t.second.data();
                }
            }
            ans->push_back(fact);
        }
    }
    return ans;
}

} //namespace Model
