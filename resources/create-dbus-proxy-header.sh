#!/bin/sh

SERVICE_XML_PATH=service.xml
SERVICE_PROXY_PATH=source/Hamster_proxy.hpp

qdbus org.gnome.Hamster /org/gnome/Hamster org.freedesktop.DBus.Introspectable.Introspect > ${SERVICE_XML_PATH} # 2> /dev/null;
dbusxx-xml2cpp ${SERVICE_XML_PATH} --proxy=${SERVICE_PROXY_PATH} # 2> /dev/null;
rm ${SERVICE_XML_PATH};
echo created ${SERVICE_PROXY_PATH};
