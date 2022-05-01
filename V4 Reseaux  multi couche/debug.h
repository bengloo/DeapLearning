#include "setting.h"
#ifdef DEBUG
#define DEBUG_C(s)  s
#define DEBUG_I(i) printf("%d\n", i);
#define DEBUG_S(s) printf("%s\n", s);
#define DEBUG_S1(s, p1) printf(s, p1);
#define DEBUG_S2(s, p1, p2) printf(s, p1, p2);
#define DEBUG_S3(s, p1, p2, p3) printf(s, p1, p2, p3);
#define DEBUG_S4(s, p1, p2, p3, p4) printf(s, p1, p2, p3, p4);
#else
#define DEBUG_C(s) (void)0
#define DEBUG_I(i)
#define DEBUG_S(s) (void)0;
#define DEBUG_S1(s, p1) (void)0;
#define DEBUG_S2(s, p1, p2) (void)0;
#define DEBUG_S3(s, p1, p2, p3) (void)0;
#define DEBUG_S4(s, p1, p2, p3, p4) (void)0;
#endif

#define ANSI_CLEAR "\033[0;0H\033[2J"
#define ANSI_RESET "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_FAINT "\033[2m"
#define ANSI_ITALIC "\033[3m"
#define ANSI_UNDERLINE "\033[4m"
#define ANSI_S_BLINK "\033[5m"
#define ANSI_R_BLINK "\033[6m"
#define ANSI_REVERSE "\033[7m"
#define ANSI_CONCEAL "\033[8m"
#define ANSI_CROSSED "\033[9m"
#define ANSI_DEFAULT "\033[10m"
#define ANSI_FRAKTUR "\033[20m"
#define ANSI_D_UNDERLINE "\033[21m"
#define ANSI_NORMAL "\033[22m"
#define ANSI_NOT_ITALIC "\033[23m"
#define ANSI_NOT_UNDERLINE "\033[24m"
#define ANSI_NOT_BLINK "\033[25m"
#define ANSI_NOT_INVERSE "\033[27m"

#define ANSI_BLACK "\033[30m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE "\033[34m"
#define ANSI_PURPLE "\033[35m"
#define ANSI_CYAN "\033[36m"
#define ANSI_WHITE "\033[37m"
