#include "cppjieba/Jieba.hpp"
#include <iostream>
#include "load_model.hpp"
using namespace std;

int main(int argc, char** argv) {
  /*
  cppjieba::Jieba jieba(DICT_PATH,
        HMM_PATH,
        USER_DICT_PATH,
        IDF_PATH,
        STOP_WORD_PATH);
      */

  modelLoader ml = modelLoader("../labels.test","../centers.test");
//trainingPipeline tp = trainingPipeline("../input_python_debug",5);

  /*
  string s1 = "张亮考上了北京大学，我考上了中专，小李去了当服务员。我们都有光明的前途。";
  string s2 = "小明到底爱不爱小刚？ 我猜他是爱的。";
  string s3 = "我考上了中专，小李子去当了服务员，张亮考上了北京大学，我们都有光明的前途。";
  string s4 = "爱就像老天白云，晴空万里，忽然暴风雨。";
  vector<string> test_input;
  test_input.push_back(s1);
  test_input.push_back(s2);
  test_input.push_back(s3);
  test_input.push_back(s4);
  for (int i =0;i<100;i++){
    test_input.push_back(s4);
  }



  Vectorizer feature = Vectorizer(test_input);
  vector<vector<string>> output = feature.tokenizer();
  cout<<output;



  vector<vector<int>> matrix = feature.build_matrix(5);
  cout<<matrix<<endl;
  cout<<matrix[0]<<endl;
  int row_size = matrix.size();
  int col_size = matrix[0].size();

  KMeansWrapper wrapper = KMeansWrapper(matrix);

  int clusterCount = 3;
  int attempts =3;
  wrapper.kmeans_wrapper(clusterCount,
      TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
         attempts, KMEANS_PP_CENTERS);

  cout<<wrapper.result_labels<<endl;
  */
  return EXIT_SUCCESS;
}
