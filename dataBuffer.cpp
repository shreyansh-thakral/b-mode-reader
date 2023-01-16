#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    numElement = 0; // default initialization of variables
    numSample = 0;
    scanline = 0;

    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer(std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    numElement = inputNumElement; // initialize variables to passed parameters
    numSample = inputNumSample;
    scanline = inputScanline;

    dataMatrix = createDataMatrix();                      
    int num = loadRFData(dataMatrix, imagFile, realFile);
}

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); // destructor deletes dataMatrix 
}

complex **dataBuffer::createDataMatrix()
{
    complex **RFData;                   // initialize RFData
    RFData = new complex *[numElement]; // Creates a pointer array complex type with numElement elements

    for (int i = 0; i < numElement; i++)
        RFData[i] = new complex[numSample]; // For every element in RFData, creates a block of type complex with size numSample
    return RFData;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile)
{
    const int MAX = 100; 
    char line[MAX];

    for (int i = 0; i < numElement; i++) {
        for (int j = 0; j < numSample; j++) {
            imagFile->getline(line, MAX); // open the imaginary text file
            RFData[i][j].imag = atof(line);     // converts each charcter array to float and then stores it in corresponding RFData array

            realFile->getline(line, MAX); // open the real text file
            RFData[i][j].real = atof(line);     // converts each charcter array to float and then stores it in corresponding RFData array
        }
    }

    if (imagFile->fail() || realFile->fail())
        return -1;
    return 0;
}

float dataBuffer::getRealRFData(int element, int sample)
{
    // Returns the real component of the stored data
    return dataMatrix[element][sample].real;
}

float dataBuffer::getImagRFData(int element, int sample)
{
    // Returns the imaginary component of the stored data
    return dataMatrix[element][sample].imag;
}

void dataBuffer::deleteDataMatrix()
{
    for (int i = 0; i < numElement; i++) // Deletes every element in dataMatrix
        delete dataMatrix[i];
    delete dataMatrix; // Deletes the array itself
}