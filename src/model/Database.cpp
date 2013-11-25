/*
 * Database.cpp
 *
 *  Created on: 23-11-2013
 *      Author: grzecho
 */
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <cstdlib>      // strcat
#include "Database.h"

namespace Model {

// TODO: change to boost::filesystem::path
const std::string DB_LOCATION = strcat(getenv("HOME"),
                                     "/.local/share/hamster-applet/hamster.db");

Database::Database() : Database(DB_LOCATION) {
}

Database::Database(const std::string& path){
    std::cout << "db path = " << path << std::endl;
    std::string connection =
            std::string("sqlite3:db=").append(path).append(";mode=readwrite");
    // TODO: verify that db exists
    sql.open(connection);
}

Database::~Database(){
    sql.close();
}

id Database::addCategory(const Category& name) {
    std::string search_name(name);
    boost::algorithm::to_lower(search_name);

    cppdb::statement st = sql.prepare("SELECT id "        \
                                       "FROM categories "   \
                                       "WHERE search_name=?");
    st.bind(search_name);
    id _id;
    cppdb::result r = st.row();
    if(!r.empty()) {
        r.fetch(0, _id);
        std::cout << "categories contains " << "'" << name << "'" << ", id = " << _id;
    }
    else {
        st = sql.prepare("INSERT INTO categories(name,search_name) VALUES(?,?)");
        st.bind(name)
          .bind(search_name)
          .exec();
        _id = st.last_insert_id();
        std::cout << "added " << "'" << name << "'" << " to categories, id = " << _id;
    }

    return _id;
}

id Database::addActivity(const Activity& name, id category_id){ return 0;}
id Database::addTag(const Tag& name){return 0;}
//idList Database::addTags(const TagsList& tags){}
id Database::addFact(const Fact& fact){return 0;}
//id addFact(id activity_id, const Time& start,
//              const Time& end, Description& desc);
id Database::addFactTag(const id fact_id, const idList& tag_idList){return 0;}

void Database::addData(const Data& data){}

} // namespace Model
