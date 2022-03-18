#include <stdio.h>
#include "caltypes.h"

/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL rtfrow.c 6.1 02/12/06 17:23:53
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
 *	This module prints out the text that is found at the beginning
 *	of a row of a table in an RTF file.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	22Dec00 : created, kgb
 *
 *----------------------------------------------------------------------*/
void rtfrow(logical_t lastweek)
{
   char **cp;

   static char *lastrow[] = {
"\\trowd \n",
"\\trqc\\trgaph108\\trrh1512\\trleft-108\\trkeep\n",
"\\trbrdrt\\brdrthtnsg\\brdrw60 \\trbrdrl\\brdrthtnsg\\brdrw60 \n",
"\\trbrdrb\\brdrtnthsg\\brdrw60 \\trbrdrr\\brdrtnthsg\\brdrw60 \n",
"\\trbrdrh\\brdrs\\brdrw15 \\trbrdrv\\brdrs\\brdrw15 \n",
"\\trftsWidth1\\trautofit1\\trpaddl108\\trpaddr108\\trpaddfl3\\trpaddfr3 \n",
"\\clvertalt\n",
"\\clbrdrt\\brdrs\\brdrw15 \\clbrdrl\\brdrthtnsg\\brdrw60 \n",
"\\clbrdrb\\brdrtnthsg\\brdrw60 \\clbrdrr\\brdrs\\brdrw15 \n",
"\\cltxlrtb\\clftsWidth3\\clwWidth1999 \\cellx1891\n",
"\\clvertalt\n",
"\\clbrdrt\\brdrs\\brdrw15 \\clbrdrl\\brdrs\\brdrw15 \n",
"\\clbrdrb\\brdrtnthsg\\brdrw60 \\clbrdrr\\brdrs\\brdrw15 \n",
"\\cltxlrtb\\clftsWidth3\\clwWidth2004 \\cellx3895\n",
"\\clvertalt\n",
"\\clbrdrt\\brdrs\\brdrw15 \\clbrdrl\\brdrs\\brdrw15 \n",
"\\clbrdrb\\brdrtnthsg\\brdrw60 \\clbrdrr\\brdrs\\brdrw15 \n",
"\\cltxlrtb\\clftsWidth3\\clwWidth2004 \\cellx5899\n",
"\\clvertalt\n",
"\\clbrdrt\\brdrs\\brdrw15 \\clbrdrl\\brdrs\\brdrw15 \n",
"\\clbrdrb\\brdrtnthsg\\brdrw60 \\clbrdrr\\brdrs\\brdrw15 \n",
"\\cltxlrtb\\clftsWidth3\\clwWidth2022 \\cellx7921\n",
"\\clvertalt\n",
"\\clbrdrt\\brdrs\\brdrw15 \\clbrdrl\\brdrs\\brdrw15 \n",
"\\clbrdrb\\brdrtnthsg\\brdrw60 \\clbrdrr\\brdrs\\brdrw15 \n",
"\\cltxlrtb\\clftsWidth3\\clwWidth2010 \\cellx9931\n",
"\\clvertalt\n",
"\\clbrdrt\\brdrs\\brdrw15 \\clbrdrl\\brdrs\\brdrw15 \n",
"\\clbrdrb\\brdrtnthsg\\brdrw60 \\clbrdrr\\brdrs\\brdrw15 \n",
"\\cltxlrtb\\clftsWidth3\\clwWidth1994 \\cellx11925\n",
"\\clvertalt\n",
"\\clbrdrt\\brdrs\\brdrw15 \\clbrdrl\\brdrs\\brdrw15 \n",
"\\clbrdrb\\brdrtnthsg\\brdrw60 \\clbrdrr\\brdrtnthsg\\brdrw60 \n",
"\\cltxlrtb\\clftsWidth3\\clwWidth2007 \\cellx13932\n",
"\n",
NULL
};
/*
 * If this is the last row (week), then the borders for the bottom edge
 * of the calendar need to be defined. Put out the RTF control words
 * for the last row.
 */
   if (lastweek) {
      for (cp = lastrow; *cp != NULL; cp++) {
         printf(*cp);
      }
   }
   printf("\n");
/*
 * Print out the text control words for the table. The important
 * tags are the \qc for centered text, \tqc\tx864 for the centered
 * tab and \tqr\tx1728 for the right justified second tab.
 */
   printf("\\pard \\qc \n");
   printf("\\li0\\ri0\\widctlpar\\intbl\\tqc\\tx864\\tqr\\tx1728\n");
   printf("\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\n");
}

