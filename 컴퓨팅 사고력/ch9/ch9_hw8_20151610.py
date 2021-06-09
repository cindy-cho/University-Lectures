'''CH9_HW8'''
score = [82, 98, 100, 40, 75, 55, 73, 24, 10, 64]
i = 1
for s in score :
    if s>=90 :
        print("%d번 학생의 성적은 A입니다."%(i))
    elif s<90 and s>=70 :
        print("%d번 학생의 성적은 B입니다."%(i))
    elif s<70 and s>=50:
        print("%d번 학생의 성적은 C입니다."%(i))
    else:
        print("%d번 학생의 성적은 F입니다."%(i))
    i+=1
