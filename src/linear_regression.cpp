#include "linear_regression.h"



/*
 Y = AX 
 we solve for X 
 A = QR 
 so 
 QTransposeY = RX 

*/


double norm_v(std::vector<double> &v)
{
    double norm_val = 0 ; 
    int n = v.size(); 
    for(int i = 0 ; i < n ; i++)
    {
        norm_val += v[i]*v[i];
    }
    norm_val = sqrtl(norm_val);

    for(int i = 0 ; i < n ; i++)
    {
        v[i] = v[i]/norm_val; 
    }
    return norm_val;
}


double dot_prod(std::vector<double> &v1,std::vector<double> &v2)
{
    int n = v1.size(); 
    
    double v = 0; 
    for(int i = 0;i<n;i++)
    {
        v += v1[i]*v2[i]; 
    }
    return v ;

}


std::vector<double> qtranspose_y(std::vector<double> &y,std::vector<std::vector<double> > &q) 
{

    int n = y.size(); 
    int m = q.size(); 
    std::vector<double> qty(m); 

    for(int i = 0 ; i < m;i++)
    {
        qty[i] = dot_prod(y,q[i]);
    }

    return qty; 

}

void sub_v1_av2(std::vector<double>&v1,std::vector<double>&v2,double val)
{
    int n = v1.size(); 
    for(int i = 0 ; i < n;i++)
    {
        v1[i] = v1[i] - val*v2[i];
    }
}

// double calculateRSquared(const std::vector<double>& actual, const std::vector<double>& predicted) {
//     double meanActual = std::accumulate(actual.begin(), actual.end(), 0.0) / actual.size();

//     double ssTotal = 0.0;
//     double ssResidual = 0.0;

//     for (size_t i = 0; i < actual.size(); ++i) {
//         ssTotal += std::pow(actual[i] - meanActual, 2);
//         ssResidual += std::pow(actual[i] - predicted[i], 2);
//     }

//     return 1 - (ssResidual / ssTotal);
// }
std::vector<std::vector<double> > r_mat_and_updateA(std::vector<std::vector <double> > &a_mat)
{
    int n = a_mat.size(); 
    int m = a_mat[0].size(); 
    std::vector<std::vector<double> > r(n,std::vector<double>(n)); 
    
    for(int i = 0 ; i < n ; i++)
    {
               
        r[i][i] = norm_v(a_mat[i]); 
      
        for(int j = i+1; j < n; j++)
        {
                     
            r[i][j] = dot_prod(a_mat[i],a_mat[j]); 
                  
            sub_v1_av2(a_mat[j],a_mat[i],r[i][j]); 
     
                    
        }

    }
                     
    return r ; 
}


std::vector<double> solve_RX_QTY(std::vector<std::vector<double> > &r_mat,std::vector<double > &qty_mat )
{
    int n = qty_mat.size(); 
    std::vector<double> x_mat(n); 
    double last_val = 0 ; 
            //  std::cout<<n<<std::endl; 
    for(int i = n-1 ; i >=0 ; i --)
    {
        last_val = 0 ; 
        for(int j = i+1 ; j < n;j++)
        {
            last_val+=r_mat[i][j]*x_mat[j];
        }

        x_mat[i] = (qty_mat[i] - last_val)/r_mat[i][i]; 
    }
           
    return x_mat; 
}

std::vector<double> mGS_orth(std::vector<std::vector<double> >&a_mat,std::vector<double> &y_mat)
{

    std::vector<std::vector<double> > r_mat = r_mat_and_updateA(a_mat); 
            //  std::cout<<"ok we begin h "<<std::endl; 
    std::vector<double> qty = qtranspose_y(y_mat,a_mat); 
            //  std::cout<<"ok we begin h2"<<std::endl; 
    return solve_RX_QTY(r_mat,qty); 
}


std::vector<std::vector<double> > dataset(std::vector <StockData>&stockdata,std::string train_start_date,std::string train_end_date)
{
    std::vector<std::vector<double> > a_mat(8); 
    
    int n = stockdata.size(); 
    int cur_date_idx = n-1; 
    while(train_start_date > replace_hyphens(stockdata[cur_date_idx].date))
    {
        cur_date_idx--;
    }
    
    for(int i = cur_date_idx; i >=0 ; i--)
    {
        std::string current_date = replace_hyphens(stockdata[i].date);
   
        if(current_date >= train_start_date && current_date <= train_end_date)
        {
            a_mat[0].push_back(1); 
            a_mat[1].push_back(stockdata[i+1].close);
            a_mat[2].push_back(stockdata[i+1].open); 
            a_mat[3].push_back(stockdata[i+1].vwap);
            a_mat[4].push_back(stockdata[i+1].low); 
            a_mat[5].push_back(stockdata[i+1].high); 
            a_mat[6].push_back(stockdata[i+1].no_of_trades);
            a_mat[7].push_back(stockdata[i].open); 
        }
        else
        {
            if(current_date < train_start_date || current_date > train_end_date)
            break; 
        }
    }

    return a_mat; 

}

