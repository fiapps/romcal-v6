#ifndef PROTO_H
#define PROTO_H
/*----------------------------------------------------------------------*
 *
 *	@(#)ROMCAL proto.h 6.3 03/01/06 16:19:41
 *
 *	Copyright (C) 1993,1995,2001, Kenneth G. Bath
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
 *	This include file has the function prototypes for the ROMCAL 
 *	program. To turn off prototyping, #define NOPROTO.
 *
 *---------------------- Software Unit History -------------------------*
 *
 *	21Dec01 : created, kgb
 *
 *----------------------------------------------------------------------*/

#ifdef NOPROTO
/* rtfrow.c        */   extern void rtfrow();
/* montail.c       */   extern void montail();
/* splitstr.c      */   extern char *splitstr();
/* psformat.c      */   extern void do_small_months();
/* monhead.c       */   extern void monhead();
/* init.c          */   extern void init();
/* lent.c          */   extern int lent();
/* center.c        */   extern char *center();
/* ord2.c          */   extern void ordinary2();
/* ord1.c          */   extern void ordinary1();
/* easter.c        */   extern int easter();
/* eastdate.c      */   extern void eastdate();
/* calhead.c       */   extern void calhead();
/* datestr.c       */   extern char *datestr();
/* gencel.c        */   extern char *gencel();
/* advent.c        */   extern int advent();
/* caltail.c       */   extern void caltail();
/* doy.c           */   extern int doy();
/* xmas2.c         */   extern void christmas2();
/* xmas1.c         */   extern int christmas1();
/* proper.c        */   extern void proper();
/* parse.c         */   extern struct Info *parse();
/* printcal.c      */   extern void printcal();
/* printhtm.c      */   extern void printhtm();
/* printics.c      */   extern void printics();
/* printmon.c      */   extern void printmon();
/* printpsc.c      */   extern void printpsc();
/* printpsg.c      */   extern void printpsg();
/* printrtf.c      */   extern void printrtf();
/* printtxt.c      */   extern void printtxt1();
/* printtxt.c      */   extern void printtxt();
/* printweb.c      */   extern void printweb1();
/* printweb.c      */   extern void printweb();
/* leapyear.c      */   extern logical_t leapyear(int);
#else
/* rtfrow.c        */   extern void rtfrow(logical_t);
/* montail.c       */   extern void montail(struct Info *);
/* splitstr.c      */   extern char *splitstr(char *,
/* splitstr.c      */                         int);
/* psformat.c      */   extern void do_small_months(month_t,
/* psformat.c      */                               int,
/* psformat.c      */                               int);
/* psformat.c      */   extern void do_fills(month_t,
/* psformat.c      */                        int,
/* psformat.c      */                        int);
/* psformat.c      */   extern int end_page(void);
/* psformat.c      */   extern void do_page1(month_t,
/* psformat.c      */                        int,
/* psformat.c      */                        int);
/* psformat.c      */   extern void do_page2(month_t,
/* psformat.c      */                        int,
/* psformat.c      */                        int);
/* monhead.c       */   extern void monhead(struct Info *,
/* monhead.c       */                       int);
/* init.c          */   extern void init(struct Info *,
/* init.c          */                    struct Cal[]);
/* lent.c          */   extern int lent(struct Info *,
/* lent.c          */                   struct Cal *);
/* center.c        */   extern char *center(char *,
/* center.c        */                       char *,
/* center.c        */                       int);
/* ord2.c          */   extern void ordinary2(struct Info *,
/* ord2.c          */                         struct Cal[],
/* ord2.c          */                         int,
/* ord2.c          */                         int);
/* ord1.c          */   extern void ordinary1(struct Info *,
/* ord1.c          */                         struct Cal[],
/* ord1.c          */                         int,
/* ord1.c          */                         int);
/* easter.c        */   extern int easter(struct Info *,
/* easter.c        */                     struct Cal[]);
/* eastdate.c      */   extern void eastdate(int,
/* eastdate.c      */                        int *,
/* eastdate.c      */                        int *);
/* calhead.c       */   extern void calhead(struct Info *);
/* datestr.c       */   extern char *datestr(int,
/* datestr.c       */                        int);
/* gencel.c        */   extern char *gencel(season_t,
/* gencel.c        */                       int,
/* gencel.c        */                       dow_t);
/* advent.c        */   extern int advent(struct Info *,
/* advent.c        */                     struct Cal *);
/* caltail.c       */   extern void caltail(struct Info *);
/* doy.c           */   extern int doy(int,
/* doy.c           */                  int,
/* doy.c           */                  int);
/* doydate.c       */   extern void doydate(int,
/* doydate.c       */                       int,
/* doydate.c       */                       int *,
/* doydate.c       */                       int *);
/* xmas2.c         */   extern void christmas2(struct Info *,
/* xmas2.c         */                          struct Cal[]);
/* xmas1.c         */   extern int christmas1(struct Info *,
/* xmas1.c         */                         struct Cal[]);
/* proper.c        */   extern void proper(struct Info *,
/* proper.c        */                      struct Cal[]);
/* parse.c         */   extern struct Info *parse(int,
/* parse.c         */                             char *[]);
/* printcal.c      */   extern void printcal(struct Info *,
/* printcal.c      */                        struct Cal *);
/* printhtm.c      */   extern void printhtm(struct Info *,
/* printhtm.c      */                        struct Cal *,
/* printhtm.c      */                        int);
/* printics.c      */   extern void printics(struct Info *,
/* printics.c      */                        struct Cal *,
/* printics.c      */                        int);
/* printmon.c      */   extern void printmon(struct Info *,
/* printmon.c      */                        struct Cal *,
/* printmon.c      */                        int);
/* printpsc.c      */   extern void printpsc(struct Info *,
/* printpsc.c      */                        struct Cal *,
/* printpsc.c      */                        int);
/* printpsg.c      */   extern void printpsg(struct Info *,
/* printpsg.c      */                        struct Cal *,
/* printpsg.c      */                        int);
/* printrtf.c      */   extern void printrtf(struct Info *,
/* printrtf.c      */                        struct Cal *,
/* printrtf.c      */                        int);
/* printtxt.c      */   extern void printtxt1(struct Info *,
/* printtxt.c      */                         struct Cal[],
/* printtxt.c      */                         int);
/* printtxt.c      */   extern void printtxt(struct Info *,
/* printtxt.c      */                        struct Cal *,
/* printtxt.c      */                        int);
/* printweb.c      */   extern void printweb1(struct Info *,
/* printweb.c      */                         struct Cal[],
/* printweb.c      */                         int);
/* printweb.c      */   extern void printweb(struct Info *,
/* printweb.c      */                        struct Cal[],
/* printweb.c      */                        int);
/* leapyear.c      */   extern logical_t leapyear(int);
#endif

#endif
