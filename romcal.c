#include <stdio.h>
#include "romcal.h"

void  main(int argc, 
	   char *argv[])
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL romcal.c 6.1 02/12/06 17:23:57
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
 *	This is the main driver module for the 'romcal' program.  This
 *	program will generate the General Roman Calendar for any given
 *	calendar year.  Note that this program will use the revised
 *	calendar for the Western Church as approved by Paul VI in
 *	Mysterii Paschalis dated 14 February 1969, and implemented in
 *	the United States in 1972, although any year of the Gregorian 
 *	calendar (i.e., A.D. 1582 or later) may be given to the program.  
 *	Also note that while the liturgical year begins with the First 
 *	Sunday of Advent, this program computes based on a calendar year.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	14mar93 : created, kgb
 *	15jul94 : fixed comment about valid year; changed interface
 *		  to parse(), kgb
 *
 *----------------------------------------------------------------------*/

   struct Info *info;

   static struct Cal cal[366];

   int   ibl;			/* End of Christmas season 	 */
   int   iaw;			/* Ash Wednesday		 */
   int   ips;			/* Pentecost Sunday		 */
   int   iav;			/* First Sunday of Advent	 */

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Parse the command line and get the year.
 */
   info = parse(argc, argv);

   if (info == NULL) {
      exit(1);
   }
/*
 * Initialize Info and Cal structures.
 */
   init(info, cal);
/*
 * Compute the early Christmas season.
 */
   ibl = christmas1(info, cal);
/*
 * Compute the season of Lent.
 */
   iaw = lent(info, cal);
/*
 * Compute the Easter season.
 */
   ips = easter(info, cal);
/*
 * Compute the Advent season.
 */
   iav = advent(info, cal);
/*
 * Compute the late Christmas season.
 */
   christmas2(info, cal);
/*
 * Fill in the Proper calendar.
 */
   proper(info, cal);
/*
 * Fill in the early Ordinary Time.
 */
   ordinary1(info, cal, ibl, iaw);
/*
 * Fill in the later Ordinary Time.
 */
   ordinary2(info, cal, ips, iav);
/*
 * Print out the calendar.
 */
   printcal(info, cal);

   exit(0);
}
