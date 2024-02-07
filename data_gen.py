from datetime import date
from datetime import datetime
# from datetime import strptime
import time
from dateutil.relativedelta import relativedelta
from jugaad_data.nse import stock_df
from jugaad_data.nse import stock_csv
import os
import matplotlib.pyplot as pt
import sys

symbol = input()
# date_string = "07/02/2024"
date_format = "%d/%m/%Y"
start_date = input()
start_date = datetime.strptime(start_date, date_format).date()
end_date = input()
end_date = datetime.strptime(end_date, date_format).date()
# print(start_date)
# print(end_date)
# stock_csv(symbol=symbol, from_date=start_date,to_date=end_date,series="EQ", output="resources/data.csv")
df = stock_df(symbol=symbol, from_date=start_date,to_date=end_date, series="EQ")
df=df.drop(["SERIES","SYMBOL"],axis=1)
file_name_csv="resources/data"+".csv"
df.to_csv(file_name_csv,index=False)
              
           






