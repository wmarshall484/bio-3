#include <iostream>
#include "UPGMABuilder.hpp"
#include "NeighborJoiner.hpp"

using namespace std;


int main(int argc, char ** argv){
  if(argc!=3){
    cout<<"USAGE:./main <treetype> <infile.grid>"<<endl;
    cout<<"treetype is either 0 for UPGMA tree or 1 for Neighbor joining tree"<<endl;
    cout<<"infile.grid is a valid grid file"<<endl;
    exit(0);
  }
  if(atoi(argv[1])==0){
    UPGMABuilder u(argv[2]);
    u.makeTree();
    u.printTree();
  }

  else if(atoi(argv[1])==1){
    NeighborJoiner n(argv[2]);
    n.makeTree();
    n.printTree();
  }
  else {
    cout<<"Invalid tree type. Enter either 0 or 1."<<endl;
    exit(0);
  }
  return 0;
}
