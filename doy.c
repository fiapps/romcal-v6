#include "romcal.h"

int   doy(int year, 
	  int month, 
	  int day)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL doy.c 6.1 02/12/06 17:23:56
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
 *	This module computes the day of the year of a given date.
 *	Range:  Leap year (0 - 365)
 *		Otherwise (0 - 364)
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	14Mar93 : created, kgb
 *	10Dec94 : added "extra" month to tables, kgb
 *
 *----------------------------------------------------------------------*/
/*
 * An "extra" month is included in the following tables so that the start
 * day-of-year and end day-of-year for every month can be computed. For
 * example:  "sdoy = doy(1994, 12, 1); edoy = doy(1994, 13, 1) - 1;" would
 * work for December, 1994.
 */
   static int lytable[] =
   {
      0, 31, 60, 91, 121, 152,
      182, 213, 244, 274, 305, 335, 366
   };

   static int oytable[] =
   {
      0, 31, 59, 90, 120, 151,
      181, 212, 243, 273, 304, 334, 365
   };

   int   ly,
         retval;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Determine if this is a leap year.
 */
   ly = leapyear(year);
/*
 * Using the appropriate table, determine the day of the year, subtracting 1
 * to make things zero relative.
 */
   if (ly) {
      retval = lytable[month - 1] + day - 1;
   }
   else {
      retval = oytable[month - 1] + day - 1;
   }

   return (retval);
}
