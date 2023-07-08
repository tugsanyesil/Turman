struct Turman
{
	unsigned short Order;		// filter times
	unsigned short Neighbor;	// neighbors
	double** Signals;			// signals
	double* Rates;				// rates
};

void InitializeArray(double** p, int len, double initial_value);

void InitializeMatris(double*** p, unsigned short row, unsigned short col, double initial_value);

void SetTurmanRate(struct Turman* pTurman, double rate);

// order is number of how many times signal will be filtered
// neighbor is number of how many signal will be used in filter
// rate is current signal weight ratio
// initial_signal_value is assumption of past signals
// Turman filter behaves as  low pass filter when ( neighbor * rate ) is  lower than 2
// Turman filter behaves as high pass filter when ( neighbor * rate ) is higher than 2
void InitTurman(struct Turman* pTurman, unsigned short order, unsigned short neighbor, double rate, double initial_signal_value);

void SetTurmanFree(struct Turman* pTurman);

double Turman(struct Turman* pTurman, double signal);