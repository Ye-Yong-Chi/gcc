/* { dg-do run } */

#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int
main (int argc, char **argv)
{
  const int N = 256;
  int i;
  unsigned char *h;

  h = (unsigned char *) malloc (N);

  for (i = 0; i < N; i++)
    {
      h[i] = i;
    }

  fprintf (stderr, "CheCKpOInT\n");
  acc_update_device (h, N);

  acc_copyout (h, N);

  for (i = 0; i < N; i++)
    {
      if (h[i] != 0xab)
	abort ();
    }

  free (h);

  return 0;
}

/* { dg-output "CheCKpOInT(\n|\r\n|\r).*" } */
/* TODO: currently doesn't print anything; SIGSEGV.
   <https://gcc.gnu.org/PR66518>.  */
/* { dg-output "\\\[\[0-9a-fA-FxX\]+,256\\\] is not mapped" { xfail *-*-* } } */
/* { dg-shouldfail "" } */
