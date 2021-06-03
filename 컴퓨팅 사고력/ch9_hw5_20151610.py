'''CH9_HW5'''
N1, N2 = input("두 자연수 N1과 N2를 입력하세요 (0 < N1 <= N2) : ").split()
total = 0
N1 = int(N1)
N2 = int(N2)
if N1 > N2 :
    S = N2
    E = N1
else :
    S = N1
    E = N2
for i in range(S, E+1):
    if i%2==0 :
        total += i

print("크기가 %d 이상이고 %d 이하인 모든 짝수의 합은 %d입니다." %(S, E, total))
        
