#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "romcal.h"
#include "montab.h"

#define MAXLEN 25
#define HTMLEN 20

void  printmon(struct Info *info,
	       struct Cal *cal,
	       int imonth)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL printmon.c 6.3 02/12/06 17:40:28
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
 *	This module prints out the text for a given month for each I/O
 *	option.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	18Feb95 : created, kgb
 *	24Feb95 : removed the printing of the color name from the
 *		  color PS output, kgb
 *	03Mar95 : broke out printstr.h, kgb
 *	26Feb00 : fixed HTML comment, kgb
 *	08Feb02 : added WEB_IO, kgb
 *
 *----------------------------------------------------------------------*/

#include "printstr.h"

   int   sdoy,
         edoy,
         first,
         idom,
         idow,
         idoy,
	 iday,
	 imon;

   char *p,
        *wrap;

   char datetime[40];

   logical_t lastweek;

   time_t clock;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Print out any required fixed header.
 */
   monhead(info, imonth);
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
 * Branch on each I/O option.
 */
   if (info->io_option == TEXT_IO ||
       info->io_option == LIST_IO) {
      printtxt(info,cal,imonth);
   }
   else if (info->io_option == PSGREY_IO) {
      printpsg(info,cal,imonth);
   }
   else if (info->io_option == PSCOLOR_IO) {
      printpsc(info,cal,imonth);
   }
   else if (info->io_option == HTML_IO) {
      printhtm(info,cal,imonth);
   }
   else if (info->io_option == ICAL_IO) {
      printics(info,cal,imonth);
   }
   else if (info->io_option == RTF_IO) {
      printrtf(info,cal,imonth);
   }
   else if (info->io_option == WEB_IO) {
      printweb(info,cal,imonth);
   }
/*
 * Print out the fixed text that comes at the end of each month.
 */
   montail(info);
}
