#include <8085.h>

struct command {
  int minLength;
  int maxLength;
  std::function<void(void)> function;
};

class terminal {
  emu8085 CPU;

  std::unordered_map<std::string, command> commandRepo;

  std::vector<std::string> token;

  std::string input;

  char delimiter = ' ';

  void init();

  command cEnd;
  command cLoad;
  command cPrint;
  command cReset;

  void fEnd();
  void fLoad();
  void fPrint();
  void fReset();

  void string_parser();

  void input_parser();

public:
  terminal();
  ~terminal();

  // void perform(std::vector<std::string> token);

  void get_input();
};