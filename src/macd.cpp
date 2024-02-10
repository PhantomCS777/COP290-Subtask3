#include "macd.h"



Output macd(std::vector <StockData>& stockdata,Input input)
{
  
    std::vector <Cash_flow> daily;
    std::vector <Order_stats> order;
    std::string start_date = input.start_date;

    std::string end_date = input.end_date;
    start_date = reverse(start_date);
    end_date = reverse(end_date);
    double profit_loss =0 ; 
    int position = 0 ; 
    std::string current_date = replace_hyphens(stockdata[0].date);  
     
    int cur_date_idx = stockdata.size() - 1  ; 
    double last_price = 0 ; 
    while(start_date > replace_hyphens(stockdata[cur_date_idx].date))
    {
          std::cout<<replace_hyphens(stockdata[cur_date_idx].date)<<std::endl; 
        cur_date_idx--;
    }
    current_date = replace_hyphens(stockdata[cur_date_idx].date); 
    double ewm0  =  stockdata[cur_date_idx].close; 
    double short_ewmt=ewm0; 
    double long_ewmt= ewm0; 
    double signal = 0; 
    Cash_flow today(current_date,profit_loss);
    daily.emplace_back(today) ; 
    double alpha1 = 2.0/13; 
    double alpha2 = 2.0/27; 
    double alpha3 = 2.0/10; 

    for(int i = cur_date_idx-1; i >= 0 ; i--)
    {
        
        current_date = (replace_hyphens(stockdata[i].date)); 
        
        if(current_date  >= start_date && current_date <=end_date)
        {
            
            last_price = stockdata[i].close; 
            short_ewmt = alpha1*(stockdata[i].close-short_ewmt) + short_ewmt; 
            long_ewmt = alpha2*(stockdata[i].close -long_ewmt) + long_ewmt; 
            double macd_val = short_ewmt - long_ewmt; 
            signal =  alpha3*(macd_val - signal ) + signal; 
         
            
            if(macd_val > signal && position < input.x)
            {

                buy_stock(stockdata[i],daily,order,profit_loss,current_date); 
                position++;

            }
            else if(macd_val < signal && position > -input.x)
            {
                sell_stock(stockdata[i],daily,order,profit_loss,current_date);
                position--;
            }
            else
            {
                Cash_flow today(current_date,profit_loss);
                daily.emplace_back(today) ; 
            }
        }
      
    }
      
    profit_loss += position*last_price;
    Output output(profit_loss,daily,order);
    return output; 


}


