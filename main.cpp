#include <iostream>
#include "UPGMABuilder.hpp"

using namespace std;

int main(){
  UPGMABuilder u("infile.grid");
  u.g.print();
  u.makeTree();
  return 0;
}
