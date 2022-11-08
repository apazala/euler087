#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int primesList[1000];
int numprimes;
void fillprimes(int upperBound);

int squares[1000];
int nsq;
int cubes[1000];
int ncub;
int quads[1000];
int nq;

int solutions[50000001];

int solve()
{
	fillprimes(1 + sqrt(51000000));

	for (int i = 0; ; i++)
	{
		int64_t v = primesList[i];
		v *= v;
		if (v > 50000000) break;

		squares[nsq++] = v;
	}
	for (int i = 0; ; i++)
	{
		int64_t v = squares[i];
		v *= primesList[i];

		if (v > 50000000) break;

		cubes[ncub++] = v;
	}
	for (int i = 0; ; i++)
	{
		int64_t v = squares[i];
		v *= v;

		if (v > 50000000) break;

		quads[nq++] = v;
	}

	for (int i = 0; i < nsq; i++)
	{
		int v1 = squares[i];
		for (int j = 0; j < ncub; j++)
		{
			int v2 = v1 + cubes[j];
			if (v2 > 50000000) break;
			for (int k = 0; k < nq; k++)
			{
				int v3 = v2 + quads[k];
				if (v3 > 50000000) break;

				solutions[v3] = 1;
			}
		}
	}

	for (int i = 0; i <= 50000000; i++)
		solutions[i] += solutions[i - 1];

	return solutions[50000000];
}

int main()
{
	int sol = solve();

	printf("%d\n", sol);

	return 0;
}



uint64_t *newbitarray(int size, int set) {
	size_t s = (1 + (size >> 6)) * sizeof(uint64_t);
	uint64_t *ba = (uint64_t *)malloc((1 + (size >> 6)) * sizeof(uint64_t));

	memset(ba, set ? (int)((1ll << 32) - 1) : 0, s);

	return ba;
}

#define baisset(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) != 0
#define baisclear(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) == 0
#define baset(ba, i) (ba)[(i)>>6] |= (1ull << ((i) & 63))

void fillprimes(int upperBound) {
	int i, j;

	uint64_t *iscompound = newbitarray(upperBound + 1, 0);

	baset(iscompound, 0);
	baset(iscompound, 1);
	int sqrtUb = sqrt(upperBound);
	for (i = 2; i <= sqrtUb; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
			for (j = i*i; j <= upperBound; j += i) {
				baset(iscompound, j);
			}
		}
	}

	for (i = sqrtUb + 1; i <= upperBound; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
		}
	}

	free(iscompound);
}



