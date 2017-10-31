.PHONY: all doc test

ROOTDIR:=Clement__Durand
CPPDIR:=${ROOTDIR}/cpp
SWGDIR:=${ROOTDIR}/swing
TGZ:=${ROOTDIR}.tar.gz
HSH:=${TGZ}.sha512
SIG:=${HSH}.sig
SIGNINGKEY:='0x2F1F95F7738D7D23'

all doc test media:
	make -C ${CPPDIR} $@

release: ${SIG}

${TGZ}:
	git clean -fdx
	tar czf $@ ${ROOTDIR}

${HSH}: ${TGZ}
	sha512sum $^ > $@

${SIG}: ${HSH}
	gpg2 --armor --output $@ --sign-with ${SIGNINGKEY} --detach-sign $^
