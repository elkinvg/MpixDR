    ROOTFLAGS     = $(shell root-config --cflags)
    ROOTLIBS      = $(shell root-config --glibs)
    TARGET        = MPixDR
    CC            = gcc
    CXX           = g++
    LINK          = g++
    DELFILE       = @rm -f
    OBJDIR        = ./obj
    BINDIR        = ./bin
    SODIR         = ./SO
    OBJS = $(OBJDIR)/main.o $(OBJDIR)/totdataread.o
    TARGETLOC     = $(BINDIR)/$(TARGET)
    CXXFLAGS      = $(ROOTFLAGS) -MD
    CXXLIBS       = $(ROOTLIBS) libtmp_cxx.so
    
    
first: all

all: $(TARGETLOC)

$(TARGETLOC): $(OBJS)
	@if ! [ -d $(BINDIR) ] ; then $(MKDIR) $(BINDIR) ; fi
	$(LINK) $(OBJS) $(CXXLIBS) -o $(TARGETLOC)
	
####### compile
$(OBJDIR)/%.o: %.cpp
	@if ! [ -d $(OBJDIR) ] ; then $(MKDIR) $(OBJDIR) ; fi
	$(CXX) -c $(CXXFLAGS) -o $@ $<
	
clean: FORCE
	$(DELFILE) ./SO/*.so ./SO/*.so* ./obj/*.o *.h~ *.cpp~

FORCE:
