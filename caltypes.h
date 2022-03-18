#ifndef CALTYPES_H
#define CALTYPES_H
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL caltypes.h 6.2 02/12/06 17:25:35
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
 *	This include file declares the type definitions used by the
 *	romcal program.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	30jan95 : created, kgb
 *	03Mar95 : added COMMEMORATION to rank_t, kgb
 *	01Apr96 : added TRIDUUM rank, kgb
 *	11Feb98 : added HOLYWEEK rank, kgb
 *	26Feb00 : added ASHWED rank, kgb
 *	21Dec01 : added dow_t, kgb
 *	08Feb02 : added WEB_IO, kgb
 *
 *----------------------------------------------------------------------*/
/*
 * Days of the Week
 */
typedef enum Days {
   SUN, MON, TUE, WED, THU, FRI, SAT
} day_t;
/*
 * Months of the Year
 */
typedef enum Months { 
   PREVDEC,  JANUARY,   FEBRUARY, MARCH,
   APRIL,    MAY,       JUNE,     JULY,
   AUGUST,   SEPTEMBER, OCTOBER, NOVEMBER,
   DECEMBER, NEXTJAN
} month_t;
/*
 * Liturgical Colors
 */
typedef enum Colors {
   NOCOLOR, GREEN, WHITE, RED, PURPLE, ROSE, BLACK
} color_t;
/*
 * Liturgical Ranks
 */
typedef enum Ranks {
   WEEKDAY,		/* Plain, old weekdays			*/
   COMMEMORATION,	/* Commemoration = Memorial in Lent 	*/
   OPTIONAL,		/* Optional Memorials			*/
   MEMORIAL,		/* Memorials				*/
   FEAST,		/* Feasts (not of the Lord)		*/
   SUNDAY,		/* Sundays 				*/
   LORD,		/* Feasts of the Lord 			*/
   ASHWED,		/* Ash Wednesday			*/
   HOLYWEEK,		/* Mon, Tue, and Wed of Holy Week	*/
   TRIDUUM,		/* The Triduum				*/
   SOLEMNITY 		/* Solemnities 				*/
} rank_t;
/*
 * Liturgical Seasons
 */
typedef enum Seasons {
   ORDINARY,
   ADVENT,
   CHRISTMAS,
   LENT,
   EASTER,
   PASCHAL	/* Ash Wed., Holy Week & Easter Octave 	*/
} season_t;
/*
 * Boolean operations.  I wanted to call this type boolean_t, but Sun
 * has used that typedef in their version of <sys/types.h>.  Therefore,
 * in honor of Fortran, I've named it logical_t.
 */
typedef enum Logical {
   L_FALSE, L_TRUE
} logical_t;
/*
 * I/O Options. These are the different output options available from
 * ROMCAL.
 */
typedef enum IO_Options {
   TEXT_IO,	/* Text output */
   LIST_IO,	/* List output. Easy to parse with awk, etc. */
   ICAL_IO,	/* iCalendar */
   PSGREY_IO,	/* Black & White Postscript */
   PSCOLOR_IO,	/* Color Postscript */
   HTML_IO,	/* Hypertext Markup Language */
   RTF_IO,	/* Rich Text Format */
   WEB_IO,	/* Create the Web Pages for the romcal.net site. */
   LIST0_IO	/* A better output. Easier to parse. */
} io_t;
/*
 * The days of the week.
 */
typedef enum DaysOfWeek {
   DOW_SUNDAY,
   DOW_MONDAY,
   DOW_TUESDAY,
   DOW_WEDNESDAY,
   DOW_THURSDAY,
   DOW_FRIDAY,
   DOW_SATURDAY
} dow_t;

#endif
