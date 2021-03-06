#include <stdio.h>

#include "create.h"
#include "mech.h"
#include "autopilot.h"
#include "p.econ_cmds.h"
#include "p.mech.restrict.h"
#include "p.mech.utils.h"
#include "p.map.conditions.h"

#define DYNAMIC_MAGIC 42

/* Code for saving / loading / setting / unsetting the dynamic pieces
   of map structure:
   - mechsOnMap
   - LOSinfo
   - mechflags
 */

#define CHELO(a,b,c,d) if (!(ugly_kludge++)) { \
  if ((tmp=fread(a,b,c,d)) != c) { fprintf (stderr, "Error loading mapdynamic for #%d - couldn't find enough entries! (found: %d, should: %d)\n", map->mynum, tmp, c); return; } } else { if ((tmp=fread(a,b,c,d)) != c) { fprintf (stderr, "Error loading mapdynamic for #%d - couldn't find enough entries! (found: %d, should: %d)\n", map->mynum, tmp, c); fflush(stderr); exit(1); } }
#define CHESA(a,b,c,d) if ((tmp=fwrite(a,b,c,d)) != c) { fprintf (stderr, "Error writing mapdynamic for #%d - couldn't find enough entries! (found: %d, should: %d)\n", map->mynum, tmp, c); fflush(stderr); exit(1); }

static int ugly_kludge = 0;	/* Nonfatal for _first_ */

void load_mapdynamic(FILE * f, MAP * map)
{
    int count = map->first_free;
    int i, tmp;
    unsigned char tmpb;



    if (count > 0) {
	Create(map->mechsOnMap, dbref, count);

	CHELO(map->mechsOnMap, sizeof(map->mechsOnMap[0]), count, f);
	Create(map->mechflags, char, count);

	CHELO(map->mechflags, sizeof(map->mechflags[0]), count, f);
	Create(map->LOSinfo, unsigned int *, count);

	for (i = 0; i < count; i++) {
	    Create(map->LOSinfo[i], unsigned int, count);

	    CHELO(map->LOSinfo[i], sizeof(map->LOSinfo[i][0]), count, f);
	}
    } else {
	map->mechsOnMap = NULL;
	map->mechflags = NULL;
	map->LOSinfo = NULL;
    }
    CHELO(&tmpb, 1, 1, f);
    if (tmpb != DYNAMIC_MAGIC) {
	fprintf(stderr, "Error reading data for obj #%d (%d != %d)!\n",
	    map->mynum, tmpb, DYNAMIC_MAGIC);
	fflush(stderr);
	exit(1);
    }
}

#define outbyte(a) tmpb=(a);CHESA(&tmpb, 1, 1, f);

void save_mapdynamic(FILE * f, MAP * map)
{
    int count = map->first_free;
    int i, tmp;
    unsigned char tmpb;

    if (count > 0) {
	CHESA(map->mechsOnMap, sizeof(map->mechsOnMap[0]), count, f);
	CHESA(map->mechflags, sizeof(map->mechflags[0]), count, f);
	for (i = 0; i < count; i++)
	    CHESA(map->LOSinfo[i], sizeof(map->LOSinfo[i][0]), count, f);
    }
    outbyte(DYNAMIC_MAGIC);
}

void mech_map_consistency_check(MECH * mech)
{
    MAP *map = getMap(mech->mapindex);

    if (!map) {
	if (mech->mapindex > 0) {
	    mech->mapindex = -1;
	    fprintf(stderr, "#%d on nonexistent map - removing..\n",
		mech->mynum);
	}
	return;
    }
    if (map->first_free <= mech->mapnumber) {
	/* Invalid: possible corruption of data, therefore un-hosing it */
	mech->mapindex = -1;
	mech_remove_from_all_maps(mech);
	fprintf(stderr, "#%d on invalid map - removing.. (#1)\n",
	    mech->mynum);
	return;
    }
    if (map->mechsOnMap[mech->mapnumber] != mech->mynum) {
	mech->mapindex = -1;
	mech_remove_from_all_maps(mech);
	fprintf(stderr, "#%d on invalid map - removing.. (#2)\n",
	    mech->mynum);
	return;
    }
    mech_remove_from_all_maps_except(mech, map->mynum);
}

void eliminate_empties(MAP * map)
{
    int i;
    int j;
    int count, oldcount;
    char tempbuf[SBUF_SIZE];

    if (!map)
	return;
    for (i = map->first_free - 1; i >= 0; i--)
	if (map->mechsOnMap[i] > 0)
	    break;
    count = i + 1;
    if (count == (oldcount = map->first_free))
	return;
    fprintf(stderr,
	"Map #%d contains empty entries ; removing %d (%d->%d)\n",
	map->mynum, oldcount - count, oldcount, count);
    if (i < 0)
	return;
    for (j = count; j < oldcount; j++)
	free((void *) map->LOSinfo[j]);
    ReCreate(map->LOSinfo, unsigned int *, count);

    ReCreate(map->mechsOnMap, dbref, count);
    ReCreate(map->mechflags, char, count);

    map->first_free = count;
    sprintf(tempbuf, "%d", map->mynum);
    mech_Rfixstuff(GOD, NULL, tempbuf);
}

