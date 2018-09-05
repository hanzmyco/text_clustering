#include "cppjieba/Jieba.hpp"
#include "vectorizer.hpp"
#include <iostream>
#include <fstream>
#include "kmeans.hpp"
using namespace cv;
using namespace std;

class trainingPipeline{
public:
  trainingPipeline(string root_path,const size_t topk){
    read_from_path(root_path);
    //cout<<this->input_strings<<endl;
    cout<<"begin vetorizing"<<endl;
    Vectorizer feature = Vectorizer(this->input_strings);
    cout<<"finish vetorizing"<<endl;
    this->matrix = feature.build_matrix(topk);
    actual_training();
  }
private:
  vector<string> input_strings;
  vector<vector<int>> matrix;
  void read_from_path(string root_path){
    vector<string> lines;
    string line;
    ifstream input_file(root_path);
    while(std::getline(input_file,line)){
      lines.push_back(line);
    }

    this->input_strings = lines ;
  }

  void actual_training(){
    int row_size = this->matrix.size();
    int col_size = this->matrix[0].size();
    cout<<"still here0"<<endl;
    cout<<row_size<<endl;
    cout<<col_size<<endl;


    KMeansWrapper wrapper = KMeansWrapper(this->matrix);
    cout<<"still here"<<endl;
    int clusterCount = 5;
    int attempts =1;
    wrapper.kmeans_wrapper(clusterCount,
        TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
           attempts, KMEANS_PP_CENTERS);
    cout<<wrapper.result_labels<<endl;
  }

};
