CC=g++
CXXFLAGS+=-std=c++11 -Wall -pedantic -g
LDFLAGS+=-lboost_filesystem -lboost_date_time -lboost_system
#LDFLAGS+=/usr/local/lib64/libcppdb.a /usr/local/lib64/libcppdb_sqlite3.a -lpthread -ldl -lsqlite3
LDFLAGS+=-lcppdb -lcppdb_sqlite3
vpath %.cpp src src/model

prog = obj/main

src = main.cpp
model_src = Data.cpp ParserXML.cpp Database.cpp

objects = $(patsubst %.cpp,obj/%.o,$(src))
model_objects = $(patsubst %.cpp,obj/%.o,$(model_src))

all: $(prog) $(model_objects) $(objects)

$(prog): $(model_objects) $(objects) src/model/Data.h src/model/Database.h src/model/ParserXML.h
	$(CXX) $(model_objects) $(objects) $(LDFLAGS) -o $(prog)

obj/%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(objects) $(model_objects): | obj
$(model_objects): $(addprefix src/model/,$(notdir $(model_objects:%.o=%.h)))
obj/ParserXML.o: src/model/Data.h
obj/Database.o: src/model/Database.h

obj:
	mkdir -p $@

.PHONY: clean
clean:
	-@$(RM) -rf $(objects) $(model_objects) $(prog) 2> /dev/null

print:
	@echo "CC      ="\'$(CC)\'
	@echo "CXXFLAGS="\'$(CXXFLAGS)\'
	@echo "LDFLAGS ="\'$(LDFLAGS)\'
	@echo "prog         = "$(prog)
	@echo "src          = "$(src)
	@echo "model_src    = "$(model_src)
	@echo "objects      = "$(objects)
	@echo "model_objects= "$(model_objects)
	@echo -----------------
