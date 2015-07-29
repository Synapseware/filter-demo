#include "filter.h"

using namespace std;


// program globals
const int		dataLen			= 2;
static int		data[dataLen];
static int		writePos		= 0;
static int		samplesAdded	= 0;
static ifstream	_fin;
static ofstream	_fout;



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


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - -
void sma_add(int sample)
{
	if (samplesAdded < dataLen)
		samplesAdded++;

	data[writePos++] = sample;
	if (writePos > dataLen - 1)
		writePos = 0;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Computes a simple moving average
int filter_sma(void)
{
	long average = 0;
	for (int i = 0; i < samplesAdded; i++)
	{
		average += data[i];
	}

	average = average / dataLen;

	return average;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Adds a new sample to the exponential moving average
static int ema_last = 0;
static int ema_average = 0;
const float ema_k = 0.7;
void ema_add(int sample)
{
	ema_average = sample * ema_k + ((1 - ema_k) * ema_average);
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 
int filter_ema(void)
{
	return ema_average;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Reads the next sample value from the input file
int read_next(void)
{
	char line[64];
	line[0] = '\0';

	// read next, but skip any comments
	while (1)
	{
		_fin.getline(line, sizeof(line) / sizeof(char));

		if (_fin.eof())
		{
			return -1;
		}

		if (line[0] == '#')
		{
			continue;
		}

		break;
	}

	return atoi(line);
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Saves the sample and it's average to the output file
void save_sample(int sample, int average)
{
	_fout << sample << "\t" << average << endl;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Processes the input file
void run_filter(const char* type)
{

}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Opens the files for the run.  Returns -1 if either file is bad.
int openDataFiles(const char* inputFile, const char* outputFile)
{
	_fin.open(inputFile);
	if (!_fin.is_open())
	{
		cout << "Failed to open " << inputFile << " for reading." << endl;
		return -1;
	}

	_fout.open(outputFile);
	if (!_fout.is_open())
	{
		_fin.close();
		cout << "Failed to open " << outputFile << " for writing." << endl;
		return -1;
	}

	return 0;
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

	if (openDataFiles(inputFile, outputFile) != 0)
	{
		return -1;
	}

	for (int i = 0; i < 100; i++)
	{
		int sample = read_next();

		int average = 0;
		if (0 == strncmp("sma", type, 3))
		{
			sma_add(sample);
			average = filter_sma();
		}
		else if (0 == strncmp("ema", type, 3))
		{
			ema_add(sample);
			average = filter_ema();
		}

		save_sample(sample, average);

		cout << "Average: " << average << endl;
	}

	_fin.close();
	_fout.close();

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
