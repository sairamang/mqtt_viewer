cmake_minimum_required(VERSION 3.10.0)
project(mqtt_viewer)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mqtt/include/)
set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mqtt)
message("CMAKE PREFIX PATH set to ${CMAKE_PREFIX_PATH}")
find_library(mqtt_library_client NAMES libpaho-mqtt3c.so)
message("Result of find library: ${mqtt_library_client}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/)
add_executable(mqtt_viewer 
                Mqtt_client.cpp
               MqttViewer.cpp
               Mqtt_controller.cpp
               ScreenHandler.cpp
               WebSocketHandler.cpp
               httpserver.cpp
               )
target_link_libraries(mqtt_viewer
                      ncurses
                      ${mqtt_library_client}
                      pthread)

