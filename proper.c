#include "romcal.h"

void  proper(info, cal)
struct Info *info;
struct Cal cal[];
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL proper.c 6.1 02/12/06 17:23:56
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
 *	This module fills in the "proper" portion of the calendar.  That
 *	is, those feasts, memorials, and solemnities that occur on the
 *	same date every year.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	14Mar93 : created, kgb
 *	19Dec93 : added options.h, kgb
 *	20Jul94 : removed options.h; added options to struct Info, kgb
 *	03Mar95 : added the rank of COMMEMORATION for memorials in the
 *		  lenten season, kgb
 *	31Mar95 : added code to transfer a Solemnity occurring during
 *		  the PASCHAL season (Holy Week and the Octave of
 *		  Easter), kgb
 *	01Apr96 : changed Commemoration to be like Optional Memorials
 *		  for printing, kgb
 *
 *----------------------------------------------------------------------*/

#include "fixed.h"

#define ST_JOSEPH 19 	/* March 19 */
#define ANNUNCIATION 25	/* March 25 */

   int   ifix,
         iday;

   logical_t overwrite;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/

   for (ifix = 0; ifix < NUMBEROF(fixed); ifix++) {
/*
 *    Determine the day of the year we are working with.
 */
      iday = doy(info->year,
		 fixed[ifix].month,
		 fixed[ifix].day);
/*
 *    It is possible for two Solemnties to occur during the PASCHAL
 *    season (Holy Week and the Octave of Easter): St. Joseph (March
 *    19) and the Annunciation (March 25). St. Joseph is moved backward
 *    to the Saturday before Palm Sunday. Annunciation is moved forward
 *    to the Monday after the Second Sunday of Easter, unless it falls
 *    on Palm Sunday. In that case it is moved to the preceeding
 *    Saturday (i.e., Saturday of the Fifth Week of Lent).
 */
      while (cal[iday].season == PASCHAL &&
	     fixed[ifix].rank == SOLEMNITY) {
	 if (cal[iday-1].season != PASCHAL ||
	     fixed[ifix].day == ST_JOSEPH) {
	    iday--;
	 }
	 else {
	    iday++;
	 }
      }
/*
 *    Copy the proper (fixed) information into the calendar.
 */
      if (fixed[ifix].rank == OPTIONAL &&
	  !info->print_optionals) {
	 overwrite = L_FALSE;
      }
      else if (cal[iday].season == LENT &&
	       fixed[ifix].rank == MEMORIAL &&
	       !info->print_optionals) {
/*
 *       Consider a Commemoration (i.e., Memorial in Lent) to be like
 *       an Optional Memorial for printing purposes.
 */
	 overwrite = L_FALSE;
      }
      else if (fixed[ifix].rank > cal[iday].rank) {
	 overwrite = L_TRUE;
/*
 *       When a Feast of the Lord, or a Solemnity occurs on a Sunday in
 *       Lent, Advent, or Easter, transfer it to the following day.
 *       Otherwise, overwrite the Sunday.
 */
	 if (cal[iday].rank == SUNDAY &&
	     (cal[iday].season == LENT ||
	      cal[iday].season == ADVENT ||
	      cal[iday].season == EASTER)) {
	    iday++;
	 }
      }
      else {
	 overwrite = L_FALSE;
      }
/*
 *    If this celebration should overwrite one already assigned to this
 *    day, then do so.
 */
      if (overwrite) {
	 cal[iday].celebration = fixed[ifix].celebration;
	 cal[iday].rank = fixed[ifix].rank;
/*
 *       If the rank of the fixed celebration is less than a Feast
 *       (i.e., an Optional Memorial or a Memorial), and the season is
 *       Lent, then the rank of the fixed celebration is reduced to a
 *       Commemoration, and the color remains the color of the season.
 *       In all other cases, the rank of the fixed celebration replaces
 *       the rank of the seasonal celebration, and, if the fixed
 *       celebration has a proper color, the color of the fixed
 *       celebration replaces the color of the seasonal celebration.
 */
	 if (cal[iday].rank < FEAST &&
	     cal[iday].season == LENT) {
	    cal[iday].rank = COMMEMORATION;
	 }
	 else if (fixed[ifix].color != NOCOLOR) {
	    cal[iday].color = fixed[ifix].color;
	 }

	 cal[iday].invitatory = fixed[ifix].invitatory;
      }
   }
}
