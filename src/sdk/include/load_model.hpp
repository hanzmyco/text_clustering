#include "cppjieba/Jieba.hpp"
#include "vectorizer.hpp"
#include <iostream>
#include <fstream>
using namespace std;


class modelLoader{
public:
  modelLoader(string label_path,string center_path){
    this->labels = get_labels(label_path);
    cout<< this->labels;
    cout <<endl<<endl;
    int linesToRead = 10;
    int cols =235;
    this->centers = get_centers(center_path,linesToRead,cols);
    cout<<this->centers;
  }

vector<vector<float>> get_centers(string center_path,int linesToRead,int cols){
  std::ifstream file(center_path, std::ios::in | std::ios::binary);
  vector<vector<float>> dstData;

  for(int i = 0; i < linesToRead; i++)
  {
      vector<float> one_row;
      for(int j = 0; j < cols; j++)
      {
          float data = 0;
            file.read((char *)(&data), sizeof(data));
            one_row.push_back(data);
      }
      dstData.push_back(one_row);
  }
  file.close();
  return dstData;
}


  vector<unsigned int> get_labels(string label_path){
    ifstream label_file(label_path,ios::in|ios::binary|ios::ate);
    char * memblock;
    streampos size;
    if(label_file.is_open()){
      size = label_file.tellg();
      memblock = new char[size];
      label_file.seekg(0,ios::beg);
      label_file.read(memblock,size);
      label_file.close();
    }

    vector<unsigned int> output;
    int mask = 0x000000FF;
    for(int i =0;i<size;i+=4){
      unsigned a = (unsigned int) (memblock[i]);
      a=a&mask;
      //cout << a <<endl;
      unsigned b = (unsigned int) (memblock[i+1]);
      b= (b<<8);
      //cout<<b<<endl;
      unsigned c = (unsigned int) (memblock[i+2]);
      c = (c<<16);
      unsigned d = (unsigned int) (memblock[i+3]);
      d = (d<<24);
      output.push_back(a+b+c+d);
    }
    delete[]memblock;
    return output;
  }
private:
  vector<unsigned int> labels;
  vector<vector<float>>centers;
};
