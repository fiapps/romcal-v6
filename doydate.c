#include "romcal.h"

void doydate(int year,
	     int doy,
	     int *month,
	     int *day)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL doydate.c 6.1 02/12/06 17:23:57
 *
 *	Copyright (C) 1993-2002 Kenneth G. Bath
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
 *	This module will compute the month and day of month of a given
 *	day of a given year. The domain for the day of the year is
 *	0 - 365 for leap years, and 0 - 364 for ordinary years. (That is,
 *	Jan. 1 is always day 0.)
 *
 *	The algorithm implemented is derived from the Date Algorithms of 
 *	Peter Baum documented at the following World Wide Web address:
 *
 *		http://home.capecod.net/~pbaum/date/date0.htm
 *
 *	Mr. Baum's contact information follows. He requests that this
 *	information be included in source code derived from his
 *	algorithm.
 *
 * 	You may contact Peter Baum at:
 *		Peter Baum 
 *      	Aesir Research 
 *      	P.O. Box 1255 
 *      	3 Prospect Avenue 
 *      	Onset, MA 02558-1255 
 *
 * 	Telecommunications: 
 *      	INTERNET: < pbaum@capecod.net> 
 *     		VOICE: (508) 291-2958 
 *		FAX: (508) 291-2958 
 *
 * 	Peter Baum's algorithm is based on years that begin on March 1. 
 *	This moves the extra day in leap years to the end of the year. A 
 *	linear approximation of the cycle of months and days can then be 
 *	used to calculate the month and day of a given day of the year.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	08feb02 : created, kgb
 *
 *----------------------------------------------------------------------*/

   int march1;
   int im, id;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * In leap years, March begins on day 60 (counting from zero).  In
 * ordinary years, it begins on day 59 (counting from zero).
 */
   march1 = (leapyear(year)) ? 60 : 59;
/*
 * If the given day of the year is before March 1, then it "belongs" to
 * the previous year. Otherwise, it belongs to the current year whose
 * beginning is shifted to March 1. (307 is the day number of Dec. 31
 * in a year that begins on March 1.) Note that the day numbering for
 * the shifted year begins at 1.
 */
   id = (doy < march1) ? (doy + 307) : (doy - march1 + 1);
/*
 * Compute the month using a linear approximation.
 */
   im = (5*id + 456)/153;
/*
 * Compute the day of the month using a linear approximation.
 */
   *day = id - (153*im - 457)/5;
/*
 * The approximation gives months in the range of 3 to 14. If the month
 * is 13, then it is January. If the month is 14, it is February.
 */
   *month = (im > 12) ? (im - 12) : (im);
}
