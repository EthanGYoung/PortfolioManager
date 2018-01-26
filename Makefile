

SRCS = Algorithm.cpp Backtest.cpp Config.cpp DataIO.cpp Factor.cpp Fund.cpp Investor.cpp Stock.cpp StockSelector.cpp

HDRS = Algorithm.h Backtest.h Config.h DataIO.h Factor.h Fund.h Investor.h Stock.h StockSelector.h

CXXFLAGS = -Wall -std=c++1y -lglpk -Wextra 

PortfolioManager: $(SRCS) $(HDRS)
	g++ $(CXXFLAGS) $(SRCS) -o $@
