#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "romcal.h"

static void  usage()
{
   version();
   fprintf(stderr, "Usage: romcal [options] [year]\n");
   fprintf(stderr, "   where [year] is the 4-digit year (>1582)\n");
   fprintf(stderr, "   and   [options] are as follows:\n");
   fprintf(stderr, "-a: Ascension on Sunday\n");
   fprintf(stderr, "-e: Epiphany on Jan. 6\n");
   fprintf(stderr, "-c: Corpus Christi on Thursday\n");
   fprintf(stderr, "-o: Do not print Optional Memorials or Commemorations\n");
   fprintf(stderr, "-v: Print Version Number and Help\n");
   fprintf(stderr, "-t: Print today's celebration\n");
   fprintf(stderr, "-l: List directed I/O\n");
   fprintf(stderr, "-L: List directed I/O (same as -l)\n");
   fprintf(stderr, "-I: iCalendar output\n");
   fprintf(stderr, "-P: PostScript output\n");
   fprintf(stderr, "-C: Color PostScript output\n");
   fprintf(stderr, "-H: HTML Output\n");
   fprintf(stderr, "-R: RTF Output\n");
   fprintf(stderr, "-W {directory}: Web Page Output\n");
   fprintf(stderr, "-d {yyyymmdd}: Print the celebration of a given date\n");
   fprintf(stderr, "Note: Current year is assumed if not provided.\n");
   fprintf(stderr, "Note: The -t and -d options can be used with the -l option.\n");
}

struct Info *parse(int   argc,
                   char *argv[])
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL parse.c 6.2 02/12/06 17:25:35
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
 *	This module will parse the command line of the 'romcal' program
 *	and initialize the Info structure.  On successful completion, it
 *	will return a pointer to the Info structure.  Otherwise, it will
 *	return NULL.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	14Mar93 : created, kgb
 *	19Dec93 : added "options.h" and "usage.h", kgb
 *	20Jul94 : changed to return Info structure, removed options.h;
 *		  added options to struct Info; added "today only"
 *		  option, kgb
 *	22Jul94 : added list directed I/O capability, kgb
 *	13Feb95 : added PostScript I/O options, kgb
 *	18Feb95 : removed "usage.h"; added "version.h", kgb
 *	28Nov01 : added the "-d" option to allow the printing of
 *		  a particular date, kgb
 *	08Feb02 : added WEB_IO; removed version.h; added call to
 *		  version(), kgb
 *
 *----------------------------------------------------------------------*/

   int   emonth,
         eday,
	 yyyymmdd,
         c;

   extern int optind;
   extern char *optarg;

   static struct Info info;

   struct tm *tp, tmstruct;

   time_t  clock;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Get the current time in a tm structure. Use local time.
 */
   time(&clock);
   tp = localtime(&clock);
/*
 * Assume that Corpus Christi and Epiphany will be on Sundays and that
 * Optional Memorials will be printed.
 */
   info.cc_on_thurs = L_FALSE;
   info.ep_on_jan6 = L_FALSE;
   info.as_on_sun = L_FALSE;
   info.print_optionals = L_TRUE;
   info.today_only = -1;
   info.io_option = TEXT_IO;
