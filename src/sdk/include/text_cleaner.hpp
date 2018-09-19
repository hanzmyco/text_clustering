#include <fstream>
using namespace std;

class textCleaner{
public:
 textCleaner(string input_text,string data_source){
   if (data_source == "weishi"){
     string delimiter ="]";
     int head=0;
     int tail =0;
     string output="";
     int tag=0;

     for (int i =0;i < input_text.length();i++){
       char iter_char = input_text.at(i);
       if ( iter_char== '['){
         tag=1;
       }
       else if (iter_char==']'){
         tag=0;
       }
       else if(tag==0 && iter_char!='\n' &&iter_char!='\r'){
         output+=iter_char;
       }
     }
     cout<<output<<endl;
   }
 }

};
