/**
* @file shopprogram.h
* @brief  shopprogram class
*
* @author Felix Abbott
* @assignment Linux Final
* @date 12/14/2020
* @credits
* 
*/

#ifndef SHOPPROGRAMFUNCTIONS_H
#define SHOPPROGRAMFUNCTIONS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class ShopProgram {
public:
	//Constructors
	ShopProgram() {};
	~ShopProgram() {};

	//Functions
	void openTextFiles();
	bool checkFilesExist();
	void readDailyFile();
	void calculations();
	void saveFile();
	void printDailyFileInfo();

	int getVectorSize();
	void merge(int beg, int mid, int end);
	void mergeSort(int beg, int end);

private:
	ifstream dailyFile; //File that holds the daily orders
	fstream finalFile; //File that stores all past orders
	string dailyFileName, finalFileName;

	//Daily File Variables
	vector<string> dailyCustomerName, dailyOrder;
	vector<float> dailyOrderCost;

	//Final File Variables
	int productionCosts, originalTotalProfit, finalProfit;
};
#endif SHOPPROGRAMFUNCTIONS_H