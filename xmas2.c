#include "romcal.h"

void  christmas2(struct Info *info, 
		 struct Cal cal[])
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL xmas2.c 6.1 02/12/06 17:23:56
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
 *	This module computes the portion of the Christmas season
 *	that occurs at the end of the year.  That is, from Christmas
 *	Day until Jan. 31.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	16Mar93 : created, kgb
 *	06Feb94 : renamed to xmas2.c for use on a PC, kgb
 *	21Dec01 : corrected the Octave of Christmas; added dow_t, kgb
 *
 *----------------------------------------------------------------------*/

   static char *hf = "Holy Family";
/*
 * Note that the first three days of the Octave will be overwritten by
 * the fixed feasts of Stephen, M; John, Ap and Ev; and Holy Innocents,
 * Mm. This will happen later when the fixed celebrations are added to
 * the calendar.
 */
   static char *cmoctave[] =
   {
      "Second day in the Octave of Christmas",
      "Third day in the Octave of Christmas",
      "Fourth day in the Octave of Christmas",
      "Fifth day in the Octave of Christmas",
      "Sixth day in the Octave of Christmas",
      "Seventh day in the Octave of Christmas"
   };

   int   iday,
	 dec26,
         dec30;

   dow_t dow;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Compute the week following Christmas.  The Sunday between Dec. 26 and Dec.
 * 31 is Holy Family.
 */
   dec26 = info->cdoy + 1;

   for (iday = dec26; iday < info->numdays; iday++) {
      dow = DOW(iday, info->sunmod);

      if (dow == DOW_SUNDAY) {
         cal[iday].celebration = hf;
	 cal[iday].rank = LORD;
      }
      else {
	 cal[iday].celebration = cmoctave[iday - dec26];
      }

      cal[iday].season = CHRISTMAS;
      cal[iday].color = WHITE;
      cal[iday].invitatory = NULL;
   }
/*
 * If Christmas falls on a Sunday, then there is no Sunday between Dec. 26
 * and Dec. 31.  In that case, Holy Family is celebrated on Dec. 30.
 */
   if (DOW(info->cdoy, info->sunmod) == DOW_SUNDAY) {
      dec30 = doy(info->year, 12, 30);
      cal[dec30].celebration = hf;
      cal[iday].season = CHRISTMAS;
      cal[iday].rank = LORD;
      cal[iday].color = WHITE;
      cal[iday].invitatory = NULL;
   }
}
