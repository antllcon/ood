add_executable(beverages main.cpp)

target_sources(beverages PRIVATE
        lib/IBeverage.h
        lib/Beverages.h
        lib/Condiments.h
)

target_include_directories(beverages PRIVATE lib)