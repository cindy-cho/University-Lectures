nums = list(map(int,input("정수들을 입력 :\n").split()))

pos = 0
neg = 0
idx = len(nums)

if idx == 0 :
    print("입력한 숫자가 없습니다")

idx -= 1
while idx>=0 :
    if nums[idx] > 0 :
        pos += 1
    elif nums[idx] < 0 :
        neg += 1

    idx-=1
print("양수: %d 개, 음수 : %d 개, 합계 : %d"%(pos,neg,sum(nums)))
