//Bond Calculation Program
//Author: Jennifer Baronat
//Release Date: November 16, 2015
//Version 1.1

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>


//Function Prototypes
double CalcPrice(double coupon, int years, double face, double rate);
double CalcYield(double coupon, int years, double face, double price);

int main()
{
	//Variables
	double couponPayment;
	int yearsMaturity;
	double faceValue;
	double discountRateYTC;
	double currentPrice;

	bool endMenu = false;
	int menu_option;

	//Menu Options
	std::cout << "Bond Yield Calculator" << std::endl << "*******************" << std::endl;

	do {
		std::cout << "1. Calculate Bond Price:" << std::endl << std::endl;
		std::cout << "2. Calculate Bond Yield:" << std::endl << std::endl;
		std::cout << "3. Exit Program" << std::endl << std::endl;

		std::cin >> menu_option;		
		std::cout << std::endl;

		if (menu_option == 1)
		{
			std::cout << "Enter coupon rate (ex: .10)" << std::endl << std::endl;
			while (!(std::cin >> couponPayment)) {        //Test if input is a numerical value
				std::cout << "Invalid input, please enter a number.";         
				std::cin.clear ();         
				std::cin.ignore (1000, '\n');  //clear buffer                                 
			}
			std::cout << "Enter years to maturity" << std::endl << std::endl;
			while (!(std::cin >> yearsMaturity)) {
				std::cout << "Invalid input, please enter a number.";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			std::cout << "Enter face value of the bond" << std::endl << std::endl;
			while (!(std::cin >> faceValue)) {
				std::cout << "Invalid input, please enter a number.";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			std::cout << "Enter discount rate or yield (ex: .15)" << std::endl << std::endl;
			while (!(std::cin >> discountRateYTC)) {
				std::cout << "Invalid input, please enter a number.";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			std::cout << " The value of the bond is " << std::fixed << std::setprecision(7)
				<< CalcPrice(couponPayment, yearsMaturity, faceValue, discountRateYTC) << std::endl;
		}
		else if (menu_option == 2)
		{
			std::cout << "Enter coupon rate (ex: .10)" << std::endl << std::endl;
			while (!(std::cin >> couponPayment)) {
				std::cout << "Invalid input, please enter a number.";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			std::cout << "Enter years to maturity" << std::endl << std::endl;
			while (!(std::cin >> yearsMaturity)) {
				std::cout << "Invalid input, please enter a number.";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			std::cout << "Enter face value of the bond" << std::endl << std::endl;
			while (!(std::cin >> faceValue)) {
				std::cout << "Invalid input, please enter a number.";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			std::cout << "Enter current price of bond" << std::endl << std::endl;
			while (!(std::cin >> currentPrice)) {
				std::cout << "Invalid input, please enter a number.";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}

			std::cout << " The yield to maturity is " << std::fixed << std::setprecision(7)
				<< CalcYield(couponPayment, yearsMaturity, faceValue, currentPrice) << std::endl;
		}
		else if (menu_option == 3)
		{
			endMenu = true;
		}
		else
		{
			std::cout << menu_option << " is not a valid menu option, please choose again." << std::endl;
		}

	} while (endMenu == false);

	system("pause");
	return 0;
}

//Function Definitions
double CalcPrice(double coupon, int years, double face, double rate)
{
	double currentPrice = 0.0;

	//add in coupon payments
	for (int i = 1; i <= years; i++)
	{
		currentPrice = currentPrice + coupon * face / pow((1 + rate), i);
	}
	//add in priciple
	currentPrice = currentPrice + face / pow((1 + rate), years);

	return currentPrice;
}

double CalcPriceSlope(double coupon, int years, double face, double rate)
{
	double slope = 0.0;

	//add in coupon payments
	for (int i = 1; i <= years; i++)
	{
		slope = slope - coupon *face*i / pow(1 + rate, i + 1);
	}
	//add in principle
	slope = slope - face*years / pow(1 + rate, years + 1);
	
	return slope;
}

double CalcYield(double coupon, int years, double face, double price)
{
	//start by approximating the rate as the coupon rate.
	double rate = coupon;
	double difference = 1;
	double slope = 0;

	//Newton's method to find better approximations until the answer is close
	while (abs(difference) > 0.00000001)
	{
		difference = CalcPrice(coupon, years, face, rate) - price;
		slope = CalcPriceSlope(coupon, years, face, rate);

		// Newton's equation
		rate = rate - difference / slope;

		//sometimes Newton's method will covercompensate if the initial estimate is much too high...
		//... and negative rates can yield infinite prices, so clamp the rate.
		if (rate < 0) rate = 0;
	}

	return rate;
}