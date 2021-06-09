def checkPassword ( userPassword ):
    '''password 유효성 체크해주는 함수'''
    if len(userPassword) < 8 :
        print("error! 8 글자 이상이어야 함")
        return False

    alphaFlag = 0; numFlag = 0; otherFlag = 0
    for p in userPassword :
        if (p>= 'a' and p<='z') or (p>='A' and p<='Z'):
            alphaFlag +=1
        elif p>='0' and p<='9':
            numFlag +=1
        else:
            otherFlag+=1
    
    if otherFlag != 0 :
        print("error! 영문자, 숫자로만 구성되어야 함")
        return False
    
    if numFlag == 0 :
        print("error! 숫자도 포함되어야 함")
        return False
    
    if alphaFlag == 0:
        print("error! 영문도 포함되어야 함")
        return False
    
    if numFlag < 2 :
        print("error! 최소한 2개의 숫자를 포함해야 함")
        return False

    return True


for i in range(5):
    userPassword = input("Enter password: ")
    if checkPassword(userPassword)==True:
        print("Valid password")
        break 
    else:
        print("Invalid password")