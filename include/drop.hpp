#ifndef __DROP__
#define __DROP__

#include <vector>

class Drop {
private:
  // Aquí irán las variables de estado (posición, velocidad, longitud...)
  int x;
  int y;
  int length;
  int speed;
  char secuencia[30];

public:
  // Constructor
  Drop(int startX, int startY);

  void update(const int &rows,
              const int &columns); // Calcula la siguiente posición
  void draw(std::vector<std::vector<char>>
                &matrix); // Dibuja la gota (modifica la matriz de pantalla)
};

#endif
