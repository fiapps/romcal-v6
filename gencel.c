#include <string.h>
#include "romcal.h"

char *gencel(season_t season, 
	     int weeknum, 
	     dow_t dow)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL gencel.c 6.1 02/12/06 17:23:55
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
 *	This module returns the general name of a celebration
 *	given a season, a week number, and a day of the week
 *	(0 = Sunday, etc.).  The return value is a character
 *	pointer returned from malloc().
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	16Mar93 : created, kgb
 *	21Dec01 : added use of dow_t and season_t, kgb
 *
 *----------------------------------------------------------------------*/

   char *malloc();

   static char *seatab[] =
   {
      "Ordinary Time",
      "Advent",
      "Christmas",
      "Lent",
      "Easter"
   };

   static char *daytab[] =
   {
      "Sunday",
      "Monday",
      "Tuesday",
      "Wednesday",
      "Thursday",
      "Friday",
      "Saturday"
   };

   static char *numtab[] =
   {
      "",
      "First",
      "Second",
      "Third",
      "Fourth",
      "Fifth",
      "Sixth",
      "Seventh",
      "Eighth",
      "Ninth",
      "Tenth",
      "Eleventh",
      "Twelfth",
      "Thirteenth",
      "Fourteenth",
      "Fifteenth",
      "Sixteenth",
      "Seventeenth",
      "Eighteenth",
      "Nineteenth"
   };

   char  numstring[30];
   char  tempstring[100];
   unsigned int length;
   char *retval;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Create the week number portion of the output string.
 */
   if (weeknum == 20) {
      strcpy(numstring, "Twentieth");
   }
   else if (weeknum == 30) {
      strcpy(numstring, "Thirtieth");
   }
   else if (weeknum > 30) {
      strcpy(numstring, "Thirty-");
      strcat(numstring, numtab[weeknum % 10]);
   }
   else if (weeknum > 20) {
      strcpy(numstring, "Twenty-");
      strcat(numstring, numtab[weeknum % 10]);
   }
   else {
      strcpy(numstring, numtab[weeknum]);
   }
/*
 * Build the output string in a temporary static buffer.  There is a special
 * case for Sunday.
 */
   if (dow == DOW_SUNDAY) {
      strcpy(tempstring, numstring);
      strcat(tempstring, " Sunday of ");
      strcat(tempstring, seatab[season]);
   }
   else {
      strcpy(tempstring, daytab[dow]);
      strcat(tempstring, " of the ");
      strcat(tempstring, numstring);
      strcat(tempstring, " Week of ");
      strcat(tempstring, seatab[season]);
   }
/*
 * Build the buffer (using malloc()) that is to be returned.
 */
   length = strlen(tempstring) + 1;
   retval = malloc(length);

   strcpy(retval,
	  tempstring);

   return (retval);
}
