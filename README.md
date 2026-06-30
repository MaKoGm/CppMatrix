# 1. Clonar el repositorio
git clone https://github.com/tu-usuario/c-matrix.git
cd c-matrix

# 2. Crear una carpeta de construcción y entrar en ella
mkdir build && cd build

# 3. Dejar que CMake genere un Makefile específico para el ordenador del usuario
cmake ..

# 4. Compilar e instalar
make
sudo make install
