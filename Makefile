#
# GOBject Introspection Tutorial 
# 
# Written in 2013 by Simon Kågedal Reimer <skagedal@gmail.com>
#
# To the extent possible under law, the author have dedicated all
# copyright and related and neighboring rights to this software to
# the public domain worldwide. This software is distributed without
# any warranty.
#
# CC0 Public Domain Dedication:
# http://creativecommons.org/publicdomain/zero/1.0/

CC=gcc
C_INCLUDES=`pkg-config --cflags gobject-2.0 gamerzilla`
CFLAGS=$(C_INCLUDES) -g
LIBS=`pkg-config --libs gobject-2.0 gamerzilla`

PREFIX ?= /usr/local
LIBDIR=$(PREFIX)/lib$(LIB_SUFFIX)
GIRDIR=$(PREFIX)/share/gir-1.0
TYPELIBDIR=$(LIBDIR)/girepository-1.0

OBJECTS=gamerzillagobj.lo
SOURCES=gamerzillagobj.c gamerzillagobj.h 

NAMESPACE=Gamerzilla
NSVERSION=0.1
GIR_FILE=$(NAMESPACE)-$(NSVERSION).gir
TYPELIB_FILE=$(NAMESPACE)-$(NSVERSION).typelib

all: libgamerzillagobj.la $(TYPELIB_FILE)

libgamerzillagobj.la: $(OBJECTS)	
	libtool link $(CC) $(LIBS) -rpath $(LIBDIR) $(OBJECTS) -o $@ 

$(TYPELIB_FILE): $(GIR_FILE)
	g-ir-compiler $(GIR_FILE) --output=$(TYPELIB_FILE)

$(GIR_FILE): gamerzillagobj.c gamerzillagobj.h
	libtool exec g-ir-scanner $^ --library=gamerzillagobj $(C_INCLUDES) --include=GObject-2.0 --namespace=$(NAMESPACE) --nsversion=$(NSVERSION) --output=$@

gamerzillagobj.lo: gamerzillagobj.c gamerzillagobj.h
	libtool compile $(CC) $(CFLAGS) -c $< -o $@

install: all
	if test ! -d $(LIBDIR); then mkdir -p $(LIBDIR); fi
	if test ! -d $(TYPELIBDIR); then mkdir -p $(TYPELIBDIR); fi
	if test ! -d $(GIRDIR); then mkdir -p $(GIRDIR); fi
	cp -P .lib/libgamerzillagobj.so* $(LIBDIR)/
	cp Gamerzilla-0.1.gir $(GIRDIR)/
	cp Gamerzilla-0.1.typelib $(TYPELIBDIR)/

clean:
	-rm *.lo libgamerzillagobj.la $(TYPELIB_FILE) $(GIR_FILE)
	-rm -rf .libs


