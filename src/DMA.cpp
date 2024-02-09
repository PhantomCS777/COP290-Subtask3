#include "DMA.h"

std::string reverse(std::string str){
    std::string ans=str.substr(str.length() - 4); 
    ans+=str.substr(3,2);
    ans+=str.substr(0,2);
    return ans;
}

std::string replace_hyphens(std::string str){
    std::string ans="";
    for(auto c:str){
        if(c=='-') ans+='/';
        else ans+=c;
    }
    return ans;
}


Output DMA(std::vector <StockData> stockdata,Input inp)
{
    std::vector <Cash_flow> daily;
    std::vector <Order_stats> order;
    double dma=0;
    int n = inp.n;
    int limit = inp.x;
    int p = inp.p;
    double final_profit_loss = 0;
    std::string start_date = inp.start_date;
    std::string end_date = inp.end_date;
    start_date=reverse(start_date);
    end_date=reverse(end_date);
    double sum = 0;
    double square_sum=0;
    int position=0;
    int total_data_size = stockdata.size();
    double last_price=0;
    for(int i=(total_data_size-1);i>=total_data_size-n+1;i--){
        sum+=stockdata[i].close;
        square_sum+=(stockdata[i].close)*(stockdata[i].close);
    }
    //till this point the sum of last n-1 days values has been caulculated.
    //also sum of squares of prices for last n-1 have been calculated
    for(int i=(total_data_size-n);i>=0;i--){
        sum+=stockdata[i].close;
        square_sum+=(stockdata[i].close)*(stockdata[i].close);
        dma=sum/n;
        double mean_square=square_sum/n;
        double sd=sqrt(mean_square-(dma*dma));
        sum-=stockdata[i+n-1].close;
        square_sum-=(stockdata[i+n-1].close*stockdata[i+n-1].close);
        double cur_price=stockdata[i].close;
        std::string cur_date=replace_hyphens(stockdata[i].date);
        if(cur_date>=start_date&&cur_date<=end_date){
            last_price=stockdata[i].close;
            if(cur_price >= dma+(p*sd) && position < limit){
                position++;
                Cash_flow a(cur_date,-1*cur_price);
                daily.emplace_back(a);
                Order_stats b(cur_date,"BUY",1,cur_price);
                order.emplace_back(b);
                final_profit_loss-=cur_price;
            }
            else if(cur_price <= dma-(p*sd) && position>(-1*limit)){
                position--;
                Cash_flow a(cur_date,cur_price);
                daily.emplace_back(a);
                Order_stats b(cur_date,"SELL",1,cur_price);
                order.emplace_back(b);
                final_profit_loss+=cur_price;
            }
            else{
                Cash_flow a(cur_date,0);
                daily.emplace_back(a);
            }
        }
    }
    final_profit_loss+=(position*last_price);
    Output out(final_profit_loss,daily,order);
    return out;
}