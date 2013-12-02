CXX=g++
CXXFLAGS+=-std=c++11 -Wall -Werror -pedantic -g
CXXFLAGS+=-I$(HDIR) $(shell pkg-config dbus-c++-1 --cflags)
LDFLAGS+=-lboost_filesystem -lboost_date_time -lboost_system
LDFLAGS+=-lcppdb -lcppdb_sqlite3
LDFLAGS+=-lmsgpack $(shell pkg-config dbus-c++-1 --libs)

HDIR=include
SRCDIR=src
OBJDIR=obj
DEPSDIR=deps
SERVICE_XML_PATH=service.xml
SERVICE_PROXY_PATH=$(HDIR)/Hamster_proxy.hpp

vpath %.h $(HDIR)
vpath %.cpp $(SRCDIR)

prog = main
src = $(notdir $(shell find $(SRCDIR) -name "*.cpp"))
objects = $(patsubst %.cpp,$(OBJDIR)/%.o,$(src))
deps = $(patsubst %.cpp,$(DEPSDIR)/%.d,$(src))
headers = $(notdir $(shell find $(HDIR) -name "*.h"))

all: $(prog) $(objects)

$(prog): $(objects) Makefile
	@$(CXX) $(objects) $(LDFLAGS) -o $(prog); \
	echo $@

$(DEPSDIR)/%.d: %.cpp Makefile | $(DEPSDIR) dbus_prepare
	@set -e; \
	rm -f $@; $(CXX) $(CXXFLAGS) -MM $< > $@.dd;\
	sed 's,\($*\)\.o[ :]*,$(OBJDIR)/\1.o $@ : ,g' < $@.dd > $@; \
	rm $@.dd;\
	echo $@
-include $(src:%.cpp=$(DEPSDIR)/%.d)

$(OBJDIR)/%.o: %.cpp $(DEPSDIR)/%.d Makefile
	@$(CXX) -c $< -o $@ $(CXXFLAGS); \
	echo $@

$(objects): | $(OBJDIR)

$(DEPSDIR) $(OBJDIR):
	@mkdir -p $@; \
	echo created: $@

dbus_prepare:
	@test -s $(SERVICE_PROXY_PATH) || { \
		qdbus org.gnome.Hamster /org/gnome/Hamster org.freedesktop.DBus.Introspectable.Introspect > $(SERVICE_XML_PATH) 2> /dev/null; \
		dbusxx-xml2cpp $(SERVICE_XML_PATH) --proxy=$(SERVICE_PROXY_PATH) 2> /dev/null; \
		rm $(SERVICE_XML_PATH); \
		echo created $(SERVICE_PROXY_PATH); \
	}

clean:
	-@$(RM) -rf $(prog) $(objects) 2> /dev/null; \
	$(RM) -rf $(DEPSDIR) 2> /dev/null
#	$(RM) $(SERVICE_PROXY_PATH) 2> /dev/null;

print:
	@echo "prog      ="\'$(prog)\'
	@echo "src       ="\'$(src)\'
	@echo "objects   ="\'$(objects)\'
	@echo "deps      ="\'$(deps)\'
	@echo "headers   ="\'$(headers)\'
	@echo $(objects:$(OBJDIR)/Storage.o=)
	@echo $(src:%.cpp=$(DEPSDIR)/%.d)
	@echo -----------------

.PHONY: all clean dbus_prepare print
