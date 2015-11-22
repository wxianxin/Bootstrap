//Author: Steven Wang Date:20151005

#ifndef BOND_H
#define BOND_H

#include <string>
#include <vector>

using namespace std;

class Bond
{
public:
	Bond(string tenor, double coupon, double price, double faceValue, int payPerAnnum, long issueDate, long maturityDate);

	string GetTenor();	
	//void setValues(double coupon, double price, double faceValue);
	//void serValues(double coupon, double price);
	double ComputeYTM();
	//double ComputeBondPrice(double faceValue, double coupon, double ytm, int numberOfCouponPayments);
	double ComputeBondPrice(double faceValue, double coupon, vector<double> vectSpotRate, int umberOfCouponPayment, int payPerAnnum);
	double ComputeSpotRate(vector<double>& vectSpotRate, int maximumCouponPayments, int interpolatedTenorStart, int interpolatedTenorEnd);

private:	
	double coupon, price, faceValue;
	string tenor;
	int payPerAnnum, numberOfCouponPayment;
	long issueDate, maturityDate;
	//double spotRate, forward6mRate, discountFactor;
};

#endif