std::vector<double> price_vector(std::vector <StockData>&stockdata,std::string train_start_date,std::string train_end_date)
{
    std::vector<double> y_mat; 
     int n = stockdata.size(); 
    int cur_date_idx = n-1; 
    while(train_start_date > replace_hyphens(stockdata[cur_date_idx].date))
    {
        cur_date_idx--;
    }
    for(int i = cur_date_idx; i >=0 ; i--)
    {
        std::string current_date = replace_hyphens(stockdata[i].date);
        if(current_date >= train_start_date && current_date <= train_end_date)
        {
            y_mat.push_back(stockdata[i].close); 
        }
         else
        {
            if(current_date < train_start_date || current_date > train_end_date)
            break; 
        }
    }
    return y_mat; 

}

double predict_price(StockData &yesterday,double todayopen,std::vector<double> &weights)
{
    
    double price = weights[0] + 
                   weights[1] * yesterday.close + 
                   weights[2] * yesterday.open + 
                   weights[3] * yesterday.vwap + 
                   weights[4] * yesterday.low + 
                   weights[5] * yesterday.high + 
                   weights[6] * yesterday.no_of_trades + 
                   weights[7] * todayopen; 
    return price; 
}

Output linear_regression(std::vector <StockData>stockdata,Input input)
{
    std::vector <Cash_flow> daily;
    std::vector <Order_stats> order;
    std::string start_date = input.start_date;
    std::string end_date = input.end_date;
    start_date = reverse(start_date); 
    end_date = reverse(input.end_date);
    std::string train_start_date = reverse(input.train_start_date); 
    std::string train_end_date = reverse(input.train_end_date); 
    int position = 0 ; 
    double profit_loss = 0 ; 
     double last_price = 0 ; 
    //  std::cout<<"hehe" <<std::endl; 
    //  std::cout<<input.start_date<<" "<<input.end_date<<" "<<input.train_end_date<<" "<<input.train_start_date<<" "<<input.x<<" "<<input.p<<std::endl;
    std::vector<std::vector<double> > a_mat = dataset(stockdata,train_start_date,train_end_date);

    std::vector<double> y_mat = price_vector(stockdata,train_start_date,train_end_date); 
        
    std::vector<double> weights = mGS_orth(a_mat,y_mat); 
    // std::vector<std::vector<double> > b_mat = dataset(stockdata,train_start_date,train_end_date);
    // // std::vector<double> pred_vector(y_mat.size()); 
    // for(int h = 0 ; h < y_mat.size(); h++)
    // {

    //     double qw = 0; 
    //     for(int j = 0 ; j < 8 ; j++)
    //     {
    //         qw+=b_mat[j][h]*weights[j];
    //     }
    //     pred_vector[h] = qw; 
    // }
    int n = stockdata.size(); 
    int cur_date_idx = n-1; 
    while(start_date > replace_hyphens(stockdata[cur_date_idx].date))
    {
        cur_date_idx--;
    }

    for(int i = cur_date_idx; i >=0; i --)
    {
        //   std::cout<<" "<<i<<std::endl; 
        std::string current_date = replace_hyphens(stockdata[i].date);
        if(current_date >= start_date && current_date <= end_date)
        {
            current_date = revback(current_date);
            last_price = stockdata[i].close; 
            double pred_price = predict_price(stockdata[i+1],stockdata[i].open,weights); 
                     std::cout<<pred_price<<" "<<last_price<<std::endl; 
            if(((pred_price-stockdata[i].close)*100 >= input.p*stockdata[i].close) && position < input.x)
            {
                buy_stock(stockdata[i],daily,order,profit_loss,current_date);
                position++;
            }
            else if(-(pred_price-stockdata[i].close)*100 >= input.p*stockdata[i].close && position > -input.x)
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
        else
        {
            if(current_date < start_date || current_date > end_date)
            break; 
        }
    }
    profit_loss += position*last_price;
    Output output(profit_loss,daily,order);
    return output; 
}