cmake_minimum_required(VERSION 3.20)
project(XamSpice CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(ext)

#Required for qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)

add_executable(XamSpice
	"src/main.cpp"
	"src/Simulation/Circuit.cpp"  
	"src/Utils/NetlistParser.cpp" 
	"src/UI/GraphWindow.cpp"
	"include/UI/GraphWindow.hpp")

target_link_libraries(XamSpice PRIVATE
	Qt6::Core
	Qt6::Gui
	Qt6::Widgets
	Qt6::Charts
)