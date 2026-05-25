cmake_minimum_required(VERSION 3.16)

project(OnlineShopQt VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(OnlineShopQt
    main.cpp
    product.h
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    catalogwindow.h
    catalogwindow.cpp
    catalogwindow.ui
    orderwindow.h
    orderwindow.cpp
    orderwindow.ui
)

target_link_libraries(OnlineShopQt PRIVATE Qt6::Widgets)
