from sklearn.decomposition import TruncatedSVD
from sklearn.preprocessing import Normalizer
from sklearn.pipeline import make_pipeline
import config
from sklearn.externals import joblib

class BaseModel(object):
    def __init__(self,model=None):
        self.model = model

    def feature_transform(self,data_in):
        self.feature = self.vectorizer.fit_transform(data_in)

        if config.n_components:
            svd = TruncatedSVD(config.n_components)
            normalizer = Normalizer(copy=False)
            lsa = make_pipeline(svd, normalizer)
            self.feature = lsa.fit_transform(self.feature)

    def serilize_model(self):
        #joblib.dump(self.vectorizer,config.vectorizer_file_name,compress=True)
        #print('stop here')
        with open(config.feature_dic_path,'w',encoding='utf-8') as f:
            for key,value in self.vectorizer.vocabulary_.items():
                f.write(key+':')
                f.write(str(value))
                f.write('\n')




    def de_serilize_model(self):
        self.vectorizer = joblib.load(config.vectorizer_file_name)

    def transform(self,data_in):
        feature = self.vectorizer.transform(data_in)

        if config.n_components:
            svd = TruncatedSVD(config.n_components)
            normalizer = Normalizer(copy=False)
            lsa = make_pipeline(svd, normalizer)
            return lsa.fit_transform(feature)
        else:
            return feature

