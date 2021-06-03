'''ch7_hw4_20151610'''
print("***** if조건문으로 작성 *****")
ifMonth = int(input("월을 입력하세요: "))
if(ifMonth==1):
    print("1월은 January입니다")
elif(ifMonth==2):
    print("2월은 February입니다")
elif(ifMonth==3):
    print("3월은 March입니다")
elif(ifMonth==4):
    print("4월은 April입니다")
elif(ifMonth==5):
    print("5월은 May입니다")
elif(ifMonth==6):
    print("6월은 June입니다")
elif(ifMonth==7):
    print("7월은 July입니다")
elif(ifMonth==8):
    print("8월은 August입니다")
elif(ifMonth==9):
    print("9월은 September입니다")
elif(ifMonth==10):
    print("10월은 October입니다")
elif(ifMonth==11):
    print("11월은 November입니다")
elif(ifMonth==12):
    print("12월은 December입니다")


print("***** 리스트로 작성 *****")
Months = ["January","February","March","April","May","June","July","August","September","October","November","December"]
listMonth = int(input("월을 입력하세요: "))
print("%d월은 %s입니다"%(listMonth,Months[listMonth-1]))
