#include <Terminal.h>

int main() {
  terminal term;

  while (1) {
    term.get_input();
  }

  return 0;
}