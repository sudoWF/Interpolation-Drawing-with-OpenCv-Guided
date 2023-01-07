import sys
import re

# 删除空行并生成新文件
with open('points.txt', 'r+') as fr, open('temp.txt', 'w+') as fd:
    for text in fr.readlines():
        if text.split():
            fd.write(text)
fr.close()
fd.close()

f1 = open('temp.txt','r',encoding='UTF-8')
# f1 = open('points.txt', 'r+')
f2 = open('points.txt', 'w+')
# print(f1.read())
# before = f1.read()
# middle = before.replace('[[[','{\n[').replace(']]]',']\n}').replace(' [[','[').replace(']]',']').replace(' ',',')
# after = middle.replace('[,','[').replace(',,',',')

before = f1.read()
middle = before.replace('[[[ ','{\n').replace('[[[','{\n').replace(']]]','\n}').replace(' [[ ','').replace(' [[','').replace(']]','').replace(' ',',')
after = middle.replace(',,',',')

# final = after.replace('\n',',')
print(after)
# a = after.split("\n")
# print(a)
f2.write(after)
f1.close()
f2.close()

# print(type(final))

# from openpyxl import Workbook
#
# workbook = Workbook()
# save_file = "写入文件.xlsx"
# worksheet = workbook.active
# #每个workbook创建后，默认会存在一个worksheet，对默认的worksheet进行重命名
# worksheet.title = "Sheet1"
# for row in after:
#     worksheet.append([row]) # 把每一行append到worksheet中
# workbook.save(filename=save_file) #不能忘


print('输出成功....')
