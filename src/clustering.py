import config
import read_json
import Vectorizer
import KMeans
import Algorithm
import BaseModel
import read_liulanqi_data
import read_weishi_data

def main():

    data_in=[]
    feed_id=[]
    print('start reading data')
    #read_json.read_json(config.path_in,data_in,config.stop_word_path,feed_id,config.data_lines)

    #read_json.test_alignment_py('../data/cpp/small.txt','../data/cpp/python_alignment_extraction1.txt','stop_words.utf8',True,True,5,data_in)
    #print('finish reading data')

    #term_id = []
    id_url = []
    #read_liulanqi_data.read_data(config.path_in, data_in, id_url,50)

    read_weishi_data.read_json(config.path_in,data_in,None,feed_id,config.data_lines,None,config.topk)


    if config.mode =='Training':
        if config.model_name == 'Counter':
            model = Vectorizer.CounterVector(config.model_name)
        elif config.model_name == 'TfIdf':
            model = Vectorizer.TfIdfVector(config.model_name)
            print('finish initilizing model')
        elif config.model_name =='FeatureHasher':
            model = Vectorizer.FeatureHasherVector(config.model_name,config.n_features)

        model.feature_transform(data_in)
        print(len(model.vectorizer.vocabulary_))

        model.serilize_model()

        if config.algo_name =='KMeans':
            algo_instance = KMeans.KMeansClustering(config.algo_name)
            print('start training model')
            algo_instance.fit(model.feature)
            algo_instance.serilize_model()
            algo_instance.output_cluster_info(data_in,model,feed_id)




    else:
        print('loading vectorizer')
        model=BaseModel.BaseModel(config.model_name)
        model.de_serilize_model()
        print('finish loading vector')


        if config.algo_name =='KMeans':
            algo_instance = Algorithm.Base_Algorithm(config.algo_name)
            algo_instance.de_serilize_model()
            print('finish desirialization')
            features=model.transform(data_in)

            labels=algo_instance.predict(features)
            print(labels)
            #algo_instance.get_centroids()
            #algo_instance.output_cluster_info(data_in, model, feed_id)
            print('finish all')


if __name__ == '__main__':
    main()
