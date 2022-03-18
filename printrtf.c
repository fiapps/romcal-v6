#include <string.h>
#include <stdio.h>
#include "romcal.h"
#include "montab.h"

void  printrtf(struct Info *info,
	       struct Cal *cal,
	       int imonth)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL printrtf.c 6.1 02/12/06 17:23:58
 *
 *	Copyright (C) 1993-2002, Kenneth G. Bath
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
 *---------------------- Software Unit History -------------------------*
 *
 *----------------------------------------------------------------------*/

#include "printstr.h"

   int   sdoy,
         edoy,
         idoy,
         first,
	 idow,
	 idom;

   logical_t lastweek;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Compute the starting day-of-year and ending day-of-year for the
 * first and last day of this month.
 */
   sdoy = doy(info->year, imonth, 1);
   edoy = doy(info->year, imonth + 1, 1);
/*
 * Compute the day of the week of the first day of this month.
 */
   first = DOW(sdoy, info->sunmod);
/*
 * Print out the text control words for the first row.
 */
   rtfrow(L_FALSE);
/*
 * For the first week, output empty cells until we reach the first day
 * of the month.
 */
   if (first) {
      printf("{");
      for (idow = 0; idow < first; idow++) {
	 printf("\\cell ");
      }
      printf("}\n");
   }
/*
 * Loop through the days of the month.
 */
   for (idoy = sdoy; idoy < edoy; idoy++) {
/*
 *    Compute the day of the month.
 */
      idom = idoy - sdoy + 1;
/*
 *    Print the day of the month.
 */
      printf("{\\b\\i\\fs36\\ul\\cf%d %d}\n",
	     rtfcolors[cal[idoy].color], idom);
/*
 *    Print the rank of the day, and the color abbreviation. Use "Ro"
 *    for rose, and the first character of the color's name in every
 *    other case.
 */
      printf("{\\fs16\\ul\\cf%d  \\tab ",
	     rtfcolors[cal[idoy].color]);

      if (cal[idoy].color == ROSE) {
	 printf("%s\\tab Ro \\par }\n",
		ranks[cal[idoy].rank]);
      }
      else {
	 printf("%s\\tab %c \\par }\n",
		ranks[cal[idoy].rank],
		*colors[cal[idoy].color]);
      }
/*
 *    Print the celebration.
 */
      printf("{\\f28\\fs16 %s\\cell }\n",
	     cal[idoy].celebration);
/*
 *    At the end of the week, print out then end-of-row tags. In the
 *    case of the last week of the month, the border is different so a
 *    flag is passed in.
 */
      if (DOW(idoy, info->sunmod) == 6) {
	 printf("\\row\n\n");
	 lastweek = (idoy + 7) >= (edoy - 1);
	 rtfrow(lastweek);
      }
   }
/*
 * RTF requires that the number of \cell tags match the number of
 * columns defined. If the month does not end on a Saturday, the we
 * have to write out \cell tags until we reach Saturday.
 * 
 * Note that idoy was incremented at the end of the loop. If the month
 * ended on a Saturday, then DOW(idoy) would now be a Sunday.
 */
   if (DOW(idoy, info->sunmod) != 0) {
      printf("{");
      while (DOW(idoy, info->sunmod) != 0) {
	 printf("\\cell ");
	 idoy++;
      }
      printf("}\n");
      printf("\\row\n");
   }
}
