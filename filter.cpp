#include "filter.h"

using namespace std;


const int dataLen = 32;
static int data[dataLen];




// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int main(int argc, char* argv[])
{
	if (argc < 6)
	{
		showHelp();
		return 0;
	}

	return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void showHelp(void)
{
	cout << "filter - Demonstrates various filter algorithms, such as an SMA or EMA." << endl;
	cout << "  SMA: Simple Moving Average" << endl;
	cout << "  EMA: Exponential Moving Average" << endl;
	cout << endl;
	cout << "filter -f {type} -i {input file} -o {output file}" << endl;
	cout << "  -f  Filter type.  Can be either sma or ema." << endl;
	cout << "  -i  Path to input file which is a text file.  One data point per line." << endl;
	cout << "  -o  Path to output file.  File will be written as a series of data points, one per line.  It may not have the " \
	" same number of lines as the input file." << endl;
}
