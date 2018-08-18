#CC=gcc
#CXX=g++

Cflags=-c -MD
CXXflags=-c -MD --std=c++11
LDflags=

Input=cli.cpp
ObjDir=obj
BinDir=lib

Name=cli++
Output=lib$(Name).a

PREFIX=/usr/local

Objects=$(addprefix $(ObjDir)/,$(addsuffix .o, $(Input)))

all: makedirs makelibs $(BinDir)/$(Output)

.PHONY: makedirs
makedirs: $(ObjDir)/ $(BinDir)/

%/:
	mkdir -p $@

makelibs:
#	make -C ...

$(BinDir)/$(Output): $(Objects)
	ar rvc -o $(BinDir)/$(Output) $(Objects) $(LDflags)

obj/%.c.o: %.c
	$(CC) $(Cflags) -o $@ $<

obj/%.cpp.o: %.cpp
	$(CXX) $(CXXflags) -o $@ $<

-include $(ObjDir)/*.d

.IGNORE: clean
clean:
	rm $(ObjDir)/*
	rm $(BinDir)/$(Output)

.PHONY: install
install: $(BinDir)/$(Output)
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	cp $< $(DESTDIR)$(PREFIX)/lib/$(Output)
	mkdir -p $(DESTDIR)$(PREFIX)/include/$(Name)
	cp *.h $(DESTDIR)$(PREFIX)/include/$(Name)

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib/$(Output)
	rm -rf $(DESTDIR)$(PREFIX)/include/$(Name)
