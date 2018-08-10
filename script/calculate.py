import sys



num_not_right=0
num_line=0
two_types=0
more_types=0
for line in open(sys.argv[1],encoding='utf-8'):
    if line.startswith('Cluster4573'):
        break
    pairs = line.strip().split('\t')
    if len(pairs)<2:
        continue
    container=[]
    for ite in pairs:
        if ite!='':
            container.append(ite)
    num_classes=container[-2].split('：')[1]
    pure_voice=container[-1].split('：')[1]
    if int(num_classes)!=0 and int(num_classes)!=1 and int(pure_voice)==0:
        num_not_right+=1
        if int(num_classes)==2:
            two_types+=1
        if int(num_classes)>2:
            more_types+=1


    num_line+=1

print(num_not_right)
print(num_line)
print(two_types)
print(more_types)


