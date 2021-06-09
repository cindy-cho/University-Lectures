#ch5_hw3
import math as m
x1, y1, x2, y2 = input("두 점의 좌표값을 x1, y1, x2, y2 순서대로 입력 : ").split()
distance = m.sqrt(pow(float(x1)-float(x2),2)+pow(float(y1)-float(y2),2))
print("두 점 사이의 거리는 %.2f 입니다." %(distance))
print("두 점 사이의 거리는 5이하 입니까?",(distance<=5))
