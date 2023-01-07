import cv2
import numpy as np

image = cv2.imread("000.png")
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)  # 转为灰度图
blurred = cv2.GaussianBlur(gray, (11, 11), 0)
edge = cv2.Canny(blurred, 30, 150)  # 用Canny算子提取边缘
#cv2.imwrite("./results/edge.jpg", edge)
cv2.imshow("image_1", edge)
cv2.waitKey(0)

contour = image.copy()
(cnts, _) = cv2.findContours(edge, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)  # 轮廓检测
cv2.drawContours(contour, cnts, -1, (0, 255, 0), 2)  # 绘制轮廓
# cv2.imwrite("./results/contour.jpg", contour)
cv2.imshow("image_2", contour)
cv2.waitKey(0)


# cnt = list(cnts)
# from openpyxl import Workbook
#
# workbook = Workbook()
# save_file = "写入文件.xlsx"
# worksheet = workbook.active
# #每个workbook创建后，默认会存在一个worksheet，对默认的worksheet进行重命名
# worksheet.title = "Sheet1"
# for row in cnt:
#     worksheet.append(str[row]) # 把每一行append到worksheet中
# workbook.save(filename=save_file) #保存文件，不能忘

#
# list_2 = [int(x) for item in cnts for x in item]
# print(list_2)

# cnt = list(cnts)
# print(cnts)
# print(cnt[0][0])
# print(type(cnt))
np.savetxt("points.txt",cnts,fmt='%s',delimiter=',')
