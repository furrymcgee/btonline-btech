
/* externs.h - Prototypes for externs not defined elsewhere */

/* $Id: externs.h,v 1.6 2005/08/08 10:30:11 murrayma Exp $ */

#include "config.h"
#include "copyright.h"

#ifndef __EXTERNS__H
#define	__EXTERNS__H

#include "db.h"
#include "mudconf.h"
#include "regexp.h"

#ifndef _DB_C
#define INLINE
#else				/* _DB_C */
#ifdef __GNUC__
#define INLINE inline
#else				/* __GNUC__ */
#define INLINE
#endif				/* __GNUC__ */
#endif				/* _DB_C */

#define ToUpper(C)	(((C) >= 'a' && (C) <= 'z')? (C) - 'a' + 'A': (C))
#define ToLower(C)	(((C) >= 'A' && (C) <= 'Z')? (C) - 'A' + 'a': (C))
#define safe_atoi(s)	((s == NULL) ? 0 : atoi(s))

/* From regexp.c (extract from Henry Spencer's package) */

extern regexp *regcomp(char *);
extern int regexec(register regexp *, register char *);
extern void regerror(char *);
extern char regexp_errbuf[];

/* From conf.c */
extern int cf_modify_bits(int *, char *, long, dbref, char *);

/* From mail.c*/
extern int load_mail(FILE *);
extern int dump_mail(FILE *);
extern void mail_init(void);
extern struct mail *mail_fetch(dbref, int);

/* From udb_achunk.c */
extern int dddb_close(void);
extern int dddb_setfile(char *);
extern int dddb_init(void);

/* From netcommon.c */
void choke_player(dbref);
void release_player(dbref);
extern void raw_notify_html(dbref, const char *);
extern void make_ulist(dbref, char *, char **);
extern int fetch_idle(dbref);
extern int fetch_connect(dbref);
extern void raw_broadcast(int, char *, ...);
extern int desc_cmp(void *, void *, void *);

/* From cque.c */
extern int nfy_que(dbref, int, int, int);
extern int halt_que(dbref, dbref);
extern void wait_que(dbref, dbref, int, dbref, int, char *, char *[], int, char *[]);
extern int que_next(void);
extern int do_top(int ncmds);
extern void recover_queue_deposits(void);

/* From eval.c */
extern void tcache_init(void);
extern char *parse_to(char **, char, int);
extern char *parse_arglist(dbref, dbref, char *, char, int, char *[], int, char *[], int);
extern int get_gender(dbref);
extern void exec(char *, char **, int, dbref, dbref, int, char **, char *[], int);

/* From game.c */
#define	notify(p,m)			notify_checked(p,p,m, \
						MSG_PUP_ALWAYS|MSG_ME_ALL|MSG_F_DOWN)
#define notify_html(p,m)                notify_checked(p,p,m, \
                                              MSG_PUP_ALWAYS|MSG_ME_ALL|MSG_F_DOWN|MSG_HTML)
#define	notify_quiet(p,m)		notify_checked(p,p,m, \
						MSG_PUP_ALWAYS|MSG_ME)
#define	notify_with_cause(p,c,m)	notify_checked(p,c,m, \
						MSG_PUP_ALWAYS|MSG_ME_ALL|MSG_F_DOWN)
#define notify_with_cause_html(p,c,m)   notify_checked(p,c,m, \
                                              MSG_PUP_ALWAYS|MSG_ME_ALL|MSG_F_DOWN|MSG_HTML)
#define	notify_quiet_with_cause(p,c,m)	notify_checked(p,c,m, \
						MSG_PUP_ALWAYS|MSG_ME)
#define	notify_puppet(p,c,m)		notify_checked(p,c,m, \
						MSG_ME_ALL|MSG_F_DOWN)
#define	notify_quiet_puppet(p,c,m)	notify_checked(p,c,m, \
						MSG_ME)
#define	notify_all(p,c,m)		notify_checked(p,c,m, \
						MSG_ME_ALL|MSG_NBR_EXITS|MSG_F_UP|MSG_F_CONTENTS)
#define	notify_all_from_inside(p,c,m)	notify_checked(p,c,m, \
						MSG_ME_ALL|MSG_NBR_EXITS_A|MSG_F_UP|MSG_F_CONTENTS|MSG_S_INSIDE)
