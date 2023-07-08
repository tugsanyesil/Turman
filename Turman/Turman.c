#include <stdio.h>
#include <stdlib.h>
#include "Turman.h"

void InitArray(double** p, int len, double initial_value)
{
	if (len > 0)
	{
		double* a = malloc(sizeof(double) * len);
		int i = 0;
		for (i = 0; i < len; i++)
		{
			a[i] = initial_value;
		}
		*p = a;
	}
}

void InitMatris(double*** p, unsigned short row, unsigned short col, double initial_value)
{
	if (row != 0 && col != 0)
	{
		double** m = malloc(sizeof(double*) * row);
		int r = 0;
		int c = 0;
		for (r = 0; r < row; r++)
		{
			m[r] = malloc(sizeof(double) * col);
			for (c = 0; c < col; c++)
			{
				m[r][c] = initial_value;
			}
		}
		*p = m;
	}
}

void SetTurmanRate(struct Turman* pTurman, double rate)
{
	InitArray(&(pTurman->Rates), pTurman->Neighbor, 0);

	double dr = 2.0 * (rate - (1.0 / pTurman->Neighbor)) / (pTurman->Neighbor - 1);

	int neighbor = 0;
	for (neighbor = 0; neighbor < pTurman->Neighbor; neighbor++)
	{
		pTurman->Rates[neighbor] = rate - (neighbor * dr);
	}
}

void InitTurman(struct Turman* pTurman, unsigned short order, unsigned short neighbor, double rate, double initial_signal_value)
{
	if (order != 0 && neighbor != 0)
	{
		pTurman->Order = order;
		pTurman->Neighbor = neighbor;

		InitMatris(&(pTurman->Signals), pTurman->Order, pTurman->Neighbor, initial_signal_value);
		SetTurmanRate(pTurman, rate);
	}
}

void SetTurmanFree(struct Turman* pTurman)
{
	if (pTurman->Neighbor != 0 && pTurman->Order != 0)
	{
		int order;
		for (order = 0; order < pTurman->Order; order++)
		{
			free(pTurman->Signals[order]);
		}
		free(pTurman->Signals);
		free(pTurman->Rates);
	}

	pTurman->Neighbor = 0;
	pTurman->Order = 0;
}

double Turman(struct Turman* pTurman, double signal)
{
	double s0 = 0; // s0 is signal will be filtered
	int order = 0;
	int neighbor = 0;
	for (neighbor = pTurman->Neighbor - 1; neighbor > 0; neighbor--) // jump forward all data
	{
		pTurman->Signals[0][neighbor] = pTurman->Signals[0][neighbor - 1];
	}

	pTurman->Signals[0][0] = signal;
	for (neighbor = 0; neighbor < pTurman->Neighbor; neighbor++) // filter signal with its prevs by their rates
	{
		s0 += pTurman->Signals[0][neighbor] * pTurman->Rates[neighbor];
	}
	pTurman->Signals[0][0] = s0;

	for (order = 1; order < pTurman->Order; order++) // there is same code in and out of order for loop because o = 0 is a special case
	{
		for (neighbor = pTurman->Neighbor - 1; neighbor > 0; neighbor--) // jump forward all data
		{
			pTurman->Signals[order][neighbor] = pTurman->Signals[order][neighbor - 1];
		}

		pTurman->Signals[order][0] = pTurman->Signals[order - 1][0];
		s0 = 0; // s0 is signal will be filtered
		for (neighbor = 0; neighbor < pTurman->Neighbor; neighbor++) // filter signal with its prevs by their rates
		{
			s0 += pTurman->Signals[order][neighbor] * pTurman->Rates[neighbor];
		}
		pTurman->Signals[order][0] = s0;
	}

	return pTurman->Signals[pTurman->Order - 1][0]; // Order - 1 means final order and we can get also the lows if we want
}