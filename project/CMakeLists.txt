cmake_minimum_required(VERSION 3.10)
project(InventoryManagement VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

set(SOURCES
    src/Product.cpp
    src/Warehouse.cpp
    src/InventoryManager.cpp
)

add_executable(inventory_app
    src/main.cpp
    ${SOURCES}
)