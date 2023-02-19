cmake_minimum_required(VERSION 3.12)

project(TexExporter)

add_library(${PROJECT_NAME} STATIC src/TexExporter.h src/TexExporter.cpp)