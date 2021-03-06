#include "cppjieba/Jieba.hpp"
#include "cppjieba/vectorizer.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;

/*
const char* const DICT_PATH = "../dict/jieba.dict.utf8";
const char* const HMM_PATH = "../dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../dict/user.dict.utf8";
const char* const IDF_PATH = "../dict/idf.utf8";
const char* const STOP_WORD_PATH = "../dict/stop_words.utf8";
*/
int main(int argc, char** argv) {
  cppjieba::Jieba jieba(DICT_PATH,
        HMM_PATH,
        USER_DICT_PATH,
        IDF_PATH,
        STOP_WORD_PATH);
  vector<string> words;
  vector<cppjieba::Word> jiebawords;
  string s;
  string result;

  s = "他来到了网易杭研大厦";
  cout << s << endl;
  cout << "[demo] Cut With HMM" << endl;
  jieba.Cut(s, words, true);
  cout << limonp::Join(words.begin(), words.end(), "/") << endl;

  cout << "[demo] Cut Without HMM " << endl;
  jieba.Cut(s, words, false);
  cout << limonp::Join(words.begin(), words.end(), "/") << endl;

  s = "我来到北京清华大学";
  cout << s << endl;
  cout << "[demo] CutAll" << endl;
  jieba.CutAll(s, words);
  cout << limonp::Join(words.begin(), words.end(), "/") << endl;

  s = "小明硕士毕业于中国科学院计算所，后在日本京都大学深造";
  cout << s << endl;
  cout << "[demo] CutForSearch" << endl;
  jieba.CutForSearch(s, words);
  cout << limonp::Join(words.begin(), words.end(), "/") << endl;

  cout << "[demo] Insert User Word" << endl;
  jieba.Cut("男默女泪", words);
  cout << limonp::Join(words.begin(), words.end(), "/") << endl;
  jieba.InsertUserWord("男默女泪");
  jieba.Cut("男默女泪", words);
  cout << limonp::Join(words.begin(), words.end(), "/") << endl;

  cout << "[demo] CutForSearch Word With Offset" << endl;
  jieba.CutForSearch(s, jiebawords, true);
  cout << jiebawords << endl;

  cout << "[demo] Lookup Tag for Single Token" << endl;
  const int DemoTokenMaxLen = 32;
  char DemoTokens[][DemoTokenMaxLen] = {"拖拉机", "CEO", "123", "。"};
  vector<pair<string, string> > LookupTagres(sizeof(DemoTokens) / DemoTokenMaxLen);
  vector<pair<string, string> >::iterator it;
  for (it = LookupTagres.begin(); it != LookupTagres.end(); it++) {
	it->first = DemoTokens[it - LookupTagres.begin()];
	it->second = jieba.LookupTag(it->first);
  }
  cout << LookupTagres << endl;

  cout << "[demo] Tagging" << endl;
  vector<pair<string, string> > tagres;
  s = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";
  jieba.Tag(s, tagres);
  cout << s << endl;
  cout << tagres << endl;

  cout << "[demo] Keyword Extraction" << endl;
  const size_t topk = 5;
  vector<cppjieba::KeywordExtractor::Word> keywordres;
  jieba.extractor.Extract(s, keywordres, topk);
  cout << s << endl;
  cout << keywordres << endl;

  string s1 = "张亮考上了北京大学，我考上了中专，小李去了当服务员。我们都有光明的前途。";
  string s2 = "小明到底爱不爱小刚？ 我猜他是爱的。";
  string s3 = "我考上了中专，小李子去当了服务员，张亮考上了北京大学，我们都有光明的前途。";
  string s4 = "爱就像老天白云，晴空万里，忽然暴风雨。";
  vector<string> test_input;
  test_input.push_back(s1);
  test_input.push_back(s2);
  test_input.push_back(s3);
  test_input.push_back(s4);


  Vectorizer feature = Vectorizer(test_input);
  //vector<vector<string>> output = feature.Keyword_Extractor(5);
  //cout<<output<<endl;
  //feature.tokenizer();
  //std::map<string, int> dic=feature.build_dictionary(output);
  vector<vector<int>> matrix = feature.build_matrix(5);
  cout<<matrix<<endl;
  cout<<matrix[0]<<endl;
  int row_size = matrix.size();
  int col_size = matrix[0].size();



















  return EXIT_SUCCESS;










}
