#include <stdio.h>
#include "caltypes.h"
#include "montab.h"

/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL psformat.c 6.1 02/12/06 17:23:53
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
 *----------------------------------------------------------------------*
 *
 *	Selected parts of the PostScript option of this software
 *	are taken or derived from "pscal - a PostScript calendar
 *	generator" written by Christopher Phillips.  The pscal
 *	copyright notice follows:
 *
 * 	"Copyright (C) 1992, Christopher Phillips"
 * 	"Permission to use and modify this software and its
 * 	documentation for any purpose other than its incorporation
 * 	into a commercial product is hereby granted without fee.
 * 	Permission to copy and distribute this software and its
 * 	documentation only for non-commercial use is also granted
 * 	without fee, provided, however, that the above copyright
 * 	notice appear in all copies, that both that copyright
 * 	notice and this permission notice appear in supporting
 * 	documentation. The author makes no representations about
 * 	the suitability of this software for any purpose. It is
 * 	provided "as is" without express or implied warranty."
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	18Feb95 : Integration with ROMCAL, includeing use of _t
 *		  types declared in caltypes.h, use of MONNAM()
 *		  macro and change of month numbering convention.
 *		  Split do_page() into do_page1() and do_page2()
 *		  to support color PostScript option, kgb
 *
 *----------------------------------------------------------------------*/

#define DAYS_PER_WEEK 7
#define NEXT_FIRST(y, m, f)  ((f + MONLEN(y,m)) % DAYS_PER_WEEK)
#define PREV_FIRST(y, m, f)        \
   ((f - (MONLEN(y,m-1) % DAYS_PER_WEEK) + DAYS_PER_WEEK) % DAYS_PER_WEEK)
#define MAX(a,b) 		(a<b ? b : a)
/*
 * format inset months
 */
void  do_small_months(mon, year, first)
month_t mon;
int   year;
int   first;
{
   int   prev_mon;
   int   next_mon;
   int   prev_first;
   int   next_first;
   int   on_top;

/*
 * If the two top-left boxes are empty, the inset months go there, else they
 * go in the two bottom-right boxes.
 */
   on_top = first > MON;
/*
 * Figure the previous and next months.
 */
   prev_mon = mon - 1;
   next_mon = mon + 1;

   prev_first = PREV_FIRST(year, mon, first);
   next_first = NEXT_FIRST(year, mon, first);
/*
 * Format the small calendar for the previous month.
 */
   printf("%d 1 %d (%s) ",
	  MONLEN(year, prev_mon),
	  prev_first,
	  MONNAM(prev_mon));

   if (on_top) {
      printf("LeftMargin TopLine HeadingHeight sub ");
   }
   else {
      printf("LeftMargin BoxWidth %d mul add BottomMargin BoxHeight add ",
	     DAYS_PER_WEEK - 2);
   }
   printf("SmallMonth\n");
/*
 * Format the small calendar for the next month.
 */
   printf("%d 1 %d (%s) ",
	  MONLEN(year, next_mon),
	  next_first,
	  MONNAM(next_mon));

   if (on_top) {
      printf("LeftMargin BoxWidth add TopLine HeadingHeight sub ");
   }
   else {
      printf("LeftMargin BoxWidth %d mul add BottomMargin BoxHeight add ",
	     DAYS_PER_WEEK - 1);
   }
   printf("SmallMonth\n");
}

/*
 * Format filling of otherwise-empty boxes
 */
void  do_fills(mon, year, first)
month_t mon;
int   year;
int   first;
{
   int   on_top;
   int   last;
   int   day1;
   int   days;

   on_top = first > MON;
   if ((last = NEXT_FIRST(year, mon, first) - 1) < SUN)
      last += DAYS_PER_WEEK;
/*
 * Boxes on the top row
 */
   if (days = first - (on_top ? TUE : SUN)) {
      day1 = 1 - days;
      printf("%d %d %d Fill\n", days, day1, first);
   }
/*
 * Boxes on the bottom row
 */
   if (days = (on_top ? SAT : THU) - last) {
      day1 = MONLEN(year, mon) + 1;
      printf("%d %d %d Fill\n", days, day1, first);
   }
}

/*
 * Print the end of page lines.
 */
end_page()
{
   printf("restore\n");
   printf("showpage\n");
   printf("%%%%EndPage\n");
}

/*
 * Format page for a given month and year.  The original do_page() module has
 * been split into two portions, do_page1() and do_page2(), to support color
 * PostScript.
 */
void  do_page1(mon, year, first)
month_t mon;
int   year;
int   first;
{
   int   weeks;
   struct passwd *pw;

/*
 * Initialize the page.
 */
   printf("save\n");
   printf("Landscape\n");
   printf("InitialHoliday\n");
/*
 * Determine the number of weeks in the month.
 */
   weeks = MAX(5, (MONLEN(year, mon) + first - 1) / DAYS_PER_WEEK + 1);
   printf("%d WeekSizes\n", weeks);
/*
 * Format the page title, e.g., (January 1992)
 */
   printf("SetTitleFont\n");
   printf("(%s %d) Title\n", MONNAM(mon), year);
}

void  do_page2(mon, year, first)
month_t mon;
int   year;
int   first;
{
/*
 * Format filling of otherwise-empty boxes
 */
   do_fills(mon, year, first);
/*
 * Format the grid of lines for the page
 */
   printf("gsave\n");
   printf("\tBorder\n");
   printf("\tHorizontalLines\n");
   printf("\tVerticalLines\n");
   printf("grestore\n");
/*
 * Format the column headings, currently the days of the week
 */
   printf("SetHeadingFont\n");
   printf("Headings\n");
/*
 * Format the date numbers
 */
   printf("SetNumberFont\n");
   printf("gsave\n");
   printf("\t%d 1 %d LeftMargin BoxWidth add NumberRightMargin sub\n",
	  MONLEN(year, mon),
	  first);
   printf("\tTopLine HeadingHeight sub NumberBaseline sub\n");
   printf("\tBoxWidth BoxHeight RightMargin\n");
   printf("\tNumbers\n");
   printf("grestore\n");
/*
 * Format inset months
 */
   do_small_months(mon, year, first);
/*
 * Set up for the holidays.
 */
   printf("SetHolidayFont\n");
   printf("%%%% Holidays go here.\n");
}
