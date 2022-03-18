#ifndef PRINTSTR_H
#define PRINTSTR_H
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL printstr.h 6.1 02/12/06 17:23:54
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
 *	This include file contains "print strings" used in the I/O
 *	routines.
 *---------------------- Software Unit History -------------------------*
 *
 *	03Mar95 : created, kgb
 *	01Apr96 : added TRIDUUM rank, kgb
 *	30Jan98 : added HTML colors, kgb
 *	26Feb00 : added ASHWED rank, kgb
 *
 *----------------------------------------------------------------------*/

   static char *colors[] =
   {
      "NOCOLOR",
      "Green  ",
      "White  ",
      "Red    ",
      "Purple ",
      "Rose   ",
      "Black  "
   };

   static char *htmlcolors[] = 
   {
      "NOCOLOR",
      "LIME",
      "WHITE",
      "RED",
      "FUCHSIA",
      "PINK",
      "GRAY"
   }; 
   
   static int rtfcolors[] = 
   {
      0, 	/* No Color */
      11, 	/* Green */
      1, 	/* White */
      6, 	/* Red */
      18, 	/* Purple */
      19, 	/* Rose */
      0		/* Black */
   };

   static char *ranks[] =
   {
      "Weekday  ",
      "Commem.  ",
      "Opt. Mem.",
      "Memorial ",
      "Feast    ",
      "Sunday   ",
      "Feast    ",
      "Weekday  ",	/* Ash Wednesday */
      "Holy Week",	/* Holy Week */
      "Triduum  ",
      "SOLEMNITY"
   };

   static char *daystr[] =
   {
      "Sun", 
      "Mon", 
      "Tue", 
      "Wed",
      "Thu", 
      "Fri", 
      "Sat"
   };


#endif
