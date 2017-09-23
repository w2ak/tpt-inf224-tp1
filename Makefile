PROGNAME = tp1
PROG     = ${PROGNAME}

SRCDIR   = src
DOCDIR   = doc
RLSDIR   = release
MEDIADIR = media

RELEASE  = ${RLSDIR}/${PROGNAME}.tar.gz

MAIN     = ${SRCDIR}/main.cpp
SOURCESF = multimedia.cpp video.cpp movie.cpp picture.cpp
HEADERSF = multimedia.h   video.h   movie.h   picture.h   group.h
SOURCES := ${SOURCESF:%=${SRCDIR}/%}
HEADERS := ${HEADERSF:%=${SRCDIR}/%}
SOURCES += ${MAIN}
OBJETS   = ${SOURCES:%.cpp=%.o}

AUXFILES = Makefile README.md LICENSE
MEDIAF   = small.mp4 small.jpg
MEDIA    = ${MEDIAF:%=${MEDIADIR}/%}

FILES    = ${PROGNAME} ${DOCDIR} ${SOURCES} ${HEADERS} ${AUXFILES} ${MEDIA}

CXX      = c++
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS  =
LDLIBS   =

.PHONY: all run ${DOCDIR} ${MEDIADIR} ${RLSDIR} clean cleandist

all: ${PROG}

run: ${PROG}
	./$<

${DOCDIR}: Doxyfile
	doxygen $<

${PROG}: depend-${PROG} ${OBJETS}
	${CXX} -o $@ ${CXXFLAGS} ${LDFLAGS} ${OBJETS} ${LDLIBS}

clean:
	-@$(RM) ${OBJETS} depend-${PROG} core 1>/dev/null 2>&1

cleandist: clean
	-@$(RM) ${PROG} 1>/dev/null 2>&1
	-@$(RM) -rf ${RLSDIR} ${DOCDIR} ${MEDIADIR}

${MEDIADIR}: ${MEDIA}

${MEDIA}:
	@mkdir -p ${@D}
	curl -Ls "https://www.neze.fr/public/tpt/inf224/$@" -o $@

${RLSDIR}: ${RELEASE}

${RELEASE}: ${FILES}
	@mkdir -p ${@D}
	tar czf $@ $^

# Gestion des dependances : creation automatique des dependances en utilisant
# l'option -MM de g++ (attention tous les compilateurs n'ont pas cette option)
#
depend-${PROG}:
	@${CXX} ${CXXFLAGS} -MM ${SOURCES} > depend-${PROG}


###########################################
#
# Regles implicites
#

.SUFFIXES: .cpp .cxx .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c (CFLAGS) $(INCPATH) -o $@ $<


#############################################
#
# Inclusion du fichier des dependances
#
-include depend-${PROG}
