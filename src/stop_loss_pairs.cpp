#include <bits/stdc++.h>
#include "simple_pairs.h"

double give_spread(StockData data1, StockData data2){
    return data1.close-data2.close;
}


Output stop_loss_pairs(std::vector <StockData> stockData1,std::vector <StockData> stockData2,Input inp){
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
    std::vector <std::pair<double,double>> already_bought;
    std::vector <std::pair<double,double>> already_sold;
    for(int i=(total_data_size-1);i>=total_data_size-n+1;i--){
        sum_spread+=give_spread(stockData1[i],stockData2[i]);
        square_sum_spread+=give_spread(stockData1[i],stockData2[i])*give_spread(stockData1[i],stockData2[i]);
    }

    for(int i=(total_data_size-n);i>=0;i--){
        
        std::string cur_date=replace_hyphens(stockData1[i].date);
        sum_spread+=give_spread(stockData1[i],stockData2[i]);
        square_sum_spread += give_spread(stockData1[i],stockData2[i])*give_spread(stockData1[i],stockData2[i]);
        double mean = sum_spread/n;
        double mean_square = square_sum_spread/n;
        double sd = sqrt(mean_square -  mean*mean);
        double z_score = (give_spread(stockData1[i],stockData2[i])-mean)/(sd);
        if(cur_date>=start_date&&cur_date<=end_date){
            last_price = give_spread(stockData1[i],stockData2[i]);
            if(z_score>threshold&&position>(-1*limit)){
                position--;
                if(already_bought.empty()){
                    already_sold.push_back({mean,sd});
                }
                else{
                    already_bought.erase(already_bought.begin());
                }
                profit_loss += give_spread(stockData1[i],stockData2[i]);
                Cash_flow a(cur_date,profit_loss);
                daily.emplace_back(a);
                Order_stats stock1 (cur_date,"SELL",1,stockData1[i].close);
                Order_stats stock2 (cur_date,"BUY",1,stockData2[i].close);
                order1.emplace_back(stock1);
                order2.emplace_back(stock2);
            }
            else if(z_score < -1*threshold &&position<limit){
                position++;
                if(already_sold.empty()){
                    already_bought.push_back({mean,sd});
                }
                else{
                    already_sold.erase(already_sold.begin());
                }
                profit_loss -= give_spread(stockData1[i],stockData2[i]);
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



    }






}