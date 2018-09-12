#include "cppjieba/Jieba.hpp"
#include "vectorizer.hpp"
#include <iostream>
#include <fstream>
//#include "kmeans.hpp"

//using namespace cv;
using namespace std;


class modelLoader{
public:
  modelLoader(string label_path,string center_path){
    ifstream label_file(label_path,ios::in|ios::binary|ios::ate);
    char * memblock;
    streampos size;
    if(label_file.is_open()){
      size = label_file.tellg();
      memblock = new char[size];
      label_file.seekg(0,ios::beg);
      label_file.read(memblock,size);
      label_file.close();
    }
    cout<<memblock[0];
    delete[]memblock;

  }
  /*
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
  }*/
};
