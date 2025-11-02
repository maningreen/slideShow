#include "include.h"
#include <cstdlib>
#include <string>

// assumed to be 
//  | either #XXXXXX
//  | or      XXXXXX
// when invalid returns `TRANSPARENT`
Color hexToCol(std::string s) {
  if(s.front() == '#')
    s.erase(0, 1);
  if(s.size() != 6)
    return TRANSPARENT;
  unsigned char r = 0, g = 0, b = 0;
  s.insert(4, " ");
  s.insert(2, " ");
  r = std::stoi(s.c_str(), nullptr, 16);
  g = std::stoi(s.c_str() + 3, nullptr, 16);
  b = std::stoi(s.c_str() + 5, nullptr, 16);
  return {
    r,
    g,
    b,
    255
  };
}
