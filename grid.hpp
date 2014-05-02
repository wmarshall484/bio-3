#ifndef __GRID
#define __GRID

/* The grid object takes a filename of a grid. */

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
  vector<group> groups;
  map<pair<group, group>, double, pairGroupComp> weight_pool;

  grid(string _infile):infile(_infile){
    parse(infile);
  }
  
  void setAndParse(string _infile){
    infile = _infile;
    groups.clear();
    weight_pool.clear();
    parse(infile);
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
    for(int i = 0; i < lines.size();i++){
      groups.push_back(group(lines[i].first));
    }

    /* Ensure that the weight in the i-th j-th position are what the
       i-th j-th and j-th i-th group map to */
    for(int i = 0; i < lines.size(); i++){
      for(int j = 0; j < lines[i].second.size(); j++){
	pair<group, group> gp_tmp(groups[i], groups[j]);
	pair<group, group> gp_tmp2(groups[j], groups[i]);
	weight_pool[gp_tmp] = lines[i].second[j];
	weight_pool[gp_tmp2] = lines[i].second[j];
      }
    }
    
    /* Uncomment to print */

    /*for(int i = 0; i < groups.size()-1;i++){
      cout<<groups[i].s<<" ";
      for(int j = i+1; j < groups.size();j++){
	cout<<weight_pool[pair<group, group>(groups[i], groups[j])]<<" ";
      }
      cout<<endl;
      }*/
  }

};


#endif