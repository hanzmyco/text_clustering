#include "cppjieba/Jieba.hpp"
#include <iostream>
#include "inference.hpp"
using namespace std;

int main(int argc, char** argv) {
  string speechTextData = "\n[00:01:26]这是的\n[00:02:10]虽然是头\n[00:05:40]一次\n[00:06:19]和\n[00:07:03]拍砖宽松\n[00:08:97]的\n[00:09:35]适合拍\n[00:10:23]同框";
  string data_source ="weishi";
  speechTextData ="你这么说我就不知道了哈利波特是一个很好的小说。";
  Inference ifer = Inference (speechTextData,data_source);
  int closestCluster = ifer.getLabel();
  cout<<closestCluster<<endl;
  vector<string> keyWords =ifer.getKeywords();
  cout<<keyWords<<endl;
  vector<float> similarityScore = ifer.getDistances();
  cout<<similarityScore<<endl;

  return EXIT_SUCCESS;
}
