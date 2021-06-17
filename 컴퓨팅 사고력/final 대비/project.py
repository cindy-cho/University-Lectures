'''Project'''

D = {20111111: ['sam', 92, 85, 65], 20101234: ['joe',100,90,75], 20124321: ['Anne', 95,90,90], 20135555:['Jane', 55,60,65]}
# key  = 학번, value : 이름, 국어, 영어, 수학


for val in D.values() :
    avg = int((val[1]+val[2]+val[3])/3)
    val.append(avg)
    
print("학번        이름          국어  영어  수학  평군")
print("-----------------------------------------")
for key, val in D.items() :
    print("%-10d %-10s %4d %4d %4d %4d" %(key,val[0],val[1],val[2],val[3],val[4]))

while True:
    print("------------------------------")
    print("1. 추가, 2. 삭제, 3. 출력, 4. 종료")
    commandOpt = int(input("숫자를 선택하세요: "))
    if commandOpt == 4 :
        break;
    elif commandOpt == 1:
        studentId = int(input("학번을 입력하세요: "))
        if (studentId in D) == True:
            print("이미 입력된 학생입니다.")
        else :
            studentName = input("이름을 입력하세요: ")
            studentKorean = int(input("국어성적을 입력하세요: "))
            studentEnglish = int(input("영어성적을 입력하세요: "))
            studentMath = int(input("수학성적을 입력하세요: "))
            studentAvg = int((studentKorean+studentEnglish+studentMath)/3)
            D[studentId] = [studentName,studentKorean,studentEnglish,studentMath,studentAvg]
            print("학생의 성적을 입력했습니다.")
            
    elif commandOpt == 2:
        studentId = int(input("삭제하기 원하는 학생의 학번을 입력하세요: "))
        if (studentId in D) == True:
            del D[studentId]
            print("학번: %d 학생의 정보를 삭제했습니다." %studentId)
        else :
            print("없는 학생입니다.")       

    elif commandOpt == 3:
        print("학번        이름          국어  영어  수학  평군")
        print("-----------------------------------------")
        for key, val in D.items() :
            print("%-10d %-10s %4d %4d %4d %4d" %(key,val[0],val[1],val[2],val[3],val[4]))
    
    
