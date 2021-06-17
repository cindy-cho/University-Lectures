'''sorted'''

A = [71,23,31]
B = [54,1]

A.extend(B)
print("extend 함수를 이용하여 합친 리스트:",A)
A = sorted(A,reverse=True)
print("내림차순으로 정렬한 리스트:",A)