void remove_mech_from_map(MAP * map, MECH * mech)
{
    int loop = map->first_free;

    clear_mech_from_LOS(mech);
    mech->mapindex = -1;
    if (map->first_free <= mech->mapnumber ||
	map->mechsOnMap[mech->mapnumber] != mech->mynum) {
	SendError(tprintf
	    ("Map indexing error for mech #%d: Map index %d contains data for #%d instead.",
		mech->mynum, mech->mapnumber,
		map->mechsOnMap ? map->mechsOnMap[mech->mapnumber] : -1));
	if (map->mechsOnMap)
	    for (loop = 0;
		(loop < map->first_free) &&
		(map->mechsOnMap[loop] != mech->mynum); loop++);
    } else
	loop = mech->mapnumber;
    mech->mapnumber = 0;
    if (loop != (map->first_free)) {
	map->mechsOnMap[loop] = -1;	/* clear it */
	map->mechflags[loop] = 0;
#if 0
	for (i = 0; i < map->first_free; i++)
	    if (map->mechsOnMap[i] > 0 && i != loop)
		if ((t = getMech(map->mechsOnMap[i])))
		    if (MechTeam(t) != MechTeam(mech) &&
			(map->LOSinfo[i][loop] & MECHLOSFLAG_SEEN)) {
			MechNumSeen(t) = MAX(0, MechNumSeen(t) - 1);
		    }
#endif
	if (loop == (map->first_free - 1))
	    map->first_free--;	/* Who cares about some lost memory? In realloc
				   we'll gain it back anyway */
    }
    if (Towed(mech)) {
	/* Check that the towing guy isn't left on the map */
	int i;
	MECH *t;

	for (i = 0; i < map->first_free; i++)
	    /* Release from towing if tow-guy ain't on same map already */
	    if ((t = FindObjectsData(map->mechsOnMap[i])))
		if (MechCarrying(t) == mech->mynum) {
		    SetCarrying(t, -1);
		    MechStatus(mech) &= ~TOWED;	/* Reset the Towed flag */
		    break;
		}
    }
    MechNumSeen(mech) = 0;
}

void add_mech_to_map(MAP * newmap, MECH * mech)
{
    int loop, count, i;

    for (loop = 0; loop < newmap->first_free; loop++)
	if (newmap->mechsOnMap[loop] == mech->mynum)
	    break;
    if (loop != newmap->first_free)
	return;
    for (loop = 0; loop < newmap->first_free; loop++)
	if (newmap->mechsOnMap[loop] < 0)
	    break;
    if (loop == newmap->first_free) {
	newmap->first_free++;
	count = newmap->first_free;
	ReCreate(newmap->mechsOnMap, dbref, count);
	ReCreate(newmap->mechflags, char, count);
	ReCreate(newmap->LOSinfo, unsigned int *, count);

	newmap->LOSinfo[count - 1] = NULL;
	for (i = 0; i < count; i++) {
	    ReCreate(newmap->LOSinfo[i], unsigned int, count);

	    newmap->LOSinfo[i][loop] = 0;
	}
	for (i = 0; i < count; i++)
	    newmap->LOSinfo[loop][i] = 0;
    }
    mech->mapindex = newmap->mynum;
    mech->mapnumber = loop;
    newmap->mechsOnMap[loop] = mech->mynum;
    newmap->mechflags[loop] = 0;
    if (MechAuto(mech) > 0) {
	AUTO *a = FindObjectsData(MechAuto(mech));

	if (a)
	    ai_set_comtitle(a, mech);
    }
    if (Towed(mech)) {
	int i;
	MECH *t;

	for (i = 0; i < newmap->first_free; i++)
	    /* Release from towing if tow-guy ain't on same map already */
	    if ((t = FindObjectsData(newmap->mechsOnMap[i])))
		if (MechCarrying(t) == mech->mynum)
		    break;
	if (i == newmap->first_free)
	    MechStatus(mech) &= ~TOWED;	/* Reset the Towed flag */
    }
    MarkForLOSUpdate(mech);
    UnZombifyMech(mech);
    UpdateConditions(mech, newmap);
}

int mech_size(MAP * map)
{
    return map->first_free * (sizeof(dbref) + sizeof(char) +
	sizeof(unsigned short *) +

	map->first_free * sizeof(unsigned short));
}
