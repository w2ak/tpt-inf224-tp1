.PHONY: all doc test

ROOTDIR:=Clement__Durand
CPPDIR:=${ROOTDIR}/cpp
SWGDIR:=${ROOTDIR}/swing
TGZ:=${ROOTDIR}.tar.gz

all doc test:
	make -C ${CPPDIR} $@

release: ${TGZ}

${TGZ}:
	git clean -fdx
	tar czf $@ ${ROOTDIR}
