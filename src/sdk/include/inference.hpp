#include "vectorizer.hpp"
#include <iostream>
#include <fstream>
#include "load_model.hpp"
using namespace std;

class Inference{
public:
  Inference(string input_text,string label_path,string dictionary_path,string center_path,int linesToRead,int cols,){
    this->input_texts.push_back(input_text);
    this-> ml =new modelLoader(label_path,center_path,linesToRead,cols,dictionary_path);
    cout<<this->input_texts;
    Vectorizer feature = Vectorizer(this->input_texts);
    int topk=5;
    this->matrix = feature.build_matrix(topk,this->ml->dictionary);
    cout<<this->matrix<<endl;
    //cout<<this->ml->dictionary<<endl;
    //cout<<this->ml->centers;
    this->distance = distances();
    cout<<this->distance<<endl;
  }

  vector<float> distances(){
    vector<float> feature_vector = this->matrix[0];
    vector<float> distance;
    for (auto it =begin(this->ml->centers);it !=end(this->ml->centers);++it){
      auto feature_vec = begin(feature_vector);
      float sum=0;
      for(auto inner_it = begin(*(it));inner_it!=end(*(it));++inner_it){
            sum+=(*(inner_it) - *(feature_vec))*(*(inner_it) - *(feature_vec));
            feature_vec++;
      }
      //cout<<sum<<endl;
      distance.push_back(sum);
    }
    return distance;
  }
private:
  vector<string> input_texts;
  vector<vector<float>> matrix;
  modelLoader *ml;
  vector<float> distance;

};
