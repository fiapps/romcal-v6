#include <stdio.h>
#include "romcal.h"
#include "calheadG.h"
#include "calheadC.h"
#include "calheadH.h"
#include "calheadR.h"

void  calhead(struct Info *info)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL calhead.c 6.2 02/12/06 17:25:35
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
 * Print out the header based on the I/O option selected by the command line.
 */
   if (info->io_option == PSCOLOR_IO) {
      for (cp = calheadC; *cp != NULL; cp++) {
	 printf(*cp,info->year);
      }
   }
   else if (info->io_option == PSGREY_IO) {
      for (cp = calheadG; *cp != NULL; cp++) {
	 printf(*cp,info->year);
      }
   }
   else if (info->io_option == HTML_IO) {
      for (cp = calheadH; *cp != NULL; cp++) {
	 printf(*cp,info->year);
      }
   }
   else if (info->io_option == RTF_IO) {
      for (cp = calheadR; *cp != NULL; cp++) {
	 printf(*cp,info->year);
      }
   }
   else if (info->io_option == ICAL_IO) {
      printf("BEGIN:VCALENDAR\r\n");
      printf("PRODID:-//Romcal//Romcal//EN\r\n");
      printf("VERSION:2.0\r\n");
      printf("METHOD:PUBLISH\r\n");
   }
}
