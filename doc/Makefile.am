################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
MAN1 = zgtask_tester.1 zgtask.1 zgtask_cli.1 zgtask_rdr.1 zgtask_wk.1
MAN3 = zgtask_task.3 zgtask_packet.3 zgtask_net.3 zgtask_client.3 zgtask_redirector.3 zgtask_worker.3 zgtask_tree.3
MAN7 = 
MAN_DOC = $(MAN1) $(MAN3) $(MAN7)

MAN_TXT = $(MAN1:%.1=%.txt)
MAN_TXT += $(MAN3:%.3=%.txt)
MAN_TXT += $(MAN7:%.7=%.txt)

EXTRA_DIST = asciidoc.conf $(MAN_TXT)

if INSTALL_MAN
dist_man_MANS = $(MAN_DOC)
endif

if BUILD_DOC
MAINTAINERCLEANFILES = $(MAN_DOC)

dist-hook : $(MAN_DOC)

SUFFIXES=.txt .xml .1 .3 .7

.txt.xml:
	asciidoc -d manpage -b docbook -f $(srcdir)/asciidoc.conf \
        -azgtask_version=@PACKAGE_VERSION@ -o$@ $<
.xml.1:
	xmlto man $<
.xml.3:
	xmlto man $<
.xml.7:
	xmlto man $<

zgtask_task.txt:
	zproject_mkman $@
zgtask_packet.txt:
	zproject_mkman $@
zgtask_net.txt:
	zproject_mkman $@
zgtask_client.txt:
	zproject_mkman $@
zgtask_redirector.txt:
	zproject_mkman $@
zgtask_worker.txt:
	zproject_mkman $@
zgtask_tree.txt:
	zproject_mkman $@
zgtask_tester.txt:
	zproject_mkman $@
zgtask.txt:
	zproject_mkman $@
zgtask_cli.txt:
	zproject_mkman $@
zgtask_rdr.txt:
	zproject_mkman $@
zgtask_wk.txt:
	zproject_mkman $@
clean:
	rm -f *.1 *.3
	zproject_mkman zgtask_task zgtask_packet zgtask_net zgtask_client zgtask_redirector zgtask_worker zgtask_tree zgtask_tester zgtask zgtask_cli zgtask_rdr zgtask_wk 
endif
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
