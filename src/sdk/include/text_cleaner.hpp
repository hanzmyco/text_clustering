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
     while (head < input_text.length() && tail < input_text.length()){
        while(input_text.at(tail)!=']'){
          tail++;
        }
        if (tail < input_text.length()){
          head=tail+1;
          while (head < input_text.length() && input_text.at(head)!='['){
            head++;
          }
          if (tail+1<input_text.length()){
            output += input_text.substr(tail+1,head);
          }
          cout<<tail<<endl;
          cout<<head<<endl;
          tail=head+1;
        }
     }
     cout<<output<<endl;
   }
 }
};
