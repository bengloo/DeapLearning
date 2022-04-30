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

#define ANSI_RESET "\033[0m"
#define ANSI_BLACK "\033[30m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE "\033[34m"
#define ANSI_PURPLE "\033[35m"
#define ANSI_CYAN "\033[36m"
#define ANSI_WHITE "\033[37m"