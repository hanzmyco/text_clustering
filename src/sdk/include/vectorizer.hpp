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

		//vector<vector<cppjieba::KeywordExtractor::Word>> output;
		vector<vector<string>> output;

		for (auto it =begin(this->text);it !=end(this->text);++it){
			vector<string> keywords;
			jieba->extractor.Extract(*it, keywords, topk);
			output.push_back(keywords);
		}
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

	vector<vector<int>> build_matrix(const size_t topk){
		vector<vector<int>>matrix;
	  vector<vector<string>> keywords=this->Keyword_Extractor(topk);
		std::map<string, int> dictionary = this->build_dictionary(keywords);
		cout<<keywords<<endl;


		for (auto it1 = begin(keywords);it1!=end(keywords);++it1)
		{
			vector<int>row (dictionary.size(),0);
			for (auto it2 = begin(*it1);it2!=end(*it1);++it2)
			{
				cout<<*it2<<" ";
				std::map<string,int>::iterator iter;
				iter=dictionary.find(*it2);
				if (iter != dictionary.end()){
					row[dictionary[*it2]]=1;
				}	
			}

			matrix.push_back(row);
		}

		return matrix;

	}



	std::map<string, int> build_dictionary(vector<vector<string>> keywords){
		std::map<string, int> dictionary;
		cout<<"begin to print dictionary"<<endl;
		int index=0;
		for (auto it1 = begin(keywords);it1!=end(keywords);++it1){
			for (auto it2 = begin(*it1);it2!=end(*it1);++it2){
				cout<<*it2<<endl;
				std::pair<std::map<string,int>::iterator,bool> ret;
			  ret=dictionary.insert(std::pair<string,int>(*it2,index));
				if (ret.second==true){
					index++;
				}
			}

		}
		/*
		for (auto it : dictionary){
			cout<<it.first << " " << it.second <<endl;
		}
		*/
		return dictionary;
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
