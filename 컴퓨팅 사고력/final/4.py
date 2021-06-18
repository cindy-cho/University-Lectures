import random as r

def multiple(nums2):
    for i in range(len(nums2)):
        nums2[i] = nums2[i]*nums2[i]
    sorted(nums2,reverse=False)

nums = []
nums2=[]
#랜덩 생성
for i in range(10):
    nums.append(r.randint(-10,10))
    nums2.append( nums[i])
    
multiple(nums2)
print("랜덤(-10~10)으로 생성된 리스트:",multiple(nums2))
print("함수에 의해 가공된 리스트:",nums)

