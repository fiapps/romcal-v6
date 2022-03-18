#include "romcal.h"

logical_t leapyear(int year)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL leapyear.c 6.2 03/01/06 16:16:55
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
 *	This module will determine if a given year is a leap year
 *	according to the Gregorian defintion of leap years.  It
 *	returns L_TRUE if the given year is a leap year; L_FALSE 
 *	otherwise.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	14Mar93 : created, kgb
 *
 *----------------------------------------------------------------------*/

   int   retval;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/

   if (year % 400 == 0) {
      retval = L_TRUE;
   }
   else if (year % 100 == 0) {
      retval = L_FALSE;
   }
   else if (year % 4 == 0) {
      retval = L_TRUE;
   }
   else {
      retval = L_FALSE;
   }

   return (retval);
}
