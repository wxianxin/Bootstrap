//Author: Steven Wang Date:20151005

#include <iostream>

#include <cmath>

#include "Bond.h"

Bond::Bond(string tenor, double coupon, double price, double faceValue, int payPerAnnum, long issueDate, long maturityDate) {
	this->tenor = tenor;
	this->coupon = coupon;
	this->price = price;
	this->faceValue = faceValue;
	this->payPerAnnum = payPerAnnum;
	this->issueDate = issueDate;
	this->maturityDate = maturityDate;
	this->numberOfCouponPayment = (maturityDate - issueDate) / 10000 * payPerAnnum;
}

string Bond::GetTenor() {
	return this->tenor;
}

double Bond::ComputeYTM() {
	double r = 0;
	double epsilon = 1.0e-5;

	//let x and y be the solution of the equation, which equals "1+r"
	double x = 1.0, y = 5.0;
	while (abs(x - y) > epsilon) {
		x = y - (-price*pow(y, numberOfCouponPayment + 2) + (price + coupon)*pow(y, numberOfCouponPayment + 1) + faceValue / 10 * y - (coupon + faceValue / 10)) / (-(numberOfCouponPayment + 2)*price*pow(y, numberOfCouponPayment + 1) + (numberOfCouponPayment + 1)*(price + coupon)*pow(y, numberOfCouponPayment) + faceValue / 10);
		y = x - (-price*pow(x, numberOfCouponPayment + 2) + (price + coupon)*pow(x, numberOfCouponPayment + 1) + faceValue / 10 * x - (coupon + faceValue / 10)) / (-(numberOfCouponPayment + 2)*price*pow(x, numberOfCouponPayment + 1) + (numberOfCouponPayment + 1)*(price + coupon)*pow(x, numberOfCouponPayment) + faceValue / 10);
	}

	return r = 100 * (y - 1);
}



double Bond::ComputeBondPrice(double faceValue, double coupon, vector<double> vectSpotRate, int numberOfCouponPayment, int payPerAnnum) {
	double price = 0.0;
	for (int i = 0; i < numberOfCouponPayment; ++i)
	{
		price += coupon*faceValue / pow(1.0 + vectSpotRate[i], i + 1);
	}
	price += faceValue / pow(1.0 + vectSpotRate[numberOfCouponPayment - 1], numberOfCouponPayment);
	
	return price;
}

double Bond::ComputeSpotRate(vector<double>& vectSpotRate, int maximumCouponPayments, int interpolatedTenorBegin, int interpolatedTenorEnd) {
	
	double r = 0, epsilon = 1.0e-5, end0 = 0.0, end1 = 100.0, tempEnd;
	vector<double>  vectSpotRate0(maximumCouponPayments, 0.0);
	vector<double>  vectSpotRate1(maximumCouponPayments, 0.0);


	while (abs(end1 - end0) > epsilon) {


		for (int i = 0; i <= interpolatedTenorBegin; ++i)
		{
			vectSpotRate0[i] = vectSpotRate[i];
			vectSpotRate1[i] = vectSpotRate[i];
		}

		tempEnd = end0 + (end1 - end0) / 2;

		for (int i = interpolatedTenorBegin + 1; i <= interpolatedTenorEnd; ++i)
		{
			vectSpotRate0[i] = vectSpotRate[interpolatedTenorBegin] + (tempEnd - vectSpotRate[interpolatedTenorBegin])
				*(i - interpolatedTenorBegin) / (interpolatedTenorEnd - interpolatedTenorBegin);
				
				vectSpotRate1[i] = vectSpotRate[interpolatedTenorBegin] + (end1 - vectSpotRate[interpolatedTenorBegin])
				*(i - interpolatedTenorBegin) / (interpolatedTenorEnd - interpolatedTenorBegin);
		}

		for (int i = 0; i < maximumCouponPayments; i++)
		{
			vectSpotRate0[i] = vectSpotRate0[i] / 100.0 / payPerAnnum;
			vectSpotRate1[i] = vectSpotRate1[i] / 100.0 / payPerAnnum;
		}

		double x, y;

		x = ComputeBondPrice(faceValue, coupon / 100.0 / payPerAnnum, vectSpotRate0, numberOfCouponPayment,
			payPerAnnum) - price / 100.0*faceValue;
		y = ComputeBondPrice(faceValue, coupon / 100.0 / payPerAnnum, vectSpotRate1, numberOfCouponPayment,
			payPerAnnum) - price / 100.0*faceValue;

		if (x*y <= 0) {
			end0 = tempEnd;
		}

		for (int i = 0; i <= interpolatedTenorBegin; ++i)
		{
			vectSpotRate0[i] = vectSpotRate[i];
			vectSpotRate1[i] = vectSpotRate[i];
		}

		for (int i = interpolatedTenorBegin + 1; i <= interpolatedTenorEnd; ++i)
		{
			vectSpotRate0[i] = vectSpotRate[interpolatedTenorBegin] + (end0 - vectSpotRate[interpolatedTenorBegin])
				*(i - interpolatedTenorBegin) / (interpolatedTenorEnd - interpolatedTenorBegin);
			vectSpotRate1[i] = vectSpotRate[interpolatedTenorBegin] + (tempEnd - vectSpotRate[interpolatedTenorBegin])
				*(i - interpolatedTenorBegin) / (interpolatedTenorEnd - interpolatedTenorBegin);
		}

		for (int i = 0; i < maximumCouponPayments; i++)
		{
			vectSpotRate0[i] = vectSpotRate0[i] / 100.0 / payPerAnnum;
			vectSpotRate1[i] = vectSpotRate1[i] / 100.0 / payPerAnnum;
		}

		x = ComputeBondPrice(faceValue, coupon / 100.0 / payPerAnnum, vectSpotRate0, numberOfCouponPayment,
			payPerAnnum) - price / 100.0*faceValue;
		y = ComputeBondPrice(faceValue, coupon / 100.0 / payPerAnnum, vectSpotRate1, numberOfCouponPayment,
			payPerAnnum) - price / 100.0*faceValue;

		if (x*y <= 0) {
			end1 = tempEnd;
		}

	}

	for (int i = interpolatedTenorBegin + 1; i <= interpolatedTenorEnd; ++i)
	{
		vectSpotRate[i] = vectSpotRate[interpolatedTenorBegin] + (end1 - vectSpotRate[interpolatedTenorBegin])
			*(i - interpolatedTenorBegin) / (interpolatedTenorEnd - interpolatedTenorBegin);
	}
	
	return 0;
}

