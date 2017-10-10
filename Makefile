PROG     = tp1
SRV      = server
CLI      = client
EXE     := ${PROG} ${SRV} ${CLI}

SRCDIR   = src
DOCDIR   = doc
RLSDIR   = release
MEDIADIR = media

TAG     ?= v0
RELEASE  = ${RLSDIR}/${PROG}${TAG}.tar.gz

MAIN_SOURCES  = main.cpp multimedia.cpp video.cpp movie.cpp picture.cpp
MAIN_HEADERS  =          multimedia.h   video.h   movie.h   picture.h   group.h   library.h
MAIN_SOURCES := ${MAIN_SOURCES:%=${SRCDIR}/%}
SOURCES      += ${MAIN_SOURCES}
HEADERS      += ${MAIN_HEADERS:%=${SRCDIR}/%}
MAIN_OBJECTS  = ${MAIN_SOURCES:%.cpp=%.o}
OBJECTS      += ${MAIN_OBJECTS}

CLI_SOURCES   = client.cpp cppsocket.cpp
CLI_HEADERS   =            cppsocket.h
CLI_SOURCES  := ${CLI_SOURCES:%=${SRCDIR}/%}
SOURCES      += ${CLI_SOURCES}
HEADERS      += ${CLI_HEADERS:%=${SRCDIR}/%}
CLI_OBJECTS   = ${CLI_SOURCES:%.cpp=%.o}
OBJECTS      += ${CLI_OBJECTS}

SRV_SOURCES   = server.cpp tcpserver.cpp cppsocket.cpp
SRV_HEADERS   =            tcpserver.h   cppsocket.h
SRV_SOURCES  := ${SRV_SOURCES:%=${SRCDIR}/%}
SOURCES      += ${SRV_SOURCES}
HEADERS      += ${SRV_HEADERS:%=${SRCDIR}/%}
SRV_OBJECTS   = ${SRV_SOURCES:%.cpp=%.o}
OBJECTS      += ${SRV_OBJECTS}


AUXFILES = Makefile README.md LICENSE
MEDIAF   = small.mp4 small.jpg
MEDIA    = ${MEDIAF:%=${MEDIADIR}/%}

FILES    = ${PROG} ${DOCDIR} ${SOURCES} ${HEADERS} ${AUXFILES} ${MEDIA}

CXX      = c++
CXXFLAGS = -std=c++11 -Wall -Werror -g
LDFLAGS  =
LDLIBS   = -lpthread

.PHONY: all run ${DOCDIR} ${MEDIADIR} ${RLSDIR} clean cleandist

all: ${EXE}

run: run-${PROG}
	./$<

run-%: %
	./$*

${DOCDIR}: Doxyfile
	doxygen $<

${PROG}: depend-${PROG} ${MAIN_OBJECTS}
	${CXX} -o $@ ${CXXFLAGS} ${LDFLAGS} ${MAIN_OBJECTS} ${LDLIBS}

${SRV}: depend-${SRV} ${SRV_OBJECTS}
	${CXX} -o $@ ${CXXFLAGS} ${LDFLAGS} ${SRV_OBJECTS} ${LDLIBS}

${CLI}: depend-${CLI} ${CLI_OBJECTS}
	${CXX} -o $@ ${CXXFLAGS} ${LDFLAGS} ${CLI_OBJECTS} ${LDLIBS}

clean:
	-@$(RM) ${OBJECTS} ${EXE:%=depend-%} core 1>/dev/null 2>&1

cleandist: clean
	-@$(RM) ${EXE} 1>/dev/null 2>&1
	-@$(RM) -rf ${DOCDIR} ${MEDIADIR}

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
	@${CXX} ${CXXFLAGS} -MM ${MAIN_SOURCES} > depend-${PROG}

depend-${CLI}:
	@${CXX} ${CXXFLAGS} -MM ${MAIN_SOURCES} > depend-${CLI}

depend-${SRV}:
	@${CXX} ${CXXFLAGS} -MM ${MAIN_SOURCES} > depend-${SRV}


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
