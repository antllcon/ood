add_executable(statistics main.cpp)

target_sources(statistics PRIVATE
        lib/Observer.h
        lib/WeatherData.h
)

target_include_directories(statistics PRIVATE lib)