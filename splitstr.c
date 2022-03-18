#include <stdio.h>
#include <string.h>

char *splitstr(s, maxlen)
char *s;
int   maxlen;
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL splitstr.c 6.1 02/12/06 17:23:53
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
 *	This module will intelligently split a long string into shorter
 *	strings of 'maxlen' or less.  Note that it returns allocated
 *	memory (from strdup) which will need to be freed by the calling
 *	module.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	05Feb95 : created, kgb
 *	11Feb98 : completely recoded, kgb
 *
 *----------------------------------------------------------------------*/

   char *p,
        *q,
	*retval,
        *split;

   int   istr,
         plen,
         splitlen;

/*
 * Split strings.  These are strings after which long lines will be
 * broken.  The split string should end in a space, and the long
 * strings will be broken on that space.
 */
   static char *strings[] =
   {
      "; ",
      " and ",
      ", ",
      " of ",
      " "
   };

#define NUM_STRINGS (sizeof(strings)/sizeof(strings[0]))

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * Duplicate the input string.  Note that this uses malloc(), and so
 * must be freed by someone.
 */
   retval = strdup(s);

   if (retval != NULL) {
/*
 *    In the following loops, p points to the beginning of the current
 *    line of the wrapped string, and q starts at the end of the
 *    current line (i.e., p + the maxlen less the length of the current
 *    split string).  q is moved backwards, searching for the current
 *    wrap string.  If the current wrap string is found, the last
 *    character of the found string (the space) is replaced with a
 *    newline.  p is then reset to point to the character after the
 *    newline and the process is repeated until the string that p is
 *    pointing to has a length less than the given maximum.
 */
      p = retval;
      plen = strlen(p);

      while (plen > maxlen) {
	 for (istr = 0; istr < NUM_STRINGS; istr++) {
	    split = strings[istr];
	    splitlen = strlen(split);

	    for (q = p + maxlen - splitlen + 1; q > p; q--) {
	       if (strncmp(q, split, splitlen) == 0) {
		  *(q + splitlen - 1) = '\n';
		  p = q + splitlen;
		  plen = strlen(p);
		  istr = NUM_STRINGS;
		  break;
	       }
	    }
	 }
      }
   }

   return (retval);
}
