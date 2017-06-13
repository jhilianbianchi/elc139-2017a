#ifdef ISBIG_ENDIAN
extern unsigned int x1[14];
#else
extern unsigned int *x1;
#endif

extern unsigned int tail;
extern unsigned int result2[4];
extern unsigned int result3[4];
extern unsigned int digest2[4];
extern unsigned int working[4];
extern unsigned int diff;

extern unsigned long count;
extern unsigned long count2;
extern unsigned int verbosity;
extern unsigned int benchmode;
extern unsigned int minimal;
extern unsigned int duration;
extern unsigned int custom;
extern unsigned int all;
extern unsigned int len, len_begin, len_end;
extern unsigned int ender;
extern unsigned int beginer;
extern unsigned int hwrite;
extern unsigned int hread;
extern unsigned int fastwrite;
extern unsigned int fast;
extern unsigned int fasta, fastb, fastc, fastd;
extern unsigned int val;
extern int counter;
extern FILE *desw;
extern long elapsed;
extern long elapsed_u;
extern char target[33];
extern char *filename;
extern char *alfa;
extern char *test;
extern char *test2;
extern char *total;
extern char *total2;
extern int optind;
extern char *optarg;
extern long start;
extern long start_u;
extern char *begin;
extern char *end;
extern unsigned int result2[4], result3[4];
extern void handle();

#ifndef RESUME_FILE
#define RESUME_FILE "/tmp/.mdcrack.resume"
#endif
#ifndef BENCH_HASH
#define BENCH_HASH "ffffffffffffffffffffffffffffffff"
#endif
#ifndef ALFA
#define ALFA "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUWXYZ"
#endif
#ifndef BLOCKSIZE
#define BLOCKSIZE 50
#endif


#ifndef NCURSES
#define printw printf
#endif

