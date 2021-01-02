#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <fstream>
#include "StoreItem.h"
#include "StoreItem.cpp"

using namespace std;

string item_ID, item_Name, item_Description, Category, Manufacturer;
int units_InStore, units_Sold;
int year, month, day;
int response;
double selling_Price, cost_Price;

void mainMenu();
void createRecord();
void updateDataRecord();
void showDataRecord();
void show_Data_Field();
void sort_Data_Field();
void deleteDataRecord();
void deleteRecord();
void BackToMain();

void BackToMain() {
    int action;
    cout << "Press 1 to change other data fields or Press 2 to go back to the Main Menu";
    cin >>  action;
    if (action == 1){
        updateDataRecord();
    }else if (action == 2) {
        mainMenu();
    }
}

// createRecord Function gets user input for data fields to create a new record in the database

void createRecord()
	{
        StoreItem objectStoring;
        objectStoring.Storing();

	    cout << "Press 1 to add another record or type 2 to go back to the main screen: " << endl;
		cin >> response;

	    if (response == 1) {
			createRecord();
		} else if (response == 2) {
			mainMenu();
		}


	}

// updateDataRecord Function user can update a data field of a record

void updateDataRecord(){

		StoreItem Store;

        system("CLS");
        string ID_Search;
        int num;
		cout << "Enter the Item ID " << endl;
		cin >> ID_Search;

        ifstream outfile("database.txt", ios::app);

		int NewInt;
		double NewDouble;
        string NewString;

	vector<int> y, m, d, ustore, usold;
    vector<string> userID, userName, userDes, cat, manu;
	vector<double> cp, sp;

    int g = 0;

    while(outfile >> item_ID >> item_Name >> item_Description >> Category >> Manufacturer >> selling_Price >> cost_Price >> units_InStore >> units_Sold >> year >> month >> day){
        userID.push_back(item_ID);
        userName.push_back(item_Name);
        userDes.push_back(item_Description);
        cat.push_back(Category);
        manu.push_back(Manufacturer);
        sp.push_back(selling_Price);
        cp.push_back(cost_Price);
        ustore.push_back(units_InStore);
        usold.push_back(units_Sold);
        y.push_back(year);
        m.push_back(month);
        d.push_back(day);
        g = g + 1;
	}
        outfile.close();
        int Exist_ID = 0;
        for (int k = 0; k < g; ++k) {
            if (static_cast<string>(userID[k]) == static_cast<string>(ID_Search)) {
                Exist_ID = 1;
            }
        }

        if (Exist_ID == 0) {
            cout << "The program was unable to find that ID in the database. Press Enter to go back to the main menu.";
            cin.ignore();
            cin.get();
            mainMenu();
        }

        cout << endl << "Enter the number for the data field you would like to update" << endl
		<< "1. Item ID" << endl << "2. Item Name" << endl << "3. Item Description" << endl
		<< "4. Category" << endl << "5. Manufacturer" << endl
		<< "6. Selling Price" << endl << "7. Cost Price" << endl
		<< "8. Units in Store" << endl << "9. Units Sold" << endl
		<< "10. Year of Date First Introduced" << endl << "11. Month of Date First Introduced" << endl
		<< "12. Day of Date First Introduced" << endl;
		cin >> num;


        for (int k = 0; k < g; ++k) {
            if (static_cast<string>(userID[k]) == static_cast<string>(ID_Search)) {

                if (num == 1) {
                    cout << "Enter the New ID" << endl;
                    cin >> NewInt;
                    userID[k] = NewInt;
                } else if (num == 2) {
                    cin.ignore(100, '\n');
                    cout << "Enter the New Item Name" << endl;
                    getline(cin, NewString);
                    userName[k] = Store.space2underscore(NewString);

                } else if (num == 3) {
                    cin.ignore(100, '\n');
                    cout << "Enter the New Item Description" << endl;
                    getline(cin, NewString);
                    userDes[k] = Store.space2underscore(NewString);

                } else if (num == 4) {
                    cin.ignore(100, '\n');
                    cout << "Enter the New Category for the Item" << endl;
                    getline(cin, NewString);
                    cat[k] = Store.space2underscore(NewString);

                } else if (num == 5) {
                    cin.ignore(100, '\n');
                    cout << "Enter the New Manufacturer for the Item" << endl;
                    getline(cin, NewString);
                    manu[k] = Store.space2underscore(NewString);

                } else if (num == 6) {
                    cout << "Enter the New Selling Price of the Item" << endl;
                    cin >> NewDouble;
					Store.CheckDouble(NewDouble);
                    sp[k] = NewDouble;
                } else if (num == 7) {
                    cout << "Enter the New Cost Price of the Item" << endl;
                    cin >> NewDouble;
					Store.CheckDouble(NewDouble);
                    cp[k] = NewDouble;

                } else if (num == 8) {
                    cout << "Enter the New Number of Units in Store" << endl;
                    cin >> NewInt;
                    ustore[k] = NewInt;

                } else if (num == 9) {
                    cout << "Enter the New Number of Units Sold" << endl;
                    cin >> NewInt;
                    usold[k] = NewInt;

                } else if (num == 10) {
                    cout << "Enter the New Year of the Date the Item was First Introduced" << endl;
                    cin >> NewInt;
					Store.CheckYear(NewInt);
                    y[k] = NewInt;

                } else if (num == 11) {
                    cout << "Enter the New Month of the date the Item was First introduced" << endl;
                    cin >> NewInt;
					Store.CheckMonth(NewInt);
                    m[k] = NewInt;

                } else if (num == 12) {
                    cout << "Enter the New Day of the date the Item was First Introduced" << endl;
                    cin >> NewInt;
					Store.CheckDay(NewInt);
                    d[k] = NewInt;

                }
            }
        }

        ofstream ofs;
        ofs.open("database.txt", ofstream::trunc);
        ofs.close();

        ofstream redo ("database.txt", ios::app);
		if (redo.is_open())
		{

		 for (int z = 0; z < g; ++z) {
            redo << userID[z] << ' ' << userName[z] << ' ' << userDes[z] << ' '
		    << cat[z] << ' ' << manu[z] << ' ' << sp[z] << ' ' << cp[z] << ' ' << ustore[z] << ' '
		    << usold[z] << ' ' << y[z] << ' ' << m[z] << ' ' << d[z] << ' '<< endl;
		 }

		}
		redo.close();

		int index;
		cout << "Press 1 to update other data fields or Press 2 to go back to the Main Menu" << endl;
		cin >> index;
		if (index == 1){
		    updateDataRecord();

		} else if (index == 2) {
		    mainMenu();
		}
}

