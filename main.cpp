#include <bits/stdc++.h> 





struct StockData 
{
    std::string date; 
    double open; 
    double close; 

    double high; 
    double low; 
    double ltp; 

    double volume; 
    double value ;
    double no_of_trades; 
    
};


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
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.close) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.high) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.low) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.ltp) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.volume) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.value) &&
            std::getline(iss, value, ',') && (std::stringstream(value) >> row.no_of_trades)) {
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

int main()
{
    std::vector<StockData> v = readStockPrice("data.csv"); 
    print_stock_data(v); 
}

