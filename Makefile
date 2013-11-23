CC=g++
CXXFLAGS+=-std=c++0x -Wall -pedantic
LDFLAGS+=-lboost_filesystem -lboost_date_time -lboost_system

vpath %.cpp src src/model

prog = obj/main

src = main.cpp Utils.cpp
model_src = Data.cpp ParserXML.cpp

objects = $(patsubst %.cpp,obj/%.o,$(src))
model_objects = $(patsubst %.cpp,obj/%.o,$(model_src))

all: $(prog) $(model_objects) $(objects)

$(prog): $(model_objects) $(objects) src/model/Data.h src/model/DatabaseOperation.h src/model/ParserXML.h
#	@echo Linking $(prog)...
	$(CXX) $(model_objects) $(objects) $(LDFLAGS) -o $(prog)
	@echo "-------------------------------------------"
	@./$(prog)
	@echo "\n"
#	@rm $(prog)

obj/%.o : %.cpp
#	@echo $<
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(objects) $(model_objects): | obj
$(model_objects): $(addprefix src/model/,$(notdir $(model_objects:%.o=%.h)))
obj/ParserXML.o: src/model/Data.h
obj/Utils.o: src/Utils.h
obj/Data.o: src/Utils.h

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
