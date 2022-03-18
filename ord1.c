#include "romcal.h"

void  ordinary1(struct Info *info, 
		struct Cal cal[], 
		int ibl, 
		int iaw)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL ord1.c 6.1 02/12/06 17:23:54
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
 *	This module computes Ordinary Time for the early part of the
 *	year.  That is, between the end of Christmas season and Ash
 *	Wednesday.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	16Mar93 : created, kgb
 *	06Feb94 : renamed from ordinary1.c for use on a PC, kgb
 *	18Feb95 : based starting DOW on the DOW of the Baptism
 *		  of the Lord, rather than assuming Monday, kgb
 *	03Dec01 : modified DOWINCR() to increment the week as well as
 *		  the day of the week, kgb
 *
 *----------------------------------------------------------------------*/

   int   iday,
         dow,
         week;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Compute the Ordinary Time.  Always fill in weekdays, and fill in Sundays
 * that are not Solemnities or Feasts of the Lord.
 */
   week = 1;
   dow = DOW(ibl,info->sunmod) + 1;

   for (iday = ibl + 1; iday < iaw; iday++) {
      if (cal[iday].rank == WEEKDAY ||
	  (dow == 0 && cal[iday].rank < LORD)) {
	 cal[iday].celebration = gencel(ORDINARY, week, dow);
	 cal[iday].season = ORDINARY;
	 cal[iday].color = GREEN;
	 cal[iday].invitatory = NULL;
      }

      DOWINCR(week, dow);
   }
}
