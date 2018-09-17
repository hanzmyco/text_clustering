#include "cppjieba/Jieba.hpp"
#include <fstream>
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
		this->tokenized_text=tokenizer();
	}
	// directly pass in string data
	Vectorizer(vector<string> text){
		this->text=text;
		init_jieba();
		this->tokenized_text=tokenizer();
		}

	vector<vector<string>> Keyword_Extractor(const size_t topk){

		vector<vector<string>> output;

		for (auto it =begin(this->tokenized_text);it !=end(this->tokenized_text);++it){
			vector<string> keywords;
			jieba->extractor.Extract(*it, keywords, topk);
			output.push_back(keywords);
		}
		return output;
	}

	vector<string> tokenizer(){
		vector<string>output;
		std::set<string> stopwords = load_stopwords(STOP_WORD_PATH);

		for (auto it =begin(this->text);it !=end(this->text);++it){
			vector<string> words;
			jieba->Cut(*it, words, true);
			string filtered_words="";
			for(auto word =begin(words);word != end(words);++word){
				if (stopwords.find(*word) ==stopwords.end())
				{
					filtered_words+=" "+*word;
				}
			}
			output.push_back(filtered_words);
		}
		return output;
	}

	vector<vector<float>> buildMatrix(const size_t topk, std::map<string,int>dictionary,vector<vector<string>> &keywords){
		vector<vector<float>>matrix;
		//vector<vector<string>> keywords=this->Keyword_Extractor(topk);

		keywords = this->Keyword_Extractor(topk);

		for (auto it1 = begin(keywords);it1!=end(keywords);++it1)
		{

			vector<float>row (dictionary.size(),0);
			for (auto it2 = begin(*it1);it2!=end(*it1);++it2)
			{
				std::map<string,int>::iterator iter;
				iter=dictionary.find(*it2);
				if (iter != dictionary.end()){
					row[dictionary[*it2]]=1.0;
				}
			}

			matrix.push_back(row);
		}
		return matrix;
	}



	std::map<string, int> build_dictionary(vector<vector<string>> keywords){
		std::map<string, int> dictionary;
		cout<<"begin to build dictionary"<<endl;
		int index=0;
		for (auto it1 = begin(keywords);it1!=end(keywords);++it1){
			for (auto it2 = begin(*it1);it2!=end(*it1);++it2){
				std::pair<std::map<string,int>::iterator,bool> ret;
			  ret=dictionary.insert(std::pair<string,int>(*it2,index));
				if (ret.second==true){
					index++;
				}
			}
		}
		return dictionary;
	}


	vector<string> text;

	vector<string> tokenized_text;

	cppjieba::Jieba * jieba;

private:
	std::set<string> load_stopwords(string stop_word_file){
		string line;
		std::set<string> stop_words_list;
		ifstream input_file(stop_word_file);
    while(std::getline(input_file,line)){
			if (line[line.length()-1]=='\r' ||line[line.length()-1]=='\n'){
        stop_words_list.insert(line.erase(line.length()-1));
      }
      else{
        stop_words_list.insert(line);
      }
    }
		return stop_words_list;
	}
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
