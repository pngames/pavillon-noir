#include <iostream>

#include "tests.h"

int main(int ac, char *av[])
{
  test_events();

  char c;
  std::cout << "Appuyez sur une touche pour continuer" << std::endl;
  fread(&c, 1, 1, stdin);

  return 0;
}
