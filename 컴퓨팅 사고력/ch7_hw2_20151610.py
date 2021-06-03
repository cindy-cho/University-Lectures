'''20151610 조유화
   ch7_hw2_20151610'''

L = [[1,2,3],[4,5],[6],[7,8]]
ans = []


tmp = L[0][0]*L[0][0] + L[0][1]*L[0][1] + L[0][2]*L[0][2]
ans[len(ans):len(ans)] = [tmp]
tmp = L[1][0]*L[1][0] + L[1][1]*L[1][1]
ans[len(ans):len(ans)] = [tmp]
tmp = L[2][0]*L[2][0]
ans[len(ans):len(ans)] = [tmp]
tmp = L[3][0]*L[3][0] + L[3][1]*L[3][1]
ans[len(ans):len(ans)] = [tmp]

print(ans)
