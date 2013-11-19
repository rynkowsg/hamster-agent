CC=g++
CXXFLAGS+=-std=c++0x -Wall
LDFLAGS=-lboost_system -lboost_date_time -lboost_filesystem
INC=-Imodel

main: main.cpp ParserXML.o
	$(CC) $(CXXFLAGS) $(INC) $^ $(LDFLAGS) -o $@
	@echo "-------------------------------------------"
	@./main
	@echo "\n"

ParserXML.o: model/ParserXML.cpp
	$(CC) $(CXXFLAGS) $(INC) -c $< $(LDFLAGS) -o $@

clean:
	@rm -f *.o main a.out

print-vars:
	@echo CC is \'$(CC)\'
	@echo CXXFLAGS is \'$(CXXFLAGS)\'
	
