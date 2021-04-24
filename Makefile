CXX= g++
CPPFLAGS= -std=c++03 -Wall -Wextra -O0 -g

SOURCEDIR = ./src
BUILDDIR = ./build

BINARIES= yamp.out
SOURCESPURE= main.cpp lex.cpp synt.cpp

SOURCES = $(patsubst %, $(SOURCEDIR)/%, $(SOURCESPURE))
OBJS=$(patsubst %.cpp, $(BUILDDIR)/%.o, $(SOURCESPURE))


all: $(BINARIES)

$(BUILDDIR)/deps.mk: $(SOURCES)
	mkdir -p $(BUILDDIR)
	rm -f $@
	$(CC) -MM $^ >> $@

include $(BUILDDIR)/deps.mk

yamp.out: $(OBJS)
	$(CXX) $(CPPFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c $^ -o $@ 

run: md.out
	./md.out

clean:
	rm -f $(BUILDDIR)/*.o

distclean: clean
	rm -rf $(BUILDDIR)
	rm -f $(BINARIES)

#include $(SOURCES:%.c=%.d)
