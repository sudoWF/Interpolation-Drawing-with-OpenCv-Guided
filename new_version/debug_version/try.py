


count = len(open("final.txt",encoding="utf-8").readlines())
print(count)
# print(type(count))

contours = n #总程序里的轮廓数

c_file = open('cHello.txt','w')



for line in open('num_1.txt', encoding="utf-8"):
    c_file.writelines(line)
# c_file.write('\n')

c_file.writelines(str(count))

c_file.writelines('][3]={\n')

for line in open('final.txt', encoding="utf-8"):
    c_file.writelines(line)
c_file.write('\n')

for line in open('num_2.txt', encoding="utf-8"):
    c_file.writelines(line)
# c_file.write('\n')

c_file.writelines(str(contours))

for line in open('num_3.txt', encoding="utf-8"):
    c_file.writelines(line)
c_file.write('\n')

c_file.close()

print('Finished')
