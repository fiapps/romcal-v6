#include <string.h>
#include "romcal.h"
#include "montab.h"

void  printhtm(struct Info *info,
	       struct Cal *cal,
	       int imonth)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL printhtm.c 6.1 02/12/06 17:23:57
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
	 idom,
         first;

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
 * Begin the first table row.
 */
   printf("<TR>\n");
/*
 * At the beginning of each month, skip over to the proper day of the
 * week.
 */
   if (first) {
      printf("<TD COLSPAN=%d> </TD>\n", first);
   }
/*
 * Loop through all of the days in the month.
 */
   for (idoy = sdoy; idoy < edoy; idoy++) {
/*
 *    Provide a comment so we can find the day of the month in the HTML
 *    file.
 */
      printf("\n<!--%s-->\n\n", datestr(idoy, info->year));
/*
 *    Determine the day of the month.
 */
      idom = idoy - sdoy + 1;
/*
 *    Print the table data tag. This includes the color for the square.
 */
      printf("<TD VALIGN=TOP "
	     "WIDTH=\"100\" HEIGHT=\"100\" BGCOLOR=\"%s\">\n",
	     htmlcolors[cal[idoy].color]);
/*
 *    Center the strings within the square.
 */
      printf("<CENTER>\n");
/*
 *    Print the day of the month.
 */
      printf("<FONT COLOR=\"#000000\" SIZE=\"+1\">");
      printf("%d", idom);
      printf("</FONT><BR>\n");
/*
 *    Print the celebration for that day.
 */
      printf("<FONT COLOR=\"#000000\">");
      printf("%s", cal[idoy].celebration);
      printf("</FONT><BR>\n");
/*
 *    Print the rank of the celebration.
 */
      printf("<FONT COLOR=\"#000000\" SIZE=\"-1\">");
      printf("%s", ranks[cal[idoy].rank]);
      printf("</FONT>\n");
/*
 *    Close the center tag and the table data tag.
 */
      printf("</CENTER>\n");
      printf("</TD>\n\n");
/*
 *    At the end of each week, end the table row, and begin the one for
 *    the next week.
 */
      if (DOW(idoy, info->sunmod) == 6) {
	 printf("</TR>\n\n");
	 printf("<TR VALIGN=\"TOP\">\n");
      }
   }
/*
 * Close the final row.
 */
   printf("</TR>\n\n");
}