#define notify_all_from_inside_html(p,c,m)      notify_checked(p,c,m, \
                                              MSG_ME_ALL|MSG_NBR_EXITS_A|MSG_F_UP|MSG_F_CONTENTS|MSG_S_INSIDE|MSG_HTML)
#define	notify_all_from_outside(p,c,m)	notify_checked(p,c,m, \
						MSG_ME_ALL|MSG_NBR_EXITS|MSG_F_UP|MSG_F_CONTENTS|MSG_S_OUTSIDE)
extern void notify_except(dbref, dbref, dbref, const char *);
extern void notify_except2(dbref, dbref, dbref, dbref, const char *);
void notify_printf(dbref, const char *, ...);
extern int check_filter(dbref, dbref, int, const char *);
extern void notify_checked(dbref, dbref, const char *, int);
extern int Hearer(dbref);
extern void report(void);
extern int atr_match(dbref, dbref, char, char *, int);
extern int list_check(dbref, dbref, char, char *, int);
extern int html_escape(const char *src, char *dest, char **destp);
/* From bsd.c */
void shutdown_services();
void flush_sockets();

/* From help.c */
extern int helpindex_read(HASHTAB *, char *);
extern void helpindex_load(dbref);
extern void helpindex_init(void);

/* From htab.c */
extern int cf_ntab_access(int *, char *, long, dbref, char *);

/* From log.c */
extern char *strip_ansi(const char *);
extern char *strip_ansi_r(char *, char *, size_t);
extern char *normal_to_white(const char *);
extern int start_log(const char *, const char *);
extern void end_log(void);
extern void log_perror(const char *, const char *, const char *, const char *);
extern void log_text(char *);
extern void log_number(int);
extern void log_name(dbref);
extern void log_name_and_loc(dbref);
extern char *OBJTYP(dbref);
extern void log_type_and_name(dbref);
extern void log_type_and_num(dbref);
#ifdef ARBITRARY_LOGFILES
extern int log_to_file(dbref, const char *, const char *);
#endif

/* From look.c */
extern void look_in(dbref, dbref, int);
extern void show_vrml_url(dbref, dbref);

/* From move.c */
extern void move_object(dbref, dbref);
extern void move_via_generic(dbref, dbref, dbref, int);
extern void move_via_exit(dbref, dbref, dbref, dbref, int);
extern int move_via_teleport(dbref, dbref, dbref, int);
extern void move_exit(dbref, dbref, int, const char *, int);
extern void do_enter_internal(dbref, dbref, int);

/* From object.c */
extern void destroy_player(dbref);
extern dbref start_home(void);
extern dbref default_home(void);
extern int can_set_home(dbref, dbref, dbref);
extern dbref new_home(dbref);
extern dbref clone_home(dbref, dbref);
extern void divest_object(dbref);
extern dbref create_obj(dbref, int, char *, int);
extern void destroy_obj(dbref, dbref);
extern void empty_obj(dbref);

/* From player.c */
extern void record_login(dbref, int, char *, char *, char *);
extern int check_pass(dbref, const char *);
extern dbref connect_player(char *, char *, char *, char *);
extern dbref create_player(char *, char *, dbref, int, int);
extern int add_player_name(dbref, char *);
extern int delete_player_name(dbref, char *);
extern dbref lookup_player(dbref, char *, int);
extern void load_player_names(void);
extern void badname_add(char *);
extern void badname_remove(char *);
extern int badname_check(char *);
extern void badname_list(dbref, const char *);

/* From predicates.c */
extern char *tprintf(const char *, ...);
extern void safe_tprintf_str(char *, char **, const char *, ...);
extern dbref insert_first(dbref, dbref);
extern dbref remove_first(dbref, dbref);
extern dbref reverse_list(dbref);
extern int member(dbref, dbref);
extern int is_integer(char *);
extern int is_number(char *);
extern int could_doit(dbref, dbref, int);
extern int can_see(dbref, dbref, int);
extern void add_quota(dbref, int);
extern int canpayfees(dbref, dbref, int, int);
extern void giveto(dbref, int);
extern int payfor(dbref, int);
extern int ok_name(const char *);
extern int ok_player_name(const char *);
extern int ok_attr_name(const char *);
extern int ok_password(const char *);
extern void handle_ears(dbref, int, int);
extern void handle_xcode(dbref, dbref, int, int);
extern int HandledCommand(dbref, dbref, char *);
extern dbref match_possessed(dbref, dbref, char *, dbref, int);
extern void parse_range(char **, dbref *, dbref *);
extern int parse_thing_slash(dbref, char *, char **, dbref *);
extern int get_obj_and_lock(dbref, char *, dbref *, ATTR **, char *, char **);
extern dbref where_is(dbref);
extern dbref where_room(dbref);
extern int locatable(dbref, dbref, dbref);
extern int nearby(dbref, dbref);
extern int exit_visible(dbref, dbref, int);
extern int exit_displayable(dbref, dbref, int);
extern void did_it(dbref, dbref, int, const char *, int, const char *, int, char *[], int);
extern void list_bufstats(dbref);
extern void list_buftrace(dbref);

