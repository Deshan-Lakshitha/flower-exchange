cmake_minimum_required(VERSION 3.26)
project(flower_exchange)

set(CMAKE_CXX_STANDARD 17)

add_executable(flower_exchange main.cpp
        CSVReader.cpp
        CSVReader.h
        Order.cpp
        Order.h
        ExchangeApp.cpp
        ExchangeApp.h
        OrderValidator.cpp
        OrderValidator.h
        OrderBook.cpp
        OrderBook.h
        ExecutionReport.cpp
        ExecutionReport.h
)
