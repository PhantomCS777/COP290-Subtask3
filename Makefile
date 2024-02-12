
# CPP_SOURCE=main.cpp
# CPP_BINARY=main


# all: $(CPP_BINARY) run


# $(CPP_BINARY): $(CPP_SOURCE)
# 	@g++ -std=c++17 -o $(CPP_BINARY) $(CPP_SOURCE)


# run: 
# 	@python3 data_gen.py $(strategy) $(symbol) $(n) $(x) $(p) $(max_hold_days) $(c1) $(c2) $(oversold_threshold) $(overbought_threshold) $(adx_threshold) $(train_start_date) $(train_end_date) $(start_date) $(end_date) $(symbol1) $(symbol2) $(threshold) $(stop_loss_threshold)
# 	@./$(CPP_BINARY) $(strategy) $(symbol) $(n) $(x) $(p) $(max_hold_days) $(c1) $(c2) $(oversold_threshold) $(overbought_threshold) $(adx_threshold) $(train_start_date) $(train_end_date) $(start_date) $(end_date) $(symbol1) $(symbol2) $(threshold) $(stop_loss_threshold)


# clean:
# 	@rm -f $(CPP_BINARY)

# Directories
SRC_DIR = src
INCLUDE_DIR = include

# Source and object files
CPP_SOURCE = main.cpp $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(CPP_SOURCE:.cpp=.o)
CPP_BINARY = main

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -I$(INCLUDE_DIR) -fopenmp -O3

# Targets
all: $(CPP_BINARY) run

$(CPP_BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(CPP_BINARY) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: 
	python3 data_gen.py $(strategy) $(symbol) $(n) $(x) $(p) $(max_hold_days) $(c1) $(c2) $(oversold_threshold) $(overbought_threshold) $(adx_threshold) $(train_start_date) $(train_end_date) $(start_date) $(end_date) $(symbol1) $(symbol2) $(threshold) $(stop_loss_threshold)
	time ./$(CPP_BINARY) $(strategy) $(symbol) $(n) $(x) $(p) $(max_hold_days) $(c1) $(c2) $(oversold_threshold) $(overbought_threshold) $(adx_threshold) $(train_start_date) $(train_end_date) $(start_date) $(end_date) $(symbol1) $(symbol2) $(threshold) $(stop_loss_threshold)

clean:
	rm -f $(CPP_BINARY) $(OBJECTS)


n = 50 
p = 2 
x = 5
max_hold_days = 28
c1 = 2 
c2 = 0.2 
oversold_threshold = 30 
overbought_threshold = 70 
adx_threshold = 25 
train_start_date = "01/01/2024"
train_end_date = "31/01/2024"
symbol1 = "a"
symbol2 = "b"
threshold=0
stop_loss_threshold=0

.PHONY: all run clean
