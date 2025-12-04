add_library(shapes
        interfaces/IShape.h
        interfaces/ILineStyle.h
        interfaces/IFillStyle.h

        styles/GroupLineStyle.cpp
        styles/GroupFillStyle.cpp

        entities/Ellipse.cpp
        entities/Triangle.cpp
        entities/Rectangle.cpp
        entities/GroupShape.cpp
)

target_link_libraries(shapes PUBLIC canvas common)