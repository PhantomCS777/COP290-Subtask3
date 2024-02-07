#include "basic.h"
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
Output basic(std::vector <StockData> stockdata,Input inp)
{
    std::vector <Cash_flow> daily;
    std::vector <Order_stats> order;
    std::string start_date = inp.start_date;
    std::string end_date = inp.end_date;
    start_date=reverse(start_date);
    end_date=reverse(end_date);
    int limit=inp.x;
    int n=inp.n;
    int curposition=0;
    int cur_trend=0;
    int trend_days=0;
    int total_data_size = stockdata.size();
    long long final_profit_loss=0;
    int cur_price;
    for(int i=total_data_size-2;i>=0;i--){
        std::string modified_date = reverse(stockdata[i].date);
        if(stockdata[i].close==stockdata[i+1].close){
            cur_trend=0;
            trend_days=0;
        }
        else if(stockdata[i].close>stockdata[i+1].close){
            if(cur_trend==0){
                cur_trend=1;
                trend_days=1;
            }
            else if(cur_trend==1){
                trend_days++;
            }
            else{
                cur_trend=1;
                trend_days=1;
            }
        }
        else{
            if(cur_trend==-1){
                trend_days++;
            }
            else{
                cur_trend=-1;
                trend_days=1;
            }
        }
        if(modified_date>=start_date&&modified_date<=end_date){
            cur_price=stockdata[i].close;
            if(trend_days>=n){
                if(cur_trend==-1&&(curposition>(-1*limit))){
                    curposition--;
                    Cash_flow a(modified_date,stockdata[i].close);
                    daily.emplace_back(a);
                    Order_stats b(modified_date,"SELL",1,stockdata[i].close);
                    order.emplace_back(b);
                    final_profit_loss+=stockdata[i].close;
                }
                else if(cur_trend==1 && (curposition<limit)){
                    curposition++;
                    Cash_flow a(modified_date,-1*stockdata[i].close);
                    daily.emplace_back(a);
                    Order_stats b(modified_date,"BUY",1,stockdata[i].close);
                    order.emplace_back(b);
                    final_profit_loss-=stockdata[i].close;
                }
                else{
                    Cash_flow a(modified_date,0);
                    daily.emplace_back(a);
                }
            }
            else{
                Cash_flow a(modified_date,0);
                daily.emplace_back(a);
            }
        }
    }
    if(curposition>0){
        final_profit_loss+=(curposition*cur_price);
    }
    else{
        final_profit_loss-=(curposition*cur_price);
    }
    Output out(final_profit_loss,daily,order);
    return out;
}

