#include <iostream>
using namespace std;
#include "ExchangeApp.h"

int main()
{
    string filename = R"(..\input\example_8.csv)";
    string output = R"(..\output\example_8.csv)";
    ExchangeApp::run(filename, output);

    return 0;
}
