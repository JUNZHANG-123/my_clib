#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IMGWIDTH 96
#define IMGHEIGHT 152
#define IMGLEN IMGWIDTH * IMGHEIGHT
#define MMAX(a, b) (((a) > (b))?(a):(b))
#define MMIN(a, b) (((a) < (b))?(a):(b))

static int mbGetThresh_Otsu(int *pHist)
{
    int i = 0, iThresh = 0, iLen = 256, iSum = 0, iSumTemp = 0;
    int iSum0 = 0, iSumTemp0 = 0;
    float iBcv = 0, iBcvMax = 0, iNum = 0, iDenom = 0;
    if (pHist == NULL)
    {
        return 0;
    }

    for (i = 0; i < iLen; ++i)
    {
        iSumTemp += pHist[i] * i;
        iSum += pHist[i];
    }

    if (iSum == 0)
    {
        return 0;
    }

    iSum0 = pHist[0];

    for (i = 1; i < iLen - 1; ++i)
    {
        iSum0 += pHist[i];
        iSumTemp0 += pHist[i] * i;

        iDenom = (float)iSum0 * (iSum - iSum0);
        if (iDenom != 0)
        {
            iNum = ((float)iSum0 / iSum * iSumTemp) - iSumTemp0;
            iBcv = iNum * iNum / iDenom;
        }
        else
        {
            iBcv = 0;
        }

        if (iBcv >= iBcvMax)
        {
            iBcvMax = iBcv;
            iThresh = i;
        }
    }

    return iThresh;
}

int mbGrayImg2BinImg(unsigned char *pDataSrc, unsigned char *pDataDst, int iw, int ih)
{
    unsigned char *pTemT = NULL, *pDstT = NULL, *pSrcT = NULL;
    int i = 0, j = 0, iRadius = 6, yStart = 0, yEnd = 0, xStart = 0, xEnd = 0;
    int maxV = 0, x = 0, y = 0;
    int hist[256] = {0}, iOtsu = 0;
    unsigned char pDataT[IMGWIDTH] ={0};
    if (pDataSrc == NULL || pDataDst == NULL )
    {
        return 0;
    }
    
    pSrcT = pDataSrc;
    pDstT = pDataDst;
    pTemT = pDataT;
    iRadius = 6;
    for (i = 0; i < ih; i+=2)
    {
        pDstT = pDataDst + i * iw ;
        pSrcT = pDataSrc + i * iw;
        yStart = MMAX(i - iRadius, 0);
        yEnd = MMIN(i + iRadius + 1, ih - 1);
        for (j = 0; j < iw; j+=2)
        {
            xStart = MMAX(j - iRadius, 0);
            xEnd = MMIN(j + iRadius + 1, iw - 1);

            if (j == 0)
            {
                for (x = 0; x < iw; x+=2)
                {
                    maxV = 0;
                    for (y = yStart; y < yEnd; y+=2)
                    {
                        maxV = MMAX(*(pDataSrc + y * iw + x), maxV);
                    }
                    *(pTemT + x) = maxV;
                }
            }//if
            maxV = 0;
            for (x = xStart; x < xEnd; x+=2)
            {
                maxV = MMAX(maxV, *(pTemT + x));
            }
            
            pDstT[j] = (unsigned char)abs(pSrcT[j] - maxV);
            hist[pDstT[j]]++;

            pDstT[j+1] = (unsigned char)abs(pSrcT[j+1] - maxV);
            hist[pDstT[j+1]]++;

            pDstT[j+ iw] = (unsigned char)abs(pSrcT[j+iw] - maxV);
            hist[pDstT[j+iw]]++;

            pDstT[j+iw+1] = (unsigned char)abs(pSrcT[j+iw+1] - maxV);
            hist[pDstT[j+iw+1]]++;
        }
    }
    
    iOtsu = mbGetThresh_Otsu(hist);

    j = iw * ih;
    pDstT = pDataDst;
    for (i = 0; i < j; ++i)
    {
        if (pDstT[i] > iOtsu)
        {
            pDstT[i] = 0xff;
        }
        else
        {
            pDstT[i] = 0;
        }
    }

    return 1;
}


int main(void)
{
	unsigned char buf0[IMGLEN], buf1[IMGLEN];
	mbGrayImg2BinImg(buf0, buf1, IMGWIDTH, IMGHEIGHT);

	return 0;
}
