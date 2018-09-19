import sys
import jieba
import jieba.analyse
import operator


def read_data(path_in,term_id,id_url,limits=None):
    limit=0
    for line in open(path_in,encoding='utf-8'):
        line=line.strip().split('\t')
        #print(line)
        terms = jieba.analyse.extract_tags(line[1],topK=5)
        terms = ' '.join(terms)
        #print(line[1])
        #print(terms)

        term_id.append(terms)
        id_url.append((line[0].strip(),line[2].strip(),line[3].strip()))
        if limits:
            limit +=1
            if limit ==limits:
                break


    #print(term_id)
    #print(id_url)



def read_data_count_terms(path_in_data,path_in_tag,term_id,id_url,cat_tags_file=None,cat_terms_file=None,cat_tags_vid_file=None,cat_terms_vid_file=None):

    data_dict={}
    category_tags_terms_dict={}
    category_tags_vid_dict = {}
    for line in open(path_in_tag,encoding ='utf-8'):
        line = line.strip().split('\t')
        vid=line[0]
        if len(line)>1:
            tag_terms = line[1].split(' ')
        if len(line)>2:
            category = line[2]
            data_dict[vid]=[category,tag_terms]
            if category not in category_tags_terms_dict:
                category_tags_terms_dict[category] ={}

            if category not in category_tags_vid_dict:
                category_tags_vid_dict[category]={}

            for tags in tag_terms:
                if tags not in category_tags_terms_dict[category]:
                    category_tags_terms_dict[category][tags]=1
                else:
                    category_tags_terms_dict[category][tags] += 1

                if tags not in category_tags_vid_dict[category]:
                    category_tags_vid_dict[category][tags]=[vid]
                else:
                    category_tags_vid_dict[category][tags].append(vid)


    if cat_tags_file != None and category_tags_terms_dict!={}:
        with open(cat_tags_file, 'w+', encoding='utf-8')as fout:
            for category in category_tags_terms_dict:
                fout.write('category : ' + str(category) + '\n')
                sorted_dic = sorted(category_tags_terms_dict[category].items(), key=lambda kv: kv[1], reverse=True)
                for ite in sorted_dic:
                    fout.write(str(ite[0]) + ': ' + str(ite[1]))
                    fout.write('\n')
                fout.write('\n')

    if cat_tags_vid_file !=None:
        with open(cat_tags_vid_file, 'w', encoding='utf-8')as fout:
            for category in category_tags_terms_dict:
                fout.write('category : ' + str(category) + '\n')
                sorted_dic = sorted(category_tags_terms_dict[category].items(), key=lambda kv: kv[1], reverse=True)
                for ite in sorted_dic:
                    fout.write(str(ite[0]) + ': '+'\n')
                    vid_list = category_tags_vid_dict[category][ite[0]]
                    fout.write(str(vid_list)+'\n')
                    fout.write('\n')
                fout.write('\n')


    category_terms_dict={}
    category_terms_vid_dict={}

    for line in open(path_in_data, encoding='utf-8'):
        line = line.strip().split('\t')
        vid = line[0]
        if len(line)<1:
            continue
        terms = jieba.analyse.extract_tags(line[1], topK=5)
        if vid in data_dict:
            data_dict[vid].append(terms)
            #data_dict[vid].append(line[2])
            #data_dict[vid].append(line[3])

            category= data_dict[vid][0]

            if category not in category_terms_dict:
                category_terms_dict[category] = {}

            if category not in category_terms_vid_dict:
                category_terms_vid_dict[category]={}

            for term in terms:
                if term not in category_terms_dict[category]:
                    category_terms_dict[category][term] = 1
                else:
                    category_terms_dict[category][term] += 1

                if term not in category_terms_vid_dict[category]:
                    category_terms_vid_dict[category][term]=[(vid,line[2],line[3])]
                else:
                    category_terms_vid_dict[category][term].append((vid, line[2], line[3]))


    if cat_terms_file != None:
        with open(cat_terms_file, 'w', encoding='utf-8')as fout:
            for category in category_terms_dict:
                fout.write('category : ' + str(category) + '\n')
                sorted_dic = sorted(category_terms_dict[category].items(), key=lambda kv: kv[1], reverse=True)
                for ite in sorted_dic:
                    fout.write(str(ite[0]) + ': ' + str(ite[1])+'\n')
                fout.write('\n')

    if cat_terms_vid_file !=None:
        with open(cat_terms_vid_file, 'w', encoding='utf-8')as fout:
            for category in category_terms_dict:
                fout.write('category : ' + str(category) + '\n')
                sorted_dic = sorted(category_terms_dict[category].items(), key=lambda kv: kv[1], reverse=True)
                for ite in sorted_dic:
                    fout.write(str(ite[0]) + ': '+'\n')
                    tuples = category_terms_vid_dict[category][ite[0]]
                    fout.write(str(tuples)+'\n')
                    fout.write('\n')
                fout.write('\n')





    '''
    

    dic_key_fre={}


    for line in open(path_in_data,encoding='utf-8'):
        line=line.strip().split('\t')
        #print(line)
        terms = jieba.analyse.extract_tags(line[1],topK=5)
        #terms = ' '.join(terms)
        #print(line[1])
        #print(terms)
        for word in terms:
            if word not in dic_key_fre:
                dic_key_fre[word]=1
            else:
                dic_key_fre[word]+=1

        #term_id.append(terms)
        #id_url.append((line[0].strip(),line[2].strip(),line[3].strip()))

    #print(term_id)
    #print(id_url)
    sorted_dic = sorted(dic_key_fre.items(),key=lambda kv:kv[1],reverse=True)
    if word_output_file:
        with open(word_output_file,'w',encoding='utf-8')as fout:
            for ite in sorted_dic:
                fout.write(str(ite[0])+': '+str(ite[1]))

                fout.write('\n')

    '''



def main():

    term_id=[]
    id_url=[]
    read_data_count_terms(sys.argv[1],sys.argv[2],term_id,id_url,sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6])


if __name__ == '__main__':
    main()
