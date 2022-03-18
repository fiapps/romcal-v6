#include "romcal.h"

int   lent(struct Info *info,
           struct Cal *cal)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL lent.c 6.1 02/12/06 17:23:54
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
 *	This module computes the season of Lent.  That is, from Ash
 *	Wednesday until the Easter Vigil.  It returns the day number
 *	of Ash Wednesday.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	16Mar93 : created, kgb
 *	01Apr96 : added Triduum rank, kgb
 *	26Feb00 : added Ash Wednesday rank, kgb
 *	03Dec01 : modified DOWINCR() to increment the week as well as
 *		  the day of the week, kgb
 *	21Dec01 : added use of dow_t, kgb
 *
 *----------------------------------------------------------------------*/

   static char *ash_week[] =
   {
      "Ash Wednesday",
      "Thursday after Ash Wednesday",
      "Friday after Ash Wednesday",
      "Saturday after Ash Wednesday"
   };

   static rank_t aw_rank[] =
   { ASHWED, WEEKDAY, WEEKDAY, WEEKDAY };

   static char *holy_week[] =
   {
      "Palm Sunday",
      "Monday of Holy Week",
      "Tuesday of Holy Week",
      "Wednesday of Holy Week",
      "Holy Thursday",
      "Good Friday",
      "Easter Vigil"
   };

   static color_t hw_color[] =
   {
      RED, PURPLE, PURPLE, PURPLE, WHITE, RED, WHITE
   };

   static rank_t hw_rank [] =
   {
      SUNDAY, HOLYWEEK, HOLYWEEK, HOLYWEEK, TRIDUUM, TRIDUUM, TRIDUUM 
   };

   int   iaw,
         lent1,
         lent4,
         palm,
         week,
         iday;

   dow_t dow;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Compute Ash Wednesday.
 */
   iaw = info->edoy - 46;

   for (iday = 0; iday < 4; iday++) {
      cal[iday + iaw].celebration = ash_week[iday];
      cal[iday + iaw].season = LENT;
      cal[iday + iaw].color = PURPLE;
      cal[iday + iaw].rank = aw_rank[iday];
      cal[iday + iaw].invitatory = NULL;
   }
   cal[iaw].season = PASCHAL;;
/*
 * Compute the First and Fourth Sundays of Lent.
 */
   lent1 = iaw + 4;
   lent4 = iaw + 25;
/*
 * Compute Palm Sunday.
 */
   palm = info->edoy - 7;
/*
 * Fill in Lent up to Palm Sunday.
 */
   dow = DOW_SUNDAY;
   week = 1;
   for (iday = lent1; iday < palm; iday++) {
      cal[iday].celebration = gencel(LENT, week, dow);
      cal[iday].season = LENT;

      if (iday == lent4) {
	 cal[iday].color = ROSE;
      }
      else {
	 cal[iday].color = PURPLE;
      }

      cal[iday].invitatory = NULL;

      DOWINCR(week, dow);
   }
/*
 * Compute Holy Week.
 */
   dow = DOW_SUNDAY;
   for (iday = palm; iday < info->edoy; iday++) {
      cal[iday].celebration = holy_week[dow];
      cal[iday].season = PASCHAL;
      cal[iday].color = hw_color[dow];
      cal[iday].invitatory = NULL;
      cal[iday].rank = hw_rank[dow];
      dow++;
   }

   return (iaw);
}
