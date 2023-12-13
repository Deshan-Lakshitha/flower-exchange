#include <iostream>
using namespace std;
#include "ExchangeApp.h"

int main()
{

    string filename = R"(..\input\example_7.csv)";
    string output = R"(..\output\example_7.csv)";
    ExchangeApp::run(filename, output);

    return 0;
}
