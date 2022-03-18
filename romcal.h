#ifndef ROMCAL_H
#define ROMCAL_H
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL romcal.h 6.1 02/12/06 17:23:53
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
 *	This is the general purpose include file for the 'romcal' 
 *	program. 
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	14Mar93 : created, kgb
 *	19Dec93 : moved externals to options.h, kgb
 *	22Jul94 : added options to Info structure, kgb
 *	22Jul94 : added list directed I/O option, kgb
 *	30Jan95 : broke out type declarations, kgb
 *	09Mar01 : added NUMBEROF() macro, kgb
 *	03Dec01 : modified DOWINCR() macro to increment the week, kgb
 *	08Feb02 : added webio_dir member to Info structure, kgb
 *
 *----------------------------------------------------------------------*/
#include "caltypes.h"
/*
 * The struct 'Cal' contains all of the information for a given day
 * in the calendar.
 */
struct Cal {
   month_t month;		/* Month of Year (1-12)		*/
   int day;			/* Day of Month (1-31)		*/
   color_t color;		/* White, Red, Green, etc.	*/
   rank_t rank;			/* Feast, Solemnity, etc.	*/
   season_t season;		/* Advent, Lent, Ordinary, etc.	*/
   char *celebration;		/* "Christmas", "Easter", etc.	*/
   char *invitatory;		/* Invitatory of the day	*/
};
/*
 * The struct 'Info' contains information which pertains to the calendar
 * as a whole, including options selected by the user.
 */
struct Info {
   int year;			/* Gregorian year		*/
   int numdays;			/* Number of days (365 or 366)	*/
   int edoy;			/* Day of year of Easter 	*/
   int cdoy;			/* Day of year of Christmas 	*/
   int sunmod;			/* Sunday Modulo		*/
   logical_t cc_on_thurs;	/* Corpus Christi on Thursday	*/
   logical_t ep_on_jan6;	/* Epiphany on Jan. 6 		*/
   logical_t as_on_sun;		/* Ascension on Sunday		*/
   logical_t print_optionals; 	/* Print Optional Memorials 	*/
   int today_only;		/* Print today's feast only 	*/
   io_t io_option;		/* Text, List, Postscript, etc	*/
   char *webio_dir;		/* Output directory for Web I/O */
};
/*
 * Macro for calculating day of week. (0=Sunday, etc.)
 */
#define DOW(doy,sunmod) ((doy+7-sunmod)%7)
/*
 * Macro for incrementing the week and day-of-week counters. The counter
 * 'd' will increment 0 1 2 3 4 5 6 0 1 2 3 4 5 6 0 ... Whenever, d is
 * equal to zero, the counter 'w' will increment. Note that 'd' and 'w'
 * must be variables when this macro is used. They cannot be constants
 * or expressions.
 */
#define DOWINCR(w,d) (w = ((d = (d+1)%7) == 0) ? (w + 1) : (w));
/*
 * Macro for finding the number of entries in an array.
 */
#define NUMBEROF(a) (sizeof(a)/sizeof(a[0]))

#ifndef NULL
#define NULL 0
#endif

#include "proto.h"
#endif