/* From set.c */
extern int parse_attrib(dbref, char *, dbref *, int *);
extern int parse_attrib_wild(dbref, char *, dbref *, int, int, int);
extern void edit_string(char *, char **, char *, char *);
extern dbref match_controlled(dbref, char *);
extern dbref match_affected(dbref, char *);
extern dbref match_examinable(dbref, char *);

/* From stringutil.c */
extern char *munge_space(char *);
extern char *trim_spaces(char *);
extern char *grabto(char **, char);
extern int string_compare(const char *, const char *);
extern int string_prefix(const char *, const char *);
extern const char *string_match(const char *, const char *);
extern char *dollar_to_space(const char *);
extern char *replace_string(const char *, const char *, const char *);
extern char *replace_string_inplace(const char *, const char *, char *);
extern char *skip_space(const char *);
extern char *seek_char(const char *, char);
extern int prefix_match(const char *, const char *);
extern int minmatch(char *, char *, int);
extern char *strsave(const char *);
extern int safe_copy_str(char *, char *, char **, int);
extern int safe_copy_chr(char, char *, char **, int);
extern int matches_exit_from_list(char *, char *);
extern char *translate_string(const char *, int);

/* From boolexp.c */
extern int eval_boolexp(dbref, dbref, dbref, BOOLEXP *);
extern BOOLEXP *parse_boolexp(dbref, const char *, int);
extern int eval_boolexp_atr(dbref, dbref, dbref, char *);

/* From functions.c */
extern int xlate(char *);

/* From unparse.c */
extern char *unparse_boolexp(dbref, BOOLEXP *);
extern char *unparse_boolexp_quiet(dbref, BOOLEXP *);
extern char *unparse_boolexp_decompile(dbref, BOOLEXP *);
extern char *unparse_boolexp_function(dbref, BOOLEXP *);

/* From walkdb.c */
extern int chown_all(dbref, dbref);
extern void olist_push(void);
extern void olist_pop(void);
extern void olist_add(dbref);
extern dbref olist_first(void);
extern dbref olist_next(void);

/* From wild.c */
extern int wild(char *, char *, char *[], int);
extern int wild_match(char *, char *);
extern int quick_wild(char *, char *);

/* From compress.c */
extern const char *uncompress(const char *, int);
extern const char *compress(const char *, int);
extern char *uncompress_str(char *, const char *, int);

/* From command.c */
extern int check_access(dbref, int);
extern void set_prefix_cmds(void);

/* from db.c */
extern int Commer(dbref);
extern void s_Pass(dbref, const char *);
extern void s_Name(dbref, char *);
extern char *Name(dbref);
extern char *PureName(dbref);
extern int fwdlist_load(FWDLIST *, dbref, char *);
extern void fwdlist_set(dbref, FWDLIST *);
extern void fwdlist_clr(dbref);
extern int fwdlist_rewrite(FWDLIST *, char *);
extern FWDLIST *fwdlist_get(dbref);
extern void clone_object(dbref, dbref);
extern void init_min_db(void);
extern void atr_push(void);
extern void atr_pop(void);
extern int atr_head(dbref, char **);
extern int atr_next(char **);
extern int init_gdbm_db(char *);
extern void atr_cpy(dbref, dbref, dbref);
extern void atr_chown(dbref);
extern void atr_clr(dbref, int);
extern void atr_add_raw(dbref, int, char *);
extern void atr_add(dbref, int, char *, dbref, int);
extern void atr_set_owner(dbref, int, dbref);
extern void atr_set_flags(dbref, int, int);
extern char *atr_get_raw(dbref, int);
extern char *atr_get(dbref, int, dbref *, int *);
extern char *atr_pget(dbref, int, dbref *, int *);
extern char *atr_get_str(char *, dbref, int, dbref *, int *);
extern char *atr_pget_str(char *, dbref, int, dbref *, int *);
extern int atr_get_info(dbref, int, dbref *, int *);
extern int atr_pget_info(dbref, int, dbref *, int *);
extern void atr_free(dbref);
extern int check_zone(dbref, dbref);
extern int check_zone_for_player(dbref, dbref);
extern void toast_player(dbref);

