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
     

};