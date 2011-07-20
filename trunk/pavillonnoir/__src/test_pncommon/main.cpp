#include <iostream>

#include "tests.h"

#include "pndefs.h"
#include "pnresources.h"

using namespace PN;

int main(int ac, char *av[])
{
  std::cout << PNResourcesManager::getInstance()->convertPath(PNRT_texture, "D:\\projets\\pavillonnoir\\gna\\pavillonnoir\\__binaries\\datafiles\\non-free\\textures\\bed_sn02.bmp") << std::endl;

  char c;
  std::cout << "Appuyez sur une touche pour continuer" << std::endl;
  fread(&c, 1, 1, stdin);

  return 0;
}