/* Mecha code: */
extern void DisposeSpecialObject(dbref, dbref);
extern void UpdateSpecialObjects(void);
extern void LoadSpecialObjects(void);
extern void ResetSpecialObjects(void);
extern void SaveSpecialObjects(int);
extern void helpindex_faction_load(dbref);
extern void list_fhashstats(dbref);
extern void list_chashstats(dbref);

/* Command handler keys */
#ifdef SQL_SUPPORT
#define QUERY_SQL       1       /* SQL Query */
#define LIST_SQL        2       /* List active and pending queries */
#define KILL_SQL        3       /* Kill an active query */
#endif
#define	ATTRIB_ACCESS	1	/* Change access to attribute */
#define	ATTRIB_RENAME	2	/* Rename attribute */
#define	ATTRIB_DELETE	4	/* Delete attribute */
#define	BOOT_QUIET	1	/* Inhibit boot message to victim */
#define	BOOT_PORT	2	/* Boot by port number */
#define CEMIT_NOHEADER  1	/* Channel emit without header */
#define	CHOWN_ONE	1	/* item = new_owner */
#define	CHOWN_ALL	2	/* old_owner = new_owner */
#define CLIST_FULL	1	/* Full listing of channels */
#define CSTATUS_FULL	1	/* Full listing of channel */
#define	CLONE_LOCATION	0	/* Create cloned object in my location */
#define	CLONE_INHERIT	1	/* Keep INHERIT bit if set */
#define	CLONE_PRESERVE	2	/* Preserve the owner of the object */
#define	CLONE_INVENTORY	4	/* Create cloned object in my inventory */
#define	CLONE_SET_COST	8	/* ARG2 is cost of cloned object */
#define	CLONE_SET_LOC	16	/* ARG2 is location of cloned object */
#define	CLONE_SET_NAME	32	/* ARG2 is alternate name of cloned object */
#define	CLONE_PARENT	64	/* Set parent on obj instd of cloning attrs */
#define	CRE_INVENTORY	0	/* Create object in my inventory */
#define	CRE_LOCATION	1	/* Create object in my location */
#define	CRE_SET_LOC	2	/* ARG2 is location of new object */
#define CSET_PUBLIC	0	/* Sets a channel public */
#define CSET_PRIVATE	1	/* Sets a channel private (default) */
#define CSET_LOUD	2	/* Channel shows connects and disconnects */
#define CSET_QUIET	3	/* Channel doesn't show connects/disconnects */
#define CSET_LIST	4	/* Lists channels */
#define CSET_OBJECT	5	/* Sets the channel object for the channel */
#define CSET_STATUS	6	/* Gives status of channel */
#define CSET_TRANSPARENT 7	/* Set channel 'transparent' */
#define CSET_OPAQUE	8	/* Set channel !transparent */
#define	DBCK_DEFAULT	1	/* Get default tests too */
#define	DBCK_REPORT	2	/* Report info to invoker */
#define	DBCK_FULL	4	/* Do all tests */
#define	DBCK_FLOATING	8	/* Look for floating rooms */
#define	DBCK_PURGE	16	/* Purge the db of refs to going objects */
#define	DBCK_LINKS	32	/* Validate exit and object chains */
#define	DBCK_WEALTH	64	/* Validate object value/wealth */
#define	DBCK_OWNER	128	/* Do more extensive owner checking */
#define	DBCK_OWN_EXIT	256	/* Check exit owner owns src or dest */
#define	DBCK_WIZARD	512	/* Check for wizards/wiz objects */
#define	DBCK_TYPES	1024	/* Check for valid & appropriate types */
#define	DBCK_SPARE	2048	/* Make sure spare header fields are NOTHING */
#define	DBCK_HOMES	4096	/* Make sure homes and droptos are valid */
#define DECOMP_DBREF    1	/* decompile by dbref */
#define	DEST_ONE	1	/* object */
#define	DEST_ALL	2	/* owner */
#define	DEST_OVERRIDE	4	/* override Safe() */
#define DEST_RECURSIVE  8
#define	DIG_TELEPORT	1	/* teleport to room after @digging */
#define DOLIST_SPACE    0	/* expect spaces as delimiter */
#define DOLIST_DELIMIT  1	/* expect custom delimiter */
#define	DOING_MESSAGE	0	/* Set my DOING message */
#define	DOING_HEADER	1	/* Set the DOING header */
#define	DOING_POLL	2	/* List DOING header */
#define	DROP_QUIET	1	/* Don't do odrop/adrop if control */
#define	DUMP_STRUCT	1	/* Dump flat structure file */
#define	DUMP_TEXT	2	/* Dump text (gdbm) file */
#define DUMP_OPTIMIZE	3	/* Reorganize the gdbm file */
#define	EXAM_DEFAULT	0	/* Default */
#define	EXAM_BRIEF	1	/* Nonowner sees just owner */
#define	EXAM_LONG	2	/* Nonowner sees public attrs too */
#define	EXAM_DEBUG	4	/* Display more info for finding db problems */
#define	EXAM_PARENT	8	/* Get attr from parent when exam obj/attr */
#define	FIXDB_OWNER	1	/* Fix OWNER field */
#define	FIXDB_LOC	2	/* Fix LOCATION field */
#define	FIXDB_CON	4	/* Fix CONTENTS field */
#define	FIXDB_EXITS	8	/* Fix EXITS field */
#define	FIXDB_NEXT	16	/* Fix NEXT field */
#define	FIXDB_PENNIES	32	/* Fix PENNIES field */
#define	FIXDB_ZONE	64	/* Fix ZONE field */
#define	FIXDB_LINK	128	/* Fix LINK field */
#define	FIXDB_PARENT	256	/* Fix PARENT field */
#define	FIXDB_DEL_PN	512	/* Remove player name from player name index */
#define	FIXDB_ADD_PN	1024	/* Add player name to player name index */
#define	FIXDB_NAME	2048	/* Set NAME attribute */
#define	FRC_PREFIX	0	/* #num command */
#define	FRC_COMMAND	1	/* what=command */
#define	GET_QUIET	1	/* Don't do osucc/asucc if control */
#define	GIVE_MONEY	1	/* Give money */
#define	GIVE_QUOTA	2	/* Give quota */
#define	GIVE_QUIET	64	/* Inhibit give messages */
#define	GLOB_ENABLE	1	/* key to enable */
#define	GLOB_DISABLE	2	/* key to disable */
#define	GLOB_LIST	3	/* key to list */
#define	HALT_ALL	1	/* halt everything */
#define	HELP_HELP	1	/* get data from help file */
#define	HELP_NEWS	2	/* get data from news file */
#define	HELP_WIZHELP	3	/* get data from wizard help file */
#define HELP_PLUSHELP   4	/* get data from plushelp file */
#define HELP_WIZNEWS    5	/* wiznews file */
#define	KILL_KILL	1	/* gives victim insurance */
#define	KILL_SLAY	2	/* no insurance */
#define	LOOK_LOOK	1	/* list desc (and succ/fail if room) */
#define	LOOK_EXAM	2	/* full listing of object */
#define	LOOK_DEXAM	3	/* debug listing of object */
#define	LOOK_INVENTORY	4	/* list inventory of object */
#define	LOOK_SCORE	5	/* list score (# coins) */
#define	LOOK_OUTSIDE    8	/* look for object in container of player */
#define MAIL_STATS	1	/* Mail stats */
#define MAIL_DSTATS	2	/* More mail stats */
#define MAIL_FSTATS	3	/* Even more mail stats */
#define MAIL_DEBUG	4	/* Various debugging options */
#define MAIL_NUKE	5	/* Nuke the post office */
#define MAIL_FOLDER	6	/* Do folder stuff */
#define MAIL_LIST	7	/* List @mail by time */
#define MAIL_READ	8	/* Read @mail message */
#define MAIL_CLEAR	9	/* Clear @mail message */
#define MAIL_UNCLEAR	10	/* Unclear @mail message */
#define MAIL_PURGE	11	/* Purge cleared @mail messages */
#define MAIL_FILE	12	/* File @mail in folders */
#define MAIL_TAG	13	/* Tag @mail messages */
#define MAIL_UNTAG	14	/* Untag @mail messages */
#define MAIL_FORWARD	15	/* Forward @mail messages */
#define MAIL_SEND	16	/* Send @mail messages in progress */
#define MAIL_EDIT	17	/* Edit @mail messages in progress */
#define MAIL_URGENT	18	/* Sends a @mail message as URGENT */
#define MAIL_ALIAS	19	/* Creates an @mail alias */
#define MAIL_ALIST	20	/* Lists @mail aliases */
#define MAIL_PROOF	21	/* Proofs @mail messages in progress */
#define MAIL_ABORT	22	/* Aborts @mail messages in progress */
#define MAIL_QUICK	23	/* Sends a quick @mail message */
#define MAIL_REVIEW	24	/* Reviews @mail sent to a player */
#define MAIL_RETRACT	25	/* Retracts @mail sent to a player */
#define MAIL_CC		26	/* Carbon copy */
#define MAIL_SAFE	27	/* Defines a piece of mail as safe. */

