#include "mech.h"
#include "mech.events.h"
#include "mech.tech.h"
#include "mech.tech.damages.h"
#include "coolmenu.h"
#include "mycool.h"
#include "p.mech.tech.h"
#include "p.mech.build.h"
#include "p.mech.status.h"

static coolmenu *c;

static void describe_repairs(EVENT * e)
{
    int type = e->type;
    MECH *mech = (MECH *) e->data;
    int earg = ((int) e->data2) % PLAYERPOS;
    dbref player = ((int) e->data2) / PLAYERPOS;
    int loc, pos, extra;
    char buf[MBUF_SIZE];
    char buf2[LBUF_SIZE];
    int fail = (e->function == very_fake_func);

    UNPACK_LOCPOS_E(earg, loc, pos, extra);
    sprintf(buf, "%s%s", ShortArmorSectionString(MechType(mech),
	    MechMove(mech), loc % 8), loc >= 8 ? "(R)" : "");
    sprintf(buf2, "%-5d ", player);
    sprintf(buf2 + strlen(buf2), "%-4d ",
	game_lag_time((e->tick - event_tick) / 60));
    switch (type) {
    case EVENT_REPAIR_REPL:
	sprintf(buf2 + strlen(buf2), "%5s:%-2d Replacement of %s crit", buf,
	    pos + 1, pos_part_name(mech, loc, pos));
	if (fail)
	    sprintf(buf2 + strlen(buf2), " (Failure)");
	break;
    case EVENT_REPAIR_REPLG:
	sprintf(buf2 + strlen(buf2), "%5s:%-2d Replacement of entire %s", buf,
	    pos + 1, pos_part_name(mech, loc, pos));
	if (fail)
	    sprintf(buf2 + strlen(buf2), " (Failure)");
	break; 
    case EVENT_REPAIR_RESE:
	sprintf(buf2 + strlen(buf2), "%5s Reseal", buf);
	if (fail)
	    sprintf(buf2 + strlen(buf2), " (Failure)");
	break; 
    case EVENT_REPAIR_REAT:
	sprintf(buf2 + strlen(buf2), "%5s Reattachment", buf);
	if (fail)
	    sprintf(buf2 + strlen(buf2), " (Failure)");
	break;
    case EVENT_REPAIR_RELO:
	sprintf(buf2 + strlen(buf2), "%5s:%-2d %sload of %s", buf, pos + 1,
	    extra ? "Un" : "Re", pos_part_name(mech, loc, pos));
	if (fail)
	    sprintf(buf2 + strlen(buf2), " (Failure)");
	break;
    case EVENT_REPAIR_FIX:
	if (fail)
	    sprintf(buf2 + strlen(buf2), "%5s:%-2d Failed armor repair",
		buf, 0);
	else
	    sprintf(buf2 + strlen(buf2),
		"%5s:%-2d Repair of armor - possibly next point", buf,
		pos);
	break;
    case EVENT_REPAIR_FIXI:
	if (fail)
	    sprintf(buf2 + strlen(buf2), "%5s:%-2d Failed internal repair",
		buf, 0);
	else
	    sprintf(buf2 + strlen(buf2),
		"%5s:%-2d Repair of internals - possibly next point", buf,
		pos);
	break;
    case EVENT_REPAIR_SCRL:
	sprintf(buf2 + strlen(buf2), "%5s Removal", buf);
	break;
    case EVENT_REPAIR_SCRP:
	sprintf(buf2 + strlen(buf2), "%5s:%-2d Scrapping of %s crit", buf,
	    pos + 1, pos_part_name(mech, loc, pos));
	break;
    case EVENT_REPAIR_SCRG:
	sprintf(buf2 + strlen(buf2), "%5s:%-2d Scrapping of entire %s", buf,
	    pos + 1, pos_part_name(mech, loc, pos));
	break;
    case EVENT_REPAIR_REPAG:
	sprintf(buf2 + strlen(buf2), "%5s:%-2d Repair of %s", buf, pos + 1,
	    pos_part_name(mech, loc, pos));
	if (fail)
	    sprintf(buf2 + strlen(buf2), " (Failure)");
	break;
    case EVENT_REPAIR_REPAP:
	sprintf(buf2 + strlen(buf2), "%5s:%-2d Repair of %s", buf, pos + 1,
	    pos_part_name(mech, loc, pos));
	if (fail)
	    sprintf(buf2 + strlen(buf2), " (Failure)");
	break;
    case EVENT_REPAIR_MOB:
	sprintf(buf2 + strlen(buf2), "%5s:%-2d Mounting of %s", buf,
	    pos + 1, pos_part_name(mech, loc, pos));
	if (fail)
	    sprintf(buf2 + strlen(buf2), " (Failure)");
	break;
    case EVENT_REPAIR_UMOB:
	sprintf(buf2 + strlen(buf2), "%5s:%-2d Removing of %s", buf,
	    pos + 1, pos_part_name(mech, loc, pos));
	if (fail)
	    sprintf(buf2 + strlen(buf2), " (Failure)");
	break; 
    case EVENT_REPAIR_OADD:
	sprintf(buf2 + strlen(buf2), "%5s:%-2d Omni add of %s", buf, pos + 1,
	    pos_part_name(mech, loc, pos));
	break; 
    case EVENT_REPAIR_OREM:
	sprintf(buf2 + strlen(buf2), "%5s:%-2d Omni remove of %s", buf, pos + 1,
	    pos_part_name(mech, loc, pos));
	break;
    }

/*   sprintf(buf2+strlen(buf2), " - %s", */

/*        get_uptime_to_string(e->tick - event_tick)); */
    vsi(buf2);
}

void tech_repairs(dbref player, MECH * mech, char *buffer)
{
    int i, isds = IsDS(mech);

    //    TECHCOMMANDC;
    DOCHECK(!(Tech(player)),"Insufficient clearance to access the command.");
    DOCHECK(!mech, "Error has occured in techcommand ; please contact a wiz");
    DOCHECK(Starting(mech) && !Wiz(player), "The mech's starting up! Please stop the sequence first."); 
    DOCHECK(Started(mech) && !Wiz(player), "The mech's started up ; please shut it down first.");
    DOCHECK(!figure_latest_tech_event(mech),
	"This 'mech has no repairs pending!");
    c = NULL;
    addline();
    cent(tprintf("Repairs/Scrapping in progress (%s)", GetMechID(mech)));
    vsi(tprintf("%-5s %-4s %s", "Plr", "Time", "Location + Description"));
    addline();
    for (i = FIRST_TECH_EVENT; i <= LAST_TECH_EVENT; i++)
	event_gothru_type_data(i, (void *) mech, describe_repairs);
    addline();
    vsi("Note: Time = Time remaining in minutes. Plr = Tech's dbref");
    addline();
    ShowCoolMenu(player, c);
    KillCoolMenu(c);
}
