cmake_minimum_required(VERSION 3.9)
project(PortfolioManger)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -lglpk -Wextra")

add_executable(PortfolioManger
        Config.cpp
        Config.h
        DataIO.cpp
        DataIO.h
        Factor.cpp
        Factor.h
        Fund.cpp
        Fund.h
        Investor.cpp
        Investor.h
        Stock.cpp
        Stock.h
        StockSelector.cpp
        StockSelector.h Algorithm.cpp Algorithm.h Backtest.cpp Backtest.h)
