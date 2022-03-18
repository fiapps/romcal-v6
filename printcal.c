#include "romcal.h"

void  printcal(struct Info *info,
               struct Cal *cal)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL printcal.c 6.2 02/12/06 17:40:28
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
 *	This module prints out the calendar that has been calculated
 *	by all of the other modules.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	17Mar93 : created, kgb
 *	22Jul94 : broke out printday(); added "today only" option, kgb
 *	22Jul94 : added list directed I/O capability, kgb
 *	08Feb02 : added WEB_IO as a "today only" option, kgb
 *
 *----------------------------------------------------------------------*/

   month_t month;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/

   if (info->today_only < 0) {
      calhead(info);

      for (month = JANUARY; month <= DECEMBER; month++) {
	 printmon(info,
		  cal,
		  month);
      }

      caltail(info);
   }
   else {
      if (info->io_option == LIST_IO ||
	  info->io_option == TEXT_IO) {
         printtxt1(info, 
	           cal, 
	           info->today_only);
      }
      else if (info->io_option == WEB_IO) {
	 printweb1(info,
		   cal,
		   info->today_only);
      }
   }
}
