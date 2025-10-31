add_library(command
        CommandHistory.cpp
        DeleteItemCommand.cpp
        InsertImageCommand.cpp
        SetTitleCommand.cpp
        ResizeImageCommand.cpp
        ReplaceTextCommand.cpp
        InsertItemCommand.cpp
)
target_include_directories(command PUBLIC ..)