#define MALIAS_DESC	1	/* Describes a mail alias */
#define MALIAS_CHOWN	2	/* Changes a mail alias's owner */
#define MALIAS_ADD	3	/* Adds a player to an alias */
#define MALIAS_REMOVE	4	/* Removes a player from an alias */
#define MALIAS_DELETE	5	/* Deletes a mail alias */
#define MALIAS_RENAME	6	/* Renames a mail alias */
#define MALIAS_LIST	8	/* Lists mail aliases */
#define MALIAS_STATUS	9	/* Status of mail aliases */
#define	MARK_SET	0	/* Set mark bits */
#define	MARK_CLEAR	1	/* Clear mark bits */
#define	MOTD_ALL	0	/* login message for all */
#define	MOTD_WIZ	1	/* login message for wizards */
#define	MOTD_DOWN	2	/* login message when logins disabled */
#define	MOTD_FULL	4	/* login message when too many players on */
#define	MOTD_LIST	8	/* Display current login messages */
#define	MOTD_BRIEF	16	/* Suppress motd file display for wizards */
#define	MOVE_QUIET	1	/* Dont do osucc/ofail/asucc/afail if ctrl */
#define	NFY_NFY		0	/* Notify first waiting command */
#define	NFY_NFYALL	1	/* Notify all waiting commands */
#define	NFY_DRAIN	2	/* Delete waiting commands */
#define	OPEN_LOCATION	0	/* Open exit in my location */
#define	OPEN_INVENTORY	1	/* Open exit in me */
#define	PASS_ANY	1	/* name=newpass */
#define	PASS_MINE	2	/* oldpass=newpass */
#define	PCRE_PLAYER	1	/* create new player */
#define	PCRE_ROBOT	2	/* create robot player */
#define	PEMIT_PEMIT	1	/* emit to named player */
#define	PEMIT_OEMIT	2	/* emit to all in current room except named */
#define	PEMIT_WHISPER	3	/* whisper to player in current room */
#define	PEMIT_FSAY	4	/* force controlled obj to say */
#define	PEMIT_FEMIT	5	/* force controlled obj to emit */
#define	PEMIT_FPOSE	6	/* force controlled obj to pose */
#define	PEMIT_FPOSE_NS	7	/* force controlled obj to pose w/o space */
#define	PEMIT_CONTENTS	8	/* Send to contents (additive) */
#define	PEMIT_HERE	16	/* Send to location (@femit, additive) */
#define	PEMIT_ROOM	32	/* Send to containing rm (@femit, additive) */
#define PEMIT_LIST      64	/* Send to a list */
#define PEMIT_HTML	128	/* HTML escape, and no newline */
#define	PS_BRIEF	0	/* Short PS report */
#define	PS_LONG		1	/* Long PS report */
#define	PS_SUMM		2	/* Queue counts only */
#define	PS_ALL		4	/* List entire queue */
#define	QUEUE_KICK	1	/* Process commands from queue */
#define	QUEUE_WARP	2	/* Advance or set back wait queue clock */
#define	QUOTA_SET	1	/* Set a quota */
#define	QUOTA_FIX	2	/* Repair a quota */
#define	QUOTA_TOT	4	/* Operate on total quota */
#define	QUOTA_REM	8	/* Operate on remaining quota */
#define	QUOTA_ALL	16	/* Operate on all players */
#define	SAY_SAY		1	/* say in current room */
#define	SAY_NOSPACE	1	/* OR with xx_EMIT to get nospace form */
#define	SAY_POSE	2	/* pose in current room */
#define	SAY_POSE_NOSPC	3	/* pose w/o space in current room */
#define	SAY_PREFIX	4	/* first char indicates foratting */
#define	SAY_EMIT	5	/* emit in current room */
#define	SAY_SHOUT	8	/* shout to all logged-in players */
#define	SAY_WALLPOSE	9	/* Pose to all logged-in players */
#define	SAY_WALLEMIT	10	/* Emit to all logged-in players */
#define	SAY_WIZSHOUT	12	/* shout to all logged-in wizards */
#define	SAY_WIZPOSE	13	/* Pose to all logged-in wizards */
#define	SAY_WIZEMIT	14	/* Emit to all logged-in wizards */
#define SAY_ADMINSHOUT	15	/* Emit to all wizards or royalty */
#define	SAY_GRIPE	16	/* Complain to management */
#define	SAY_NOTE	17	/* Comment to log for wizards */
#define	SAY_NOTAG	32	/* Don't put Broadcast: in front (additive) */
#define	SAY_HERE	64	/* Output to current location */
#define	SAY_ROOM	128	/* Output to containing room */
#define SAY_HTML	256	/* Don't output a newline */
#define	SET_QUIET	1	/* Don't display 'Set.' message. */
#define	SHUTDN_NORMAL	0	/* Normal shutdown */
#define	SHUTDN_PANIC	1	/* Write a panic dump file */
#define	SHUTDN_EXIT	2	/* Exit from shutdown code */
#define	SHUTDN_COREDUMP	4	/* Produce a coredump */
#define	SRCH_SEARCH	1	/* Do a normal search */
#define	SRCH_MARK	2	/* Set mark bit for matches */
#define	SRCH_UNMARK	3	/* Clear mark bit for matches */
#define	STAT_PLAYER	0	/* Display stats for one player or tot objs */
#define	STAT_ALL	1	/* Display global stats */
#define	STAT_ME		2	/* Display stats for me */
#define	SWITCH_DEFAULT	0	/* Use the configured default for switch */
#define	SWITCH_ANY	1	/* Execute all cases that match */
#define	SWITCH_ONE	2	/* Execute only first case that matches */
#define	SWEEP_ME	1	/* Check my inventory */
#define	SWEEP_HERE	2	/* Check my location */
#define	SWEEP_COMMANDS	4	/* Check for $-commands */
#define	SWEEP_LISTEN	8	/* Check for @listen-ers */
#define	SWEEP_PLAYER	16	/* Check for players and puppets */
#define	SWEEP_CONNECT	32	/* Search for connected players/puppets */
#define	SWEEP_EXITS	64	/* Search the exits for audible flags */
#define	SWEEP_SCAN	128	/* Scan for pattern matching */
#define	SWEEP_VERBOSE	256	/* Display what pattern matches */
#define TELEPORT_DEFAULT 1	/* Emit all messages */
#define TELEPORT_QUIET   2	/* Teleport in quietly */
#define	TOAD_NO_CHOWN	1	/* Don't change ownership */
#define	TRIG_QUIET	1	/* Don't display 'Triggered.' message. */
#define	TWARP_QUEUE	1	/* Warp the wait and sem queues */
#define	TWARP_DUMP	2	/* Warp the dump interval */
#define	TWARP_CLEAN	4	/* Warp the cleaning interval */
#define	TWARP_IDLE	8	/* Warp the idle check interval */

