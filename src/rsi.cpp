#include "rsi.h"
#include <bits/stdc++.h>



double gain(double a,double b){
    return std::max<double>(a-b,0);
}

double loss(double a,double b){
    return std::max<double>(b-a,0);
}


Output rsi(std::vector <StockData> stockData, Input inp){
    
    
    std::vector <Cash_flow> daily;
    std::vector <Order_stats> order;
    std::string start_date = inp.start_date;
    std::string end_date = inp.end_date;
    start_date = reverse(start_date);
    end_date = reverse(end_date);
    int limit = inp.x;
    int n = inp.n;
    int position = 0;
    int total_data_size = stockData.size();
    double profit_loss = 0;
    double cur_price;
    double sum_price_gain=0;
    double sum_loss = 0;
    for(int i=total_data_size-2;i>=total_data_size-n;i--){
        sum_price_gain += gain(stockData[i].close,stockData[i+1].close);
        sum_loss += loss(stockData[i].close,stockData[i+1].close);       
    }
    for(int i=total_data_size-n-1;i>=0;i--)
    {
        sum_price_gain+=gain(stockData[i].close,stockData[i+1].close);
        sum_loss += loss(stockData[i].close,stockData[i+1].close);
        std::string cur_date = replace_hyphens(stockData[i].date);
        if(cur_date>=start_date&&cur_date<=end_date){
            cur_price=stockData[i].close;
            cur_date = revback(cur_date);
            double rsi;
            if(fabs(sum_loss)>0.000001)
            {
                double rs=sum_price_gain/sum_loss;
                rsi=100.0-(100.0/(1.0+rs));
            }
            else rsi=100.0;
            if(rsi<=inp.oversold_threshold&&position<limit){
                position++;
                buy_stock(stockData[i],daily,order,profit_loss,cur_date);
            }
            else if(rsi>=inp.overbought_threshold&&position>(-1*limit)){
                position--;
                sell_stock(stockData[i],daily,order,profit_loss,cur_date);
            }
            else{
                Cash_flow a(cur_date,profit_loss);
                daily.emplace_back(a);
            }
        }
        sum_price_gain-=gain(stockData[i+n-1].close,stockData[i+n].close);
        sum_loss-= loss(stockData[i+n-1].close,stockData[i+n].close);
    }
    profit_loss+=position*cur_price;//final squaring off
    Output out(profit_loss,daily,order);
    return out;
}