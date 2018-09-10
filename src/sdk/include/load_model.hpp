#include "cppjieba/Jieba.hpp"
#include "vectorizer.hpp"
#include <iostream>
#include <fstream>
#include "kmeans.hpp"
using namespace cv;
using namespace std;

class modelLoader{
public:
  modelLoader(string data_path){
    read_from_path(data_path);
  }

  void read_from_path(string root_path){
    vector<string> lines;
    string line;
    ifstream input_file(root_path);
    while(std::getline(input_file,line)){
      if (line[line.length()-1]=='\r' ||line[line.length()-1]=='\n'){
        lines.push_back(line.erase(line.length()-1));
      }
      else{
        lines.push_back(line);
      }
    }

    this->input_strings = lines ;
  }
};
