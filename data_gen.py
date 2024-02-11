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

def get_future_date(date_str, n):
  
    
    print("this is it2",date_str)
    given_date = datetime.strptime(date_str, date_format)


    new_date = given_date + timedelta(days=n)


    return new_date.strftime(date_format)

def compare_dates(date1, date2):
    date_format = '%d/%m/%Y'  # Format for day/month/year

    try:
        date1_obj = datetime.strptime(date1, date_format).date()
        date2_obj = datetime.strptime(date2, date_format).date()
    except ValueError as e:
        print("ValueError:", e)
        print("Input dates:", date1, date2)
        return None

    # Print parsed date objects
    print("Parsed date 1:", date1_obj)
    print("Parsed date 2:", date2_obj)

    # Compare the dates
    if date1_obj < date2_obj:
        return True
    else:
        return False
    
def write_function(start_date,end_date,symbol):
    start_date = datetime.strptime(start_date, date_format).date()

    end_date = datetime.strptime(end_date, date_format).date()
    
    df = stock_df(symbol=symbol, from_date=start_date,to_date=end_date, series="EQ")
    df=df.drop(["SERIES","SYMBOL"],axis=1)
    print(df)
    file_name_csv="resources/data"+".csv"
    df.to_csv(file_name_csv,index=False)
    
def strategy(args):
    strat = args[1] 
    symbol = args[2] 
    start_date = args[14]
    end_date = args[15]
    n = int(args[3])
    
    
        
    
    if strat == "LINEAR_REGRESSION": 
      
        train_start_date = args[12]
        train_end_date = args[13] 
        
        
        print("why h",train_start_date)
        if compare_dates(train_start_date,start_date):
            start_date = train_start_date
        if not compare_dates(train_end_date,end_date):
            end_date = train_end_date 
        
        
        

        
    #pairs is remaining 
    if strat == "BEST_OF_ALL":
        start_date = get_past_date(start_date,365)
        
    start_date = get_past_date(start_date,7*n/5 + 7)

    end_date = get_future_date(end_date,7)

    
    return (symbol,start_date,end_date)
        
        
           
def main(args):
    print("Python Script Output:")
    i = 0 
    for arg in args:
        print(i,arg)
        i = i+1
    
    strats = strategy(args) 
    write_function(strats[1],strats[2],strats[0]) 
   

if __name__ == "__main__":
    main(sys.argv)





