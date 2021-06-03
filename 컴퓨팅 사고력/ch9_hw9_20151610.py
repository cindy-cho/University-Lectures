'''CH9_HW9'''
score = input("성적들을 입력하세요: ").split()
i = 1
for s in score :
    s = int(s)
    if s>=90 :
        print("%d번 학생의 성적은 A입니다."%(i))
    elif s<90 and s>=70 :
        print("%d번 학생의 성적은 B입니다."%(i))
    elif s<70 and s>=50:
        print("%d번 학생의 성적은 C입니다."%(i))
    else:
        print("%d번 학생의 성적은 F입니다."%(i))
    i+=1
