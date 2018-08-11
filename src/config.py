use_hashing = False
model_name="TfIdf"
path_in="../data/subtitle/"
stop_word_path="../data/chinese_stop_words.txt"
algo_name='KMeans'
max_iter=2000
cluster_number=5000
top_terms_file='../data/'+str(cluster_number)+"_clusters_"+str(max_iter)+"_iters_top_terms.txt"
cluster_out_file="../data/"+str(cluster_number)+"_clusters_"+str(max_iter)+"_iters.txt"
n_features=10000
n_components=False
minibatch=None
verbose=False
data_lines=None
model_file_name="../model/"+str(cluster_number)+"_clusters_"+str(max_iter)+"_iters.pkl"
mode = 'Inference'