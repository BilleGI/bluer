cmake_minimum_required(VERSION 3.22)

project("Blure effect" VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

find_package(Qt6 COMPONENTS Core Widgets Concurrent REQUIRED)

add_subdirectory(src)

target_link_libraries(my_blure PRIVATE Qt6::Core Qt6::Widgets Qt6::Concurrent)

set_target_properties(my_blure PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

install(TARGETS my_blure
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
