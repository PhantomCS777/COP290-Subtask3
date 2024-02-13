
# COP290: Design Practices - Trading Simulator and Analyzer

## Installation

Install requirments.txt 

```bash
    pip install -r requirements.txt
```

Use the following commands to simulate the strategies on the given parameters.(date should be in DD/MM/YY format) 
```bash
    make strategy=BASIC symbol=SBIN n=5 x=2 start_date="b" end_date="a"
    make strategy=DMA symbol=SBIN n=50 x=3 p=2 start_date="a" end_date="b"
    make strategy="DMA++" symbol=SBIN x=4 p=5 n=14 max_hold_days=28 c1=0.2 c2=2 start_date="a" end_date="b"
    make strategy=MACD symbol=SBIN x=3 start_date="a" end_date="b"
    make strategy=RSI symbol=SBIN x=3 n=14 oversold_threshold=30 overbought_threshold=70 start_date="a" end_date="b"
    make strategy=ADX symbol=SBIN x=3 n=14 adx_threshold=25 start_date="a" end_date="b"
    make strategy="LINEAR_REGRESSION" symbol=SBIN x=3 p=2 train_start_date="a" train_end_date="b" start_date="c" end_date="d"
    make strategy="BEST_OF_ALL" symbol=SBIN start_date="a" end_date="b"
    make strategy=PAIRS symbol1=SBIN symbol2=ADANIENT x=5 n=20 threshold=2 start_date="a" end_date="b"
    make strategy=PAIRS symbol1=SBIN symbol2=ADANIENT x=5 n=20 threshold=2 stop_loss_threshold=4 start_date="a" end_date="b"
```

## Abstract 
In the following report we discuss about our implentations of various strategies and what design/abstraction decisions we took while writing of our code. We then also discuss briefly about the strategies themselves and our takeways from analysising them.  



## Introduction
Focusing on the design and implementation of a Trading Simulator and Analyzer. The goal is to explore various algorithmic trading strategies, implement them in C++, and analyze their performance using historical data. below are the strategies we have implemented 

### Strategies Implemented
1. **Momentum-Based Strategies**: Observes price series patterns over the past `n` days to make trading decisions.
2. **Trend-Based Strategy (n-Day Moving Average - DMA)**: Uses the mean price of the past `n` days and standard deviation to decide on trades.
3. **Improving DMA**: Incorporates stop-loss and an adaptive Moving Average (AMA) into the DMA strategy.
4. **MACD (Moving Average Convergence Divergence)**: Implements the MACD indicator for trend analysis.
5. **RSI (Relative Strength Index)**: Utilizes the RSI indicator to identify overbought or oversold conditions.
6. **ADX (Average Directional Index)**: Applies the ADX indicator to measure the strength of a trend.
7. **Linear Regression**: Predicts stock prices using linear regression and makes trading decisions based on the prediction accuracy.
8. **Pairs Trading Strategy**: Focuses on the price spread between a pair of correlated stocks.
9. **Stop-Loss in Pairs Trading Strategy**: Implements a loss-based stop-loss strategy in pairs trading.

### Project Structure
The project directory is structured as follows:

- `include/`: May contain the additional header files for the C++ source code. 
- `resources/`: The data for the strategies to work upon are made availiable in the resources. 
- `src/`: The source code for the trading strategies implemented in the project.
  - `adx.cpp/h`: Implementation of the Average Directional Index (ADX) strategy.
  - `basic.cpp/h`: Code for the basic momentum trading strategy.
  - `bestofall.cpp/h`: Combines various strategies to determine the best performing one.
  - `DMA.cpp/h`: Code for the n-Day Moving Average strategy.
  - `DMA++.cpp/h`: Improves upon the DMA strategy by incorporating additional features.
  - `linear_regression.cpp/h`: Implementation of the Linear Regression strategy for price prediction.
  - `macd.cpp/h`: Moving Average Convergence Divergence (MACD) indicator-based strategy.
  - `rsi.cpp/h`: Relative Strength Index (RSI) indicator-based strategy.
  - `simple_pairs.cpp/h`: Pairs trading strategy based on the correlation between two stocks.
  - `stock_data.cpp/h`: Utilities to manage and process stock data.
  - `stop_loss_pairs.cpp/h`: Implementation of the stop-loss feature in the pairs trading strategy.

- `data_gen.py`: A Python script for generating historical data required for backtesting the strategies.
- `main.cpp`: The entry point of the application, tying together all the strategies.
- `Makefile`: Script for automating the compilation process. Simplifies the build process to a simple `make` command.
- `README.md`: This markdown file providing a comprehensive overview of the project.
- `requirements.txt`: Lists all the Python dependencies required for the project.

## Building and Running
Provide instructions on how to build and run the project, including any dependencies that need to be installed.

Example:
```bash
make strategy=BASIC symbol=SBIN n=5 x=2 start_date="01/01/2023" end_date="31/12/2023"

