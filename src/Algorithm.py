from sklearn.externals import joblib
import config
import protobuf_test_pb2 as protobuf_test
import labels_pb2 as labels_proto

class Base_Algorithm(object):
    def __init__(self,algo_name=None):
        self.algo_name = algo_name

    def fit(self, feature):
        self.algo.fit(feature)

    def serilize_model(self):
        centers = self.algo.cluster_centers_.tolist()
        labels = self.algo.labels_.tolist()
        print(centers)
        print(labels)
        pb_centers = protobuf_test.centers()
        for i in range(len(centers)):
            row = pb_centers.one_row.add()
            for j in range(len(centers[0])):
                row.points.append(centers[i][j])
        print(pb_centers)
        f = open(config.model_file_name, 'wb')
        f.write(pb_centers.SerializeToString())
        f.close()

        pb_labels = labels_proto.labels()
        for i in range(len(labels)):
            pb_labels.points.append(labels[i])
        print(pb_labels)
        f = open(config.label_file_name,'wb')
        f.write(pb_labels.SerializeToString())
        f.close()







    def de_serilize_model(self):
        self.algo = joblib.load(config.model_file_name)

    def predict(self,sample):
        return self.algo.predict(sample)