// deleteDataRecord Function user can delete a specified data field. -1 is the value for deleted data field

void deleteDataRecord()
{
    system("CLS");
    string ID_Search;
    int num;
    cout << "Enter the Item ID " << endl;
    cin >> ID_Search;
    ifstream outfile("database.txt", ios::app);

	int DeleteInteger = -1;
	string DeleteString = "-1";
	double DeleteDouble = -1.0;


		vector<int> y, m, d, ustore, usold;
        vector<string> userID, userName, userDes, cat, manu;
		vector<double> cp, sp;

        int g = 0;

        while(outfile >> item_ID >> item_Name >> item_Description >> Category >> Manufacturer >> selling_Price >> cost_Price >> units_InStore >> units_Sold >> year >> month >> day){
                userID.push_back(item_ID);
                userName.push_back(item_Name);
                userDes.push_back(item_Description);
                cat.push_back(Category);
                manu.push_back(Manufacturer);
                sp.push_back(selling_Price);
                cp.push_back(cost_Price);
                ustore.push_back(units_InStore);
                usold.push_back(units_Sold);
                y.push_back(year);
                m.push_back(month);
                d.push_back(day);
                g = g + 1;
		}

        outfile.close();
        int Exist_ID = 0;
        for (int k = 0; k < g; ++k) {
            if (static_cast<string>(userID[k]) == static_cast<string>(ID_Search)) {
                Exist_ID = 1;
            }
        }

        if (Exist_ID == 0) {
            cout << "The program was unable to find that ID in the database. Press Enter to go back to the Main Menu.";
            cin.ignore();
            cin.get();
            mainMenu();
        }

        cout << endl << "Enter the number for the data field you would like to delete" << endl
        << endl << "1. Item Name" << endl << "2. Item Description" << endl
        << "3. Category" << endl << "4. Manufacturer" << endl
        << "5. Selling Price" << endl << "6. Cost Price" << endl
        << "7. Units in Store" << endl << "8. Units Sold" << endl
        << "9. Year of Date First Introduced" << endl << "10. Month of Date First Introduced" << endl
        << "11. Day of Date First Introduced" << endl;
        cin >> num;

        for (int k = 0; k < g; ++k) {
            if (static_cast<string>(userID[k]) == static_cast<string>(ID_Search)) {

                if (num == 1) {
                    userName[k] = DeleteString;

                } else if (num == 2) {
                    userDes[k] = DeleteString;

                } else if (num == 3) {
                    cat[k] = DeleteString;

                } else if (num == 4) {
                    manu[k] = DeleteString;

                } else if (num == 5) {
                    sp[k] = DeleteDouble;

                } else if (num == 6) {
                    cp[k] = DeleteDouble;

                } else if (num == 7) {
                    ustore[k] = DeleteInteger;

                } else if (num == 8) {
                    usold[k] = DeleteInteger;

                } else if (num == 9) {
                    y[k] = DeleteInteger;

                } else if (num == 10) {
                    m[k] = DeleteInteger;

                } else if (num == 11) {
                    d[k] = DeleteInteger;

                }
            }
        }

        ofstream ofs;
        ofs.open("database.txt", ofstream::trunc);
        ofs.close();

        ofstream redo ("database.txt", ios::app);
		if (redo.is_open())
		{

		 for (int k = 0; k < g; ++k) {
            redo << userID[k] << ' ' << userName[k] << ' ' << userDes[k] << ' '
		    << cat[k] << ' ' << manu[k] << ' ' << sp[k] << ' ' << cp[k] << ' ' << ustore[k] << ' '
		    << usold[k] << ' ' << y[k] << ' ' << m[k] << ' ' << d[k] << ' '<< endl;
		 }

		}
		redo.close();

		int index;
		cout << "Press 1 to delete other data fields or 2 to go back to the Main Menu" << endl;
		cin >> index;
		if (index == 1){
		    deleteDataRecord();

		} else if (index == 2) {
		    mainMenu();
		}

}

// Function user can delete an entire record by inputting ID

void deleteRecord() {
    system("CLS");
    ifstream outfile("database.txt", ios::app);


	vector<int> y, m, d, ustore, usold;
    vector<string> userID, userName, userDes, cat, manu;
	vector<double> cp, sp;

    int g = 0;

    while(outfile >> item_ID >> item_Name >> item_Description >> Category >> Manufacturer >> selling_Price >> cost_Price >> units_InStore >> units_Sold >> year >> month >> day){
        userID.push_back(item_ID);
        userName.push_back(item_Name);
        userDes.push_back(item_Description);
        cat.push_back(Category);
        manu.push_back(Manufacturer);
        sp.push_back(selling_Price);
        cp.push_back(cost_Price);
        ustore.push_back(units_InStore);
        usold.push_back(units_Sold);
        y.push_back(year);
        m.push_back(month);
        d.push_back(day);
        g = g + 1;
	}

    outfile.close();

    string ID_To_Delete;
    int element_To_Delete;
    cout << "Enter the Item ID you want to delete: ";
    cin >> ID_To_Delete;

    for (int k = 0; k < g; ++k) {
        if (userID[k] == ID_To_Delete) {
            element_To_Delete = k;
        }
    }

    userID.erase(userID.begin() + element_To_Delete);
    userName.erase(userName.begin() + element_To_Delete);
    userDes.erase(userDes.begin() + element_To_Delete);
    cat.erase(cat.begin() + element_To_Delete);
    manu.erase(manu.begin() + element_To_Delete);
    sp.erase(sp.begin() + element_To_Delete);
    cp.erase(cp.begin() + element_To_Delete);
    ustore.erase(ustore.begin() + element_To_Delete);
    usold.erase(usold.begin() + element_To_Delete);
    y.erase(y.begin() + element_To_Delete);
    m.erase(m.begin() + element_To_Delete);
    d.erase(d.begin() + element_To_Delete);

    ofstream ofs;
    ofs.open("database.txt", ofstream::trunc);
    ofs.close();

    ofstream redo ("database.txt", ios::app);
    if (redo.is_open())
    {

     for (int k = 0; k < g - 1; ++k) {
        redo << userID[k] << ' ' << userName[k] << ' ' << userDes[k] << ' '
        << cat[k] << ' ' << manu[k] << ' ' << sp[k] << ' ' << cp[k] << ' ' << ustore[k] << ' '
        << usold[k] << ' ' << y[k] << ' ' << m[k] << ' ' << d[k] << ' '<< endl;
     }

    }
    redo.close();

    cout << "The record has successfully been deleted" << endl;

    cout << endl << "Press Enter to go back to the Main Menu." << endl;
    cin.ignore();
    cin.get();
    mainMenu();


}

