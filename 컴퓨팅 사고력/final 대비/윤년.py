'''윤년판단'''

year = int(input("윤년인지 확인하기 위한 연도를 입력하시오: "))

if(year%4 == 0 and year%100!=0 or year%400==0) :
    print("입력한 %d년은 윤년입니다."%year)
else:
    print("입력한 %d년은 윤년이 아닙니다."%year)
