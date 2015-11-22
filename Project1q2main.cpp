//Author: Steven Wang Date:20151005

#include <iostream>

#include <fstream>

#include "Bond.h"

#include "BondTermStructure.h"

#include <iomanip>

int main() {

	vector<Bond> vectBond;

	ifstream inFile;
	inFile.open("data.txt");
	
	string tempTenor;
	double tempCoupon;
	double tempPrice;
	double tempFaceValue;
	int tempPayPerAnnum;
	long tempIssueDate;
	long tempMaturityDate;

	
	while (!inFile.eof()) {
		inFile >> tempTenor >> tempCoupon >> tempPrice >> tempFaceValue >> tempPayPerAnnum >> tempIssueDate >> tempMaturityDate;
		Bond* tempBond = new Bond(tempTenor, tempCoupon, tempPrice, tempFaceValue, tempPayPerAnnum, tempIssueDate, tempMaturityDate);
		vectBond.push_back(*tempBond);

	
	
	}

	inFile.close();

	BondTermStructure* bondTermStructure = new BondTermStructure();
	bondTermStructure->SetBond(vectBond);
	bondTermStructure->ComputeSpotRates();
	bondTermStructure->ComputeDiscountFactors();
	bondTermStructure->ComputeForward6mRates();

	static string TENOR[20] = { "6m", "1y", "18m", "2y", "2.5y", "3y", "3.5y", "4y", "4.5y", "5y",
		"5.5y", "6y", "6.5y", "7y", "7.5y", "8y", "8.5y", "9y", "9.5y", "10y" };

	cout << "Tenor" << "\t\t" << "Spot(%)" << "\t\t\t" << "DF(%)" << "\t\t\t" << "6mFwd(%)" << endl;
	for (int i = 0; i < 20; ++i)
	{
		cout << TENOR[i]
			<< "\t\t" << fixed << setw(10) << setprecision(5) << bondTermStructure->GetSpotRate(i)
			<< "\t\t" << fixed << setw(10) << setprecision(5) << bondTermStructure->GetDiscountFactor(i)
			<< "\t\t" << fixed << setw(10) << setprecision(5) << bondTermStructure->GetForward6mRate(i)
			<< endl;
	}



	return 0;
}