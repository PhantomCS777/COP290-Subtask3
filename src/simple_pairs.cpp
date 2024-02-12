#include <bits/stdc++.h>
#include "simple_pairs.h"

double spread(StockData data1, StockData data2){
    return data1.close-data2.close;
}
Output simple_pairs(std::vector <StockData> stockData1,std::vector <StockData> stockData2,Input inp){
    std::string start_date = inp.start_date;
    std::string end_date = inp.end_date;
    start_date = reverse(start_date);
    end_date = reverse(end_date);
    std::vector <Cash_flow> daily;
    std::vector <Order_stats> order1;
    std::vector <Order_stats> order2;
    int n = inp.n;
    int limit = inp.x;
    int position=0;
    double threshold = inp.threshold;
    double sum_spread = 0;
    double square_sum_spread = 0;
    double last_price=0;
    double profit_loss=0;
    int total_data_size = stockData1.size();
    for(int i=(total_data_size-1);i>=total_data_size-n+1;i--){
        sum_spread+=spread(stockData1[i],stockData2[i]);
        square_sum_spread+=spread(stockData1[i],stockData2[i])*spread(stockData1[i],stockData2[i]);
    }
    //till this point the sum of last n-1 days values has been caulculated.
    //also sum of squares of prices for last n-1 have been calculated
    for(int i=(total_data_size-n);i>=0;i--){
        std::string cur_date=replace_hyphens(stockData1[i].date);
        sum_spread+=spread(stockData1[i],stockData2[i]);
        square_sum_spread += spread(stockData1[i],stockData2[i])*spread(stockData1[i],stockData2[i]);
        double mean = sum_spread/n;
        double mean_square = square_sum_spread/n;
        double sd = sqrt(mean_square -  mean*mean);
        double z_score = (spread(stockData1[i],stockData2[i])-mean)/(sd);
        // till this point z score is calculated now we need to resolve the issue of how to think of position and i am going to do it tommorow.
        if(cur_date>=start_date && cur_date<=end_date){
            last_price = spread(stockData1[i],stockData2[i]); 
            cur_date  = revback(cur_date); 
            if(z_score>threshold&&position>(-1*limit)){
                position--;
                profit_loss += spread(stockData1[i],stockData2[i]);
                Cash_flow a(cur_date,profit_loss);
                daily.emplace_back(a);
                Order_stats stock1 (cur_date,"SELL",1,stockData1[i].close);
                Order_stats stock2 (cur_date,"BUY",1,stockData2[i].close);
                order1.emplace_back(stock1);
                order2.emplace_back(stock2);
            }
            else if(z_score < -1*threshold &&position<limit){
                position++;
                profit_loss = profit_loss  - spread(stockData1[i],stockData2[i]);
                Cash_flow a(cur_date,profit_loss);
                daily.emplace_back(a);
                Order_stats stock1(cur_date,"BUY",1,stockData1[i].close);
                Order_stats stock2(cur_date,"SELL",1,stockData2[i].close);
                order1.emplace_back(stock1);
                order2.emplace_back(stock2);
            }
            else{
                Cash_flow a(cur_date,profit_loss);
                daily.emplace_back(a); 
            }
        }
        square_sum_spread -= spread(stockData1[i+n-1],stockData2[i+n-1])*spread(stockData1[i+n-1],stockData2[i+n-1]);
        sum_spread-=spread(stockData1[i+n-1],stockData2[i+n-1]);

    }

    profit_loss+=position*last_price;
    Output out(profit_loss,daily,order1,order2);
    return out;
}