
/*
   p.db_rw.h

   Automatically created by protomaker (C) 1998 Markus Stenberg (fingon@iki.fi)
   Protomaker is actually only a wrapper script for cproto, but well.. I like
   fancy headers and stuff :)
   */

/* Generated at Thu Mar 11 17:43:44 CET 1999 from db_rw.c */

#ifndef _P_DB_RW_H
#define _P_DB_RW_H

/* db_rw.c */
dbref db_read(FILE * f, int *db_format, int *db_version, int *db_flags);
dbref db_write(FILE * f, int format, int version);

#endif				/* _P_DB_RW_H */
