#include <Terminal.h>

int main() {
  terminal term;

  context *cpuContext = (context *)(term.perform("context"));

  std::cout << static_cast<int>(cpuContext->SPU);

  return 0;
}