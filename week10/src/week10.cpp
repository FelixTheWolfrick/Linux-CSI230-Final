/**
* @file shopprogram.cpp
* @brief  program that calculates the total profit you made that month from sales
*
* @author Felix Abbott
* @assignment Linux Final
* @date 12/14/2020
* @credits
* 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "shopprogram.h"

using namespace std;

int main()
{
	//Variables
	ShopProgram shopProgramObj;

	//Call Functions
	do
	{
		shopProgramObj.openTextFiles();
	} while (!shopProgramObj.checkFilesExist());

	cout << endl;
	shopProgramObj.readDailyFile();
	cout << endl;

	cout << "------Daily File Info------" << endl;
	shopProgramObj.printDailyFileInfo();
	cout << endl;

	int vectorSize = shopProgramObj.getVectorSize();
	shopProgramObj.mergeSort(0, vectorSize - 1);

	cout << "------Daily File Sorted------" << endl;
	shopProgramObj.printDailyFileInfo();
	cout << endl;

	cout << "------Calculations------" << endl;
	shopProgramObj.calculations();
	cout << endl;

	shopProgramObj.saveFile();

	//Return
	system("pause");
	return 0;
}