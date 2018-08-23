import random
def feedid2url(file_in,file_out,top_k):
    count_cluster=0
    container=[]
    num_larger_10=0
    num_smaller_10=0
    with open(file_out, 'w', encoding='utf-8') as f_out:
        with open(file_in, encoding='utf-8') as f_in:
            text='1'
            while text:
                text=f_in.readline()
                print(text)
                if text.startswith('Cluster'):
                    if len(container) >10:
                        num_larger_10 += 1
                        for ite in random.sample(container,10):
                            f_out.write(ite)
                    else:
                        num_smaller_10+=1
                        for ite in container:
                            f_out.write(ite)
                    f_out.write('\n')
                    count_cluster += 1
                    if count_cluster>=10000:
                        print('stop')
                    if count_cluster > top_k:
                        return

                    for ite in text.split(' '):
                        f_out.write(ite.strip()+'\t')
                    f_out.write('\n')

                    container=[]
                elif text.strip()!='':
                    container.append('https://h5.qzone.qq.com/weishi/feed?_proxy=1&_wv=1&id='+text)
        if len(container) > 10:
            for ite in random.sample(container, 10):
                f_out.write(ite)
            num_larger_10+=1
        else:
            num_smaller_10+=1
            for ite in container:
                f_out.write(ite)

    print(num_larger_10)
    print(num_smaller_10)


file_in='C:\\Users\\mycohzhang\\source\\text_clustering\\data\\debug\\5000_clusters_10000_iters_top_terms.txt'
file_out='C:\\Users\\mycohzhang\\source\\text_clustering\\data\\debug\\5000_clusters_10000_iters_top_terms_to_check.txt'
top_k=10
feedid2url(file_in,file_out,5000)

