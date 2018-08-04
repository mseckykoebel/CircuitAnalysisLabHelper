//Authors: Jacob O'Connor, Jaime De La Vega, Evan Supple, Mason Secky-Koebel
//Date: 12/08/16
//Ttile: Circuit Analysis Program
/*Description: This program is designed to aid in the completion of a circuit analysis lab. The program will
accept a user input of input voltage used in the tests, the critical frequency of the apparatus and the
capacitor value for the apparatus (if no value is specified a default 0.01 micro farads will be the assigned
value). For each individual test run by the user the program will also accept the values of output voltage
and tested frequency for the individual test. After collecting data from the user the program will solve for
resistance of the apparatus, experimental decibel gain and experimental decibal gain. Lastly the program will
display the values of the tested frequency, input voltage, output voltage, theoretical decibel gain and
experimental decibel gain in a neat table that will also be exported to a save file named doublearray.txt.*/

#include<iostream>
#include<iomanip>
#include<cmath>
#include<fstream>

using namespace std;

//Below are the globalized variables of the program.
double voltout; //Stores a user input value for the experimental output voltage. Globalized.
double testfreq; //Stores a user input value for tested frequency. Globalized.
double arr[40][5] = { { 0 } }; //A double array for the data used in the program. initialized at 0. Globalized.
const double PI = 3.1415926; //Stores a constant value for the irrational number pi to 8 digits. Globalized.

struct data //A struct for storing the values of critical frequency, capacitance, and the resistor strength.
{
	double critfreq; //Stores the critical frequency value.
	double capacitor = 0.01; //Stores the capacitor value, initialized at a default .01 value.
	double resistor; //Stores the calculated resistor value.
}theorName;

//Below are the declarations for the user defined functions.
void intro(); //Introduces the program to the user.
void expAvg(double, int); //Calculates the experimental decibel gain for each test.
void requestFandV(int); //Requests values for tested frequency and output voltage from the user.
void theorAvg(int); //Calculates the theoretical decibel gain.
void fillArray(int); //Creates a table from the info, and creates a table in a file on the desktop.

int main()
{
	//Below are the declarations for the int main function.
	double voltin; //Stores the user input value for input voltage.
	int colRows; //Stores a user input value for the number of data points.
	int i; //Used as an incremented integer in a for loop.
	char response;

	intro(); //A call to function void intro.

	//Below is n output statement asking for the number of data points to be processed.
	cout << endl << " Please enter the number of rows that the data table will have. This number \n"
		<< " cannot exceed 40: ";
	cin >> colRows;

	cout << endl;

	//If the user enters too many rows, the program will terminate.
	if (colRows > 40)
	{
		cout << " The row number entered is greater than 40. Program will terminate.";
		cout << endl << endl;
		return -1;
	}

	cout << " Please enter the voltage input. This will remain the same: ";
	cin >> voltin;
	cout << endl;

	cout << " Would you like to use a default value of 0.01 micro-farads for your\n apparatus? Please enter"
		<< " \'y\' for yes or \'n\' for no:   ";
	cin >> response;

	//Below is an if statement for if the user has entered anything other than y for char response.
	if (response == 'n' || response == 'N')
	{
		cout << endl << " Please enter the capacitor value you would like to use\n in micro-farads: ";
		cin >> theorName.capacitor; //Inputs new capacitor value into the struct replacing the default value.
	}

	cout << endl;

	//Enter the critical frequency.
	cout << " Please enter the critical frequency: ";
	//Stored in the struct
	cin >> theorName.critfreq;
	cout << endl;
	//Value for the resistor is calculated
	theorName.resistor = (1 / (2 * PI * theorName.capacitor * theorName.critfreq));

	//Call to function that gathers the many frequencies, and the corresponding voltage out.
	requestFandV(colRows);

	cout << endl << endl << endl;

	//For loop to call to the function to gather the experimental and theoretical average.
	for (i = 0; i < colRows; i++)
	{
		expAvg(voltin, colRows);
		theorAvg(colRows);
	}

	//Call to function that prints the table data, and outputs the data to a file
	fillArray(colRows);

	return 0;
}

