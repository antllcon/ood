add_executable(stream main.cpp)

target_sources(stream PRIVATE
        lib/input/IInputDataStream.h
        lib/input/MemoryInputStream.h
        lib/input/FileInputStream.h
        lib/input/InputDataStreamDecorator.h
        lib/input/DecompressInputStream.h
        lib/input/DecryptInputStream.h

        lib/output/IOutputDataStream.h
        lib/output/MemoryOutputStream.h
        lib/output/FileOutputStream.h
        lib/output/OutputDataStreamDecorator.h
        lib/output/CompressOutputStream.h
        lib/output/EncryptOutputStream.h

        lib/processStream/ProcessStream.h
        lib/processStream/ProcessStream.cpp

        lib/cryptUtils/CryptUtils.h
        lib/cryptUtils/CryptUtils.cpp
)

target_include_directories(stream PRIVATE lib)


#add_executable(stream-test test/test.cpp)
#
#target_sources(stream-test PRIVATE
#        lib/Observer.h
#        lib/WeatherData.h
#)
#
#target_include_directories(stream-test PRIVATE lib test)
#target_link_libraries(stream-test PRIVATE gtest_main gmock_main)
#enable_testing()
#add_test(NAME stream-tests COMMAND stream-test)