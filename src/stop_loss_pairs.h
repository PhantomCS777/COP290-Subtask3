#pragma once
#include "stock_data.h"
#include <bits/stdc++.h>

Output stop_loss_pairs (std::vector <StockData> stockData1,std::vector <StockData> stockData2,Input) ;

class Stock_info{
    public:
    std::string buy_date;
    double mean;
    double sd;
    Stock_info(std::string buy_date,double mean,double sd){
        this->buy_date = buy_date;
        this->mean = mean;
        this->sd = sd;
    }
};