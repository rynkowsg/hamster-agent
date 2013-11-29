/*
 * Storage.cpp
 *
 *  Created on: 29 lis 2013
 *      Author: grzecho
 */

#include "Storage.h"

Storage::Storage(DBus::Connection &connection, const char *path, const char *name)
        : DBus::ObjectProxy(connection, path, name){
    // TODO Auto-generated constructor stub

}

Storage::~Storage() {
    // TODO Auto-generated destructor stub
}

Storage& Storage::instance() {
    static DBus::BusDispatcher dispatcher;
    DBus::default_dispatcher = &dispatcher;
    DBus::Connection bus = DBus::Connection::SessionBus();
    static Storage inst(bus, "/org/gnome/Hamster", "org.gnome.Hamster");
    return inst;
}

void Storage::ActivitiesChanged() {
}

void Storage::FactsChanged() {
}

void Storage::TagsChanged() {
}

void Storage::ToggleCalled() {
}

