#include <bits/stdc++.h> 
#include "src/stock_data.h"
#include "src/basic.h"






std::vector<StockData> readStockPrice(const std::string& filename)
{
    std::vector<StockData> stock_data;
    std::ifstream file("resources/" +filename); 
    if (!file.is_open()) {
     
        throw std::runtime_error("file is not open");
        return stock_data;
    }
    std::string line,value; 
    std::getline(file,line); 
    while(std::getline(file,line))
    {
    
        std::istringstream iss(line);

        StockData row; 
        if (std::getline(iss, row.date, ',') &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.open) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.high) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.low) &&

            std::getline(iss, value, ',') && (std::stringstream(value) >> row.prev_close) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.ltp) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.close) &&

            std::getline(iss, value, ',') && (std::stringstream(value) >> row.vwap) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.wh52) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.wl52) &&

            std::getline(iss, value, ',') && (std::stringstream(value) >> row.volume) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.value) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.no_of_trades))
        {

  
            stock_data.push_back(row);
        }
        

    }
     file.close();
     return stock_data;
}

void print_stock_data(std::vector<StockData> stock_data)
{
   
    int length = stock_data.size(); 
    for(int i = 0 ; i < length; i++)
    {
        std::cout<<stock_data[i].date<<" ";
        std::cout<<stock_data[i].open<<" ";
        std::cout<<stock_data[i].close<<" ";

        std::cout<<stock_data[i].high<<" ";
        std::cout<<stock_data[i].low<<" ";
        std::cout<<stock_data[i].ltp<<" ";

        std::cout<<stock_data[i].volume<<" ";
        std::cout<<stock_data[i].value<<" ";
        std::cout<<stock_data[i].no_of_trades<<std::endl;
    }
      
}

int main(int argc, char* argv[])
{
    std::cout<<"c++ output"<<std::endl; 
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    std::vector<StockData> v = readStockPrice("data.csv"); 
    Input input; 
    std::string strategy = argv[1]; 
    if(strategy == "BASIC")
    {
        input.strategy = strategy; 
        input.symbol = argv[2]; 
        input.n  = std::stoi(argv[3]); 
        input.x = std::stoi(argv[4]);
        input.start_date = argv[5];
        input.end_date = argv[6];
        Output a= basic(v,input);
        std::cout<<"c++ output"<<std::endl; 
        std::cout<<a.final_profit_loss<<std::endl;
        std::cout<<a.daily.size()<<std::endl;
        for(auto ele:a.daily){
            std::cout<<ele.date<<" "<<ele.transaction<<std::endl; 
        }
        
    }
    else if(strategy == "DMA")
    {
        input.strategy = strategy; 
        input.symbol = argv[2]; 
        input.n  = std::stoi(argv[3]); 
        input.x = std::stoi(argv[4]);
        input.p = std::stod(argv[5]);
        input.start_date = argv[6];
        input.end_date = argv[7];

    }
     else if(strategy == "DMA++")
    {
        input.strategy = strategy; 
        input.symbol = argv[2]; 
        input.n  = std::stoi(argv[5]); 
        input.x = std::stoi(argv[3]);
        input.p = std::stod(argv[4]);
        input.max_hold_days = std::stoi(argv[6]); 
        input.c1 = std::stod(argv[7]); 
        input.c2 = std::stod(argv[8]); 
        input.start_date = argv[9];
        input.end_date = argv[10];

    }
      else if(strategy == "MACD")
    {
        input.strategy = strategy; 
        input.symbol = argv[2]; 
      
        input.x = std::stoi(argv[3]);
       
        input.start_date = argv[4];
        input.end_date = argv[5];

    }

     else if(strategy == "RSI")
    {
        input.strategy = strategy; 
        input.symbol = argv[2]; 
        input.n  = std::stoi(argv[4]); 
        input.x = std::stoi(argv[3]);
        input.oversold_threshold = std::stod(argv[5]);
        input.overbought_threshold = std::stod(argv[6]);
        input.start_date = argv[7];
        input.end_date = argv[8];

    }
     else if(strategy == "ADX")
    {
        input.strategy = strategy; 
        input.symbol = argv[2]; 
        input.n  = std::stoi(argv[4]); 
        input.x = std::stoi(argv[3]);
        input.adx_threshold = std::stod(argv[5]); 
        input.start_date = argv[6];
        input.end_date = argv[7];

    }
     else if(strategy == "LINEAR_REGRESSION")
    {
        input.strategy = strategy; 
        input.symbol = argv[2]; 
        input.p  = std::stoi(argv[4]); 
        input.x = std::stoi(argv[3]);
        input.train_start_date = (argv[5]); 
        input.train_end_date = argv[6];
        input.start_date = argv[7];
        input.end_date = argv[8];

    }
     else if(strategy == "BEST_OF_ALL")
    {
        input.strategy = strategy; 
        input.symbol = argv[2]; 
        input.start_date = argv[3];
        input.end_date = argv[4];

    }
     else if(strategy == "PAIRS")
    {
        input.strategy = strategy; 
        input.symbol1 = argv[2]; 
        input.symbol2 = argv[3]; 
        input.n  = std::stoi(argv[5]); 
        input.x = std::stoi(argv[4]);
        input.threshold = std::stod(argv[6]); 
        if(argc == 9){
        input.start_date = argv[7];
        input.end_date = argv[8];
        }
        else
        {
            input.stop_loss_threshold = std::stod(argv[7]); 
            input.start_date = argv[8];
            input.end_date = argv[9];
        }

    }

   

    // print_stock_data(v); 
}
