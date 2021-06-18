D = {'사과' : 100, '배' : 203, '오렌지' : 121, '바나나' : 9}

#딕셔너리를 리스트로 변환 
DL = list(D.items())
ANS = []
SUM = 0
#추출하여 과일의 개수를 넣어준다
#추출동시에 전체 과일의 개수를 SUM에 저장한다.
for val in DL :
    ANS.append(val[1])
    SUM += int(val[1])

print("과일의 개수 리스트:",ANS)
print("전체 과일의 개수:",SUM)
