#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

class KMeansWrapper {
public:
  KMeansWrapper(vector<vector<int>> matrix){
    this->feature = matrix;
    int row_size = matrix.size();
    int col_size = matrix[0].size();
    cout<<"initilizing kmeans"<<endl;
    this->points =new Mat(matrix.size(),matrix[0].size(),CV_32F);
    for(int i =0;i<matrix.size();i++){
      for (int j =0;j<matrix[0].size();j++){
        (*(this->points)).at<float>(i,j) = float(matrix[i][j]);
      }
    }
  }

  double kmeans_wrapper(int 	K_clusters,TermCriteria 	criteria,int 	attempts,int 	flags){

    Mat labels;
    cout<<"still running"<<endl;
    Mat centers;

    double accuracy = kmeans(*points, K_clusters, labels,
        criteria,attempts, KMEANS_PP_CENTERS, centers);

    this->result_labels=labels;
    this->centers = centers;
  }
void printLabels(){
  cout<<this->result_labels;
}
void printCenters(){
  cout<<this->centers;
}
void saveLabels(string file_name){
  FileStorage fs(file_name,cv::FileStorage::WRITE);
  fs<<"result_labels" <<this->result_labels;
}
void saveCenters(string file_name){
  FileStorage fs(file_name,cv::FileStorage::WRITE);
  fs<<"centers" << this->centers;
}

private:
  vector<vector<int>> feature;
  Mat *points;
  Mat result_labels;
  Mat 	centers;
};
