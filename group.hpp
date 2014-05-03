#ifndef __GROUP
#define __GROUP

/* The group object can be thought of as a node in a binary tree that
   either references two interior nodes (groups), and interior and a
   leaf, or two leafs. Each group has a height associated with it,
   which is equal to half the distance between its two subgroups. The
   left and right weights are equal to (height/2)-left_weight and
   (height/2)-right_weight, respectively. */

#include <vector>
#include <utility>
#include <string>
#include <sstream>

using namespace std;

class group{
  /* Counter for group ids */
  static int global_count;
public:
  bool is_leaf;

  /*Vars for if node is not a leaf */
  double height;
  group *left, *right;
  double left_weight, right_weight;
  vector<group *> leafs;

  /* Unique group id. Auto increments. */
  int group_id;

  /* If node is a leaf */
  string s;
  //group *leaf;

  group(){
  }

  group(string _s){
    s=_s;
    height=0;
    left=NULL; right=NULL;
    left_weight=0; right_weight=0;
    leafs=vector<group *>();
    is_leaf=true;
    leafs.push_back(this);
    //cout<<leafs[0]->s<<endl;
    group_id=global_count++;
  }

  group(group *g1, group *g2, double _height):left(g1), right(g2){
    //cout<<"Making group dist/2 is "<<_height<<endl;
    group_id=global_count++;
    is_leaf=false;
    height=_height;
    left=g1;
    right=g2;
    left_weight=height-left->height;
    right_weight=height-right->height;
    
    //Populate list of leafs contained in tree
    for(uint i = 0; i < left->leafs.size(); i++){
      leafs.push_back(left->leafs[i]);
    }

    for(uint i = 0; i < right->leafs.size(); i++){
      leafs.push_back(right->leafs[i]);
    }
  }

  //group& operator=(const group &r) const{
    
  //}

};


/* Initialize the global count of groups to zero */
int group::global_count=0;

/* struct that contains operator that can compare std::pairs of groups */

struct pairGroupComp{
  bool operator()(const pair<group *, group *> &pg1, const pair<group *, group *> &pg2) const {
    stringstream ss1, ss2;
    ss1<<pg1.first->group_id<<pg1.second->group_id;
    ss2<<pg2.first->group_id<<pg2.second->group_id;
    return ss1.str()<ss2.str();
  }
};

#endif
