// For different discriminants D, list group size and representation size
// of resulting MNT curves.

#include "pbc.h"

int consider(cm_info_t cm, void *data) {
  unsigned int D = (unsigned int) data;
  int qbits, rbits;
  qbits = mpz_sizeinbase(cm->q, 2);
  rbits = mpz_sizeinbase(cm->r, 2);
  printf("%d, %d, %d\n", D, qbits, rbits);
  fflush(stdout);
  return 0;
}

void try(unsigned int D) {
  cm_search_d(consider, (void *) D, D, 500);
}

int main(int argc, char **argv)
{
  unsigned int D = 7;

  if (argc > 1) {
    D = atoi(argv[1]);
    if (D < 7 || (D % 4) != 3) {
      pbc_die("D must be 3 mod 4 and at least 7");
    }
  }

  const unsigned int maxD = 1000000000;
  printf("D < %u, bits in q, bits in r\n", maxD);
  while (D < maxD) {
    try(D);
    D++;
    try(D);
    D+=3;
  }

  return 0;
}
