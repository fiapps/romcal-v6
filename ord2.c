#include "romcal.h"

void  ordinary2(struct Info *info, 
		struct Cal cal[], 
		int ips, 
		int iav)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL ord2.c 6.1 02/12/06 17:23:54
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
 *	This module computes Ordinary Time for the later part of the
 *	year.  That is, between Pentecost Sunday and the First Sunday
 *	of Advent.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	16Mar93 : created, kgb
 *	06Feb94 : renamed from ordinary2.c for use on a PC, kgb
 *
 *----------------------------------------------------------------------*/

   static char *ck = "Christ the King";
   int   ick;

   int   iday,
         dow,
         week;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Compute Christ the King.
 */
   ick = iav - 7;
   cal[ick].celebration = ck;
   cal[ick].season = ORDINARY;
   cal[ick].rank = SOLEMNITY;
   cal[ick].color = WHITE;
   cal[ick].invitatory = NULL;
/*
 * Compute the Ordinary Time.  Always fill in weekdays, and fill in Sundays
 * that are not Solemnities or Feasts of the Lord.
 * 
 * The following loop runs backwards.  The last week of Ordinary Time is always
 * the 34th Week of Ordinary Time.
 */
   week = 34;
   dow = 6;
   for (iday = iav - 1; iday > ips; iday--) {
      if (cal[iday].rank == WEEKDAY ||
	  (dow == 0 && cal[iday].rank < LORD)) {
	 cal[iday].celebration = gencel(ORDINARY, week, dow);
	 cal[iday].season = ORDINARY;
	 cal[iday].color = GREEN;
	 cal[iday].invitatory = NULL;
      }
      dow--;
      if (dow == -1) {
	 week--;
	 dow = 6;
      }
   }
}
