cmake_minimum_required(VERSION 3.20.0)

set(DTC_OVERLAY_FILE app.overlay)

find_package(Zephyr REQUIRED)
project(my_zephyr_app)

target_sources(app PRIVATE src/main.cpp)
