/*
 * Storage.h
 *
 *  Created on: 29 lis 2013
 *      Author: grzecho
 */
#include "Hamster_proxy.hpp"


#ifndef STORAGE_H_
#define STORAGE_H_

class Storage : public org::gnome::Hamster_proxy,
                 public DBus::IntrospectableProxy,
                 public DBus::ObjectProxy
{
public:
    Storage(DBus::Connection &connection, const char *path, const char *name);
    virtual ~Storage();
    static Storage& instance();

    void ActivitiesChanged();
    void FactsChanged();
    void TagsChanged();
    void ToggleCalled();
};

#endif /* STORAGE_H_ */
