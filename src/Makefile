CC=g++
CXXFLAGS+=-std=c++0x

main: main.cpp
	$(CC) $(CXXFLAGS) -o $@ $^
	@echo "run the program:"
	@./main
	@echo "\n"
	@rm main
	
clean:
	rm -f *.o main a.out

print-vars:
	@echo CC is \'$(CC)\'
	@echo CXXFLAGS is \'$(CXXFLAGS)\'
	
