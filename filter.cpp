#include "filter.h"

using namespace std;


const int dataLen = 32;
static int data[dataLen];
static int writePos = 0;


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - -
void push_sample(int sample)
{
	data[writePos++] = sample;
	if (writePos > dataLen - 1)
		writePos = 0;
}


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
// Computes a simple moving average
int filter_sma(void)
{
	long average = 0;
	for (int i = 0; i < dataLen; i++)
	{
		average += data[i];
	}

	average = average / dataLen;

	return average;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 
int filter_ema(void)
{
	return -1;
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
		if (0 == strncmp("-t", argv[i], 2))
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

	cout << "Processing input data " << inputFile << " using the " << type << " filter." << endl;
	cout << "Results will be saved to " << outputFile << endl;
	cout << endl;

	for (int i = 0; i < 256; i+= 2)
	{
		push_sample(i);

		int sample = 0;
		if (0 == strncmp("sma", type, 3))
		{
			sample = filter_sma();
		}
		else if (0 == strncmp("ema", type, 3))
		{
			sample = filter_ema();
		}

		cout << "Average: " << sample << endl;
	}

	cout << endl;

	return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void showHelp(void)
{
	cout << "filter - Demonstrates various filter algorithms, such as an SMA or EMA." << endl;
	cout << "  SMA: Simple Moving Average" << endl;
	cout << "  EMA: Exponential Moving Average" << endl;
	cout << endl;
	cout << "filter -t {type} -i {input file} -o {output file}" << endl;
	cout << "  -t  Filter type.  Can be either sma or ema." << endl;
	cout << "  -i  Path to input file which is a text file.  One data point per line." << endl;
	cout << "  -o  Path to output file.  File will be written as a series of data points, one per line.  It may not have the " \
	" same number of lines as the input file." << endl;
}
