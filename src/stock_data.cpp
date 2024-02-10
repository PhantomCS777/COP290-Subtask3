#include "stock_data.h"
std::string reverse(std::string str){
    std::string ans=str.substr(str.length() - 4); 
    ans+='/';
    ans+=str.substr(3,2);
      ans+='/';
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

void buy_stock(StockData row, std::vector<Cash_flow> &daily, std::vector<Order_stats> &order, double &profit_loss,std::string modified_date)
{
    Cash_flow a(modified_date,profit_loss-1*row.close);
    daily.emplace_back(a);
    Order_stats b(modified_date,"BUY",1,row.close);
    order.emplace_back(b);
    profit_loss-=row.close;
    return;
}

void sell_stock(StockData row, std::vector<Cash_flow> &daily, std::vector<Order_stats> &order, double & profit_loss,std::string modified_date)
{
    Cash_flow a(modified_date,profit_loss+row.close);
    daily.emplace_back(a);
    Order_stats b(modified_date,"SELL",1,row.close);
    order.emplace_back(b);
    profit_loss+=row.close;
    return;
}

void Output::write()
{
    std::string file_name = "daily_cashflow.csv";
    std::ofstream file(file_name);
    file<<"Date,"<<"Cashflow"<<std::endl;
    for(auto ele:this->daily){
        file<<ele.date<<","<<ele.transaction<<std::endl;
    }
    file.close();
    file_name= "order_statistics.csv";
    std::ofstream file1(file_name);
    file1<<"Date,Order_dir,Quantity,Price"<<std::endl;
    for(auto ele:this->order){
        file1<<ele.date<<","<<ele.order_dir<<","<<ele.quantity<<","<<ele.price<<std::endl;
    }
    file1.close();
    file_name="final_pnl.txt";
    std::ofstream file2(file_name);
    file2<<this->final_profit_loss;
    file2.close();
}
