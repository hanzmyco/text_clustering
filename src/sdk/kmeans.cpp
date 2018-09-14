#include "cppjieba/Jieba.hpp"
#include <iostream>
#include "inference.hpp"
//#include "load_model.hpp"
//#include "vectorizer.hpp"
using namespace std;

int main(int argc, char** argv) {
  Inference ifer = Inference ("丝绸之路是我国买下来的二当家，还有谁,10,150,23,CF,H2","../labels.test","../feature_dict.txt","../centers.test",10,235);

/*
modelLoader ml = modelLoader("../labels.test","../centers.test",50,235,"../feature_dict.txt");
vector<string>input_texts;
string input_text = "丝绸之路是我国买下来的二当家，还有谁";
input_texts.push_back(input_text);
Vectorizer feature = Vectorizer(input_texts);
int topk=5;
vector<vector<float>> matrix;
cout<<"here"<<endl;
cout<<ml.dictionary;
matrix = feature.build_matrix(topk,ml.dictionary);
cout<<matrix;
*/

  return EXIT_SUCCESS;
}
