#include <stdio.h>

char *datestr(int doy, 
	      int year)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL datestr.c 6.1 02/12/06 17:23:55
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
 *	This module will return a pointer to a character string of
 *	a date given the day of year and year.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	14Mar93 : created, kgb
 *	08Feb02 : recoded to use doydate, kgb
 *
 *----------------------------------------------------------------------*/

   static char *montab[] =
   {
      "Jan", "Feb", "Mar", "Apr", "May", "Jun",
      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
   };

   int   imon,
         iday;

   static char retval[40];

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Convert the day of the year to month/day.
 */
   doydate(year, doy, &imon, &iday);
/*
 * Form a string with the month, day, and year.
 */
   sprintf(retval, "%s %2d, %d", montab[imon-1], iday, year);

   return (&retval[0]);
}
