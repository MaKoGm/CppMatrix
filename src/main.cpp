#include <cstdint>
#include <iostream>
#include <random>
#include <signal.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "drop.hpp"

void screen_size(int &rows, int &columns);
void flush_buffer(const int &colour);
void clear_buffer();
void help();
void manejadora(int sigmun);

int rows = 0, columns = 0;
std::vector<std::vector<char>> buffer_dinamico;

volatile sig_atomic_t fin = 0;

int main(int argc, char *argv[]) {

  signal(SIGINT, manejadora);
  int optchr = 0, opterr = 0, speed = 1, colour = 0;
  float density = 0.8;

  while ((optchr = getopt(argc, argv, "hd:v:c:")) != -1) {
    switch (optchr) {
    case 'h':
      help();
      return 0;
    case 'd':
      density = std::stof(optarg);
      break;
    case 'v':
      speed = std::stoi(optarg);
      if (speed <= 0)
        speed = 1;
      break;
    case 'c': {
      std::string_view aux_colour = optarg;
      if (aux_colour == "red") {
        colour = 1;
      } else if (aux_colour == "yellow") {
        colour = 2;
      } else if (aux_colour == "blue") {
        colour = 3;
      } else if (aux_colour == "magenta") {
        colour = 4;
      }
      break;
    }
    default:
      help();
      return 1;
    }
  }

  screen_size(rows, columns);

  buffer_dinamico.assign(rows + 1, std::vector<char>(columns, ' '));

  int rows_act = rows, columns_act = columns;
  int num_opt = density * columns_act;

  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(0, 255);

  std::vector<Drop> vector_drop;
  for (size_t i = 0; i < num_opt; i++) {

    Drop aux_drop(distrib(gen) % columns, (distrib(gen) % 150 - 150));
    vector_drop.push_back(aux_drop);
  }

  std::cout << "\033[?25l"; // ocultar el cursor

  while (!fin) {
    screen_size(rows, columns);
    if (columns != columns_act || rows != rows_act) {
      buffer_dinamico.assign(rows + 1, std::vector<char>(columns, ' '));

      num_opt = density * columns;
      columns_act = columns;
      rows_act = rows;

      while (num_opt != vector_drop.size()) {
        if (vector_drop.size() < num_opt) {
          Drop aux_drop(distrib(gen) % columns, (distrib(gen) % 150 - 150));
          vector_drop.push_back(aux_drop);
        } else {
          vector_drop.pop_back();
        }
      }
    }

    clear_buffer();
    for (auto &gota : vector_drop) {
      gota.update(rows, columns);
      gota.draw(buffer_dinamico);
    }

    flush_buffer(colour);

    usleep(100000 / speed);
  }

  std::cout << "\e[?25h";
  clear_buffer();
  flush_buffer(colour);
  std::cout << "\033[H";
  return 0;
}

void screen_size(int &rows, int &columns) {
  struct winsize terminal_size;
  ioctl(0, TIOCGWINSZ, &terminal_size);
  rows = terminal_size.ws_row;
  columns = terminal_size.ws_col;
}

void clear_buffer() {
  /*
  for (size_t i = 0; i < rows; i++)
  {
      for (size_t j = 0; j < columns; j++)
      {
          buffer[i][j] = ' ';
      }
  }
  */
  // una forma más rápida de hacerlo cuando usamos el std::vector
  buffer_dinamico.assign(rows + 1, std::vector<char>(columns, ' '));
}

void flush_buffer(const int &colour) {
  std::cout << "\033[H"; // movemos el cursor al origen

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (buffer_dinamico[i][j] == ' ') {
        std::cout << ' ';
      } else {
        if (buffer_dinamico[i + 1][j] == ' ') {
          std::cout << "\033[1;37m" << buffer_dinamico[i][j]; // Blanco
        } else {
          switch (colour) {
          case 0:
            std::cout << "\033[32m";
            break; // Verde
          case 1:
            std::cout << "\033[31m";
            break; // Rojo
          case 2:
            std::cout << "\033[33m";
            break; // Amarillo
          case 3:
            std::cout << "\033[34m";
            break; // Azul
          case 4:
            std::cout << "\033[35m";
            break; // Magenta
          }
          std::cout << buffer_dinamico[i][j];
        }
      }
    }
    std::cout << "\n";
  }
  std::cout << std::flush;
}

void help() {
  std::cout << "Uso de CMatrix Clon:\n";
  std::cout << "  -v <num> : Velocidad (ej: 1, 2, 5). Por defecto: 1\n";
  std::cout << "  -d <num> : Densidad (ej: 0.5, 1.5). Por defecto: 0.8\n";
  std::cout << "  -c <color>: Color (red, yellow, blue, magenta). Por defecto: "
               "verde\n";
  std::cout << "  -h       : Muestra esta ayuda.\n";
}

void manejadora(int sigmun) { fin = 1; }
