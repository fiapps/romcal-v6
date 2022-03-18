#include <stdio.h>
#include "romcal.h"
#include "montab.h"
#include "monheadH.h"
#include "monheadR.h"

void  monhead(struct Info *info,
              int   month)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL monhead.c 6.1 02/12/06 17:23:53
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
 *	This module will print the fixed text which must be printed at 
 *	the beginning of a month for each I/O option.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	18Feb95 : created, kgb
 *
 *----------------------------------------------------------------------*/

   char **cp;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/

   if (info->io_option == PSGREY_IO) {
      do_page1(month,
	      info->year,
	      DOW(MONDOY(info->year, month), info->sunmod));

      do_page2(month,
	      info->year,
	      DOW(MONDOY(info->year, month), info->sunmod));
   }
   else if (info->io_option == PSCOLOR_IO) {
      do_page1(month,
	      info->year,
	      DOW(MONDOY(info->year, month), info->sunmod));

   }
   else if (info->io_option == HTML_IO) {
      for (cp = monheadH; *cp != NULL; cp++) {
	 printf(*cp,mon_names[month],info->year);
      }
   }
   else if (info->io_option == RTF_IO) {
      for (cp = monheadR; *cp != NULL; cp++) {
	 printf(*cp,mon_names[month],info->year);
      }
   }
}
