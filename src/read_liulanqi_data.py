import sys
import jieba
import jieba.analyse
import operator

def read_data(path_in,term_id,id_url,word_output_file=None):
    dic={}

    for line in open(path_in,encoding='utf-8'):
        line=line.strip().split('\t')
        #print(line)
        terms = jieba.analyse.extract_tags(line[1],topK=5)
        #terms = ' '.join(terms)
        #print(line[1])
        #print(terms)
        for word in terms:
            if word not in dic:
                dic[word]=1
            else:
                dic[word]+=1

        #term_id.append(terms)
        #id_url.append((line[0].strip(),line[2].strip(),line[3].strip()))

    #print(term_id)
    #print(id_url)
    sorted_dic = sorted(dic.items(),key=lambda kv:kv[1],reverse=True)
    if word_output_file:
        with open(word_output_file,'w',encoding='utf-8')as fout:
            for ite in sorted_dic:
                fout.write(str(ite[0])+': '+str(ite[1]))

                fout.write('\n')





def main():

    term_id=[]
    id_url=[]
    read_data(sys.argv[1],term_id,id_url,sys.argv[2])


if __name__ == '__main__':
    main()
