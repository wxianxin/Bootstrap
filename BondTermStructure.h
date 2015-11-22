//Author: Steven Wang Date:20151005

#ifndef TERMSTRUCTURE_H
#define TERMSTRUCTURE_H

#include <vector>

#include "Bond.h"

class BondTermStructure {

public:

	BondTermStructure();

	void SetBond(vector<Bond> vectBond);
	double GetSpotRate(int index);
	double GetForward6mRate(int index);
	double GetDiscountFactor(int index);
	//??why the last 3 methods has a tail of const?

	//void ComputeSpotRates();
	void ComputeSpotRates();
	void ComputeForward6mRates();
	void ComputeDiscountFactors();




private:
	vector<Bond> vectBond;
	vector<double> vectSpotRate;
	vector<double> vectForward6mRate;
	vector<double> vectDiscountFactor;
};

#endif