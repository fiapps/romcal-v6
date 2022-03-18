#include <stdio.h>
#ifndef SEEK_CUR
#include <unistd.h>
#endif
#include <time.h>
#include "romcal.h"

void  main(argc, argv)
int   argc;
char *argv[];
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL mkfix.c 6.2 03/01/06 16:19:11
 *
 *	Copyright (C) 1993,1995,1999,2003 Kenneth G. Bath
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
 *	This program generates the fixed.h include file from the
 *	fixed.dat data file.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	14Mar93 : created, kgb
 *	16Mar93 : added season, kgb
 *	17Mar93 : added exit status for Suns, kgb
 *	18Feb95 : removed "usage.h"; added "version.h", kgb
 *	08Feb02 : removed "version.h", kgb
 *
 *----------------------------------------------------------------------*/

#define WHITESPACE " \t"
   long  clock;

   FILE *fpi,
        *fpo;

   char  line[256];

   char *strtok();

   char *m,
        *d,
        *r,
        *c,
        *l;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Open the input file.
 */
   fpi = fopen("fixed.dat", "r");

   if (fpi == NULL) {
      perror("fixed.dat");
      exit(1);
   }
/*
 * Open the output file.
 */
   fpo = fopen("fixed.h", "w");

   if (fpo == NULL) {
      perror("fixed.h");
      exit(2);
   }
/*
 * Get the current time.
 */
   time(&clock);
/*
 * Print out the header.
 */
   fprintf(fpo,
"/*----------------------------------------------------------------------*\n"
" *\n"
" *	Copyright (C) 1993,1995 Kenneth G. Bath\n"
" *	Permission to use and modify this software and its\n"
" *	documentation for any purpose other than its incorporation\n"
" *	into a commercial product is hereby granted without fee.\n"
" *\n"
" *	Permission to copy and distribute this software and its\n"
" *	documentation only for non-commercial use is also granted\n"
" *	without fee, provided, however, that the above copyright\n"
" *	notice appear in all copies, that both that copyright\n"
" *	notice and this permission notice appear in supporting\n"
" *	documentation. The author makes no representations about\n"
" *	the suitability of this software for any purpose. It is\n"
" *	provided \"as is\" without express or implied warranty.\n"
" *\n"
" *-------------------- Software Unit Description -----------------------*\n"
" *\n"
" *	WARNING:  THIS INCLUDE FILE WAS CREATED USING %s!!!\n"
" *	This include file contains the fixed dates of the Roman\n"
" *	Calendar.\n"
" *\n"
" *---------------------- Software Unit History -------------------------*\n"
" *\n"
" *	Created by tool at %s"
" *\n"
" *----------------------------------------------------------------------*/\n",
	   argv[0],ctime(&clock));
/*
 * Open the structure definition.
 */
   fprintf(fpo, "\n");
   fprintf(fpo, "static struct Cal fixed[] = {\n");
/*
 * Read in the data file and create a structure.
 */
   while (fgets(line, sizeof(line), fpi)) {
      if (line[0] != '#') {
	 m = strtok(line, WHITESPACE);	/* Month	 */
	 d = strtok(NULL, WHITESPACE);	/* Day		 */
	 r = strtok(NULL, WHITESPACE);	/* Rank		 */
	 c = strtok(NULL, WHITESPACE);	/* Color	 */
	 l = strtok(NULL, "\n");	/* Celebration	 */
	 if (m && d && r && c && l) {
/*
 *          Write month and day.
 */
	    fprintf(fpo, "   { %s, %s, ", m, d);
/*
 *          Write color.
 */
	    if (*c == 'G')
	       fprintf(fpo, "GREEN, ");
	    if (*c == 'R')
	       fprintf(fpo, "RED, ");
	    if (*c == 'W')
	       fprintf(fpo, "WHITE, ");
	    if (*c == 'P')
	       fprintf(fpo, "PURPLE, ");
	    if (*c == '-')
	       fprintf(fpo, "NOCOLOR, ");
/*
 *          Write rank.
 */
	    if (*r == 'O')
	       fprintf(fpo, "OPTIONAL, ");
	    if (*r == 'M')
	       fprintf(fpo, "MEMORIAL, ");
	    if (*r == 'F')
	       fprintf(fpo, "FEAST, ");
	    if (*r == 'L')
	       fprintf(fpo, "LORD, ");
	    if (*r == 'S')
	       fprintf(fpo, "SOLEMNITY, ");
/*
 *          Assume the season is Ordinary Time.  This will be
 *	    overwritten when necessary.
 */
	    fprintf(fpo, "ORDINARY, ");
/*
 *          Write a null for the invitatory (temp. code).
 */
	    fprintf(fpo, "\n      \"%s\", NULL  },\n", l);
	 }
      }
   }
/*
 * Seek backwards two characters to overwrite the comma following the last
 * entry.
 */
   fseek(fpo, -2, SEEK_CUR);
/*
 * Close the structure definition.
 */
   fprintf(fpo, "\n};\n");
/*
 * Close the files.
 */
   fclose(fpi);
   fclose(fpo);

   exit(0);
}
