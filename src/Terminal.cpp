#include <Terminal.h>
#include <sstream>

terminal::terminal() {
  CPU.reset();

  cEnd.minLength = 1;
  cEnd.maxLength = 1;
  cEnd.function = std::bind(&terminal::fEnd, this);

  cLoad.minLength = 4;
  cLoad.maxLength = 256;
  cLoad.function = std::bind(&terminal::fLoad, this);

  cPrint.minLength = 3;
  cPrint.maxLength = 3;
  cPrint.function = std::bind(&terminal::fPrint, this);

  cReset.minLength = 1;
  cReset.maxLength = 1;
  cReset.function = std::bind(&terminal::fReset, this);

  init();
}

terminal::~terminal() { delete &CPU; }

void terminal::init() {
  commandRepo["end"] = cEnd;
  commandRepo["load"] = cLoad;
  commandRepo["print"] = cPrint;
  commandRepo["reset"] = cReset;
}

void terminal::fEnd() {
  std::cout << "Terminating Program" << '\n';
  exit(0);
}

void terminal::fLoad() {
  std::cout << "Loading input to : " << token.at(1) << token.at(2) << "H"
            << '\n';
  byte value1 = std::stoi(token.at(1), nullptr, 16);
  byte value2 = std::stoi(token.at(2), nullptr, 16);
  word memLoc = (value1 << 8) + value2;
  for (int i = 3; i < token.size(); i++) {
    byte data = std::stoi(token.at(i), nullptr, 16);
    CPU.load_DB(data);
    CPU.mem_write(memLoc + i - 3);
  }
}

void terminal::fPrint() {
  std::cout << "Printing 8 bytes from : " << token.at(1) << token.at(2) << "H"
            << '\n';
  byte value1 = std::stoi(token.at(1), nullptr, 16);
  byte value2 = std::stoi(token.at(2), nullptr, 16);
  word memLoc = (value1 << 8) + value2;
  CPU.print(memLoc);
  std::cout << '\n';
}

void terminal::fReset() {
  std::cout << "Resetting memory and the CPU context" << '\n';
  CPU.reset();
}

void terminal::string_parser() {
  std::istringstream stream(input);
  std::string temp;

  while (getline(stream, temp, delimiter)) {
    token.push_back(temp);
  }
}

void terminal::input_parser() {

  try {
    if (token.size() == 0) {
      return;
    }

    else if (commandRepo.at(token.at(0)).minLength <= token.size() &
             (commandRepo.at(token.at(0)).maxLength >= token.size())) {
      commandRepo.at(token.at(0)).function();
    }

    else {
      std::cout << "Command incomplete or missing arguments" << '\n';
    }

  }

  catch (std::out_of_range) {
    std::cout << "Invalid Command" << '\n';
  }
}

void terminal::get_input() {
  std::cout << ">> ";
  std::getline(std::cin, input);

  string_parser();
  input_parser();
  token.clear();
}
