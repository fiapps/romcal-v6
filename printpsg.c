#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "romcal.h"
#include "montab.h"

void  printpsg(struct Info *info,
	       struct Cal *cal,
	       int imonth)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL printpsg.c 6.1 02/12/06 17:23:57
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

#define MAXLEN 25

   int sdoy,
       edoy,
       idoy,
       idom,
       first;

   char *p,
	*wrap;

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
 * Loop through all of the days of the month, formatting a "Holiday"
 * command for each celebration.
 */
   for (idoy = sdoy; idoy < edoy; idoy++) {
/*
 *    Compute the day of the month.
 */
      idom = idoy - sdoy + 1;
/*
 *    Print our the color and the rank.
 */
      printf("[(%s %s) ( ) ", colors[cal[idoy].color],
	     ranks[cal[idoy].rank]);
/*
 *    Split the string at logical places.  Note that splitstr() returns
 *    allocated memory which must later be freed.
 */
      wrap = splitstr(cal[idoy].celebration,
		      MAXLEN);
/*
 *    Loop backwards through the string (since PostScript wants things
 *    in reverse order).  Find the last newline in the wrapped string,
 *    print everything after it, replace the newline with a null, and
 *    repeat until all newlines are gone.
 */
      while ((p = strrchr(wrap, '\n')) != NULL) {
	 printf("(%s) ", p + 1);
	 *p = '\0';
      }
/*
 *    Print the first part of the string with a Holiday command.
 */
      printf("(%s)] %d %d Holiday\n", wrap, first, idom);
/*
 *    Free the allocated memory.
 */
      free(wrap);
   }
}
