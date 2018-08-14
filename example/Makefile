CC=gcc
CXX=g++
LD=g++

Cflags=-c -MD
CXXflags=-c -MD --std=c++11
LDflags=-lcli++

Input=main.cpp
ObjDir=obj
BinDir=bin
Output=example

Objects=$(addprefix $(ObjDir)/,$(addsuffix .o, $(Input)))

all: makedirs makelibs $(BinDir)/$(Output)
	cd $(BinDir); ./$(Output)

.PHONY: makedirs
makedirs: $(ObjDir)/ $(BinDir)/

%/:
	mkdir -p $@

makelibs:
	#make -C ..

$(BinDir)/$(Output): $(Objects)
	$(LD) -o $(BinDir)/$(Output) $(Objects) $(LDflags)

obj/%.c.o: %.c
	$(CC) $(Cflags) -o $@ $<

obj/%.cpp.o: %.cpp
	$(CXX) $(CXXflags) -o $@ $<

-include $(ObjDir)/*.d

.IGNORE: clean
clean:
	rm $(ObjDir)/*
	rm $(BinDir)/$(Output)
