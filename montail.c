#include <stdio.h>
#include "romcal.h"

void  montail(struct Info *info)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL montail.c 6.1 02/12/06 17:23:53
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
 *	This module prints out the fixed text which must be printed at
 *	the conclusion of each month for each I/O option.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	18Feb95 : created, kgb
 *
 *----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/

   if (info->io_option == TEXT_IO) {
      printf("\f\n");
   }
   else if (info->io_option == PSGREY_IO) {
      end_page();
   }
   else if (info->io_option == PSCOLOR_IO) {
      end_page();
   }
   else if (info->io_option == HTML_IO) {
      printf("</TABLE>\n");
      printf("<A HREF=\"#Top\">Back to top</A>\n");
      printf("<HR>\n");
   }
   else if (info->io_option == RTF_IO) {
      printf("\\pard\n");
      printf("\\ql \\li0\\ri0\\widctlpar\\aspalpha\\aspnum");
      printf("\\faauto\\adjustright\\rin0\\lin0\\itap0 \n");
      printf("{\\par \\page \\par }\n");
   }
}