/* emprty		16 */
#define TWARP_EVENTS	32	/* Warp the events checking interval */

/* Hush codes for movement messages */

#define	HUSH_ENTER	1	/* xENTER/xEFAIL */
#define	HUSH_LEAVE	2	/* xLEAVE/xLFAIL */
#define	HUSH_EXIT	4	/* xSUCC/xDROP/xFAIL from exits */

/* Evaluation directives */

#define	EV_FMASK	0x00000300	/* Mask for function type check */
#define	EV_FIGNORE	0x00000000	/* Don't look for func if () found */
#define	EV_FMAND	0x00000100	/* Text before () must be func name */
#define	EV_FCHECK	0x00000200	/* Check text before () for function */
#define	EV_STRIP	0x00000400	/* Strip one level of brackets */
#define	EV_EVAL		0x00000800	/* Evaluate results before returning */
#define	EV_STRIP_TS	0x00001000	/* Strip trailing spaces */
#define	EV_STRIP_LS	0x00002000	/* Strip leading spaces */
#define	EV_STRIP_ESC	0x00004000	/* Strip one level of \ characters */
#define	EV_STRIP_AROUND	0x00008000	/* Strip {} only at ends of string */
#define	EV_TOP		0x00010000	/* This is a toplevel call to eval() */
#define	EV_NOTRACE	0x00020000	/* Don't trace this call to eval */
#define EV_NO_COMPRESS  0x00040000	/* Don't compress spaces. */
#define EV_NO_LOCATION	0x00080000	/* Supresses %l */
#define EV_NOFCHECK	0x00100000	/* Do not evaluate functions! */

