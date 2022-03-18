#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "romcal.h"

void  printweb1(struct Info *info,
	        struct Cal cal[],
	        int iday)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL printweb.c 6.2 02/12/06 17:40:28
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
 *	This module will create an HTML file suitable for use as the 
 *	banner on the romcal.net web site. One file will be created
 *	whose name is yyyymmdd.htm, where yyyy is the year, mm is the 
 *	month (01-12), and dd is the day (01-31).
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	10jan02 : created, kgb
 *
 *----------------------------------------------------------------------*/

#include "printstr.h"

   FILE *fp;

   char *filename;

   int month, day;

   static char *gifcolors[] =
   {
      "NOCOLOR",
      "green",
      "white",
      "red",
      "purple",
      "rose",
      "black"
   };

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Form the filename of the output HTML file. This based on the date
 * of the celebration and has the form yyyymmdd.html.
 */
   filename = malloc(strlen(info->webio_dir) + 40);

   doydate(info->year,
	   iday,
	   &month,
	   &day);

   sprintf(filename,
	   "%s/%04d%02d%02d.html",
	   info->webio_dir,
	   info->year,
	   month,
	   day);
/*
 * Open the output file.
 */
   if ((fp = fopen(filename,"w")) == NULL) {
      fprintf(stderr, "Cannot create %s\n",filename);
      return;
   }
/*
 * Ouput the HTML header.
 */
   fprintf(fp, "<html>\n");
   fprintf(fp, "<head>\n");
   fprintf(fp, "</head>\n");
/*
 * Begin the HTML body.
 */
   fprintf(fp, "<body background=\"../images/background.jpg\" nosave>\n");
   fprintf(fp, "\n");
/*
 * The banner image.
 */
   fprintf(fp, "<center>\n");
   fprintf(fp, "<a href=\"/index.html\" target=\"_top\">\n");
   fprintf(fp, "<img SRC=\"../images/%s.gif\" border=0 nosave>\n",
	       gifcolors[cal[iday].color]);
   fprintf(fp, "</a>\n");
   fprintf(fp, "</center>\n");
   fprintf(fp, "\n");
/*
 * The date, celebration, and rank.
 */
   fprintf(fp, "<center>\n");
   fprintf(fp, "<table WIDTH=\"100%%\" HEIGHT=\"40\" NOSAVE >\n");
   fprintf(fp, "<tr NOSAVE>\n");
   fprintf(fp, "<td WIDTH=\"15%%\" NOSAVE>\n");
   fprintf(fp, "<font SIZE=-1>%s %s</font>\n",
	        daystr[DOW(iday, info->sunmod)],
	        datestr(iday, info->year));
   fprintf(fp, "</td>\n");
   fprintf(fp, "\n");

   fprintf(fp, "<td NOSAVE>\n");
   fprintf(fp, "<center>\n");
   fprintf(fp, "<b>%s</b>\n", 
	       cal[iday].celebration);
   fprintf(fp, "</center>\n");
   fprintf(fp, "</td>\n");
   fprintf(fp, "\n");

   fprintf(fp, "<td WIDTH=\"15%%\" NOSAVE>\n");
   fprintf(fp, "<div align=right><font SIZE=-1>%s</font></div>\n",
	       ranks[cal[iday].rank]);
   fprintf(fp, "</td>\n");
   fprintf(fp, "</tr>\n");
   fprintf(fp, "</table>\n");
   fprintf(fp, "</center>\n");
   fprintf(fp, "\n");
/*
 * Close the HTML body.
 */
   fprintf(fp, "</body>\n");
   fprintf(fp, "</html>\n");
/*
 * Close the output file.
 */
   fclose(fp);
}

void  printweb(struct Info *info,
	       struct Cal cal[],
	       int imonth)
{
/*-------------------- Software Unit Description -----------------------*
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	06dec02 : created, kgb
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
      printweb1(info,cal,idoy);
   }
}
