#include "showcase/Showcase.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    Showcase::run();
    return 0;
}
