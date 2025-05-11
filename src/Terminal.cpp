#include <8085.h>
#include <sstream>
#include <string>
#include <vector>
emu8085 CPU;
void string_parser(std::string &input, std::vector<std::string> &token,
                   char delimiter);

void input_parser(std::vector<std::string> &input);

int main() {

  CPU.reset();

  std::string input;
  std::vector<std::string> token;
  char delimiter = ' ';
  while (1) {
    std::cout << ">> ";
    std::getline(std::cin, input);
    string_parser(input, token, delimiter);
    input_parser(token);
    token.clear();
  }

  return 0;
}

void input_parser(std::vector<std::string> &token) {
  if (token.at(0).compare("end") == 0) {
    exit(0);
  } else if (token.at(0).compare("load") == 0) {
    byte value1 = std::stoi(token.at(1), nullptr, 16);
    byte value2 = std::stoi(token.at(2), nullptr, 16);
    word memLoc = (value1 << 8) + value2;
    for (int i = 3; i < token.size(); i++) {
      byte data = std::stoi(token.at(i), nullptr, 16);
      CPU.load_DB(data);
      CPU.mem_write(memLoc + i - 3);
    }
  } else if (token.at(0).compare("print") == 0) {
    byte value1 = std::stoi(token.at(1), nullptr, 16);
    byte value2 = std::stoi(token.at(2), nullptr, 16);
    word memLoc = (value1 << 8) + value2;
    CPU.print(memLoc);
    std::cout << '\n';
  }

  else if (token.at(0).compare("exec") == 0) {
    byte value1 = std::stoi(token.at(1), nullptr, 16);
    byte value2 = std::stoi(token.at(2), nullptr, 16);
    word programCounter = (value1 << 8) + value2;
    CPU.set_PC(programCounter);
    CPU.execute();
  } else if (token.at(0).compare("context") == 0) {
    CPU.print_reg();
  }
}

void string_parser(std::string &input, std::vector<std::string> &token,
                   char delimiter) {
  std::istringstream stream(input);
  std::string temp;

  while (getline(stream, temp, delimiter)) {
    token.push_back(temp);
  }
}