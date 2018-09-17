#include "cppjieba/Jieba.hpp"
#include <iostream>
#include "inference.hpp"
#include "text_cleaner.hpp"
using namespace std;

int main(int argc, char** argv) {
  string speechTextData = "丝绸之路是我国买下来的二当家,还有谁,10,150,23,CF,H2";
  speechTextData = "\n[00:01:26]这是的\n[00:02:10]虽然是头\n[00:05:40]一次\n[00:06:19]和\n[00:07:03]拍砖宽松\n[00:08:97]的\n[00:09:35]适合拍\n[00:10:23]同框";
  textCleaner tc = textCleaner(speechTextData,"weishi");
  Inference ifer = Inference (speechTextData);
  int closestCluster = ifer.getLabel();
  cout<<closestCluster<<endl;
  vector<string> keyWords =ifer.getKeywords();
  cout<<keyWords<<endl;
  vector<float> similarityScore = ifer.getDistances();
  cout<<similarityScore<<endl;

  return EXIT_SUCCESS;
}