/*
 * Parse options string(s).  See getopt(3).
 */
   while ((c = getopt(argc, argv, "ad:vceotlLIPCHRW:")) != EOF) {
      if (c == 'c') {
	 info.cc_on_thurs = L_TRUE;
      }
      else if (c == 'e') {
	 info.ep_on_jan6 = L_TRUE;
      }
      else if (c == 'a') {
	 info.as_on_sun = L_TRUE;
      }
      else if (c == 'o') {
	 info.print_optionals = L_FALSE;
      }
      else if (c == 't') {
	 if (optarg == NULL) {
	    info.today_only = tp->tm_yday;
	    info.year = tp->tm_year + 1900;
	 }
	 else {
/*
 *          Clear out the temporary tm structure.
 */
	    memset(&tmstruct, 0, sizeof(tmstruct));
/*
 *          Expect the date in yyyymmdd format to be given as
 *          an argument.
 */
	    yyyymmdd = atoi(optarg);
/*
 *          Strip off the day of the month.
 */
	    tmstruct.tm_mday = yyyymmdd % 100;
	    yyyymmdd = yyyymmdd/100;
/*
 *          Strip off the month of the year. Note that one is subtracted
 *          because the tm structure defines its tm_mon member to be
 *          in the range 0 to 11.
 */
	    tmstruct.tm_mon = (yyyymmdd % 100) - 1;
	    yyyymmdd = yyyymmdd/100;
/*
 *          Strip off the year. Note that 1900 is subtracted because
 *          the tm structure defines its tm_year member to be the year
 *          minus 1900. For example, the year 2001 should be 101.
 */
	    tmstruct.tm_year = (yyyymmdd % 10000) - 1900;
/*
 *          According to the mktime() man page:
 *
 *          In addition to computing the calendar time, mktime() normal-
 *          izes  the supplied tm structure.  The original values of the
 *          tm_wday and tm_yday components of the structure are ignored,
 *          and the original values of the other components are not res-
 *          tricted to the ranges indicated in  the  definition  of  the
 *          structure.   On  successful  completion,  the  values of the
 *          tm_wday and tm_yday components are  set  appropriately,  and
 *          the  other  components  are  set  to represent the specified
 *          calendar time, but with their values forced to be within the
 *          appropriate  ranges.   The final value of tm_mday is not set
 *          until tm_mon and tm_year are determined.
 */
	    clock = mktime(&tmstruct);
/*
 *          Set up the info structure from the returned values of
 *          mktime().
 */
	    info.today_only = tmstruct.tm_yday;
	    info.year = tmstruct.tm_year + 1900;
	 }
      }
      else if (c == 'l' || c == 'L') {
	 info.io_option = LIST_IO;
      }
      else if (c == 'I') {
	 info.io_option = ICAL_IO;
      }
      else if (c == 'P') {
	 info.io_option = PSGREY_IO;
      }
      else if (c == 'C') {
	 info.io_option = PSCOLOR_IO;
      }
      else if (c == 'H') {
	 info.io_option = HTML_IO;
      }
      else if (c == 'R') {
	 info.io_option = RTF_IO;
      }
      else if (c == 'W') {
	 info.io_option = WEB_IO;
	 info.webio_dir = optarg;
	 fprintf(stderr, 
		 "Web Output Directory: %s\n",
	         info.webio_dir);
      }
      else if (c == 'd') {
/*
 *       Clear out the temporary tm structure.
 */
	 memset(&tmstruct, 0, sizeof(tmstruct));
/*
 *       Expect the date in yyyymmdd format to be given as
 *       an argument.
 */
	 yyyymmdd = atoi(optarg);
/*
 *       Strip off the day of the month.
 */
	 tmstruct.tm_mday = yyyymmdd % 100;
	 yyyymmdd = yyyymmdd/100;
/*
 *       Strip off the month of the year. Note that one is subtracted
 *       because the tm structure defines its tm_mon member to be
 *       in the range 0 to 11.
 */
	 tmstruct.tm_mon = (yyyymmdd % 100) - 1;
	 yyyymmdd = yyyymmdd/100;
/*
 *       Strip off the year. Note that 1900 is subtracted because
 *       the tm structure defines its tm_year member to be the year
 *       minus 1900. For example, the year 2001 should be 101.
 */
	 tmstruct.tm_year = (yyyymmdd % 10000) - 1900;
/*
 *       According to the mktime() man page:
 *
 *       In addition to computing the calendar time, mktime() normal-
 *       izes  the supplied tm structure.  The original values of the
 *       tm_wday and tm_yday components of the structure are ignored,
 *       and the original values of the other components are not res-
 *       tricted to the ranges indicated in  the  definition  of  the
 *       structure.   On  successful  completion,  the  values of the
 *       tm_wday and tm_yday components are  set  appropriately,  and
 *       the  other  components  are  set  to represent the specified
 *       calendar time, but with their values forced to be within the
 *       appropriate  ranges.   The final value of tm_mday is not set
 *       until tm_mon and tm_year are determined.
 */
	 clock = mktime(&tmstruct);
/*
 *       Set up the info structure from the returned values of mktime().
 */
	 info.today_only = tmstruct.tm_yday;
	 info.year = tmstruct.tm_year + 1900;
      }
      else if (c == '?' || c == 'v') {
	 usage();
	 return (NULL);
      }
   }

   if (info.today_only < 0) {
/*
 *    If no year was given, assume the current year.
 */
      if (optind == argc - 1) {
         info.year = atoi(argv[optind]);
      }
      else {
	 info.year = tp->tm_year + 1900;
      }
/*
 *    Validate the year.
 */
      if (info.year < 1583) {
	 fprintf(stderr, 
		 "Year must be in Gregorian Calendar (> 1582).\n");
	 return (NULL);
      }
   }
   else {
      if (info.io_option == PSGREY_IO ||
	  info.io_option == PSCOLOR_IO ||
	  info.io_option == HTML_IO ||
	  info.io_option == RTF_IO) {
	 fprintf(stderr, 
		 "PostScript, HTML, and RTF options not allowed with -t option\n");
	 return (NULL);
      }
   }
/*
 * Compute the number of days.
 */
   if (leapyear(info.year)) {
      info.numdays = 366;
   }
   else {
      info.numdays = 365;
   }
/*
 * Compute the day number of Easter Sunday.
 */
   eastdate(info.year, &emonth, &eday);
   info.edoy = doy(info.year, emonth, eday);
/*
 * Compute the day number of Christmas Day.
 */
   info.cdoy = doy(info.year, 12, 25);
/*
 * Compute the Sunday Modulo.  This is the value of the day number of any
 * given Sunday, modulo 7.  (Easter is always on a Sunday, so we'll use that
 * one.)
 */
   info.sunmod = info.edoy % 7;
/*
 * Return pointer to Info structure.
 */
   return (&info);
}
