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
    OBJS          = $(OBJDIR)/main.o 
#    $(OBJDIR)/totdataread.o
    TARGETLOC     = $(BINDIR)/$(TARGET)
    CXXFLAGS      = $(ROOTFLAGS) -MD
    CXXLIBS       = $(ROOTLIBS)
    ROOTSO        = totdataread_cpp.so
    
first: all

all: $(TARGETLOC)

$(TARGETLOC): $(OBJS) $(BINDIR)/$(ROOTSO)
	@if ! [ -d $(BINDIR) ] ; then $(MKDIR) $(BINDIR) ; fi
	$(LINK) $(OBJS) $(BINDIR)/$(ROOTSO) $(CXXLIBS) -o $(TARGETLOC)
	
####### compile
$(OBJDIR)/%.o: %.cpp
	@if ! [ -d $(OBJDIR) ] ; then $(MKDIR) $(OBJDIR) ; fi
	$(CXX) -c $(CXXFLAGS) -o $@ $<
	
########### root-cint compile
#rootcint: $(BINDIR)/$(ROOTSO)
#	@if ! [ -d $(SODIR) ] ; then $(MKDIR) $(SODIR) ; fi
$(BINDIR)/$(ROOTSO):
	root makeroot.C
	@mv $(ROOTSO) $(BINDIR)
	
clean: FORCE
	$(DELFILE) ./SO/*.so ./SO/*.so* ./bin/*so ./obj/*.o *.h~ *.cpp~ *.d

FORCE:
