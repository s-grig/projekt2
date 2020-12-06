cmake_minimum_required(VERSION 3.4)    

set(CMAKE_CXX_STANDARD 17)            
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR YES)
set(CMAKE_AUTOMOC ON)

project(PROJEKT2)
set(PROJEKT2_VERSION_MAJOR 1)  
set(PROJEKT2_VERSION_MINOR 0)  
set(PROJEKT2_VERSION_PATCH 1)  
set(PROJEKT2_VERSION  
${PROJEKT2_VERSION_MAJOR}.${PROJEKT2_VERSION_MINOR}.${PROJEKT2_VERSION_PATCH}.${PROJEKT2_VERSION_TWEAK})  
set(PROJEKT2_VERSION_STRING "v${PROJEKT2_VERSION}") 





find_package(SFML REQUIRED COMPONENTS system window graphics)

find_package(Tesseract CONFIG REQUIRED)

find_package(Qt5Gui CONFIG REQUIRED)

find_package(Qt5Widgets CONFIG REQUIRED)

#-DCMAKE_TOOLCHAIN_FILE=C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake

add_executable(main
${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/ui.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/drawer.cpp)


target_include_directories(main
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#set_target_properties(main PROPERTIES AUTOMOC TRUE)

target_link_libraries(main PRIVATE libtesseract)

target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics)

target_link_libraries(main PRIVATE ${Qt5Gui_LIBRARIES})

target_link_libraries(main PRIVATE ${Qt5Widgets_LIBRARIES})
