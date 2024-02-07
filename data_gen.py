from datetime import date
from datetime import datetime
# from datetime import strptime
import time
from datetime import datetime, timedelta
from jugaad_data.nse import stock_df
from jugaad_data.nse import stock_csv
import os
import matplotlib.pyplot as pt
import sys


# date_string = "07/02/2024"
date_format = "%d/%m/%Y"

def get_past_date(date_str, n):
  
    
    print("this is it",date_str)
    given_date = datetime.strptime(date_str, date_format)


    past_date = given_date - timedelta(days=n)


    return past_date.strftime(date_format)

def write_function(start_date,end_date,symbol):
    start_date = datetime.strptime(start_date, date_format).date()

    end_date = datetime.strptime(end_date, date_format).date()
    
    df = stock_df(symbol=symbol, from_date=start_date,to_date=end_date, series="EQ")
    df=df.drop(["SERIES","SYMBOL"],axis=1)
    file_name_csv="resources/data"+".csv"
    df.to_csv(file_name_csv,index=False)
    
def strategy(args):
    strat = args[1] 
    if strat == "BASIC":
        symbol = args[2] 
        n = int(args[3])
        start_date = args[5]
        end_date = args[6]    
        start_date = get_past_date(start_date,7*n/5 + 7)
        return (symbol,start_date,end_date)

        
        
           
def main(args):
    print("Python Script Output:")
    i = 0 
    for arg in args:
        print(i,arg)
        i = i+1
    print("ok")
    strats = strategy(args) 
    write_function(strats[1],strats[2],strats[0]) 
    print("done")

if __name__ == "__main__":
    main(sys.argv)





