
/*
   p.template.h

   Automatically created by protomaker (C) 1998 Markus Stenberg (fingon@iki.fi)
   Protomaker is actually only a wrapper script for cproto, but well.. I like
   fancy headers and stuff :)
   */

/* Generated at Fri Jan 15 15:33:05 CET 1999 from template.c */

#ifndef _P_TEMPLATE_H
#define _P_TEMPLATE_H

/* template.c */ 
int count_special_items(void);
int compare_array(char *list[], char *command);
char *one_arg(char *argument, char *first_arg);
char *BuildBitString(char *bitdescs[], int data);
char *my_shortform(char *buf);
char *part_figure_out_shname(int i);
char *part_figure_out_name(int i);
char *part_figure_out_sname(int i);
void dump_locations(FILE * fp, MECH * mech, const char *locdesc[]);
float generic_computer_multiplier(MECH * mech);
int generic_radio_type(int i, int isClan);
float generic_radio_multiplier(MECH * mech);
void computer_conversion(MECH * mech);
void try_to_find_name(char *mechref, MECH * mech);
int DefaultFuelByType(MECH * mech);
int save_template(dbref player, MECH * mech, char *reference,

    char *filename);
char *read_desc(FILE * fp, char *data);
int find_section(char *cmd, int type, int mtype);
long BuildBitVector(char **list, char *line);
int WeaponIFromString(char *data);
int AmmoIFromString(char *data);
void update_specials(MECH * mech);
int update_oweight(MECH * mech, int value);
int get_weight(MECH * mech);
int load_template(dbref player, MECH * mech, char *filename);
void DumpMechSpecialObjects(dbref player);
void DumpWeapons(dbref player);
char *techlist_func(MECH * mech);

#endif				/* _P_TEMPLATE_H */
