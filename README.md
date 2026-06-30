# C++ Matrix Clone

> Un clon ligero, rápido y configurable del clásico efecto de **"The Matrix"** para la terminal, escrito en C++.

---

##  Características

* **Adaptable:** Se redimensiona automáticamente al cambiar el tamaño de la ventana de la terminal.
* **Controlable:** Permite ajustar la velocidad, densidad y colores mediante argumentos.

---

##  Instalación

### 1. Clona el repositorio

```bash
git clone https://github.com/MaKoGm/CppMatrix.git
cd CppMatrix
```

### 2. Crea la carpeta de compilación

```bash
mkdir build && cd build
```

### 3. Compila e instala

```bash
cmake ..
make
sudo make install
```

---

##  Desinstalar

La forma más fácil es eliminar el ejecutable que hemos generado.

```bash
sudo rm /usr/local/bin/c++matrix
```

---

##  Uso

Una vez instalado, puedes ejecutarlo desde cualquier terminal simplemente escribiendo:

```bash
c++matrix
```

###  Opciones disponibles

| Opción       | Descripción                                                           |
| ------------ | --------------------------------------------------------------------- |
| `-v <num>`   | Velocidad (ej: `1`, `2`, `5`). **Por defecto:** `1`.                  |
| `-d <num>`   | Densidad (ej: `0.5`, `1.5`). **Por defecto:** `0.8`.                  |
| `-c <color>` | Color (`red`, `yellow`, `blue`, `magenta`). **Por defecto:** `verde`. |
| `-h`         | Muestra el menú de ayuda.                                             |

---

##  Licencia

Este proyecto es libre para uso personal y educativo. ¡Siéntete libre de experimentar con el código!

