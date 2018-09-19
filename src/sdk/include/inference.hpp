#include "vectorizer.hpp"
#include <iostream>
#include <fstream>
#include "load_model.hpp"
using namespace std;

class Inference{
public:
  Inference(string input_text,string data_source){
    this->input_texts.push_back(input_text);
    string label_path ="../model/labels.test";
    string dictionary_path="../model/feature_dict.txt";
    string center_path="../model/centers.test";
    int linesToRead=10;  // how many clusters in training data
    int cols =235;   //vocabullary size in training

    this-> ml =new modelLoader(label_path,center_path,linesToRead,cols,dictionary_path);

    Vectorizer feature = Vectorizer(this->input_texts,data_source);
    int topk=5;

    vector<vector <string>> multi_line_keywords;
    this->matrix = feature.buildMatrix(topk,this->ml->dictionary,multi_line_keywords);
    this->distance = setDistances();
    this->keywords = multi_line_keywords[0];
  }

  vector<float> setDistances(){
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
    auto minIt = std::min_element(distance.begin(),distance.end());
    int minIndex = minIt - distance.begin();
    this->result_label = minIndex;
    return distance;
  }
  vector<float> getDistances(){
    return this->distance;
  }
  vector<string>getKeywords(){
    return this->keywords;
  }
  int getLabel(){
    return this->result_label;
  }
private:
  vector<string> input_texts;
  vector<vector<float>> matrix;
  modelLoader *ml;
  vector<float> distance;
  int result_label;
  vector<string> keywords;


};
