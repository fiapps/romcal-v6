#include <time.h>
#include <unistd.h>
#include <string.h>
#include "romcal.h"
#include "montab.h"

void printics(struct Info *info,
	      struct Cal *cal,
	      int imonth)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL printics.c 6.4 03/01/06 16:20:00
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
 *---------------------- Software Unit History -------------------------*
 *
 *----------------------------------------------------------------------*/

#include "printstr.h"

   int sdoy,
       edoy,
       idoy,
       imon,
       iday;

   time_t clock;

   char datetime[40];

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
 * Get the date/time stamp. The double double quotes are added to the 
 * strftime() format to fool SCCS.
 */
	 time(&clock);

	 strftime(datetime,
	          sizeof(datetime),
		  "%Y""%m""%dT%H""%M""%SZ",
		  gmtime(&clock));

	 for (idoy = sdoy; idoy < edoy; idoy++) {
	    printf("COMMENT:------------\r\n");
	    printf("COMMENT:%s\r\n", datestr(idoy, info->year));
	    printf("COMMENT:------------\r\n");
	    printf("BEGIN:VEVENT\r\n");
/*
 *          Print out the start date, which is the date of the
 *          celebration.
 */
	    doydate(info->year,
		    idoy,
		    &imon,
		    &iday);

            printf("DTSTART;VALUE=DATE:%d%02d%02d\r\n",
		   info->year,
		   imon,
		   iday);
/*
 *          Print out the end date, which is the date after the
 *          celebration. There is a special case for the end of
 *          the year.
 */
	    if (idoy == info->numdays-1) {
	       printf("DTEND;VALUE=DATE:%d0101\r\n",
		      info->year+1);
	    }
	    else {
	       doydate(info->year,
		       idoy+1,
		       &imon,
		       &iday);

	       printf("DTEND;VALUE=DATE:%d%02d%02d\r\n",
		      info->year,
		      imon,
		      iday);
	    }
/*
 *          Transparent events show up as free time.
 */
	    printf("TRANSP:TRANSPARENT\r\n");
	    printf("SEQUENCE:0\r\n");
/*
 *          The UID needs to be unique, so it is made of of the
 *          current time, the computer ID, and the day of the year
 *          of the celebration.
 */
	    printf("UID:%s-%08x-%03d\r\n",
		    datetime,
		    gethostid(),
		    idoy);
/*
 *          Time stamp is the current time.
 */
	    printf("DTSTAMP:%s\r\n",
		    datetime);
/*
 *          The description appears as the text of the calendar entry.
 */
	    printf("DESCRIPTION:Today's Color: %s\\n"
		   "Today's Rank: %s\\n\r\n",
	            colors[cal[idoy].color],
		    ranks[cal[idoy].rank]);
/*
 *          The summary is the subject of the calendar entry.
 */
	    printf("SUMMARY:%s\r\n",
	           cal[idoy].celebration);
/*
 *          Put everything into the Romcal category so that it can
 *          be sorted out and deleted if necessary.
 */
	    printf("CATEGORIES:Romcal-%s\r\n",ranks[cal[idoy].rank]);
	    printf("PRIORITY:5\r\n");
	    printf("CLASS:PUBLIC\r\n");
	    printf("END:VEVENT\r\n");
	 }

}
