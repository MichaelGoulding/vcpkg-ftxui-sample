cmake_minimum_required (VERSION 3.20)

cmake_policy(SET CMP0110 NEW)

project ("test"
    VERSION 0.0.1
    )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt)
find_package(ftxui)

string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWER)

if (${BUILD_TYPE_LOWER} STREQUAL "debug")
    add_compile_options(/DDEBUG)
else()
    string(REPLACE "/Ob1" "/Ob2" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
endif()

add_compile_options(/permissive- /Zc:wchar_t /Zc:forScope /Zc:inline /Zc:throwingNew)
add_compile_options(/Zc:alignedNew) # enable C++17 aligned-new support

add_executable(testApp main.cpp)

target_link_libraries(testApp PRIVATE
    fmt::fmt
    OneCore_apiset
    ftxui::screen
    ftxui::dom
    ftxui::component
    )
