//Author: Steven Wang Date:20151005

#include <iostream>

#include <vector>

#include <iomanip>

#include "BondTermStructure.h"



BondTermStructure::BondTermStructure() {

	for (int i = 0; i < 20; ++i)
	{
		vectSpotRate.push_back(0.0);
		vectForward6mRate.push_back(0.0);
		vectDiscountFactor.push_back(0.0);
	}
	
}

void BondTermStructure::SetBond(vector<Bond> vectBond) {
	this->vectBond = vectBond;
}

double BondTermStructure::GetSpotRate(int index) {
	return vectSpotRate[index];
}

double BondTermStructure::GetForward6mRate(int index) {
	return vectForward6mRate[index];
}

double BondTermStructure::GetDiscountFactor(int index) {
	return vectDiscountFactor[index];
}

void BondTermStructure::ComputeSpotRates() {
	
	for (vector<Bond>::iterator iter = vectBond.begin(); iter != vectBond.end(); ++iter) {
		//??learn the iterator

		if (iter->GetTenor() == "6m") {
			vectSpotRate[0] = iter->ComputeYTM();
		}

		if (iter->GetTenor() == "1y") {
			iter->ComputeSpotRate(vectSpotRate, 20, 0, 1);
		}
		
		if (iter->GetTenor() == "2y") {
			iter->ComputeSpotRate(vectSpotRate, 20, 1, 3);
		}
		
		if (iter->GetTenor() == "3y") {
			iter->ComputeSpotRate(vectSpotRate, 20, 3, 5);
		}
		
		if (iter->GetTenor() == "5y") {
			iter->ComputeSpotRate(vectSpotRate, 20, 5, 9);
		}
		
		if (iter->GetTenor() == "7y") {
			iter->ComputeSpotRate(vectSpotRate, 20, 9, 13);
		}
		
		if (iter->GetTenor() == "10y") {
			iter->ComputeSpotRate(vectSpotRate, 20, 13, 19);
		}
	}

}

void BondTermStructure::ComputeDiscountFactors() {
	for (int i = 0; i < vectSpotRate.size(); ++i)
	{
		vectDiscountFactor[i] = 100 * pow(1.0 + vectSpotRate[i] / 100.0 / 2.0, -(i + 1));
	}
}

void BondTermStructure::ComputeForward6mRates()
{
	for (int i = 0; i < vectSpotRate.size() - 1; ++i)
	{
		vectForward6mRate[i] = (pow((pow(1.0 + vectSpotRate[i + 1] / 100.0 / 2.0, (i + 2) / 2.0) /
			pow(1.0 + vectSpotRate[i] / 100.0 / 2.0, (i + 1) / 2.0)), 1.0 / 0.5) - 1.0) * 100.0 * 2.0;
	}
}
