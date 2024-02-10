#include "adx.h"
Output adx(std::vector <StockData> stockData,Input inp){
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
    for(int i=(total_data_size-1);i>=0;i--){
        last_price = stockData[i].close;
        std::string cur_date=replace_hyphens(stockData[i].date);
        if(cur_date>=start_date&&cur_date<=end_date){
            trading_day++;
        }

    }

}