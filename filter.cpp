#include "filter.h"

using namespace std;


const int dataLen = 32;
static int data[dataLen];


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - -
// gets the size of the file
int getFileSize(FILE* file)
{
	int current = ftell(file);

	fseek(file, 0, SEEK_END);
	int filesize = ftell(file);
	fseek(file, current, SEEK_SET);

	return filesize;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int main(int argc, char* argv[])
{
	if (argc < 6)
	{
		showHelp();
		return 0;
	}


	char *type = NULL,
		*inputFile = NULL,
		*outputFile = NULL;

	for (int i = 0; i < argc; i++)
	{
		if (0 == strncmp("-f", argv[i], 2))
			type = argv[++i];
		else if (0 == strncmp("-i", argv[i], 2))
			inputFile = argv[++i];
		else if (0 == strncmp("-o", argv[i], 2))
			outputFile = argv[++i];
	}

	if (type == NULL)
	{
		cout << "Error: No type specified.  Must be sma or ema." << endl;
		return -1;
	}
	if (!(0 == strncmp("sma", type, 3) || 0 == strncmp("ema", type, 3)))
	{
		cout << "Error: Invalid type specified.  Must be sma or ema." << endl;
		return -1;
	}
	if (inputFile == NULL)
	{
		cout << "Error: Input file is required." << endl;
		return -1;
	}
	if (outputFile == NULL)
	{
		cout << "Error: Output file is required." << endl;
		return -1;
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
