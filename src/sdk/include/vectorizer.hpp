#include "cppjieba/Jieba.hpp"

using namespace std;

const char* const DICT_PATH = "../dict/jieba.dict.utf8";
const char* const HMM_PATH = "../dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../dict/user.dict.utf8";
const char* const IDF_PATH = "../dict/idf.utf8";
const char* const STOP_WORD_PATH = "../dict/stop_words.utf8";

/*utf8*/
class Vectorizer {
public:
	//  can pass in both file or a single point of data
	Vectorizer(string in_path){
		this->text = readfile(in_path);
		init_jieba();
	}
	// directly pass in string data
	Vectorizer(vector<string> text){
		this->text=text;
		init_jieba();
	}

	vector<vector<string>> Keyword_Extractor(const size_t topk){
		cout << "[demo] Keyword Extraction" << endl;
	  //const size_t topk = 5;
	  //vector<cppjieba::KeywordExtractor::Word> keywordres;
		vector<string> keywords;

		//vector<vector<cppjieba::KeywordExtractor::Word>> output;
		vector<vector<string>> output;

		for (auto it =begin(this->text);it !=end(this->text);++it){
			jieba->extractor.Extract(*it, keywords, topk);

		  //cout << *it << endl;
			output.push_back(keywords);
		}
		//cout << keywords << endl;

		return output;
	}

	vector<vector<string>> tokenizer(){
		vector<vector<string>>output;
		for (auto it =begin(this->text);it !=end(this->text);++it){
			vector<string> words;
			jieba->Cut(*it, words, true);
			output.push_back(words);
			cout << limonp::Join(words.begin(), words.end(), "/") << endl;
		}
		return output;
	}

	std::map<string, int> build_dictionary(vector<vector<string>> keywords){
		std::map<string, int> dictionary;
		cout<<"begin to print dictionary"<<endl;
		int index=0;
		for (auto it1 = begin(keywords);it1!=end(keywords);++it1){
			for (auto it2 = begin(*it1);it2!=end(*it1);++it2){
				//cout<<*it2<<endl;
				std::pair<std::map<string,int>::iterator,bool> ret;
			  ret=dictionary.insert(std::pair<string,int>(*it2,index));
				if (ret.second==true){
					index++;
				}
			}

		}
		for (auto it : dictionary){
			cout<<it.first << " " << it.second <<endl;
		}
		return dictionary;
	}

	std::vector<vector<int>> vector_maker(){
		vector<vector<string>> output = this.Keyword_Extractor(5);
	  cout<<output<<endl;
	  //feature.tokenizer();
	  /* after this step, we have a dicitonary to count term frequency*/
	  std::map<string, int> dic=this.build_dictionary(output);
		vector<vector<int>> vector_output;

		for(auto it1 = begin(output);it1!=end(output);++it1){
			vector<int> inner_vector;
			for(auto it2 = begin(*it1);it2!=end(*ite1);++it2){
				inner_vector.push_back(dictionary.find(*it2))
			}
		}
		return vector_output;
	}


	vector<string> text;

	vector<string> tokenized_text;

	cppjieba::Jieba * jieba;

private:
	vector<string> readfile(string in_path){
		vector<string> a;
		return a;
	}

	void init_jieba(){
		this->jieba=new cppjieba::Jieba(DICT_PATH,
	        HMM_PATH,
	        USER_DICT_PATH,
	        IDF_PATH,
	        STOP_WORD_PATH);
	}
};
