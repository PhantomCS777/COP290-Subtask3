#pragma once
#include <bits/stdc++.h> 
struct StockData 
{
    std::string date; 

    double open; 
    double close; 
    double high; 

    double prev_close; 
    double wh52; 
    double wl52; 

    double low; 
    double ltp; 
    double vwap; 

    double volume; 
    double value ;
    double no_of_trades; 
    
};

struct Input
{
    std::string strategy; 
    std::string symbol; 
    std::string symbol1; 
    std::string symbol2; 
    std::string start_date; 
    std::string end_date; 
    std::string train_start_date; 
    std::string train_end_date;
     int n; 
     int x; 
     double p; 
     int max_hold_days; 
     double c1; 
     double c2; 
     double oversold_threshold; 
     double overbought_threshold;
     double adx_threshold;
     double threshold; 
     double stop_loss_threshold; 
     

};

class Cash_flow{
    public:
    std::string date;
    double transaction;

    Cash_flow(std::string date,double transaction){
        this->date=date;
        this->transaction=transaction;
    }
};

class Order_stats{
    public:
    std::string date;
    std::string order_dir;
    int quantity;
    double price;
    Order_stats(std::string date,std::string order_dir,int quantity,double price){
        this->date=date;
        this->order_dir=order_dir;
        this->quantity=quantity;
        this->price=price;
    }
};

class Output{
    public:
    double final_profit_loss;
    std::vector <Cash_flow> daily;
    std::vector <Order_stats> order;
    Output(double final_profit_loss,std::vector <Cash_flow> daily,std::vector<Order_stats> order){
        this->final_profit_loss=final_profit_loss;
        this->daily=daily;
        this->order=order;
    }
    void write();
};

std::string reverse(std::string str);
std::string replace_hyphens(std::string str);


void buy_stock(StockData,std::vector <Cash_flow> & daily,std::vector <Order_stats> & order,double & profit_loss);
void sell_stock(StockData,std::vector <Cash_flow> & daily,std::vector <Order_stats> & order,double & profit_loss);