cmake_minimum_required (VERSION 3.1)

project(opencv_test)

find_package(OpenCV CONFIG REQUIRED)

set(HDRS 
    include/Coordinate.hpp
    include/CorrectionPoint.hpp
    include/BrokenPoint.hpp
    include/ImageCorrector.hpp
    include/Line.hpp
)
         
set(SRCS 
    src/main.cpp
    src/Coordinate.cpp
    src/BrokenPoint.cpp
    src/ImageCorrector.cpp
    src/Line.cpp
)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

target_include_directories(${PROJECT_NAME} PRIVATE 
    include/
    ${OpenCV_INCLUDE_DIRS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})