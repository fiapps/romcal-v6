#include <stdio.h>
#include <stdlib.h>
#ifndef MAINPROG
#include "romcal.h"
#endif

void  eastdate(int year, 
	       int *month, 
	       int *day)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL eastdate.c 6.2 03/01/06 16:17:23
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
 *	This module returns the date of Easter Sunday (day, month)
 *	given the year, assuming Gregorian calendar.  The method
 *	used here is taked from an algorithm in section 12.22 of
 *	"The Explanatory Supplement to the Astronomical Almanac",
 *	edited by P. Kenneth Seidelmann, USNO, 1995.  The Explanatory
 *	Supplement credits the algorithm to Oudin, J.-M. (1940) 
 *	"Etude sur la Date de Paques".  Bull. Astronomique (2), vol.
 *	12, pp. 391-410.
 *
 *	Chapter 12 of the Explanatory Supplement provides an excelent
 *	discussion of calendars in general, and section 12.22 explains
 *	the computation of the date of Easter.  Another good reference
 *	concerning the computation and history of the date of Easter
 *	is the "Book of Days" (See March 27).
 *
 *	The compiler directive "MAINPROG" is included should it
 *	be desired to build this module as a stand-alone program.
 *	To do this, compile this program with this command line:
 *		cc -DMAINPROG eastdate.c -o eastdate
 *	The usage would then be:
 *		eastdate {year}
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	14Mar93 : created, kgb
 *	06Feb94 : added main program option, kgb
 *	18Feb95 : changed to algorithm found in Expanatory Supplement,
 *		  kgb
 *
 *----------------------------------------------------------------------*/

   int y,c,n,k,i,j,l,m,d;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/

   y = year;

   c = y/100;
   n = y - 19*(y/19);
   k = (c - 17)/25;
   i = c - c/4 - (c-k)/3 + 19*n + 15;
   i = i - 30*(i/30);
   i = i - (i/28) * (1 - (i/28) * (29/(i+1)) * ((21 - n)/11));
   j = y + y/4 + i + 2 - c + c/4;
   j = j - 7*(j/7);
   l = i - j;
   
   m = 3 + (l+40)/44;
   d = l + 28 - 31*(m/4);

   *month = m;
   *day = d;
}
#ifdef MAINPROG
int main(argc,argv)
int argc;
char *argv[];
{
   int im,id;
   if (argc != 2) {
      printf ("Usage: %s year\n",argv[0]);
      exit(1);
   }
   eastdate(atoi(argv[1]),&im,&id);
   if (im == 3) {
      printf ("Easter Sunday: %02d-Mar-%04d\n",id,atoi(argv[1]));
   }
   else {
      printf ("Easter Sunday: %02d-Apr-%04d\n",id,atoi(argv[1]));
   }
   exit(0);
}
#endif

