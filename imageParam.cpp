#include "imageParam.h"

using namespace std;

imageParam::imageParam()
{
    numElement = 128; // initialize variables
    numSample = 3338;
    numScanline = 127;

    elementPosition = genElementPosition();
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition);
}

imageParam::~imageParam()
{
    deletePositionArray();
}

float *imageParam::genElementPosition()
{
    // array containing element positions
    float *elePosition = new float[numElement]; // declare elePosition array with 128 elements
    for (int i = 0; i < numElement + 1; i++)
        elePosition[i] = (i - ((float(numElement) - 1) / 2)) * PITCH; // Solves for eleLocation at each element
    return elePosition;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float *elementLocation)
{
    // Prompt user to input values for depth and numPixels
    float depth;
    cout << "Enter scanline depth (>0): ";
    cin >> depth;
    cout << "Enter the number of pixels: ";
    cin >> numPixel;

    float2 **scanlinePosition = new float2 *[numScanline];
    float depthstepsize = depth / numPixel;

    for (int i = 0; i < numScanline; i++)
    {
        scanlinePosition[i] = new float2[numPixel];
        for (int k = 0; k < numPixel; k++)
        {
            scanlinePosition[i][k].x = (i - ((numScanline - 1) / 2)) * PITCH; // stores values in scanlinePosition
            scanlinePosition[i][k].y = depthstepsize * k;
        }
    }
    return scanlinePosition;
}

float imageParam::getXPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].x;
}

float imageParam::getYPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].y;
}

float imageParam::getElementPosition(int element)
{
    return elementPosition[element];
}

int imageParam::getNumElement()
{
    return numElement;
}

int imageParam::getNumSample()
{
    return numSample;
}

int imageParam::getNumScanline()
{
    return numScanline;
}

int imageParam::getNumPixel()
{
    return numPixel;
}

void imageParam::deletePositionArray()
{
    for (int i = 0; i < numPixel; i++)
        delete scanlinePosition[i]; // delete each element
    delete elementPosition; // delete the arrays
    delete scanlinePosition;
}