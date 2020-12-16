/**
* @file shopprogram.cpp
* @brief  functions to run shopprogram class
*
* @author Felix Abbott
* @assignment Linux Final
* @date 12/14/2020
* @credits
* 
*/

#include "shopprogram.h"
#include "calculator.hpp" //Library
#include <string.h>
#include <vector>
#include <algorithm>

//Get necessary text files
void ShopProgram::openTextFiles()
{
	//Variables
	string fileNameReverse, fileCheck;

	//Get Daily File
	cout << "What's the name of the file that has your daily orders? (txt files only): " << endl;
	getline(cin, dailyFileName);
	cout << endl;

	//Get Final File
	cout << "What's the name of the file that has all your past orders? (txt files only): " << endl;
	getline(cin, finalFileName);

	//Check if daily filename includes .txt
	//Reverse File Name
	fileNameReverse = dailyFileName;
	reverse(fileNameReverse.begin(), fileNameReverse.end());

	//Check last four (first four) characters
	for (int i = 0; i < 4; i++)
	{
		fileCheck += fileNameReverse.at(i);
	}

	//Add .txt ending if not already added
	if (fileCheck != "txt.")
	{
		dailyFileName += ".txt";
	}

	//Reset Variables
	fileNameReverse = "";
	fileCheck = "";

	//Check if total filename includes .txt
	//Reverse File Name
	fileNameReverse = finalFileName;
	reverse(fileNameReverse.begin(), fileNameReverse.end());

	//Check last four (first four) characters
	for (int i = 0; i < 4; i++)
	{
		fileCheck += fileNameReverse.at(i);
	}

	//Add .txt ending if not already added
	if (fileCheck != "txt.")
	{
		finalFileName += ".txt";
	}

	//Open Files
	dailyFile.open(dailyFileName);
	finalFile.open(finalFileName, std::ios::app);
}

//Check to make sure files exist
bool ShopProgram::checkFilesExist()
{
	//Variables
	bool dailyFileExists, finalFileExists, fileExists;

	//Check Files
	if (dailyFile.is_open())
	{
		dailyFileExists = true;
	}
	else
	{
		cout << "ERROR: " << dailyFileName << " DOESN'T EXIST. PLEASE RE-ENTER FILE NAMES." << endl;
		dailyFileExists = false;
	}

	if (finalFile.is_open())
	{
		finalFileExists = true;
	}
	else
	{
		cout << "ERROR: " << finalFileName << " DOESN'T EXIST. PLEASE RE-ENTER FILE NAMES." << endl;
		finalFileExists = false;
	}

	if (!finalFileExists || !dailyFileExists)
	{
		fileExists = false;
	}
	else
	{
		fileExists = true;
	}

	//Return 
	return fileExists;
}

//Store info from daily file
void ShopProgram::readDailyFile()
{
	//Variables
	char temp, trash;
	string tempStringHolder;
	float tempCostHolder;
	int value = 0; //Starting Value
	bool check = false;

	//Mark Beginning of Daily File Reading
	cout << dailyFileName << " being read..." << endl;

	//Read Daily File
	while (!dailyFile.eof()) //Keep going until it gets to the end of the file
	{
		dailyFile.get(temp);

		//Check for Variable Divider
		if (temp != '|')
		{
			tempStringHolder += temp;
		}
		else //Once Reached End of Section
		{
			switch (value) //Add Value to Proper Variable
			{
			case 0: //Customers Name
				dailyCustomerName.push_back(tempStringHolder);
				value = 1; //Next Value is Customer Order
				tempStringHolder = ""; //Reset Temp Variable
				break;
			case 1: //Customers Order
				dailyOrder.push_back(tempStringHolder);
				value = 2; //Next Value is Customer Cost
				tempStringHolder = ""; //Reset Temp Variable
			case 2:
				//Get Customer Cost
				dailyFile >> tempCostHolder;
				dailyOrderCost.push_back(tempCostHolder);
				value = 0; //Restart at New Line w/ Customer Name
				dailyFile.get(trash); //Get Rid of New Line
				break;
			default:
				cout << "ERROR: OUT OF BOUNDS - readDailyFile()" << endl;
			}
		}
	}

	//Get Rid of Extra Name
	//dailyCustomerName.erase(dailyCustomerName.end());

	//Mark Ending of Daily File Reading
	cout << dailyFileName << " read" << endl;
}

