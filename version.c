#include <stdio.h>

void version()
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL version.c 6.2 03/01/06 16:10:03
 *
 *	Copyright (C) 1993, Kenneth G. Bath
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
 * 	This module prints out the copyright notice and version number.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	08feb02 : created, kgb
 *
 *----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/
/*
 * The following constants are filled in by SCCS automatically.
 */
   fprintf(stderr,
	   "ROMCAL Version %d - Copyright 1993-%.4s, Kenneth G. Bath\n",
	   6,
	   "2003/01/06");
}
