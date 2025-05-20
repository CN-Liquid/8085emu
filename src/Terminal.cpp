#include <Terminal.h>
#include <sstream>

terminal::terminal() {
  CPU.reset();

  cEnd.minLength = 1;
  cEnd.maxLength = 1;
  cEnd.function = std::bind(&terminal::fEnd, this);

  cLoad.minLength = 4;
  cLoad.maxLength = 255;
  cLoad.function = std::bind(&terminal::fLoad, this);

  cPrint.minLength = 3;
  cPrint.maxLength = 3;
  cPrint.function = std::bind(&terminal::fPrint, this);

  cReset.minLength = 1;
  cReset.maxLength = 1;
  cReset.function = std::bind(&terminal::fReset, this);

  cExec.minLength = 1;
  cExec.maxLength = 1;
  cExec.function = std::bind(&terminal::fExec, this);

  cCounter.minLength = 3;
  cCounter.maxLength = 3;
  cCounter.function = std::bind(&terminal::fCounter, this);

  cContext.minLength = 1;
  cContext.maxLength = 1;
  cContext.function = std::bind(&terminal::fContext, this);

  cMessage.minLength = 1;
  cMessage.maxLength = 1;
  cMessage.function = std::bind(&terminal::fMessage, this);

  init();
}

terminal::~terminal() {}

void terminal::init() {
  commandRepo["end"] = cEnd;
  commandRepo["load"] = cLoad;
  commandRepo["print"] = cPrint;
  commandRepo["reset"] = cReset;
  commandRepo["context"] = cContext;
  commandRepo["counter"] = cCounter;
  commandRepo["exec"] = cExec;
  commandRepo["message"] = cMessage;
}

void terminal::string_parser() {
  std::istringstream stream(input);
  std::string temp;

  while (getline(stream, temp, delimiter)) {
    token.push_back(temp);
  }
}

void *terminal::input_parser() {
  void *returnPointer = nullptr;
  try {
    if (token.size() == 0) {
    }

    else if (commandRepo.at(token.at(0)).minLength <= token.size() &&
             (commandRepo.at(token.at(0)).maxLength >= token.size())) {

      returnPointer = commandRepo.at(token.at(0)).function();
    }

    else {
      if (enableMessages) {
        std::cout << "Syntax error or missing arguments" << '\n';
      }
    }

  }

  catch (std::out_of_range) {
    if (enableMessages) {
      std::cout << "Command not found" << '\n';
    }
  }

  token.clear();
  return returnPointer;
}

void terminal::get_input() {
  std::cout << ">> ";
  std::getline(std::cin, input);

  string_parser();
  input_parser();
}
void *terminal::fEnd() {
  if (enableMessages) {
    std::cout << "Terminating Program" << '\n';
  }
  exit(0);
  return nullptr;
}

void *terminal::fLoad() {
  if (enableMessages) {
    std::cout << "Loading input to : " << token.at(1) << token.at(2) << "H"
              << '\n';
  }
  byte value1 = std::stoi(token.at(1), nullptr, 16);
  byte value2 = std::stoi(token.at(2), nullptr, 16);
  word memLoc = (value1 << 8) + value2;
  for (int i = 3; i < token.size(); i++) {
    byte data = std::stoi(token.at(i), nullptr, 16);
    CPU.load_DB(data);
    CPU.mem_write(memLoc + i - 3);
  }
  return nullptr;
}

void *terminal::fPrint() {
  if (enableMessages) {
    std::cout << "Printing 8 bytes from : " << token.at(1) << token.at(2) << "H"
              << '\n';
  }
  byte value1 = std::stoi(token.at(1), nullptr, 16);
  byte value2 = std::stoi(token.at(2), nullptr, 16);
  word memLoc = (value1 << 8) + value2;
  if (enableMessages) {
    CPU.print(memLoc);

    std::cout << '\n';
  }
  CPU.mem_read(memLoc);
  CPU.refresh_context();
  return &CPU.cachedContext;
}

void *terminal::fReset() {
  if (enableMessages) {
    std::cout << "Resetting memory and the CPU context" << '\n';
  }
  CPU.reset();
  return nullptr;
}

void *terminal::fExec() {
  CPU.execute();
  return nullptr;
}

void *terminal::fCounter() {
  byte value1 = std::stoi(token.at(1), nullptr, 16);
  byte value2 = std::stoi(token.at(2), nullptr, 16);
  word memLoc = (value1 << 8) + value2;
  CPU.set_PC(memLoc);
  if (enableMessages) {
    std::cout << "The program counter now is : " << std::hex << CPU.get_PC()
              << std::dec << '\n';
  }

  return nullptr;
}

void *terminal::fContext() {
  if (enableMessages) {
    CPU.print_reg();
  }
  CPU.refresh_context();
  return &CPU.cachedContext;
}

void *terminal::fMessage() {
  if (enableMessages) {
    std::cout << "Disabled Messages" << '\n';
    enableMessages = !enableMessages;
  }

  else {
    std::cout << "Enabled Messages" << '\n';
    enableMessages = !enableMessages;
  }
  return nullptr;
}

void *terminal::perform(std::string input) {
  this->input = input;
  string_parser();
  return input_parser();
}