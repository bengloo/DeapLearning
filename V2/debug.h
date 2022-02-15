#define DEBUG
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