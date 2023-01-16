#include "BmodeClass.h"

BmodeClass::BmodeClass()
{
    imparams = NULL; // default initialization of variables
    RFData = NULL;
    next = NULL;
    line = 0;
}

BmodeClass::BmodeClass(imageParam *params, dataBuffer *data, int numline)
{
    imparams = params;
    RFData = data;
    line = numline; 

    scanline = createScanline(imparams->getNumPixel());
    beamform();
}

BmodeClass::~BmodeClass()
{
    deleteScanline();
}

float *BmodeClass::createScanline(int numPixel)
{
    float *mem = new float[numPixel];
    return mem;
}

void BmodeClass::beamform()
{
    float tForward = 0;
    float tBackward = 0;
    float tTotal = 0;
    int s = 0;
    float pReal;
    float pImag;

    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        tForward = (imparams->getYPosition(line, i)) / imparams->SOS; // calculate tforward

        for (int k = 0; k < imparams->getNumElement(); k++)
        {
            tBackward = sqrt(pow(imparams->getYPosition(line, i), 2) + pow((imparams->getXPosition(line, i)) - imparams->getElementPosition(k), 2)) / imparams->SOS; // calculation for tBackward
            tTotal = tForward + tBackward;                                                                                                                           // calculation for tTotal
            s = floor(tTotal * imparams->FS);

            if (s < imparams->getNumSample())
            {
                pReal = pReal + RFData->getRealRFData(k, s); // calculate pReal
                pImag = pImag + RFData->getImagRFData(k, s); // calculate sample number (integer)
            }                                                // calculate for pImag
        }
        scanline[i] = sqrt(pow(pReal, 2) + pow(pImag, 2)); // calculatethe echo magnitude and store in scanline
        pReal = 0;
        pImag = 0;
    }
}

void BmodeClass::getScanline(float *data)
{
    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        data[i] = scanline[i];
    }
}

void BmodeClass::deleteScanline()
{
    delete scanline;
}