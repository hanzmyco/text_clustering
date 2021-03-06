import json
from pprint import pprint
import sys
from pathlib import Path
from pathlib import PureWindowsPath
import jieba
import jieba.analyse

def read_json4cpp(path_in,set_limit=None,file_out=None):
    p = Path(path_in)
    file_names = list(p.glob('*.txt'))
    data_out=[]

    #stoplist = set([line.strip() for line in open(stop_word_path,encoding='utf-8')])

    limit=0


    for file_name in file_names:
        file_name = str(file_name)
        with open(file_name, encoding='utf-8') as f:
            data = json.load(f)
            for vid in data:
                if set_limit and limit >set_limit:
                    break
                ite = ''
                for text in data[vid].split('\n'):
                    words = text.strip().split(']')
                    if len(words) > 1 and (words[1] != '\n' or words[1] != '\r'):
                        # print(words[1])
                        for token in words[1]:
                            if token != '' and token != ' ':
                                ite += token
                data_out.append(ite)
                if set_limit:
                    limit+=1
    with open(file_out,'w',encoding='utf-8') as f_out:
        for ite in data_out:
            f_out.write(ite)
            f_out.write('\n')


def read_json(path_in,data_out,stop_word_path,vid_out=None,set_limit=None,file_out=None):
    p = Path(path_in)
    file_names = list(p.glob('*.txt'))

    stoplist = set([line.strip() for line in open(stop_word_path,encoding='utf-8')])

    limit=0


    for file_name in file_names:
        file_name = str(file_name)
        with open(file_name, encoding='utf-8') as f:
            data = json.load(f)
            for vid in data:
                if set_limit and limit >set_limit:
                    break
                ite = ''
                for text in data[vid].split('\n'):
                    words = text.strip().split(']')
                    if len(words) > 1 and (words[1] != '\n' or words[1] != '\r'):
                        # print(words[1])
                        for token in words[1]:
                            if token != '' and token != ' ':
                                ite += token
                if vid_out!=None:
                    vid_out.append(vid)

                seg_list = jieba.cut(ite, cut_all=False)
                segs = [str(word) for word in list(seg_list) if word not in stoplist]
                put_in = ' '.join(segs)
                if put_in .strip()=='' or put_in .strip()==None:
                    continue
                data_out.append(put_in)

                if set_limit:
                    limit+=1

    if file_out !=None:
        with open(file_out,'w',encoding='utf-8') as f_out:
            for ite in data_out:
                f_out.write(ite)
                f_out.write('\n')

def test_alignment_py(file_name,file_out,stop_word_path,stop_word =True,extraction=False,topk=None,data_out=None):
    stoplist = set()

    if stop_word:
        stoplist = set([line.strip() for line in open(stop_word_path, encoding='utf-8')])

    with open(file_out,'w',encoding='utf-8') as f:
        for line in  open(file_name,encoding='utf-8'):
            ite = line.strip()
            seg_list = jieba.cut(ite, cut_all=False)
            segs = [str(word) for word in list(seg_list) if word not in stoplist]
            item = ' '.join(segs)

            if extraction:
                item= jieba.analyse.extract_tags(item,topk)
                item= ' '.join(item)
            if item.strip() !='' and  item.strip() !=None:
                f.write(item)
                f.write('\n')
                if data_out!=None:
                    data_out.append(item)


def main():
    #read_json4cpp('../data/subtitle/',None,'../data/cpp/input.txt')
    data_out=[]
    #read_json('../data/subtitle_debug/',data_out,'stop_words.utf8',None,None,'../data/cpp/input_python_debug.txt')
    #test_alignment_py('../data/cpp/small.txt','../data/cpp/python_alignment_tokenizer_no_stopwords.txt','stop_words.utf8',False,False)

if __name__ == '__main__':
    main()