/* Termination directives */

#define PT_NOTHING	0x00000000
#define PT_BRACE	0x00000001
#define PT_BRACKET	0x00000002
#define PT_PAREN	0x00000004
#define PT_COMMA	0x00000008
#define PT_SEMI		0x00000010
#define PT_EQUALS	0x00000020
#define PT_SPACE	0x00000040

/* Message forwarding directives */

#define	MSG_PUP_ALWAYS	1	/* Always forward msg to puppet own */
#define	MSG_INV		2	/* Forward msg to contents */
#define	MSG_INV_L	4	/* ... only if msg passes my @listen */
#define	MSG_INV_EXITS	8	/* Forward through my audible exits */
#define	MSG_NBR		16	/* Forward msg to neighbors */
#define	MSG_NBR_A	32	/* ... only if I am audible */
#define	MSG_NBR_EXITS	64	/* Also forward to neighbor exits */
#define	MSG_NBR_EXITS_A	128	/* ... only if I am audible */
#define	MSG_LOC		256	/* Send to my location */
#define	MSG_LOC_A	512	/* ... only if I am audible */
#define	MSG_FWDLIST	1024	/* Forward to my fwdlist members if aud */
#define	MSG_ME		2048	/* Send to me */
#define	MSG_S_INSIDE	4096	/* Originator is inside target */
#define	MSG_S_OUTSIDE	8192	/* Originator is outside target */
#define MSG_COLORIZE    16384	/* Message needs to be given color */
#define MSG_HTML	32768	/* Don't send \r\n */
#define MSG_NO_SLAVE    65536	/* Don't send to slaves */
#define	MSG_ME_ALL	(MSG_ME|MSG_INV_EXITS|MSG_FWDLIST)
#define	MSG_F_CONTENTS	(MSG_INV)
#define	MSG_F_UP	(MSG_NBR_A|MSG_LOC_A)
#define	MSG_F_DOWN	(MSG_INV_L)

