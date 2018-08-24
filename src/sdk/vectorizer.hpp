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
		this.text = this.readfile(in_path);
	}
	// directly pass in string data
	Vectorizer(vector<string> text){
		this.text=text;
	}

	vector<string> tokenizer(){
		this.tokenized_text=    /*jieba cut here*/ (this.text);

	}


	vector<string> text;

	vector<string> tokenized_text;





private:
	vector<string> readfile(string in_path){
		return null;
	}



}

