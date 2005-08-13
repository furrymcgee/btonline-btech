#ifndef COOLMENU_INTERFACE_H
#define COOLMENU_INTERFACE_H

/* To be included _after_ mech.h */
#include "mech.h"

#define ECOMMANDS(bname,letter) \
ECMD(bname ## _add); \
ECMD(bname ## _minus); \
ECMD(bname ## _toggle); \
ECMD(bname ## _set)

#define ECOMMANDSET(name) \
ECOMMANDS(name ## _a,'a'); \
ECOMMANDS(name ## _b,'b'); \
ECOMMANDS(name ## _c,'c'); \
ECOMMANDS(name ## _d,'d'); \
ECOMMANDS(name ## _e,'e'); \
ECOMMANDS(name ## _f,'f'); \
ECOMMANDS(name ## _g,'g'); \
ECOMMANDS(name ## _h,'h'); \
ECOMMANDS(name ## _i,'i'); \
ECOMMANDS(name ## _j,'j'); \
ECOMMANDS(name ## _k,'k'); \
ECOMMANDS(name ## _l,'l'); \
ECOMMANDS(name ## _m,'m'); \
ECOMMANDS(name ## _n,'n'); \
ECOMMANDS(name ## _o,'o'); \
ECOMMANDS(name ## _p,'p'); \
ECOMMANDS(name ## _q,'q'); \
ECOMMANDS(name ## _r,'r'); \
ECOMMANDS(name ## _s,'s'); \
ECOMMANDS(name ## _t,'t'); \
ECOMMANDS(name ## _u,'u'); \
ECOMMANDS(name ## _v,'v'); \
ECOMMANDS(name ## _w,'w'); \
ECOMMANDS(name ## _x,'x'); \
ECOMMANDS(name ## _y,'y'); \
				/* ECOMMANDS(name ## _z,'z');  */

#define GCOMMAND_PLUS(bname,n) \
{0,#n,"nada", bname ## _add},
#define GCOMMAND_MINUS(bname,n) \
{0,#n,"nada", bname ## _minus},
#define GCOMMAND_SET(bname,n) \
{0,#n,"nada", bname ## _set},
#define GCOMMAND_TOGGLE(bname,n) \
{0,#n,"nada", bname ## _toggle},


#define GCOMMANDS(bname,letter) \
GCOMMAND_PLUS(bname,#letter "+") \
GCOMMAND_MINUS(bname,#letter "-") \
GCOMMAND_SET(bname,#letter "=") \
GCOMMAND_TOGGLE(bname,#letter ".") \
GCOMMAND_TOGGLE(bname,#letter)


#define GCOMMANDSET(name) \
GCOMMANDS(name ## _a,a) \
GCOMMANDS(name ## _b,b) \
GCOMMANDS(name ## _c,c) \
GCOMMANDS(name ## _d,d) \
GCOMMANDS(name ## _e,e) \
GCOMMANDS(name ## _f,f) \
GCOMMANDS(name ## _g,g) \
GCOMMANDS(name ## _h,h) \
GCOMMANDS(name ## _i,i) \
GCOMMANDS(name ## _j,j) \
GCOMMANDS(name ## _k,k) \
GCOMMANDS(name ## _l,l) \
GCOMMANDS(name ## _m,m) \
GCOMMANDS(name ## _n,n) \
GCOMMANDS(name ## _o,o) \
GCOMMANDS(name ## _p,p) \
GCOMMANDS(name ## _q,q) \
GCOMMANDS(name ## _r,r) \
GCOMMANDS(name ## _s,s) \
GCOMMANDS(name ## _t,t) \
GCOMMANDS(name ## _u,u) \
GCOMMANDS(name ## _v,v) \
GCOMMANDS(name ## _w,w) \
GCOMMANDS(name ## _x,x) \
GCOMMANDS(name ## _y,y) \
				/* GCOMMANDS(name##_z,z)  */

#endif				/* COOLMENU_INTERFACE_H */
