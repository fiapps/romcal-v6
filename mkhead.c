#include <stdio.h>

int main(int   argc,
         char *argv[])
{
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL mkhead.c 6.1 02/12/06 17:23:53
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
 *	This program creates a header file from a data file.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	25Jul94 : created, kgb
 *	08Feb94 : removed version.h, kgb
 *
 *----------------------------------------------------------------------*/

   char  line[120];

   char *p;

/*----------------------------------------------------------------------*
 *	begin code							*
 *----------------------------------------------------------------------*/

   printf("static char *__MKHEAD__[] = {\n");
   while (gets(line)) {
      printf("\"");
      for (p = &line[0]; *p != NULL; p++) {
	 switch (*p) {
	    case '%':
	       putchar('%');
	       putchar('%');
	       break;
	    case '\t':
	       putchar('\\');
	       putchar('t');
	       break;
	    case '"':
	       putchar('\\');
	       putchar('"');
	       break;
	    case '\\':
	       putchar('\\');
	       putchar('\\');
	       break;
	    default:
	       putchar(*p);
	       break;
	 }
      }
      printf("\\n\",\n");
   }
   printf("NULL\n};\n");

   return 0;
}
