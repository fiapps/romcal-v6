#include <string.h>
#include <stdio.h>
#include "romcal.h"
#include "montab.h"

void  printtxt1(struct Info *info,
	        struct Cal cal[],
	        int iday)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL printtxt.c 6.2 02/12/06 17:40:29
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
 *	This module prints out one day (cal[iday]) from the calendar 
 *	that has been calculated by all of the other modules.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	22Jul94 : created, kgb
 *	23Jul94 : added list directed I/O, kgb
 *	03Mar95 : broke out printstr.h, kgb
 *
 *----------------------------------------------------------------------*/

#include "printstr.h"

   char  line1[75];
   char  buffer[75];

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/

   if (info->io_option == TEXT_IO) {
      sprintf(line1, 
	      "%s                %s %s                   %s",
	      ranks[cal[iday].rank],
	      daystr[DOW(iday, info->sunmod)],
	      datestr(iday, info->year),
	      colors[cal[iday].color]);

      printf("%s\n", center(line1, buffer, sizeof(buffer)));

      printf("%s\n", center(cal[iday].celebration, buffer, sizeof(buffer)));

      printf("\n");
   }
   else if (info->io_option == LIST_IO) {
      printf("%s %s:%s:%s:%s\n",
	     daystr[DOW(iday, info->sunmod)],
	     datestr(iday,info->year),
	     ranks[cal[iday].rank],
	     colors[cal[iday].color],
	     cal[iday].celebration);
   }
}

void printtxt(struct Info *info,
	      struct Cal *cal,
	      int imonth)
{
/*-------------------- Software Unit Description -----------------------*
 *
 *---------------------- Software Unit History -------------------------*
 *
 *----------------------------------------------------------------------*/

   int sdoy,
       edoy,
       idoy,
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

   for (idoy = sdoy; idoy < edoy; idoy++) {
      printtxt1(info,cal,idoy);
   }
}
