#include "romcal.h"

void  init(struct Info *info, 
	   struct Cal cal[])
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL init.c 6.2 03/01/06 16:16:22
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
 *	This module initializes the Info and Cal data structures.  It
 *	returns a pointer to the Info structure that other modules
 *	will need to use.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	14Mar93 : created, kgb
 *	20Jul94 : modified to accept the Info structure as an argument;
 *		  moved init of Info structure to parse(),
 *		  kgb
 *
 *----------------------------------------------------------------------*/

   int   iday;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Init the calendar structure.
 */
   for (iday = 0; iday < info->numdays; iday++) {
      if (iday % 7 == info->sunmod) {
	 cal[iday].rank = SUNDAY;
      }
      else {
	 cal[iday].rank = WEEKDAY;
      }
      cal[iday].color = GREEN;
      cal[iday].celebration = NULL;
      cal[iday].invitatory = NULL;
      cal[iday].season = ORDINARY;
   }
}
