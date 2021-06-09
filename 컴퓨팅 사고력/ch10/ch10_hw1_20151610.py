'''CH10_HW1_20151610'''

inputarr=[]
while(True):
    a = int(input("정수를 입력 (0을 입력하면 종료) : "))
    if a == 0 :
        break
    inputarr.append(a)

print("입력한 정수 리스트 :",inputarr)
print("합계 : %d" %(sum(inputarr)))
print("평균 : %.2f" %(sum(inputarr)/len(inputarr)))
