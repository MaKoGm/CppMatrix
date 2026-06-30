cmake_minimum_required(VERSION 3.10)
project(C++Matrix)

# 1. Creamos el ejecutable con todos sus archivos "cocina" (.cpp)
add_executable(c++matrix
    src/main.cpp 
    src/drop.cpp
)

# 2. Le decimos a ese ejecutable dónde buscar sus "menús" (.hpp)
target_include_directories(c++matrix PRIVATE include)

# Le dice a CMake que cuando el usuario ejecute "make install", 
# copie el ejecutable a /usr/local/bin (el estándar en Linux)
install(TARGETS c++matrix DESTINATION bin)
