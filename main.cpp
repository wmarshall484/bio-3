#include <iostream>
#include "UPGMABuilder.hpp"
#include "NeighborJoiner.hpp"

using namespace std;


int main(){
  NeighborJoiner n("testfile.grid");
  //u.g.print();
  cout<<n.g.groups.size()<<endl;
  n.makeTree();
  cout<<n.g.groups.size()<<endl;
  n.printTree();

  /*UPGMABuilder u("infile.grid");
  //u.g.print();
  cout<<u.g.groups.size()<<endl;
  u.makeTree();
  cout<<u.g.groups.size()<<endl;
  u.printTree();*/
  return 0;
}
