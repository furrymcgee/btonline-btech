if BTPR_PENN
MAYBE_PENN = -I$(srcdir)/penn/include
endif

if BTPR_MUX2
MAYBE_MUX2 = -I$(srcdir)/mux2/include
endif

AM_CPPFLAGS = $(MAYBE_PENN) -I$(srcdir)/include

noinst_LTLIBRARIES = libbtpr.la

libbtpr_la_SOURCES = event.c \
	comsys.c conf.c db.c dllist.c eval.c game.c flags.c functions.c log.c \
	move.c netcommon.c player.c powers.c pqueue.c predicates.c rbtab.c \
	rbtree.c stringutil.c wild.c \
	pqueue.h include/alloc.h include/ansi.h include/attrs.h \
	include/copyright.h include/db.h include/config.h include/create.h \
	include/dllist.h include/externs.h include/flags.h include/htab.h \
	include/debug.h include/mudconf.h \
	include/muxevent.h include/powers.h \
	include/p.event.h include/p.functions.h include/rbtree.h \
	include/interface.h \
	penn/btpr_alloc.h penn/btpr_db.h penn/btpr_interface.h \
	penn/btpr_mudconf.h


check_PROGRAMS = pqtest

TESTS = pqtest

pqtest_SOURCES = tests/pqtest.c
pqtest_LDADD = libbtpr.la
