#include "romcal.h"

int   easter(struct Info *info, 
	     struct Cal cal[])
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL easter.c 6.1 02/12/06 17:23:54
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
 *	This module computes the Easter season.  That is, from Easter
 *	Sunday until Pentecost Sunday.  Additionally, it will compute
 *	those feast which occur after Pentecost but still depend on
 *	the date of Easter.  That is, Trinity Sunday, Corpus Christi,
 *	Sacred Heart, and Immaculate Heart.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	16Mar93 : created, kgb
 *	19Mar93 : added options.h, kgb
 *	20Jul94 : removed options.h; added options to struct Info, kgb
 *	05Mar95 : changed proper color of Sacred Heart to white, kgb
 *	31Mar95 : adjusted the Easter Octave to include the following
 *		  Sunday as part of the "PASCHAL" season, kgb
 *	01Apr96 : added OCTLEN, kgb
 *	06Sep01 : Imm. Heart of Mary is now a Memorial. Version 4 had
 *		  the rank correct, but it didn't print when the
 *		  Optional Memorials were printed. This is now fixed,
 *		  kgb
 *	18sep01 : Changed the color for the Immaculate Heart to white
 *		  from green, kgb
 *	03Dec01 : Modified DOWINCR() to increment week as well as day
 *		  of week, kgb
 *
 *----------------------------------------------------------------------*/

#define OCTLEN NUMBEROF(eaoctave)

   static char *eaoctave[] =
   {
      "Easter Sunday",
      "Monday in the Octave of Easter",
      "Tuesday in the Octave of Easter",
      "Wednesday in the Octave of Easter",
      "Thursday in the Octave of Easter",
      "Friday in the Octave of Easter",
      "Saturday in the Octave of Easter",
      "Second Sunday of Easter"
   };

   static char *at = "Ascension of the Lord";
   int   iat;

   static char *ps = "Pentecost Sunday";
   int   ips;

   static char *ts = "Trinity Sunday";
   int   its;

   static char *cc = "Corpus Christi";
   int   icc;

   static char *sh = "Sacred Heart of Jesus";
   int   ish;

   static char *ih = "Immaculate Heart of Mary";
   int   iih;

   int   east,
         dow,
         iday,
         week;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Compute the Octave of Easter.  The days following Easter, up to and
 * including the Second Sunday of Easter ("Low Sunday") are considered
 * Solemnities and are part of the "PASCHAL" season.  This is important
 * for the computation of the Annunciation in proper.c
 */
   east = info->edoy;
   for (iday = 0; iday < OCTLEN; iday++) {
      cal[iday + east].celebration = eaoctave[iday];
      cal[iday + east].season = PASCHAL;
      cal[iday + east].rank = SOLEMNITY;
      cal[iday + east].color = WHITE;
      cal[iday + east].invitatory = NULL;
   }
/*
 * Compute Pentecost Sunday.
 */
   ips = info->edoy + 49;
   cal[ips].celebration = ps;
   cal[ips].season = EASTER;
   cal[ips].rank = SOLEMNITY;
   cal[ips].color = RED;
   cal[ips].invitatory = NULL;
/*
 * Compute the Easter Season.
 */
   dow = 1;
   week = 2;
   for (iday = info->edoy + 8; iday < ips; iday++) {
      cal[iday].celebration = gencel(EASTER, week, dow);
      cal[iday].season = EASTER;
      cal[iday].color = WHITE;
      cal[iday].invitatory = NULL;
      DOWINCR(week, dow);
   }
/*
 * Compute Ascension Thursday.
 */
   if (info->as_on_sun) {
      iat = info->edoy + 42;
   }
   else {
      iat = info->edoy + 39;
   }
   cal[iat].celebration = at;
   cal[iat].season = EASTER;
   cal[iat].rank = SOLEMNITY;
   cal[iat].color = WHITE;
   cal[iat].invitatory = NULL;
/*
 * Compute Trinity Sunday.
 */
   its = info->edoy + 56;
   cal[its].celebration = ts;
   cal[its].season = ORDINARY;
   cal[its].rank = SOLEMNITY;
   cal[its].color = WHITE;
   cal[its].invitatory = NULL;
/*
 * Compute Corpus Christi.
 */
   if (info->cc_on_thurs) {
      icc = info->edoy + 60;
   }
   else {
      icc = info->edoy + 63;
   }
   cal[icc].celebration = cc;
   cal[icc].season = ORDINARY;
   cal[icc].rank = SOLEMNITY;
   cal[icc].color = WHITE;
   cal[icc].invitatory = NULL;
/*
 * Compute the Sacred Heart of Jesus.
 */
   ish = info->edoy + 68;
   cal[ish].celebration = sh;
   cal[ish].season = ORDINARY;
   cal[ish].rank = SOLEMNITY;
   cal[ish].color = WHITE;
   cal[ish].invitatory = NULL;
/*
 * Compute the Immaculate Heart of Mary.
 */
   iih = info->edoy + 69;
   cal[iih].celebration = ih;
   cal[iih].season = ORDINARY;
   cal[iih].rank = MEMORIAL;
   cal[iih].color = WHITE;
   cal[iih].invitatory = NULL;

   return (ips);
}
