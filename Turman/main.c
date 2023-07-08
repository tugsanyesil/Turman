#include <stdio.h>
#include <stdlib.h>
#include "Turman.h"

double GetSignal()
{
	return (rand() % 100);
}

int main()
{
	struct Turman T;

	InitTurman(&T, 3, 5, 0.3, 0);
	double signal;
	double filtered_signal;

	while (1)
	{
		signal = GetSignal();
		filtered_signal = Turman(&T, signal);

		printf("%f      %f", signal, filtered_signal);
		printf("\r ");
		Sleep(100);
	}

	return 0;
}