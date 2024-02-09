#include "DMA++.h"

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

double mod_sub(double a,double b){
    if(a>=b) return a-b;
    else return b-a;
}
Output modi_dma(std::vector <StockData> stockData,Input inp)
{
    std::vector <Cash_flow> daily;
    std::vector <Order_stats> order;
    std::string start_date = inp.start_date;
    std::string end_date = inp.end_date;
    start_date=reverse(start_date);
    end_date=reverse(end_date);
    int max_hold_days=inp.max_hold_days;
    int limit=inp.x;
    int n=inp.n;
    double c1=inp.c1;
    double c2=inp.c2;
    int p = inp.p;
    double sf=0.5;
    double ama;
    double profit_loss=0;
    std::queue <int> sell_day;
    std::queue <int> buy_day;
    // int day_no=0;
    int position=0;
    int total_data_size = stockData.size();
    double sum_abs_diff = 0;
    double last_price=0;
    for(int i=total_data_size-2;i>=total_data_size-n;i--){
        sum_abs_diff=mod_sub(stockData[i].close,stockData[i+1].close);       
    }
    // double ER = stockData[i].close-stockData[i+n].close;
    //         if(sum_abs_diff==0) continue;
    //         ER = ER/sum_abs_diff;
    //         double num = (2*ER/(1+c2))-1;
    //         double den = (2*ER/(1+c2)) +1;
    //         double done = num/den;
    //         done=done-sf;
    // sp the sum_abs_diff always contains the sum of differnce in closing price for n-1 days;
    for(int i=total_data_size-n-1;i>=0;i--)
    {
        double cur_price=stockData[i].close;
        sum_abs_diff+=mod_sub(stockData[i].close,stockData[i+1].close);
        std::string cur_date = replace_hyphens(stockData[i].date);
        if(cur_date>=start_date&&cur_date<=end_date){
            last_price=cur_price;
            if(cur_date!=start_date){
                double ER = stockData[i].close-stockData[i+n].close;
                if(sum_abs_diff==0) continue;
                ER = ER/sum_abs_diff;
                double num = (2*ER/(1+c2))-1;
                double den = (2*ER/(1+c2)) +1;
                double done = num/den;
                done = done - sf;
                done = done * c1;
                sf=sf+done;
                ama=ama+sf*(cur_price-ama);
            }
            else{
                ama=cur_price;
            }
            Cash_flow a(cur_date,0);
            Order_stats b(cur_date,"lol",0,0);
            // uptill this point all the factors required have been calculated
            if(cur_price>=ama+((p*ama)/100)&&position<limit){
                    position++;
                    a.transaction-=cur_price;
                    profit_loss-=cur_price;
                    b.quantity=1;
                    b.price=cur_price;
                    b.order_dir="BUY";
                    if(!buy_day.empty()){
                        buy_day.pop();
                    }
                    else{
                        sell_day.push(i-max_hold_days);
                    }


//buy stock here and add it to the queue

            }
            else if(cur_price<=(ama)-((p*ama)/100) && position>(-1*limit)){
                //sell the stock and add it to the queue
                position--;
                a.transaction+=cur_price;
                profit_loss+=cur_price;
                b.quantity=1;
                b.price=cur_price;
                b.order_dir="SELL";
                if(!sell_day.empty()){
                    sell_day.pop();
                }
                else{
                    buy_day.push(i-max_hold_days);
                }
            }
            
            if(!sell_day.empty()){
                if(sell_day.front()==i){
                    profit_loss+=cur_price;
                    if(a.transaction!=0){
                        // this means there must have been buying that day already
                        position--;
                        sell_day.pop();
                        a.transaction+=cur_price;
                        b.quantity=0;
                    }
                    else{
                        //means that day no other trading has been done
                        position--;
                        sell_day.pop();
                        a.transaction+=cur_price;
                        b.order_dir="SELL";
                        b.price=cur_price;
                        b.quantity=1;
                    }
                }
            }
            if(!buy_day.empty()){
                if(buy_day.front()==i){
                    profit_loss-=cur_price;
                    if(a.transaction!=0){
                        // this means already a transaction has been performes in the day.
                        position++;
                        buy_day.pop();
                        a.transaction-=cur_price;
                        b.quantity=0;
                    }
                    else{
                        position++;
                        buy_day.pop();
                        a.transaction-=cur_price;
                        b.order_dir="BUY";
                        b.price=cur_price;
                        b.quantity=1;
                    }
                }
            }

            daily.emplace_back(a);
            if(b.quantity!=0){
                order.emplace_back(b);
            }
            // now i need to think of squaring off last day and profit and loss calculation
        }
        sum_abs_diff-=mod_sub(stockData[i+n-1].close,stockData[i+n].close);
    }

    profit_loss+=(position*last_price);
    // after squaring off final profit loss accomodated.
    // appropriate changes done
    Output ans(profit_loss,daily,order);
    return ans;
}