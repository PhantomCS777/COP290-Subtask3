#include "adx.h"
#include <bits/stdc++.h>

Output adx(std::vector <StockData> stockData,Input inp){
    std::cout<<"here it all started"<<std::endl;
    std::vector <Cash_flow> daily;
    std::vector <Order_stats> order;
    std::string start_date = inp.start_date;
    std::string end_date = inp.end_date;
    start_date = reverse(start_date);
    end_date = reverse(end_date);
    int limit = inp.x;
    int n = inp.n;
    double adx_threshold = inp.adx_threshold;
    int total_data_size=stockData.size();
    double last_price=0;
    int trading_day=0;
    double alpha= (2.0/(n+1.0));
    double atr;
    double di_plus;
    double di_minus;
    double dx;
    double adx;
    double profit_loss=0;
    int position=0;
    std::cout<<"total_data_size "<<total_data_size<<std::endl;
    for(int i=(total_data_size-1);i>=0;i--){
        std::string cur_date=replace_hyphens(stockData[i].date);
        if(cur_date>=start_date&&cur_date<=end_date){
            // std::cout<<"am i here"<<std::endl;
            // std::cout<<" i "<<i<<std::endl;
            trading_day++;
            last_price = stockData[i].close;
            double dm_plus = std::max<double>(0,stockData[i].high-stockData[i+1].high); 
            double tr= std::max<double> (stockData[i].high-stockData[i].low,stockData[i].high-stockData[i].prev_close);
            tr = std::max<double> (tr,stockData[i].low-stockData[i].prev_close);
            double dm_minus = std::max<double> (0,stockData[i].low-stockData[i+1].low);
            if(trading_day==1){
                atr = tr;    
            }
            else{
                atr=alpha*(tr-atr)+atr;
            }
            std::cout<<"atr "<<atr<<std::endl;
            double ratio_plus=dm_plus/atr;
            double ratio_minus=dm_minus/atr;
            if(trading_day==1){
                di_plus=ratio_plus;
            }
            else{
                di_plus=alpha*(ratio_plus-di_plus)+di_plus;
            }            
            if(trading_day==1){
                di_minus = ratio_minus;
            }
            else{
                di_minus = alpha*(ratio_minus-di_minus)+di_minus;
            }
            dx = (di_plus-di_minus)/(di_plus+di_minus)*100.0;
            if(trading_day==1){
                adx=dx;
            }
            else{
                adx=alpha*(dx-adx)+adx;
            }
            std::cout<<" cur_date "<<cur_date<<" adx "<<adx<<std::endl;
            if(adx>=adx_threshold&&position<limit){
                position++;
                buy_stock(stockData[i],daily,order,profit_loss,cur_date);
            }
            else if(adx<=adx_threshold&&position>(-1*limit)){
                position--;
                sell_stock(stockData[i],daily,order,profit_loss,cur_date);
            }
            else{
                Cash_flow today(cur_date,0);
                daily.emplace_back(today);
            }
        }
    }
    profit_loss+=position*last_price;
    Output out(profit_loss,daily,order);
    out.write(false);
    return out;
}