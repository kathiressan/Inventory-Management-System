#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include "StoreItem.h"

using namespace std;


string StoreItem::space2underscore(string &a){

	for(int i = 0; i < a.length(); i++){
        if(a[i] == ' ')
            a[i] = '_';
    }

    return a;
}

int StoreItem::CheckYear(int &a){

	StoreItem Store;
	Store.CheckInteger(a);

	int CurrentY = 2018, DummyLooping = 0;
	while( DummyLooping >= 0 ){
		if( a > CurrentY ){
			cout << "Month is not valid. \n";
			cout << "Enter Month Introduced: ";
			cin >> a;
		}

		else {
			break;
		}
		DummyLooping = DummyLooping + 1;
	}
	return a;
}

double StoreItem::CheckDouble(double &a){
	int DummyLoop = 0;
	while(DummyLoop < 10){

		if(cin.fail()){
			cin.clear();
			cin.ignore();
			cout << "Re-enter your Data: ";
			cin >> a;
		}

		else{
			break;
		}
	}

	return a;
}

int StoreItem::CheckDay(int &a){

	StoreItem Store;
	Store.CheckInteger(a);
	int DummyLooping = 0;
	int MaxDay = 31;
	while( DummyLooping >= 0 ){
		if( a > MaxDay ){
			cout << "Day is not valid. \n";
			cout << "Enter Day Introduced: ";
			cin >> a;
		} else {
			break;
		}
		DummyLooping = DummyLooping + 1;
	}

	return a;
}

int StoreItem::CheckMonth(int &a){

	StoreItem Store;
	Store.CheckInteger(a);
	int MaxMonth = 12, DummyLooping = 0;
	while( DummyLooping >= 0 ){
		if( a > MaxMonth ){
			cout << "Month is not valid. \n";
			cout << "Enter Month Introduced: ";
			cin >> a;
		} else {
			break;
		}
		DummyLooping = DummyLooping + 1;
	}

	return a;
}

int StoreItem::CheckInteger(int &a){

	int DummyLoop = 0;
	while(DummyLoop < 10){
		if(cin.fail()){
			cin.clear();
			cin.ignore();
			cout << " Please re-enter valid input: ";
			cin >> a;
		}

		else{
			break;
		}
	}

	return a;
}

    void StoreItem::Storing(){

	StoreItem Store;

    int a = 0;

    string item_Name;
    string Category;
    string item_Description;
    string Manufacturer;
    int year;
    int month;
    int day;
    string item_ID;
    int units_InStore;
    int units_Sold;
    double selling_Price;
    double cost_Price;

    system("CLS");
        ifstream outfile("database.txt", ios::app);

		vector<int> y, m, d, ustore, usold;
        vector<string> userID, userName, des, cat, manu;
		vector<double> cp, sp;

        string New;

        while(outfile >> item_ID >> item_Name >> item_Description >> Category >> Manufacturer >> selling_Price >> cost_Price >> units_InStore >> units_Sold >> year >> month >> day){
                userID.push_back(item_ID);
                userName.push_back(item_Name);
                des.push_back(item_Description);
                cat.push_back(Category);
                manu.push_back(Manufacturer);
                sp.push_back(selling_Price);
                cp.push_back(cost_Price);
                ustore.push_back(units_InStore);
                usold.push_back(units_Sold);
                y.push_back(year);
                m.push_back(month);
                d.push_back(day);
                a = a + 1;
		}

        outfile.close();

		cout << "Enter the data fields below" << endl;
        int counter = 0;
        while (counter == 0) {
            int AlreadyUsed = 0;
            cout << "Item ID: ";
            cin >> item_ID;

            for (int x = 0; x < a; ++x) {
                if (userID[x] == item_ID) {
                    AlreadyUsed = 1;
                }
            }
            if (AlreadyUsed == 1) {
                cout << "That ID has already been used. Please enter another ID." << endl;
            } else if (AlreadyUsed == 0){
                counter = 1;
            }

        }

		cin.ignore(100, '\n');

		cout << "Item Name: ";
		getline(cin, item_Name);
		Store.space2underscore(item_Name);

        cout << "Item Description: ";
		getline(cin,item_Description);
		Store.space2underscore(item_Description);

		cout << "Category: ";
		getline(cin, Category);
		Store.space2underscore(Category);

		cout << "Manufacturer: ";
		getline(cin, Manufacturer);
		Store.space2underscore(Manufacturer);

		cout << "Selling Price: ";
		cin >> selling_Price;
		Store.CheckDouble(selling_Price);

        cin.ignore(100, '\n');

		cout << "Cost Price: ";
		cin >> cost_Price;
		Store.CheckDouble(cost_Price);

		cout << "Units in Store: ";
		cin >> units_InStore;
		Store.CheckInteger(units_InStore);

		cout << "Units Sold: ";
		cin >> units_Sold;
		Store.CheckInteger(units_Sold);

		cout << "Year of Date First Introduced: ";
		cin >> year;
		Store.CheckYear(year);

		cout << "Month of Date First Introduced: ";
		cin >> month;
		Store.CheckMonth(month);

		cout << "Day of Date First Introduced: ";
		cin >> day;
		Store.CheckDay(day);

		ofstream infile ("database.txt", ios::app);
		if (infile.is_open()){
		    infile << item_ID << ' ' << item_Name << ' ' << item_Description << ' '
		    << Category << ' ' << Manufacturer << ' ' << selling_Price << ' ' << cost_Price << ' ' << units_InStore << ' '
		    << units_Sold << ' ' << year << ' ' << month << ' ' << day << ' '<< endl;
		    infile.close();
		}


}
