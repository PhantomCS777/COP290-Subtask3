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
    double stop_loss_threshold = inp.stop_loss_threshold;
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
        sum_spread-=give_spread(stockData1[i+n-1],stockData2[i+n-1]);
        square_sum_spread-=give_spread(stockData1[i+n-1],stockData2[i+n-1])*give_spread(stockData1[i+n-1],stockData2[i+n-1]);
        double z_score = (give_spread(stockData1[i],stockData2[i])-mean)/(sd);
        if(cur_date>=start_date&&cur_date<=end_date){
            int sold=0;
            int bought=0;
            double cur_spread = give_spread(stockData1[i],stockData2[i]);
            Cash_flow today_cash (cur_date,profit_loss); 
            last_price = give_spread(stockData1[i],stockData2[i]);
            Order_stats stock1(cur_date,"lol",0,0);
            Order_stats stock2(cur_date,"lol",0,0);
            std::cout<<"cur_date "<<cur_date<<" z_score "<<z_score<<" sd "<<sd<<std::endl;
            if(z_score>threshold&&position>(-1*limit)){
                if(already_bought.empty()){
                    already_sold.push_back({mean,sd});
                }
                else{
                    already_bought.erase(already_bought.begin());
                }
                sold++;
            }
            else if(z_score < -1*threshold &&position<limit){
                if(already_sold.empty()){
                    already_bought.push_back({mean,sd});
                }
                else{
                    already_sold.erase(already_sold.begin());
                }
                bought++;
            }
            std::vector <std::pair<double,double>> already_sold_remain;
            std::vector <std::pair<double,double>> already_bought_remain;  
            for(auto ele:already_sold){
                double z_score = (cur_spread-ele.first)/(ele.second);
                if(z_score > stop_loss_threshold){
                    bought++;
                }
                else{
                    already_sold_remain.emplace_back(ele);
                }
            }

            for(auto ele:already_bought){
                double z_score = (cur_spread-ele.first)/(ele.second);
                if(z_score<-1*stop_loss_threshold){
                    sold++;
                }
                else{
                    already_bought_remain.emplace_back(ele);
                }
            }
            already_sold = already_sold_remain;
            already_bought =  already_bought_remain;
            position=position+bought-sold;
            profit_loss = profit_loss + sold*cur_spread - bought*cur_spread;
            today_cash.transaction = profit_loss;
            if(bought-sold>0){
                stock1.order_dir="BUY";
                stock2.order_dir="SELL";
                stock1.price = stockData1[i].close;
                stock2.price = stockData2[i].close;
                stock1.quantity=bought-sold; 
                stock2.quantity=bought-sold;
            }
            if(bought-sold<0){
                stock1.order_dir="SELL";
                stock2.order_dir="BUY";
                stock1.price = stockData1[i].close;
                stock2.price = stockData2[i].close;
                stock1.quantity=sold-bought; 
                stock2.quantity=sold-bought;
            }
            if(bought-sold!=0){
                order1.emplace_back(stock1);
                order2.emplace_back(stock2);
            }
            daily.emplace_back(today_cash);
        }

    }
    profit_loss+=position*last_price;
    std::cout<<" order1 "<<order1.size()<<" order2 "<<order2.size()<<std::endl; 
    for(auto ele:order2){
        std::cout<<ele.date<<" "<<ele.order_dir<<" "<<ele.price<<" "<<ele.quantity<<std::endl;
    }
    Output out(profit_loss,daily,order1,order2);

    return out;






}