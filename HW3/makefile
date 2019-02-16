.PHONY: clean
source = $(shell find . -name *.cpp)
objects = $(patsubst ./src/%.cpp,./build/%.o, $(source))
depends = $(patsubst ./src/%.cpp,./build/%.d, $(source))
compile = g++ -Wall -Og -std=c++11 -o $@
buildFolders = $(sort $(dir $(objects)))

hw3: $(objects) makefile
	$(compile) $(objects)

./build/%.o:./src/%.cpp | $(buildFolders)
	$(compile) -c $< -MMD -MP

$(buildFolders):
	mkdir -p $(buildFolders)

clean:
	rm -rf build
	rm -f hw3

ifneq ($(MAKECMDGOALS),clean)
-include $(depends)
endif

# This is an automatic makefile I made a while ago, it finds and builds all the
# cpp files and handles all the dependencies and whatnot for me.
