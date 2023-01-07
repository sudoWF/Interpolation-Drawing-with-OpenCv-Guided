import sys
import re

# 删除空行并生成新文件
with open('points.txt', 'r+') as fr, open('temp.txt', 'w+') as fd:
    for text in fr.readlines():
        if text.split():
            fd.write(text)


f1 = open('temp.txt','r',encoding='UTF-8')
# f1 = open('points.txt', 'r+')
f2 = open('points.txt', 'w+')
# print(f1.read())
before = f1.read()
middle = before.replace('[[[','{\n[').replace(']]]',']\n}').replace(' [[','[').replace(']]',']').replace(' ',',')
after = middle.replace('[,','[').replace(',,',',')
print(after)
f2.write(after)
f1.close()
f2.close()



#去括号
# f=open('points.txt','r')
# alllines=f.readlines()
# f.close()
# f=open('points.txt','w+')
# for eachline in alllines:
#     sk = "[[["
#     a=re.sub(sk,'{',eachline)
#     f.writelines(a)
# for eachline in alllines:
#     a=re.sub("hello",'hi',eachline)
#     f.writelines(a)
# for eachline in alllines:
#     a=re.sub('hello','hi',eachline)
#     f.writelines(a)
#
# f.close()



print('输出成功....')
