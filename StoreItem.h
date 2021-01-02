#include <iostream>
#include <algorithm>
//#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
//#include <sstream>
#include <unistd.h>
#include <stdlib.h>

#ifndef STOREITEM_H
#define STOREITEM_H


class StoreItem{

    public:

        void Storing();
		std::string space2underscore(std::string &a);
		int CheckInteger(int &a);
		double CheckDouble(double &a);
		int CheckYear(int &a);
		int CheckMonth(int &a);
		int CheckDay(int &a);
};

#endif // STOREITEM_H
