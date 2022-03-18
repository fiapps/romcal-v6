#ifndef MONTAB_H
#define MONTAB_H
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL montab.h 6.1 02/12/06 17:23:53
 *
 *	Copyright (C) 1993,1995,1999 Kenneth G. Bath
 *	Permission to use and modify this software and its
 *	documentation for any purpose other than its incorporation
 *	into a commercial product is hereby granted without fee.
 *
 *	Permission to copy and distribute this software and its
 *	documentation only for non-commercial use is also granted
 *	without fee, provided, however, that the above copyright
 *	notice appear in all copies, that both that copyright
 *	notice and this permission notice appear in supporting
 *	documentation. The author makes no representations about
 *	the suitability of this software for any purpose. It is
 *	provided "as is" without express or implied warranty.
 *
 *-------------------- Software Unit Description -----------------------*
 *
 *	This include file contains useful tables and macros for
 *	manipulating the months of the year.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *----------------------------------------------------------------------*/
/*
 * 'names' - names of the months
 */
static char *mon_names[] = {
	"December",	"January", 	"February", 	"March", 
	"April", 	"May", 		"June",
	"July",		"August",	"September",
	"October",	"November",	"December",	"January"
};
/*
 * 'abbvs' - abbreviations of the month names
 */
static char *mon_abbvs[] = {
	"Dec",	"Jan",	"Feb",	"Mar",
	"Apr",	"May",	"Jun",
	"Jul",	"Aug",	"Sep",
	"Oct",	"Nov",	"Dec",	"Jan"
};
/*
 * 'lylen' - number of days in each month of a leap year
 */
static int mon_lylen[] = {
	31,	31,	29,	31,
	30,	31,	30,
	31,	31,	30,
	31,	30,	31,	31
};
/*
 * 'oylen' - number of days in each month of a non-leap year
 */
static int mon_oylen[] = {
	31,	31,	28,	31,
	30,	31,	30,
	31,	31,	30,
	31,	30,	31,	31
};
/*
 * 'lydoy' - day of a leap year of the first of each month
 *
 * An "extra" month is included in the following table to allow
 * computation of the last day of the year for a given month, as 
 * well as the first day of the year for a given month.
 */
static int mon_lydoy[] = {
	-31,	0, 	31, 	60,
	91, 	121, 	152,
	182, 	213, 	244, 
	274, 	305, 	335, 	367
};
/*
 * 'oydoy' - day of a non-leap year of the first of each month
 *
 * An "extra" month is included in the following table to allow
 * computation of the last day of the year for a given month, as 
 * well as the first day of the year for a given month.
 */
static int mon_oydoy[] = {
	-31,	0, 	31, 	59,
	90, 	120, 	151,
	181, 	212, 	243, 
	273, 	304, 	334, 	366
};
/*
 * Useful recurring macros.
 */
#define MONLEN(y,m) (leapyear(y) ? mon_lylen[m] : mon_oylen[m])
#define MONDOY(y,m) (leapyear(y) ? mon_lydoy[m] : mon_oydoy[m])
#define MONNAM(m) mon_names[m]
#define MONABV(m) mon_abbvs[m]

#endif