// Function user can view data fields in ascending or descending order (Sorting)

void sort_Data_Field() {
	StoreItem Store;
    system("CLS");
    ifstream outfile("database.txt", ios::app);


	vector<int> y, m, d, ustore, usold;
    vector<string> userID, userName, userDes, cat, manu;
	vector<double> cp, sp;

    int g = 0;

    while(outfile >> item_ID >> item_Name >> item_Description >> Category >> Manufacturer >> selling_Price >> cost_Price >> units_InStore >> units_Sold >> year >> month >> day){
        userID.push_back(item_ID);
        userName.push_back(item_Name);
        userDes.push_back(item_Description);
        cat.push_back(Category);
        manu.push_back(Manufacturer);
        sp.push_back(selling_Price);
        cp.push_back(cost_Price);
        ustore.push_back(units_InStore);
        usold.push_back(units_Sold);
        y.push_back(year);
        m.push_back(month);
        d.push_back(day);
        g = g + 1;
	}

    outfile.close();

    int response;
    int choice_Sorting;
    cout << "Select a data field to view all the data" << endl;
    cout << endl
    << "1. Item ID" << endl << "2. Item Name" << endl << "3. Item Description" << endl
    << "4. Category" << endl << "5. Manufacturer" << endl
    << "6. Selling Price" << endl << "7. Cost Price" << endl
    << "8. Units in Store" << endl << "9. Units Sold" << endl
    << "10. Year of Date First Introduced" << endl << "11. Month of Date First Introduced" << endl
    << "12. Day of Date First Introduced" << endl << "13. Go back to the main menu" << endl;

    int index = 0;
    while (index == 0) {
        cin >> response;
        if (response <= 13) {
            index = 1;
        } else if (response > 13) {
            cout << "Enter the valid selection" << endl;
        }
    }

    if (response == 13) {
        mainMenu();
    }

    cout << endl;
    cout << "Please select the sorting order that you want to view the data" << endl;
    cout << "1. Ascending Order" << endl;
    cout << "2. Descending Order" << endl;
    cout << "3. No Specific Order" << endl;

    int counter = 0;
    while (counter == 0) {
        cin >> choice_Sorting;
        if (choice_Sorting <= 3) {
            counter = 1;
        } else if (choice_Sorting > 3) {
            cout << "Enter the valid selections" << endl;
        }
    }

    system("CLS");

    if (response == 1) {
            if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(userID.begin(), userID.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << userID[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(userID.begin(), userID.end());
                reverse(userID.begin(), userID.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << userID[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << userID[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }
    } else if (response == 2) {
        if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(userName.begin(), userName.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(userName[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(userName.begin(), userName.end());
                reverse(userName.begin(), userName.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(userName[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(userName[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }

    } else if (response == 3) {
        if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(userDes.begin(), userDes.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(userDes[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(userDes.begin(), userDes.end());
                reverse(userDes.begin(), userDes.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(userDes[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(userDes[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }

    } else if (response == 4) {
        if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(cat.begin(), cat.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(cat[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(cat.begin(), cat.end());
                reverse(cat.begin(), cat.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(cat[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(cat[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }

    } else if (response == 5) {
        if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(manu.begin(), manu.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(manu[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(manu.begin(), manu.end());
                reverse(manu.begin(), manu.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(manu[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << Store.space2underscore(manu[k]) << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }

    } else if (response == 6) {
        if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(sp.begin(), sp.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << sp[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(sp.begin(), sp.end());
                reverse(sp.begin(), sp.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << sp[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << sp[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }

    } else if (response == 7) {
        if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(cp.begin(), cp.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << cp[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(cp.begin(), cp.end());
                reverse(cp.begin(), cp.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << cp[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << cp[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }

    } else if (response == 8) {
        if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(ustore.begin(), ustore.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << ustore[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(ustore.begin(), ustore.end());
                reverse(ustore.begin(), ustore.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << ustore[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << ustore[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }

    } else if (response == 9) {
        if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(usold.begin(), usold.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << usold[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(usold.begin(), usold.end());
                reverse(usold.begin(), usold.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << usold[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << usold[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }

    } else if (response == 10) {
        if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(y.begin(), y.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << y[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(y.begin(), y.end());
                reverse(y.begin(), y.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << y[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; k++) {
                    cout << counter_Num << ". " << y[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }

    } else if (response == 11) {
        if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(m.begin(), m.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << m[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(m.begin(), m.end());
                reverse(m.begin(), m.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << m[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the sort data field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << m[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }

    } else if (response == 12) {
        if (choice_Sorting == 1) {
                int counter_Num = 1;
                sort(d.begin(), d.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << d[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 2) {
                int counter_Num = 1;
                sort(d.begin(), d.end());
                reverse(d.begin(), d.end());
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << d[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            } else if (choice_Sorting == 3) {
                int counter_Num = 1;
                for (int k = 0; k < g; ++k) {
                    cout << counter_Num << ". " << d[k] << endl;
                    counter_Num++;
                }

                cout << endl << "Press Enter to go back to the Sort Data Field screen." << endl;
                cin.ignore();
                cin.get();
                sort_Data_Field();

            }

    }

}

// showDataRecord Function display the data fields of a record by inputting the ID

void showDataRecord() {
	StoreItem Store;
    system("CLS");
    ifstream outfile("database.txt", ios::app);

	vector<int> y, m, d, ustore, usold;
    vector<string> userID, userName, userDes, cat, manu;
	vector<double> cp, sp;

    int g = 0;

    while(outfile >> item_ID >> item_Name >> item_Description >> Category >> Manufacturer >> selling_Price >> cost_Price >> units_InStore >> units_Sold >> year >> month >> day){
        userID.push_back(item_ID);
        userName.push_back(item_Name);
        userDes.push_back(item_Description);
        cat.push_back(Category);
        manu.push_back(Manufacturer);
        sp.push_back(selling_Price);
        cp.push_back(cost_Price);
        ustore.push_back(units_InStore);
        usold.push_back(units_Sold);
        y.push_back(year);
        m.push_back(month);
        d.push_back(day);
        g = g + 1;
	}

    outfile.close();

    int index = 0;

    cout << "1) Show a record by entering the ID" << endl;
    cout << "2) Find a record with a search condition" << endl;
    cout << "3) Go back to the main menu" << endl;
    int action;
    while (index == 0) {
        cin >> action;
        if (action == 1 || action == 2 || action == 3) {
            index = 1;
        } else {
            cout << "Please enter the valid selection" << endl;
        }
    }

    if (action == 1) {
        system("CLS");
        string ID_Search;
        cout << "Enter the Item ID of the record that you want to see " << endl;
        cin >> ID_Search;
        int Exist_ID = 0;

        for (int k = 0; k < g; ++k) {
            if (static_cast<string>(userID[k]) == static_cast<string>(ID_Search)) {
                system("CLS");
                cout << "Item ID: " << userID[k] << endl;
                cout << "Item Name: " << Store.space2underscore(userName[k]) << endl;
                cout << "Item Description: " << Store.space2underscore(userDes[k]) << endl;
                cout << "Item Category: " << Store.space2underscore(cat[k]) << endl;
                cout << "Item Manufacturer: " << Store.space2underscore(manu[k]) << endl;
                cout << "Selling Price of Item: " << sp[k] << endl;
                cout << "Cost Price of Item: " << cp[k] << endl;
                cout << "Number of Units In Store: " << ustore[k] << endl;
                cout << "Number of Units In Sold: " << usold[k] << endl;
                cout << "Year of Date Manufactured: " << y[k] << endl;
                cout << "Month of Date Manufactured: " << m[k] << endl;
                cout << "Day of Date Manufactured: " << d[k] << endl << endl << endl;
                cout << "Press enter to go back to the show record screen..." << endl;
                cin.ignore();
                cin.get();
                showDataRecord();

                Exist_ID = 1;

            }
        }

        if (Exist_ID == 0) {
            cout << "The program was unable to find the ID in the database. Press Enter to go back to the Show Record screen.";
            cin.ignore();
            cin.get();
            showDataRecord();
        }

    } else if (action == 2) {
        system("CLS");
        int action1;
        cout << "Select the data field to apply the search condition on" << endl << "1. Item Name" << endl
        << "2. Category" << endl << "3. Manufacturer" << endl
        << "4. Selling Price" << endl << "5. Cost Price" << endl << "6. Go back" << endl;
        int choice_Action = 0;
        while (choice_Action == 0) {
            cin >> action1;
            if (action1 == 1 || action1 == 2 || action1 == 3 || action1 == 4 || action1 == 5 || action1 == 6) {
                choice_Action = 1;
            } else {
                cout << "Please enter the valid inputs as stated above" << endl;
            }
        }

        if (action1 == 1 || action1 == 2 || action1 == 3) {
            system("CLS");
            int action2;
            int index = 0;
            cout << "1) Full text match" << endl << "2) Sub-string match" << endl;
            while (index == 0) {
                cin >> action2;
                if (action2 == 1 || action2 == 2) {
                    index = 1;
                } else {
                    cout << "Please enter valid input. Press either 1 or 2." << endl;
                }
            }

            if (action2 == 1) {
                system("CLS");
                string text;
                cout << "Enter the text to search" << endl;
                cin.ignore();
                getline(cin, text);
                int search_Full = 0;
                cout << endl << endl;

                if (action1 == 1) {
                    for(int k = 0; k < g; ++k){
                        if (static_cast<string>(userName[k]) == Store.space2underscore(text)) {
                                cout << "Item ID: " << userID[k] << endl;
                                cout << "Item Name: " << Store.space2underscore(userName[k]) << endl;
                                cout << "Item Description: " << Store.space2underscore(userDes[k]) << endl;
                                cout << "Item Category: " << Store.space2underscore(cat[k]) << endl;
                                cout << "Item Manufacturer: " << Store.space2underscore(manu[k]) << endl;
                                cout << "Selling Price of Item: " << sp[k] << endl;
                                cout << "Cost Price of Item: " << cp[k] << endl;
                                cout << "Number of Units In Store: " << ustore[k] << endl;
                                cout << "Number of Units In Sold: " << usold[k] << endl;
                                cout << "Year of Date Manufactured: " << y[k] << endl;
                                cout << "Month of Date Manufactured: " << m[k] << endl;
                                cout << "Day of Date Manufactured: " << d[k] << endl << endl;
                                search_Full = 1;
                            }
                    }
                    if (search_Full == 1) {
                        cout << "Press Enter to go back to the Show Record screen." << endl;
                        cin.get();
                        showDataRecord();
                    } else if (search_Full == 0) {
                        cout << "The program was unable to find the record you are searching for. You can try by using the sub-string search for accurate results." << endl;
                        cout << "Press Enter to go back to the Show Record screen.";
                        cin.get();
                        showDataRecord();
                    }
                } else if (action1 == 2) {
                    int search_Full = 0;
                    for (int k = 0 ; k < g; ++k) {
                            if (static_cast<string>(cat[k]) == Store.space2underscore(text)) {
                                cout << "Item ID: " << userID[k] << endl;
                                cout << "Item Name: " << Store.space2underscore(userName[k]) << endl;
                                cout << "Item Description: " << Store.space2underscore(userDes[k]) << endl;
                                cout << "Item Category: " << Store.space2underscore(cat[k]) << endl;
                                cout << "Item Manufacturer: " << Store.space2underscore(manu[k]) << endl;
                                cout << "Selling Price of Item: " << sp[k] << endl;
                                cout << "Cost Price of Item: " << cp[k] << endl;
                                cout << "Number of Units In Store: " << ustore[k] << endl;
                                cout << "Number of Units In Sold: " << usold[k] << endl;
                                cout << "Year of Date Manufactured: " << y[k] << endl;
                                cout << "Month of Date Manufactured: " << m[k] << endl;
                                cout << "Day of Date Manufactured: " << d[k] << endl << endl;
                                search_Full = 1;
                            }
                    }

                    if (search_Full == 1) {
                        cout << "Press Enter to go back to the Show Record screen..." << endl;
                        cin.get();
                        showDataRecord();
                    } else if (search_Full == 0) {
                        cout << "The program was unable to find the record you are searching for. You can try by using the sub-string search for accurate results." << endl;
                        cout << "Press Enter to go back to the Show Record screen...";
                        cin.get();
                        showDataRecord();
                    }

                } else if (action1 == 3) {
                    int search_Full = 0;
                    for (int k = 0 ; k < g; ++k) {
                            if (static_cast<string>(manu[k]) == Store.space2underscore(text)) {
                                cout << "Item ID: " << userID[k] << endl;
                                cout << "Item Name: " << Store.space2underscore(userName[k]) << endl;
                                cout << "Item Description: " << Store.space2underscore(userDes[k]) << endl;
                                cout << "Item Category: " << Store.space2underscore(cat[k]) << endl;
                                cout << "Item Manufacturer: " << Store.space2underscore(manu[k]) << endl;
                                cout << "Selling Price of Item: " << sp[k] << endl;
                                cout << "Cost Price of Item: " << cp[k] << endl;
                                cout << "Number of Units In Store: " << ustore[k] << endl;
                                cout << "Number of Units In Sold: " << usold[k] << endl;
                                cout << "Year of Date Manufactured: " << y[k] << endl;
                                cout << "Month of Date Manufactured: " << m[k] << endl;
                                cout << "Day of Date Manufactured: " << d[k] << endl << endl;
                                search_Full = 1;
                            }
                    }

                    if (search_Full == 1) {
                        cout << "Press Enter to go back to the Show Record screen." << endl;
                        cin.get();
                        showDataRecord();
                    } else if (search_Full == 0) {
                        cout << "The program was unable to find the record you are looking for. You can try by using the sub-string search for accurate results." << endl;
                        cout << "Press Enter to go back to the Show Record screen.";
                        cin.get();
                        showDataRecord();
                    }

                }
            } else if (action2 == 2) {
                if (action1 == 1) {
                    system("CLS");
                    int search_Partial = 0;
                    string partialText;
                    cout << "Enter the sub-string text to search" << endl;
                    cin.ignore();
                    getline(cin, partialText);
                    transform(partialText.begin(), partialText.end(), partialText.begin(), ::tolower);

                    for (int k = 0; k < g; ++k) {
                            transform(userName[k].begin(), userName[k].end(), userName[k].begin(), ::tolower);
                            int found = userName[k].find(partialText);

                            if(found != -1){
                            transform(userName[k].begin(), userName[k].end(), userName[k].begin(), ::toupper);
                            cout << "Item ID: " << userID[k] << endl;
                            cout << "Item Name: " << Store.space2underscore(userName[k]) << endl;
                            cout << "Item Description: " << Store.space2underscore(userDes[k]) << endl;
                            cout << "Item Category: " << Store.space2underscore(cat[k]) << endl;
                            cout << "Item Manufacturer: " << Store.space2underscore(manu[k]) << endl;
                            cout << "Selling Price of Item: " << sp[k] << endl;
                            cout << "Cost Price of Item: " << cp[k] << endl;
                            cout << "Number of Units In Store: " << ustore[k] << endl;
                            cout << "Number of Units In Sold: " << usold[k] << endl;
                            cout << "Year of Date Manufactured: " << y[k] << endl;
                            cout << "Month of Date Manufactured: " << m[k] << endl;
                            cout << "Day of Date Manufactured: " << d[k] << endl << endl;
                            search_Partial = 1;
                            }
                    }

                    if (search_Partial == 1) {
                        cout << "Press Enter to go back to the Show Record screen." << endl;
                        cin.get();
                        showDataRecord();
                    } else if (search_Partial == 0) {
                        cout << "The program was unable to find the record you are looking for." << endl;
                        cout << "Press Enter to go back to the Show Record screen.";
                        cin.get();
                        showDataRecord();
                    }

                } else if (action1 == 2) {
                    system("CLS");
                    int search_Partial = 0;
                    string partialText;
                    cout << "Enter the sub-string text to search" << endl;
                    cin.ignore();
                    getline(cin, partialText);
                    transform(partialText.begin(), partialText.end(), partialText.begin(), ::tolower);

                    for (int k = 0; k < g; ++k) {
                        transform(cat[k].begin(), cat[k].end(), cat[k].begin(), ::tolower);
                        int found = cat[k].find(partialText);

                        if(found != -1){
                        transform(cat[k].begin(), cat[k].end(), cat[k].begin(), ::toupper);
                        cout << "Item ID: " << userID[k] << endl;
                        cout << "Item Name: " << Store.space2underscore(userName[k]) << endl;
                        cout << "Item Description: " << Store.space2underscore(userDes[k]) << endl;
                        cout << "Item Category: " << Store.space2underscore(cat[k]) << endl;
                        cout << "Item Manufacturer: " << Store.space2underscore(manu[k]) << endl;
                        cout << "Selling Price of Item: " << sp[k] << endl;
                        cout << "Cost Price of Item: " << cp[k] << endl;
                        cout << "Number of Units In Store: " << ustore[k] << endl;
                        cout << "Number of Units In Sold: " << usold[k] << endl;
                        cout << "Year of Date Manufactured: " << y[k] << endl;
                        cout << "Month of Date Manufactured: " << m[k] << endl;
                        cout << "Day of Date Manufactured: " << d[k] << endl;
                        search_Partial = 1;
                        }
                    }

                    if (search_Partial == 1) {
                        cout << "Press Enter to go back to the Show Record screen." << endl;\
                        cin.get();
                        showDataRecord();
                    } else if (search_Partial == 0) {
                        cout << "The program was unable to find the record you are looking for." << endl;
                        cout << "Press Enter to go back to the Show Record screen.";\
                        cin.get();
                        showDataRecord();
                    }

                } else if (action1 == 3) {
                    system("CLS");
                    int search_Partial = 0;
                    string partialText;
                    cout << "Enter the sub-string text to search" << endl;
                    cin.ignore();
                    getline(cin,partialText);
                    transform(partialText.begin(), partialText.end(), partialText.begin(), ::tolower);

                    for (int k = 0; k < g; ++k) {
                        transform(manu[k].begin(), manu[k].end(), manu[k].begin(), ::tolower);
                        int found = manu[k].find(partialText);

                        if(found != -1){
                        transform(manu[k].begin(), manu[k].end(), manu[k].begin(), ::toupper);
                        cout << "Item ID: " << userID[k] << endl;
                        cout << "Item Name: " << Store.space2underscore(userName[k]) << endl;
                        cout << "Item Description: " << Store.space2underscore(userDes[k]) << endl;
                        cout << "Item Category: " << Store.space2underscore(cat[k]) << endl;
                        cout << "Item Manufacturer: " << Store.space2underscore(manu[k]) << endl;
                        cout << "Selling Price of Item: " << sp[k] << endl;
                        cout << "Cost Price of Item: " << cp[k] << endl;
                        cout << "Number of Units In Store: " << ustore[k] << endl;
                        cout << "Number of Units In Sold: " << usold[k] << endl;
                        cout << "Year of Date Manufactured: " << y[k] << endl;
                        cout << "Month of Date Manufactured: " << m[k] << endl;
                        cout << "Day of Date Manufactured: " << d[k] << endl << endl;
                        search_Partial = 1;
                        }
                    }

                    if (search_Partial == 1) {
                        cout << "Press Enter to go back to the Show Record screen." << endl;
                        cin.get();
                        showDataRecord();
                    } else if (search_Partial == 0) {
                        cout << "The program was unable to find the record you are looking for." << endl;
                        cout << "Press Enter to go back to the Show Record screen.";
                        cin.get();
                        showDataRecord();
                    }
                }
            }

        } else if (action1 == 4 || action1 == 5) {
            system("CLS");
            cout << "1) Equivalence condition" << endl << "2) Less than condition" << endl << "3) More than condition" << endl;
            int action3;
            int index = 0;

            while (index == 0) {
                cin >> action3;
                if (action3 == 1 || action3 == 2 || action3 == 3) {
                    index = 1;
                } else {
                    cout << "Please enter the valid selection as stated above." << endl;
                }
            }

            if (action3 == 1) {
                if (action1 == 4) {
                    system("CLS");
                    int search_Price = 0;
                    double present_Price;
                    cout << "Enter a price to be equal to: ";
                    cin >> present_Price;

                    int x = 0;
                    for (int i = 0; i < g; i++) {
                        double selling_price;
                        stringstream ss;
                        ss << sp[i];
                        ss >> selling_price;
                        if (present_Price == selling_price) {
                            cout << "Item ID: " << userID[i] << endl;
                            cout << "Item Name: " << Store.space2underscore(userName[i]) << endl;
                            cout << "Item Description: " << Store.space2underscore(userDes[i]) << endl;
                            cout << "Item Category: " << Store.space2underscore(cat[i]) << endl;
                            cout << "Item Manufacturer: " << Store.space2underscore(manu[i]) << endl;
                            cout << "Selling Price of Item: " << sp[i] << endl;
                            cout << "Cost Price of Item: " << cp[i] << endl;
                            cout << "Number of Units In Store: " << ustore[i] << endl;
                            cout << "Number of Units In Sold: " << usold[i] << endl;
                            cout << "Year of Date Manufactured: " << y[i] << endl;
                            cout << "Month of Date Manufactured: " << m[i] << endl;
                            cout << "Day of Date Manufactured: " << d[i] << endl << endl;
                            search_Price = 1;
                        }
                    }

                    if (search_Price == 1) {
                        cout << "Press Enter to go back to the Show Record screen." << endl;
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    } else if (search_Price == 0) {
                        cout << "The program was unable to find the record you are looking for." << endl;
                        cout << "Press Enter to go back to the Show Record screen.";
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    }

                } else if (action1 == 5) {
                    system("CLS");
                    int search_Price = 0;
                    double present_Price;
                    cout << "Enter a price to be equal to: ";
                    cin >> present_Price;

                    int x = 0;
                    for (int i = 0; i < g; i++) {
                        double cost_price;
                        stringstream ss;
                        ss << cp[i];
                        ss >> cost_price;
                        if (present_Price == cost_price) {
                            cout << "Item ID: " << userID[i] << endl;
                            cout << "Item Name: " << Store.space2underscore(userName[i]) << endl;
                            cout << "Item Description: " << Store.space2underscore(userDes[i]) << endl;
                            cout << "Item Category: " << Store.space2underscore(cat[i]) << endl;
                            cout << "Item Manufacturer: " << Store.space2underscore(manu[i]) << endl;
                            cout << "Selling Price of Item: " << sp[i] << endl;
                            cout << "Cost Price of Item: " << cp[i] << endl;
                            cout << "Number of Units In Store: " << ustore[i] << endl;
                            cout << "Number of Units In Sold: " << usold[i] << endl;
                            cout << "Year of Date Manufactured: " << y[i] << endl;
                            cout << "Month of Date Manufactured: " << m[i] << endl;
                            cout << "Day of Date Manufactured: " << d[i] << endl << endl;
                            search_Price = 1;
                        }
                    }

                    if (search_Price == 1) {
                        cout << "Press Enter to go back to the Show Record screen." << endl;
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    } else if (search_Price == 0) {
                        cout << "The program was unable to find the record you are looking for." << endl;
                        cout << "Press Enter to go back to the Show Record screen.";
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    }

                }

            } else if (action3 == 2) {
                if (action1 == 4) {
                    system("CLS");
                    int search_Price = 0;
                    double present_Price;
                    cout << "Enter a price to be less than to: ";
                    cin >> present_Price;

                    int x = 0;
                    for (int i = 0; i < g; i++) {
                        double selling_price;
                        stringstream ss;
                        ss << sp[i];
                        ss >> selling_price;
                        if (selling_price < present_Price) {
                            cout << "Item ID: " << userID[i] << endl;
                            cout << "Item Name: " << Store.space2underscore(userName[i]) << endl;
                            cout << "Item Description: " << Store.space2underscore(userDes[i]) << endl;
                            cout << "Item Category: " << Store.space2underscore(cat[i]) << endl;
                            cout << "Item Manufacturer: " << Store.space2underscore(manu[i]) << endl;
                            cout << "Selling Price of Item: " << sp[i] << endl;
                            cout << "Cost Price of Item: " << cp[i] << endl;
                            cout << "Number of Units In Store: " << ustore[i] << endl;
                            cout << "Number of Units In Sold: " << usold[i] << endl;
                            cout << "Year of Date Manufactured: " << y[i] << endl;
                            cout << "Month of Date Manufactured: " << m[i] << endl;
                            cout << "Day of Date Manufactured: " << d[i] << endl << endl;
                            search_Price = 1;
                        }
                    }

                    if (search_Price == 1) {
                        cout << "Press Enter to go back to the Show Record screen..." << endl;
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    } else if (search_Price == 0) {
                        cout << "The program was unable to find the record you are looking for." << endl;
                        cout << "Press Enter to go back to the Show Record screen...";
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    }

                } else if (action1 == 5) {
                    system("CLS");
                    int search_Price = 0;
                    double present_Price;
                    cout << "Enter a price to be less than to: ";
                    cin >> present_Price;

                    int x = 0;
                    for (int i = 0; i < g; i++) {
                        double cost_price;
                        stringstream ss;
                        ss << cp[i];
                        ss >> cost_price;
                        if (cost_price < present_Price) {
                            cout << "Item ID: " << userID[i] << endl;
                            cout << "Item Name: " << Store.space2underscore(userName[i]) << endl;
                            cout << "Item Description: " << Store.space2underscore(userDes[i]) << endl;
                            cout << "Item Category: " << Store.space2underscore(cat[i]) << endl;
                            cout << "Item Manufacturer: " << Store.space2underscore(manu[i]) << endl;
                            cout << "Selling Price of Item: " << sp[i] << endl;
                            cout << "Cost Price of Item: " << cp[i] << endl;
                            cout << "Number of Units In Store: " << ustore[i] << endl;
                            cout << "Number of Units In Sold: " << usold[i] << endl;
                            cout << "Year of Date Manufactured: " << y[i] << endl;
                            cout << "Month of Date Manufactured: " << m[i] << endl;
                            cout << "Day of Date Manufactured: " << d[i] << endl << endl;
                            search_Price = 1;
                        }
                    }

                    if (search_Price == 1) {
                        cout << "Press Enter to go back to the Show Record screen..." << endl;
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    } else if (search_Price == 0) {
                        cout << "The program was unable to find the record you are looking for." << endl;
                        cout << "Press Enter to go back to the Show Record screen...";
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    }

                }

            } else if (action3 == 3) {
                if (action1 == 4) {
                    system("CLS");
                    int search_Price = 0;
                    double present_Price;
                    cout << "Enter a price to be more than to: ";
                    cin >> present_Price;

                    int x = 0;
                    for (int i = 0; i < g; i++) {
                        double selling_price;
                        stringstream ss;
                        ss << sp[i];
                        ss >> selling_price;
                        if (selling_price > present_Price) {
                            cout << "Item ID: " << userID[i] << endl;
                            cout << "Item Name: " << Store.space2underscore(userName[i]) << endl;
                            cout << "Item Description: " << Store.space2underscore(userDes[i]) << endl;
                            cout << "Item Category: " << Store.space2underscore(cat[i]) << endl;
                            cout << "Item Manufacturer: " << Store.space2underscore(manu[i]) << endl;
                            cout << "Selling Price of Item: " << sp[i] << endl;
                            cout << "Cost Price of Item: " << cp[i] << endl;
                            cout << "Number of Units In Store: " << ustore[i] << endl;
                            cout << "Number of Units In Sold: " << usold[i] << endl;
                            cout << "Year of Date Manufactured: " << y[i] << endl;
                            cout << "Month of Date Manufactured: " << m[i] << endl;
                            cout << "Day of Date Manufactured: " << d[i] << endl << endl;
                            search_Price = 1;
                        }
                    }

                    if (search_Price == 1) {
                        cout << "Press Enter to go back to the Show Record screen." << endl;
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    } else if (search_Price == 0) {
                        cout << "The program was unable to find the record you are looking for." << endl;
                        cout << "Press Enter to go back to the Show Record screen...";
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    }

                } else if (action1 == 5) {
                    system("CLS");
                    int search_Price = 0;
                    double present_Price;
                    cout << "Enter a price to be more than to: ";
                    cin >> present_Price;

                    int x = 0;
                    for (int i = 0; i < g; i++) {
                        double cost_price;
                        stringstream ss;
                        ss << cp[i];
                        ss >> cost_price;
                        if (cost_price > present_Price) {
                            cout << "Item ID: " << userID[i] << endl;
                            cout << "Item Name: " << Store.space2underscore(userName[i]) << endl;
                            cout << "Item Description: " << Store.space2underscore(userDes[i]) << endl;
                            cout << "Item Category: " << Store.space2underscore(cat[i]) << endl;
                            cout << "Item Manufacturer: " << Store.space2underscore(manu[i]) << endl;
                            cout << "Selling Price of Item: " << sp[i] << endl;
                            cout << "Cost Price of Item: " << cp[i] << endl;
                            cout << "Number of Units In Store: " << ustore[i] << endl;
                            cout << "Number of Units In Sold: " << usold[i] << endl;
                            cout << "Year of Date Manufactured: " << y[i] << endl;
                            cout << "Month of Date Manufactured: " << m[i] << endl;
                            cout << "Day of Date Manufactured: " << d[i] << endl << endl;
                            search_Price = 1;
                        }
                    }

                    if (search_Price == 1) {
                        cout << "Press Enter to go back to the Show Record screen..." << endl;
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    } else if (search_Price == 0) {
                        cout << "The program was unable to find the record you are looking for." << endl;
                        cout << "Press Enter to go back to the Show Record screen...";
                        cin.ignore();
                        cin.get();
                        showDataRecord();
                    }

                }

            }
        } else if (action1 == 6) {
            showDataRecord();
        }
    } else if (action == 3) {
        mainMenu();
    }
}

// show_Data_Field Function user can view selected data fields by inputting ID

void show_Data_Field()
{
	StoreItem Store;
    system("CLS");
    ifstream outfile("database.txt", ios::app);

	vector<int> y, m, d, ustore, usold;
    vector<string> userID, userName, userDes, cat, manu;
	vector<double> cp, sp;

    int g = 0;

    while(outfile >> item_ID >> item_Name >> item_Description >> Category >> Manufacturer >> selling_Price >> cost_Price >> units_InStore >> units_Sold >> year >> month >> day){
        userID.push_back(item_ID);
        userName.push_back(item_Name);
        userDes.push_back(item_Description);
        cat.push_back(Category);
        manu.push_back(Manufacturer);
        sp.push_back(selling_Price);
        cp.push_back(cost_Price);
        ustore.push_back(units_InStore);
        usold.push_back(units_Sold);
        y.push_back(year);
        m.push_back(month);
        d.push_back(day);
        g = g + 1;
	}

    outfile.close();

    string ID_Search;
    int index = 0, digit, Sorting, selection_Sorting;
    cout << "Enter the Item ID to see the data fields of the Item ID" << endl;
    cin >> ID_Search;

    int Exist_ID = 0;

        for (int k = 0; k < g; ++k) {
            if (static_cast<string>(userID[k]) == static_cast<string>(ID_Search)) {
                Exist_ID = 1;
            }
        }

        if (Exist_ID == 0) {
            cout << "The program was unable to find that Item ID in the database. Press Enter to go back to the Main Menu.";
            cin.ignore();
            cin.get();
            mainMenu();
        }

    cout << "How many data fields would you like to view?" << endl;
    cin >> digit;

    cout << endl
    << "1. Item ID" << endl << "2. Item Name" << endl << "3. Item Description" << endl
    << "4. Category" << endl << "5. Manufacturer" << endl
    << "6. Selling Price" << endl << "7. Cost Price" << endl
    << "8. Units in Store" << endl << "9. Units Sold" << endl
    << "10. Year of Date First Introduced" << endl << "11. Month of Date First Introduced" << endl
    << "12. Day of Date First Introduced" << endl;


    while (index < digit) {
        cout << endl << "Enter the number of the data field you want to view" << endl;
        cin >> Sorting;
        for (int k = 0; k < g; ++k) {
            if (static_cast<string>(userID[k]) == ID_Search) {
                if (Sorting == 1) {
                        cout << "Item ID: " << userID[k] << endl;
                } else if (Sorting == 2) {
                    cout << "Item Name: " << Store.space2underscore(userName[k]) << endl;

                } else if (Sorting == 3) {
                    cout << "Item Description: " << Store.space2underscore(userDes[k]) << endl;

                } else if (Sorting == 4) {
                    cout << "Category: " << Store.space2underscore(cat[k]) << endl;

                } else if (Sorting == 5) {
                    cout << "Manufacturer: " << Store.space2underscore(manu[k]) << endl;

                } else if (Sorting == 6) {
                    cout << "Selling Price: " << sp[k];

                } else if (Sorting == 7) {
                    cout << "Cost Price: " << cp[k] << endl;

                } else if (Sorting == 8) {
                    cout << "Units in Store: " << ustore[k] << endl;

                } else if (Sorting == 9) {
                    cout << "Units Sold: " << usold[k] << endl;

                } else if (Sorting == 10) {
                    cout << "Year of Date First Introduced: " << y[k] << endl;

                } else if (Sorting == 11) {
                    cout << "Month of Date First Introduced: " << m[k] << endl;

                } else if (Sorting == 12) {
                    cout << "Day of Date First Introduced: " << d[k] << endl;

                }
            }
		 }

		 index = index + 1;
    }

    int u = 0, selection;
    while (u == 0) {

        cout << endl << "Press 1 to display the data fields of another record or Press 2 to go back to the Main Menu." << endl;
        cin >> selection;
        if (selection == 1) {
            u = 1;
            show_Data_Field();
        }  else if (selection == 2) {
            u = 1;
            mainMenu();
        } else {
            cout << "Please enter a valid input" << endl;
        }

    }
}

// mainMenu Function shows the user all the applicable features

void mainMenu() {
	StoreItem Store;
    system("CLS");
	cout << "*---------------------------------------------------*" << endl;
	cout << "<----------Inventory System for IT company---------->" << endl;
    cout << "Choose the number of desired action" << endl;
    cout << "1. Insert a new record" << endl;
    cout << "2. Update data field in a record" << endl;
    cout << "3. Delete data field in a record" << endl;
    cout << "4. Delete a record" << endl;
    cout << "5. Display a record on screen" << endl;
    cout << "6. Display selected data fields" << endl;
    cout << "7. Display all data in a data field (Sorting is applicable)" << endl;
    cout << "8. Exit the Program" << endl;

    int index = 0;
    int response;
    while (index == 0) {
        cin >> response;
		Store.CheckInteger(response);
        if (response <= 8) {
            index = 1;
        } else if (response > 8) {
            cout << endl << "Please enter a valid input from 1-7 as stated above" << endl;
        }
    }

    if (response == 1) {
        createRecord();
    } else if (response == 2) {
        updateDataRecord();
    } else if (response == 3) {
        deleteDataRecord();
    } else if (response == 4) {
        deleteRecord();
    }else if (response == 5) {
        showDataRecord();
    } else if (response == 6) {
        show_Data_Field();
    } else if (response == 7) {
        sort_Data_Field();
    } else if (response == 8) {
        exit(0);
    }

}


int main ()
{
	mainMenu();

	return 0;
}

