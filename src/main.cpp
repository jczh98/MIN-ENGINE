#include <iostream>
#include <vector>
#include <string>

struct Options {

};

void InitOptions(Options options) {

}

void CleanUp() {

}

bool ParseFile(const std::string &basic_string) {
  return false;
}

int main(int argc, char *argv[]) {
  Options options;
  std::vector<std::string> filenames;
  // Handle parameter parser
  InitOptions(options);
  // Handle scene description
  if (filenames.size() == 0) {
    // Parse from standard input
    ParseFile("-");
  } else {
    // Parse from custom input file
    for (const std::string &f : filenames) {
      if (!ParseFile(f)) {
        fprintf(stderr, "Couldn't open scence file \"%s\"\n", f.c_str());
      }
    }
  }
  CleanUp();
  return 0;
}