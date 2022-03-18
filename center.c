#include <string.h>
#include "romcal.h"

char *center(char *string, 
	     char *buffer, 
	     int bufsiz)
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL center.c 6.2 02/12/06 17:25:03
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
 *	This module centers the string pointed to by 'string' within
 *	the string pointed to by 'buffer', whose length is 'buflen'.
 *	Blanks will be added to the beginning of 'buffer' to make
 *	'string' centered.  'buffer' will be null terminated.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	17mar93 : created, kgb
 *
 *----------------------------------------------------------------------*/

   int   i,
         b2,
         s2,
         nblank;

   char *p,
        *q;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Find the midpoints of the buffer and the string.
 */
   b2 = bufsiz / 2;
   s2 = strlen(string) / 2;
/*
 * Compute the number of blanks that should be at the beginning of the
 * buffer.
 */
   nblank = b2 - s2;
/*
 * Fill in the blanks.
 */
   p = buffer;

   for (i = 0; i < nblank; i++) {
      *p = ' ';
      p++;
   }
/*
 * Copy the string to the buffer after the blanks.
 */
   for (q = string; *q != '\0'; q++) {
      *p = *q;
      p++;
   }
/*
 * Null terminate the buffer.
 */
   *p = '\0';
   return (buffer);
}