/* Look primitive directives */

#define	LK_IDESC	0x0001
#define	LK_OBEYTERSE	0x0002
#define	LK_SHOWATTR	0x0004
#define	LK_SHOWEXIT	0x0008
#define LK_SHOWVRML	0x0010

/* Exit visibility precalculation codes */

#define	VE_LOC_XAM	0x01	/* Location is examinable */
#define	VE_LOC_DARK	0x02	/* Location is dark */
#define	VE_LOC_LIGHT	0x04	/* Location is light */
#define	VE_BASE_XAM	0x08	/* Base location (pre-parent) is examinable */
#define	VE_BASE_DARK	0x10	/* Base location (pre-parent) is dark */
#define	VE_BASE_LIGHT	0x20	/* Base location (pre-parent) is light */

/* Signal handling directives */

#define	SA_EXIT		1	/* Exit, and dump core */
#define	SA_DFLT		2	/* Try to restart on a fatal error */

#define	STARTLOG(key,p,s) \
	if ((((key) & mudconf.log_options) != 0) && start_log(p, s))
#define	ENDLOG \
	end_log()
#define	LOG_SIMPLE(key,p,s,m) \
	STARTLOG(key,p,s) { \
		log_text(m); \
	ENDLOG; }

#define	test_top()		((mudstate.qfirst != NULL) ? 1 : 0)
#define	controls(p,x)		Controls(p,x)

#endif				/* __EXTERNS_H */
