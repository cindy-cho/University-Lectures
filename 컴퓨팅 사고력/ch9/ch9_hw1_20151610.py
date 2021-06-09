#ch9_hw1_20151610

for i in range(1,11):
    num = int(input("Enter a number : "))
    if num == 0 :
        print("입력 받은 수가 0 입니다")
        print("프로그램을 종료합니다")
        break
    if num < 0 :
        if num % 2 == 0 :
            print(num,": 음수, 짝수")
        else :
            print(num,": 음수, 홀수")
    else :
        if num % 2 == 0:
            print(num,": 양수, 짝수")
        else :
            print(num,": 양수, 홀수")

