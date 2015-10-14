/* { dg-do compile { target fpic } } */
/* { dg-options "-O2 -fPIC" } */

extern int strcmp (const char *, const char *);
extern int strcmp (const char *, const char *)
  __attribute__ ((visibility ("hidden")));

int
bar (const char *d, const char *s)
{
  return __builtin_strcmp (d, s);
}

/* { dg-final { scan-assembler-not "strcmp@PLT" } } */
