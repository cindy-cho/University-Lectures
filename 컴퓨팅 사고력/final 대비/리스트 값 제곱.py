'''리스트 원소 곱하기'''
'''인덱싱 사용'''
'''저장은 슬라이싱'''



L = [[1,2,3], [4,5], [6], [7,8]]

A = []
A.append( L[0][0]*L[0][0] + L[0][1] * L[0][1] + L[0][2]*L[0][2])
A.append(L[1][0]*L[1][0] + L[1][1] * L[1][1])
A.append( L[2][0]*L[2][0])
A.append( L[3][0]*L[3][0] + L[3][1] * L[3][1])

print(A)

