D = {3:'사과', 4:'배', 1:'오렌지', 2:'바나나'}

#키 밸류 리스트로 튜플을 구해서 리스트로 만들기 
DL = list(D.items())

#오름차순 정렬하기 
DL.sort()

print("After sort:",DL)
