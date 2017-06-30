.PHONY: all clean

all: sample

STDC_CXXFLAGS = -std=c++11
#STD_CXXFLAGS = -std=c++14

#DEBUG_CXXFLAGS =
DEBUG_CXXFLAGS = -DDEBUG_MODIFIED_THOMPSON_TAU

CXXFLAGS = $(STDC_CXXFLAGS) $(DEBUG_CXXFLAGS)

OBJS = modified_thompson_tau.o

sample: sample.o $(OBJS)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

modified_thompson_tau.o: modified_thompson_tau.hh tau_table/tau_table.hh

tau_table/tau_table.hh:
	$(MAKE) -C tau_table

clean:
	$(MAKE) -C tau_table clean
	-rm -f *~ *.o
