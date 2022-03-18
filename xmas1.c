#include "romcal.h"

int   christmas1(struct Info *info, 
		 struct Cal cal[])
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL xmas1.c 6.1 02/12/06 17:23:56
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
 *	This module computes the Christmas season that occurs at the
 *	beginning of the year.  That is, from Jan. 1 until the Baptism
 *	of the Lord.  It returns the day number of the Baptism of the
 *	Lord.
 *
 *------------------------ Special Discussion --------------------------*
 *
 *	If Epiphany is celebrated on Jan. 6:
 *	   a.  	Jan. 1 is the Solemnity of Mary, Mother of God.
 *	   b.  	Days between Jan. 2. and Jan. 5 are called "*day before
 *		Epiphany."
 *	   c.	Any Sunday between Jan. 2 and Jan. 5 is called the 
 *		"Second Sunday of Christmas".
 *	   d.  	Epiphany is celebrated Jan. 6.
 *	   e.  	Days between Jan. 6 and the following Sunday are called
 *	       	"*day after Epiphany".
 *	   f.  	The Baptism of the Lord occurs on the Sunday following
 *	       	Jan. 6.
 *	   g.  	Ordinary time begins on the Monday after the Baptism of 
 *		the Lord.
 *
 *	S  M  T  W  T  F  S  S  M  T  W  T  F  S  S  M  T  W  T  F  S  S
 *	1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
 *	M  b  b  b  b  E  a  B  O  O  O  O  O  O  S
 *	   1  2  3  4  5  6  7  8  9 10 11 12 13 14
 *	   M  b  b  b  b  E  B  O  O  O  O  O  O  S
 *	      1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
 *	      M  b  b  b  b  E  a  a  a  a  a  a  B  O  O  O  O  O  O  S
 *	         1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
 *	         M  b  b  b  C  E  a  a  a  a  a  B  O  O  O  O  O  O  S
 *	            1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18
 *	            M  b  b  C  b  E  a  a  a  a  B  O  O  O  O  O  O  S
 *	               1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
 *	               M  b  C  b  b  E  a  a  a  B  O  O  O  O  O  O  S
 *	                  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
 *	                  M  C  b  b  b  E  a  a  B  O  O  O  O  O  O  S
 *
 *	M=Sol. of Mary
 *	E=Epiphany
 *	B=Baptism of the Lord
 *	S=Second Sunday of Ordinary Time
 *	C=Second Sunday of Christmas
 *	b=*day before Epiphany
 *	a=*day after Epiphany
 *	O=*day of the First Week of Ordinary Time
 *
 *
 *
 *
 *	If Epiphany is not celebrated on Jan. 6:
 *	   a.  	Jan. 1 is the Solemnity of Mary, Mother of God.
 *	   b.	Epiphany is the Sunday occuring between Jan. 2 and
 *		Jan. 8.
 *	   c.	Days after Jan. 1 and before the Epiphany are called
 *		"*day before Epiphany".
 *	   d.  	If Epiphany occurs on Jan. 7 or Jan. 8, then the Baptism
 *	       	of the Lord is the next day (Monday).
 *	   e.  	If Epiphany occurs between Jan. 2 and Jan. 6, then the
 *	       	Sunday following Epiphany is the Baptism of the Lord.
 *	   f.   If Epiphany occurs between Jan. 2 and Jan. 6, then the
 *	        days of the week following Epiphany but before the
 *		Baptism of the Lord are called "*day after Epiphany".
 *	   g.	Ordinary time begins on the day following the Baptism
 *		of the Lord (Monday or Tuesday).
 *
 *	S  M  T  W  T  F  S  S  M  T  W  T  F  S  S  M  T  W  T  F  S  S
 *	1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
 *	M  b  b  b  b  b  b  E  B  O  O  O  O  O  S
 *	   1  2  3  4  5  6  7  8  9 10 11 12 13 14
 *	   M  b  b  b  b  b  E  B  O  O  O  O  O  S
 *	      1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
 *	      M  b  b  b  b  E  a  a  a  a  a  a  B  O  O  O  O  O  O  S
 *	         1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
 *	         M  b  b  b  E  a  a  a  a  a  a  B  O  O  O  O  O  O  S
 *	            1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18
 *	            M  b  b  E  a  a  a  a  a  a  B  O  O  O  O  O  O  S
 *	               1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
 *	               M  b  E  a  a  a  a  a  a  B  O  O  O  O  O  O  S
 *	                  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
 *	                  M  E  a  a  a  a  a  a  B  O  O  O  O  O  O  S
 *
 *	M=Sol. of Mary
 *	E=Epiphany
 *	B=Baptism of the Lord
 *	S=Second Sunday of Ordinary Time
 *	C=*day before Epiphany
 *	A=*day after Epiphany
 *	O=*day of the First Week of Ordinary Time
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	16Mar93 : created, kgb
 *	19Dec93 : added options.h, kgb
 *	06Feb94 : renamed to xmas1.c for use on a PC, kgb
 *	20Jul94 : removed options.h; added options to struct Info, kgb
 *	13Feb95 : changed algorithm to transfer the Baptism of the Lord
 *		  to Monday when Epiphany occurs on Jan. 7 or 8, rather
 *		  than omit it, kgb
 *	18Feb95 : corrected incrementing of dow within loop that fills
 *		  the second week of Christmas, kgb
 *	03Dec01 : modified DOWINCR() to increment the week as well as
 *		  the day of the week, kgb
 *	21Dec01 : corrected the time before and after Epiphany; added
 *		  dow_t, kgb
 *
 *----------------------------------------------------------------------*/

   static char *ep = "Epiphany of the Lord";
   int   iep;

   static char *bl = "Baptism of the Lord";
   int   ibl;

   static char *epbefore[] =
   {
      "",
      "Monday before Epiphany",
      "Tuesday before Epiphany",
      "Wednesday before Epiphany",
      "Thursday before Epiphany",
      "Friday before Epiphany",
      "Saturday before Epiphany"
   };

   static char *epoctave[] =
   {
      "",
      "Monday after Epiphany",
      "Tuesday after Epiphany",
      "Wednesday after Epiphany",
      "Thursday after Epiphany",
      "Friday after Epiphany",
      "Saturday after Epiphany"
   };

   dow_t jan1,
	 dow;

   int   iday;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/

   if (info->ep_on_jan6) {
/*
 *    Compute the days before Epiphany.
 */
      for (iday = 1; iday < 5; iday++) {
	 dow = DOW(iday, info->sunmod);

	 if (dow == DOW_SUNDAY) {
	    cal[iday].celebration = gencel(CHRISTMAS, 2, dow);
	 }
	 else {
	    cal[iday].celebration = epbefore[dow];
	 }

	 cal[iday].season = CHRISTMAS;
	 cal[iday].color = WHITE;
	 cal[iday].invitatory = NULL;
      }
/*
 *    Compute the Epiphany.
 */
      iep = 5;
      cal[iep].celebration = ep;
      cal[iep].season = CHRISTMAS;
      cal[iep].rank = SOLEMNITY;
      cal[iep].color = WHITE;
      cal[iep].invitatory = NULL;
/*
 *    Compute the Baptism of the Lord. This is the Sunday after
 *    Epiphany.
 */
      ibl = 12 - DOW(5, info->sunmod);
      cal[ibl].celebration = bl;
      cal[ibl].season = CHRISTMAS;
      cal[ibl].rank = LORD;
      cal[ibl].color = WHITE;
      cal[ibl].invitatory = NULL;
/*
 *    Fill in the time between Epiphany and the Baptism.
 */
      for (iday = iep + 1; iday < ibl; iday++) {
	 dow = DOW(iday, info->sunmod);
	 cal[iday].celebration = epoctave[dow];
	 cal[iday].season = CHRISTMAS;
	 cal[iday].color = WHITE;
	 cal[iday].invitatory = NULL;
      }
   }
   else {
/*
 *    Compute the day of the Epiphany.
 */
      jan1 = DOW(0, info->sunmod);
      iep = 7 - jan1;
/*
 *    If the year starts on Sunday or Monday, then Epiphany will fall
 *    on Jan. 7 or Jan. 8.  In that case, the Baptism of the Lord is 
 *    moved to the Monday after Epiphany. Otherwise, it is the Sunday
 *    following Epiphany.
 */
      if (jan1 == DOW_SUNDAY || jan1 == DOW_MONDAY) {
	 ibl = iep + 1;
      }
      else {
	 ibl = iep + 7;
      }

      for (iday = 1; iday <= ibl; iday++) {
	 dow = DOW(iday, info->sunmod);

	 cal[iday].season = CHRISTMAS;
	 cal[iday].color = WHITE;
	 cal[iday].invitatory = NULL;

	 if (iday < iep) {
	    cal[iday].celebration = epbefore[dow];
	 }
	 else if (iday == iep) {
	    cal[iday].celebration = ep;
            cal[iday].rank = SOLEMNITY;
	 }
	 else if (iday < ibl) {
	    cal[iday].celebration = epoctave[dow];
	 }
	 else if (iday == ibl) {
	    cal[iday].celebration = bl;
	    cal[iday].rank = LORD;
	 }
      }
   }

   return (ibl);
}