//Calculate profit - using library
void ShopProgram::calculations()
{
	//Variables
	int dailyOrderCostsTotal, dailyFileProfit;
	int tempValue = 0;
	string dailyOrderCostsTotalMath = "0", dailyFileProfitMath = ""; //Used for calculator library

	//Get daily file production cost (Cost to make the orders in the daily file)
	cout << "What were your production costs for the time period of the daily file? " << endl;
	cin >> productionCosts;
	cout << endl;
	
	cout << "Calculating..." << endl;
	cout << endl;

	//Get all daily file costs
	for (int i = 0; i < dailyOrderCost.size(); i++)
	{
		tempValue = dailyOrderCost.at(i);
		dailyOrderCostsTotalMath += " + " + to_string(tempValue);
	}

	//Add all daily file costs
	originalTotalProfit = calculator::eval<int>(dailyOrderCostsTotalMath);
	cout << "Daily File Revenue: $" << originalTotalProfit << endl;

	//Calculate daily file profit
	dailyFileProfitMath = to_string(originalTotalProfit) + " - " + to_string(productionCosts);
	finalProfit = calculator::eval<int>(dailyFileProfitMath);
	cout << "Daily File Profit: $" << finalProfit << endl;
	cout << endl;

	cout << "Calculations Complete." << endl;
}

//Save info in final file & empty daily file
void ShopProgram::saveFile()
{
	//Variables
	string dateBegin, dateEnd;

	//Get date range
	cout << "Please enter the starting date and ending date of the information stored in the file." << endl;
	cout << "What is the start date? (MM/DD/YYYY)" << endl;
	getline(cin, dateBegin); //This trash line
	getline(cin, dateBegin);
	cout << endl;

	cout << "What is the end date? (MM/DD/YYYY)" << endl;
	getline(cin, dateEnd);

	//Store info in text file
	finalFile << dateBegin << " - " << dateEnd << endl;
	finalFile << "Production Costs: $" << productionCosts << endl;
	finalFile << "Revenue: $" << originalTotalProfit << endl;
	finalFile << "Profit: $" << finalProfit << endl;
	finalFile << endl; //Skip line for next time

	//Close Files
	dailyFile.close();
	finalFile.close();
}

//Mainly for Debugging
void ShopProgram::printDailyFileInfo()
{
	for (int i = 0; i < dailyOrder.size(); i++)
	{
		cout << dailyCustomerName.at(i) << "-" << dailyOrder.at(i) << ": $" << dailyOrderCost.at(i) << endl;
	}
}

//Get size of vectors
int ShopProgram::getVectorSize()
{
	return dailyCustomerName.size();
}

//Sort in alphabetical order
void ShopProgram::merge(int beg, int mid, int end)
{
	int left = mid - beg + 1;
	int right = end - mid;

	vector<string> nameLeftVector;
	vector<string> nameRightVector;
	vector<string> orderLeftVector;
	vector<string> orderRightVector;
	vector<int> costLeftVector;
	vector<int> costRightVector;

	for (int i = 0; i < getVectorSize(); i++)
	{
		nameLeftVector.push_back("Temp");
		nameRightVector.push_back("Temp");
		orderLeftVector.push_back("Temp");
		orderRightVector.push_back("Temp");
		costLeftVector.push_back(-1);
		costRightVector.push_back(-1);
	}

	for (int i = 0; i < left; i++)
	{
		nameLeftVector.at(i) = dailyCustomerName.at(beg + i);
		orderLeftVector.at(i) = dailyOrder.at(beg + i);
		costLeftVector.at(i) = dailyOrderCost.at(beg + i);
	}

	for (int i = 0; i < right; i ++)
	{
		nameRightVector.at(i) = dailyCustomerName.at(mid + 1 + i);
		orderRightVector.at(i) = dailyOrder.at(mid + 1 + i);
		costRightVector.at(i) = dailyOrderCost.at(mid + 1 + i);
	}

	int i = 0, j = 0;
	int k = beg;
	while (i < left && j < right)
	{
		if (nameLeftVector.at(i) <= nameRightVector.at(j))
		{
			dailyCustomerName.at(k) = nameLeftVector.at(i);
			dailyOrder.at(k) = orderLeftVector.at(i);
			dailyOrderCost.at(k) = costLeftVector.at(i);
			i++;
		}
		else
		{
			dailyCustomerName.at(k) = nameRightVector.at(j);
			dailyOrder.at(k) = orderRightVector.at(j);
			dailyOrderCost.at(k) = costRightVector.at(j);
			j++;
		}
		k++;
	}

	while (i < left)
	{
		dailyCustomerName.at(k) = nameLeftVector.at(i);
		dailyOrder.at(k) = orderLeftVector.at(i);
		dailyOrderCost.at(k) = costLeftVector.at(i);
		i++;
		k++;
	}

	while (j < right)
	{
		dailyCustomerName.at(k) = nameRightVector.at(j);
		dailyOrder.at(k) = orderRightVector.at(j);
		dailyOrderCost.at(k) = costRightVector.at(j);
		j++;
		k++;
	}
}

void ShopProgram::mergeSort(int beg, int end)
{
	cout << "Sorting Daily File Info..." << endl;

	if (beg < end)
	{
		int mid = (beg + end) / 2;
		mergeSort(beg, mid);
		mergeSort(mid + 1, end);
		merge(beg, mid, end);
	}

	cout << "Daily File Info Sorted." << endl;
}