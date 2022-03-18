#include <stdio.h>
#include "romcal.h"
#include "caltailH.h"
#include "caltailR.h"

void  caltail(struct Info *info)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL caltail.c 6.2 02/12/06 17:25:03
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
 *	This module will write to stdout any required file header.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	08jan95 : created, kgb
 *
 *----------------------------------------------------------------------*/

   char **cp;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Print out the trailer based on the I/O option selected by the command line.
 */
   if (info->io_option == HTML_IO) {
      for (cp = caltailH; *cp != NULL; cp++) {
	 printf(*cp,info->year);
      }
   }
   else if (info->io_option == RTF_IO) {
      for (cp = caltailR; *cp != NULL; cp++) {
	 printf(*cp,info->year);
      }
   }
   else if (info->io_option == ICAL_IO) {
      printf("END:VCALENDAR\r\n");
   }
}
