#include <bits/stdc++.h> 
#include <omp.h>
#include "src/stock_data.h"
#include "src/basic.h"
#include "src/DMA.h"
#include "src/DMA++.h"
#include "src/macd.h"
#include "src/linear_regression.h"
#include "src/rsi.h" 
#include "src/adx.h"
#include "src/simple_pairs.h"


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

// $(strategy) $(symbol) $(n) $(x) $(p) $(max_hold_days) $(c1) $(c2) $(oversold_threshold) $(overbought_threshold) $(adx_threshold) $(train_start_date) $(train_end_date) $(start_date) $(end_date) $(symbol1) $(symbol2) $(threshold) $(stop_loss_threshold)
int main(int argc, char* argv[])
{




    std::cout<<"c++ output"<<std::endl; 
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    std::vector<StockData> v = readStockPrice("data.csv"); 
    Input input; 
    std::string strategy = argv[1]; 
    input.strategy = strategy; 
    input.symbol = argv[2]; 
    input.n = std::stoi(argv[3]); 
    input.x = std::stod(argv[4]); 
    input.p = std::stod(argv[5]); 
    input.max_hold_days = std::stoi(argv[6]); 
    input.c1 = std::stod(argv[7]); 
    input.c2 = std::stod(argv[8]); 
    input.oversold_threshold = std::stod(argv[9]); 
    input.overbought_threshold = std::stod(argv[10]); 
    input.adx_threshold = std::stod(argv[11]); 
    input.train_start_date = argv[12]; 
    input.train_end_date = argv[13]; 
    input.start_date = argv[14]; 
    input.end_date = argv[15]; 
    input.symbol1 = argv[16]; 
    input.symbol2 = argv[17]; 
    input.threshold = std::stod(argv[18]); 
    input.stop_loss_threshold = std::stod(argv[19]); 
    Output a; 

    if(strategy == "BASIC")
    {
        // input.strategy = strategy; 
        // input.symbol = argv[2]; 
        // input.n  = std::stoi(argv[3]); 
        // input.x = std::stoi(argv[4]);
        // input.start_date = argv[5];
        // input.end_date = argv[6];
         a= basic(v,input);
       
        
    }
    else if(strategy == "DMA")
    {
         a= DMA(v,input);
        
        Output a= DMA(v,input);
        std::cout<<"c++ output"<<std::endl; 
        std::cout<<a.final_profit_loss<<std::endl;
        std::cout<<a.daily.size()<<std::endl;
        for(auto ele:a.daily){
            std::cout<<ele.date<<" "<<ele.transaction<<std::endl; 
        }
    }
     else if(strategy == "DMA++")
    {
        // input.strategy = strategy; 
        // input.symbol = argv[2]; 
        // input.n  = std::stoi(argv[5]); 
        // input.x = std::stoi(argv[3]);
        // input.p = std::stod(argv[4]);
        // input.max_hold_days = std::stoi(argv[6]); 
        // input.c1 = std::stod(argv[7]); 
        // input.c2 = std::stod(argv[8]); 
        // input.start_date = argv[9];
        // input.end_date = argv[10];

    }
      else if(strategy == "MACD")
    {
        
         a= macd(v,input);
       

    }

     else if(strategy == "RSI")
    {
        // input.strategy = strategy; 
        // input.symbol = argv[2]; 
        // input.n  = std::stoi(argv[4]); 
        // input.x = std::stoi(argv[3]);
        // input.oversold_threshold = std::stod(argv[5]);
        // input.overbought_threshold = std::stod(argv[6]);
        // input.start_date = argv[7];
        // input.end_date = argv[8];

    }
     else if(strategy == "ADX")
    {
        // input.strategy = strategy; 
        // input.symbol = argv[2]; 
        // input.n  = std::stoi(argv[4]); 
        // input.x = std::stoi(argv[3]);
        // input.adx_threshold = std::stod(argv[5]); 
        // input.start_date = argv[6];
        // input.end_date = argv[7];

    }
     else if(strategy == "LINEAR_REGRESSION")
    {
        
        std::cout<<"entring linear reg"<<std::endl; 
        a = linear_regression(v,input);
        std::cout<<"done li re"<<std::endl; 


    }
     else if(strategy == "BEST_OF_ALL")
    {
        // input.strategy = strategy; 
        // input.symbol = argv[2]; 
        // input.start_date = argv[3];
        // input.end_date = argv[4];
        Input input_basic = input; 
        input_basic.n= 7; 
        Input input_DMA = input; 
        input_DMA.n = 50; 
        Input input_DMApp = input; 
        Input input_RSI = input; 
        Input input_ADX = input; 
        input_ADX.n=input_DMApp.n=input_RSI.n = 14; 
        input_DMApp.p = 5 ; 
        Input input_LR = input; 
        input_LR.train_start_date = input.start_date.substr(0,6) + std::to_string(std::stoi(input.start_date.substr(6,4))-1);
        input_LR.train_end_date = input.end_date.substr(0,6) + std::to_string(std::stoi(input.end_date.substr(6,4))-1);

        std::vector<Output> outputs(7);

        Output b1,b2,b3,b4,b5,b6,b7;
      
        #pragma omp parallel for num_threads(7)
        
        for(int id = 0 ; id < 7; id++){
        
        switch (id)
        {
        case 0:
            std::cout<<" thread is "<<id<<std::endl; 
            b1 = basic(v,input_basic);
            std::cout<<"thisn b1 : "<<b1.final_profit_loss<<std::endl;
            break;
        case 1:
            std::cout<<" thread is "<<id<<std::endl; 
            b2 = DMA(v,input_DMA);
            break;
        case 2:
            std::cout<<" thread is "<<id<<std::endl; 
            b3 = modi_dma(v,input_DMApp);
            break; 
        case 3:
            std::cout<<" thread is "<<id+10<<std::endl; 
            b4 = macd(v,input);
            std::cout<<"the fac"<<std::endl; 
            break; 
        case 4:
            std::cout<<"oh no "<<std::endl; 
            std::cout<<" thread is "<<id<<std::endl; 
            b5 = linear_regression(v,input_LR); 
            break;
        case 5:
            std::cout<<" thread is "<<id<<std::endl; 
            b6 = rsi(v,input_RSI);
            break;
        case 6:
            b7 = adx(v,input_ADX);
            break;
        default:
            break;
        }

        
    }
    outputs[0] = b1;
    outputs[1] = b2; 
    outputs[2]=b3;
    outputs[3]=b4;
    outputs[4] = b5; 
    outputs[5] = b6; 
    outputs[6] = b7; 
    std::vector<std::string> stratss = {" BASIC "," DMA "," DMA++ "," MACD "," LINEAR_REGRESSION "," RSI "," ADX "};
    Output best_of_all = outputs[0]; 
    for(int h = 0 ; h < 7; h++)
    {
        std::cout<<h<<stratss[h]<<outputs[h].final_profit_loss<<std::endl; 
        if (best_of_all.final_profit_loss < outputs[h].final_profit_loss)
        {
            best_of_all = outputs[h];
        }
    }
    a = best_of_all ;
    }
     else if(strategy == "PAIRS")
    {
        // input.strategy = strategy; 
        // input.symbol1 = argv[2]; 
        // input.symbol2 = argv[3]; 
        // input.n  = std::stoi(argv[5]); 
        // input.x = std::stoi(argv[4]);
        // input.threshold = std::stod(argv[6]); 
        // if(argc == 9){
        // input.start_date = argv[7];
        // input.end_date = argv[8];
        // }
        // else
        // {
        //     input.stop_loss_threshold = std::stod(argv[7]); 
        //     input.start_date = argv[8];
        //     input.end_date = argv[9];
        // }
        std::vector<StockData> v2 = readStockPrice("data1.csv"); 
        a = simple_pairs(v,v2,input); 

    }

   std::cout<<"c++ output"<<std::endl; 
        std::cout<<a.final_profit_loss<<std::endl;
        // std::cout<<a.daily.size()<<std::endl;
        // for(auto ele:a.daily){
        //     std::cout<<ele.date<<" "<<ele.transaction<<std::endl; 
        // }

    return 0 ; 

    // print_stock_data(v); 
}
