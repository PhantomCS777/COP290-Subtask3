#include "DMA.h"

Output DMA(std::vector <StockData> stockdata,Input inp)
{
    double dma=0;
    int n = inp.n;
    int x = inp.x;
    double p = inp.p;
    double sum = 0;
    int total_data_size = stockdata.size();
    for(int i=(total_data_size-1);i>=total_data_size-n;i--) sum+=stockdata[i].close;
    dma=sum/n;
}