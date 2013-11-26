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
    std::cout << "DB_PATH = " << path << std::endl;
    std::string connection =
            std::string("sqlite3:db=").append(path).append(";mode=readwrite");
    // TODO: verify that db exists
    sql.open(connection);
}

Database::~Database(){
    sql.close();
}

id Database::getCategoryId(const std::string& search_name) {
    id res;
    cppdb::statement st = sql.prepare("SELECT id "           \
                                       "FROM categories "     \
                                       "WHERE search_name=?");
    st.bind(search_name);
    st.row().fetch(0,res);
    return res;
}

id Database::getActivityId(const std::string& search_name, id category_id) {
    id res;
    cppdb::statement st = sql.prepare("SELECT id "           \
                                       "FROM activities "     \
                                       "WHERE search_name=? AND category_id=?");
    st.bind(search_name).bind(category_id);
    st.row().fetch(0,res);
    return res;
}

id Database::getTagId(const std::string& name) {
    id res;
    cppdb::statement st = sql.prepare("SELECT id "           \
                                       "FROM tags "           \
                                       "WHERE name=?");
    st.bind(name);
    st.row().fetch(0,res);
    return res;
}

id Database::addCategory(const std::string& name) {
    std::string search_name(name);
    boost::algorithm::to_lower(search_name);

    id idCategory = getCategoryId(search_name);
    if(0 == idCategory) {
        cppdb::statement st = sql.prepare("INSERT INTO categories(name,search_name) VALUES(?,?)");
        st.bind(name).bind(search_name).exec();
        idCategory = st.last_insert_id();
        std::cout << "added " << "'" << name << "'" << " to categories, idCategory = " << idCategory << "\n";
    }
    else {
        std::cout << "categories contains " << "'" << name << "'" << ", idCategory = " << idCategory << "\n";
    }
    return idCategory;
}

id Database::addActivity(const std::string& name, id category_id) {
    std::string search_name(name);
    boost::algorithm::to_lower(search_name);

    id idActivity = getActivityId(search_name, category_id);
    if(0 == idActivity) {
        cppdb::statement st = sql.prepare("INSERT INTO activities(name,category_id,search_name) VALUES(?,?,?)");
        st.bind(name).bind(category_id).bind(search_name).exec();
        idActivity = st.last_insert_id();
        std::cout << "added " << "'" << name << "'" << " to activities, id = " << idActivity << "\n";
    }
    else {
        std::cout << "activities contains " << "'" << name << "'" << ", id = " << idActivity << "\n";
    }
    return idActivity;
}

id Database::addTag(const std::string& name) {
    id idTag = getTagId(name);
    if(0 == idTag) {
        cppdb::statement st = sql.prepare("INSERT INTO tags(name) VALUES(?)");
        st.bind(name).exec();
        idTag = st.last_insert_id();
        std::cout << "added " << "'" << name << "'" << " to tags, idTag = " << idTag << "\n";
    }
    else {
        std::cout << "tags contains " << "'" << name << "'" << ", idTag = " << idTag << "\n";
    }
    return idTag;
}


//idList Database::addTags(const TagsList& tags){}
//id Database::addFact(const Fact& fact){return 0;}
//id addFact(id activity_id, const Time& start,
//              const Time& end, Description& desc);
//id Database::addFactTag(const id fact_id, const idList& tag_idList){return 0;}
//void Database::addData(const Data& data){}


void Database::test()
{
//    try {
        id idCategory = addCategory("Praca");
        addActivity("Sprawdzanie korespondencji",idCategory);
        addTag("rutynowe");
//    }
//    // http://cppcms.com/sql/cppdb/query.html
//    catch(const cppdb::bad_value_cast& ){
//        // conversion fails (fetch?)
//    }
//    catch(const cppdb::null_value_fetch& ){
//        // get(): fetched value was null
//    }
//    catch(const cppdb:: multiple_rows_query& ){
//        // row(): more then one rows had been fetched
//    }
//    catch(const cppdb::empty_row_access& ){
//        // operator >> right after row manipulator: the empty result was fetched
//    }
//    catch(...)
//    {
//
//    }

}
} // namespace Model