//Author: Mason Secky-Koebel, Jacob O'Connor
//Created: December 7, 2016
//Intro: This function requests the frequency values and the corresponding exp voltage out (peak
//-to-peak).
void requestFandV(int count)
{
	//Varaibles used to only process the array.
	int i;
	double frequency;

	for (i = 0; i < count; i++)
	{
		cout << " Please enter the frequency of data point " << i + 1 << ": ";
		cin >> frequency;
		arr[i][0] = frequency; //Frequency info stored in the array. 1st column, row changes.
		cout << endl;
		cout << " Please enter the peak-to-peak voltage output found at this frequency: ";
		cin >> voltout;
		arr[i][2] = voltout; //Vout info stored in the array. 3rd column, row changes.
		cout << endl;
	}
}

//Author: Mason Secky-Koebel
//Created: December 6, 2016
//Intro: Function that calculates the theoretical average given the frequency and the capaciter value.
//The capaciter value is located in the struct, and the resistor value is located in the struct.
//The value for the theoretical avergae is then stored and processed in the array.
void theorAvg(int count)
{
	double theorAvg;
	double num, num2, num3, num4;
	int i;

	//For loop stores the data for the theoretical average in the array, 4th column, the
	//row changes from 0 to the count value (row value).
	for (i = 0; i < count; i++)
	{
		num4 = (2 * PI * arr[i][0] * theorName.resistor * theorName.capacitor);
		num3 = pow(num4, 2);
		num2 = sqrt(1 + num3);
		num = (1 / num2);
		theorAvg = 20 * log10(num);
		arr[i][3] = theorAvg;
	}
}

//Author: Mason Secky-Koebel
//Created: December 6, 2016
//Intro: Function that calculates the experimental average from the voltage input and the
//voltage output given by the user. The value is stored and processed in the array.
void expAvg(double VIN, int count)
{
	double expAvg;
	double num;
	int i;

	//For loop stores the data for the experimental average in the array, 3rd column,
	//the row changes from 0 to the count value (row value).
	for (i = 0; i < count; i++)
	{
		num = (arr[i][2] / VIN);
		expAvg = 20 * log10(num);
		arr[i][4] = expAvg; //expavg info stored in the array. 5th column, row changes.
		arr[i][1] = VIN;
	}
}

// Author: Evan Supple
// Created: December 06, 2016
// Intro: This is a function to display a message to the user about this program.
void intro()
{
	cout << " Welcome to the Circuit Analysis Lab Data Collector and Organizer " << endl;
	cout << " This program is intended to help you with your lab on passive filters.  " << endl;
	cout << endl;
	cout << " You can enter your values for your critical frequency, resistance" << endl;
	cout << " and capacitance(in micro-farad). If you wish the deafult value of" << endl;
	cout << " .01 micro-farads can also be used.  " << endl;
	cout << endl;
	cout << " During the lab you will have to test multiple frequency values " << endl;
	cout << " above and below your critical frequency. You must specify how  " << endl;
	cout << " many  of the values you are going to test. You must also specify" << endl;

	cout << " a constant peak to peak input voltage value. Based on your " << endl;
	cout << " experimental values the gain of the filter will be calculated, " << endl;
	cout << " while the theoretical gain will be calculated from the intial" << endl;
	cout << " condintions you entered. " << endl;
	cout << endl;
	cout << " Finally all the values inputted and calculated  " << endl;
	cout << " will be displayed in concise table for further analysis " << endl;
}

// Author: Jaime De La Vega
// Created: December 06, 2016
// Intro: Function that prints the data in the array both on the console, and to an
//output file for further user manipulation.
void fillArray(int count)
{
	//Defines an output stream for the data file
	ofstream dataOut;

	//Creating and opening the output file
	dataOut.open("Circuit Data.txt");

	//This for loop is used to display headings
	for (int i = 0; i < 1; i++)
	{
		cout << "f(Hz)" << "\t\tVs p-p" << "\t\tExp Vo p-p" << "\tTheor Av(dB)" << "\tExp Av(dB)";
		dataOut << "f(Hz)" << "\t\tVs p-p" << "\t\tExp Vo p-p" << "\tTheor Av(dB)" << "\tExp Av(dB)";
	}
	cout << "\n" << endl;
	dataOut << "\n" << endl;

	//This nested for loop is used to display the elements in the array
	const char separator = ' ';
	const int nameWidth = 6;
	const int numWidth = 8;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << left << setw(nameWidth) << setfill(separator) <<
				setprecision(5) << arr[i][j] << "\t\t";
			dataOut << left << setw(nameWidth) << setfill(separator) <<
				setprecision(5) << arr[i][j] << "\t\t";
		}
		cout << "\n";
		dataOut << "\n";
	}

	//Close the file
	dataOut.close();
}
