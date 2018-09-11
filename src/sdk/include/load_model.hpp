#include "cppjieba/Jieba.hpp"
#include "vectorizer.hpp"
#include <iostream>
#include <fstream>
#include "kmeans.hpp"
#include "labels.pb.h"
using namespace cv;
using namespace std;
using namespace labels;

class modelLoader{
public:
  modelLoader(string data_path){
    GOOGLE_PROTOBUF_VERSION;
    labels::labels label_vector;
    fstream input(data_path,ios::in|ios::binary);
    if(!input){
      cout<< data_path<<": not found"<<endl;
    }
    else if (!label_vector.ParseFromIstream(&input)){
      cerr << "failed to parse address book. " << endl;
      return -1;
    }
    cout<<label_vector.points();
    return label_vector;

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
