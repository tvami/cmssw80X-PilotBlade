include Makefile.arch

PILOTLSHISTOMAKERO      = PilotLSHistoMaker.$(ObjSuf)
PILOTLSHISTOMAKERS      = PilotLSHistoMaker.$(SrcSuf)
PILOTLSHISTOMAKER       = PilotLSHistoMaker$(ExeSuf)

OBJS          += $(PILOTLSHISTOMAKERO)
PROGRAMS      += $(PILOTLSHISTOMAKER)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all:            $(PROGRAMS)

$(PILOTLSHISTOMAKER):     $(PILOTLSHISTOMAKERO)
		$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt)$@
		$(MT_EXE)
		@echo "$@ done"

clean:
		@rm -f $(OBJS) core

distclean:      clean
		@rm -f $(PROGRAMS) *Dict.* *.def *.exp \
		   *.root *.ps *.so *.lib *.dll *.d *.log .def so_locations
		@rm -rf cxx_repository

.SUFFIXES: .$(SrcSuf)

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

