#ifndef __GRID
#define __GRID

/* The grid object takes a filename of a grid, turns each line in the
   grid into a group, and makes a map of groups to weights. */

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "group.hpp"

using namespace std;

class grid{
public:
  string infile;
  vector<group *> groups;
  map<pair<group *, group *>, double, pairGroupComp> weight_pool;

  grid(string _infile):infile(_infile){
    parse(infile);
    //for(int i = 0; i < groups.size()-1;i++){
      //group g=*(groups[i].leafs[0]);
      //pair<group,group> gp(*(groups[i].leafs[0]), *(groups[i+1].leafs[0]));
      //cout<<gp.first.s<<endl;
      //cout<<g.s<<endl;
    //}
  }
  
  void setAndParse(string _infile){
    infile = _infile;
    groups.clear();
    weight_pool.clear();
    parse(infile);
  }

  /* Returns the distance between two groups */
  double groupDistance(group *g1, group *g2){
    /*for(int i = 0; i < g1->leafs.size();i++){
      cout<<g1->leafs[i]->group_id<<endl;
    }
    cout<<endl;

    for(int i = 0; i < g2->leafs.size();i++){
      cout<<g2->leafs[i]->group_id<<endl;
    }
    exit(0);*/
    //cout<<"Got here"<<endl<<flush;
    int n = g1->leafs.size()+g2->leafs.size();
    double total_distance=0;
    for(vector<group *>::iterator i=g1->leafs.begin(); i!=g1->leafs.end();i++){
      for(vector<group *>::iterator j=g2->leafs.begin(); j!=g2->leafs.end();j++){
	pair<group*, group*> gp(*i,*j);
	if(weight_pool.find(gp)==weight_pool.end()){
	  cout<<"Could not find entry for groups "<<gp.first->group_id<<" "<<gp.second->group_id<<endl;
	  exit(0);
	}
	//cout<<"Got here"<<endl<<flush;
	total_distance+=weight_pool[gp];
      }
    }
    return total_distance/(double)n;
  }

  /* Prints IDs and weight matrix */
  void print(){
    for(uint i = 0; i < groups.size()-1;i++){
      //cout<<groups[i].s<<" "<<endl<<flush;
      for(uint j = i+1; j < groups.size();j++){
	pair<group *, group *> gp(groups[i]->leafs[0], groups[j]->leafs[0]);
	cout<<weight_pool[gp]<<" ";
      }
      cout<<endl;
    }
    
  }

private:

  /* Assumed format is lower triangular */
  void parse(string in){
    ifstream ifile(in.c_str());
    if(!ifile.is_open()){
      cout<<"Could not open file"<<endl;
      exit(0);
    }
    string line;
    /* each line is an ID followed by weights. Format is lower-triangular */
    vector<pair<string, vector<double> > > lines;

    /* This code is agnostic of the first line indicating the number
       of ids, this getline throws away that input */
    getline(ifile, line);
    while(getline(ifile, line)){
      stringstream ss(line);
      string id;
      ss>>id;
      /* vector of weights */
      vector<double> vd_tmp;
      while(ss.good()){
	
	/* Sometimes there are spurious characters at the end of the
	   line, so ss.good() doesn't return false. In that case, only
	   continue if ss.good() AND it has a double. Java's
	   hasNextDouble() would have come in handy :/ */

	double d_tmp=-1;
	ss>>d_tmp;
	if(d_tmp==-1)
	  break;
	vd_tmp.push_back(d_tmp);
      }
      lines.push_back(pair<string, vector<double> >(id, vd_tmp));
    }
    
    /* Turn line IDs into groups and put them in a vector, preserving
       line-order */
    for(uint i = 0; i < lines.size();i++){
      groups.push_back(new group(lines[i].first));
    }

    /* Ensure that the weight in the i-th j-th position are what the
       i-th j-th and j-th i-th group map to */
    for(uint i = 0; i < lines.size(); i++){
      for(uint j = 0; j < lines[i].second.size(); j++){
	pair<group *, group *> gp_tmp(groups[i], groups[j]);
	pair<group *, group *> gp_tmp2(groups[j], groups[i]);
	weight_pool[gp_tmp] = lines[i].second[j];
	weight_pool[gp_tmp2] = lines[i].second[j];
	//cout<<"Just added "<<groups[i]->group_id<<" "<<groups[j]->group_id<<" ";
	//cout<<"value is: "<<weight_pool[gp_tmp]<<endl;
      }
    }
  }

};


#endif
