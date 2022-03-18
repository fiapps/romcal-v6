#include "romcal.h"

int   advent(struct Info *info, 
	     struct Cal *cal)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL advent.c 6.1 02/12/06 17:23:55
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
 *	This module computes the Advent season.  That is, from the
 *	First Sunday of Advent until the Christmas Vigil.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	16Mar93 : created, kgb
 *	03Dec01 : modified DOWINCR() to increment week as well as day
 *		  of week, kgb
 *
 *----------------------------------------------------------------------*/
/*
 * The following table is indexed by the day of the week that Christmas falls
 * on (0=Sunday).  It contains the length in days of the Advent season.
 */
   static int adventlen[] = {28, 22, 23, 24, 25, 26, 27};

   int   advent1,
         advent3,
         dow,
         iday,
         week,
         xmas_dow;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Compute the day of the week that Christmas falls on.
 */
   xmas_dow = DOW(info->cdoy,
		  info->sunmod);
/*
 * Based on the day of the week of Christmas, we can determine the length of
 * Advent from the adventlen table.  From that, we can determine the day of
 * the First and Third Sundays of Advent.
 */
   advent1 = info->cdoy - adventlen[xmas_dow];
   advent3 = advent1 + 14;
/*
 * Fill in the Advent season.
 */
   dow = 0;
   week = 1;
   for (iday = advent1; iday < info->cdoy; iday++) {
      cal[iday].celebration = gencel(ADVENT, week, dow);
      cal[iday].season = ADVENT;

      if (iday == advent3) {
	 cal[iday].color = ROSE;
      }
      else {
	 cal[iday].color = PURPLE;
      }

      cal[iday].invitatory = NULL;

      DOWINCR(week, dow);
   }

   return (advent1);
}
