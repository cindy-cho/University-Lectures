'''ch8_hw3_20151610'''
#재고량, 단가
fruit = {'배' : [2, 1000], '자몽' : [1,2000], '메론' : [1,8000], '감' : [6,800]}

wantToEat = input("먹고 싶은 과일은? : ")
if fruit.get(wantToEat) == None :
    print(wantToEat,"준비되어 있지 않습니다\n")
else :
    print(wantToEat,"맛있게 드세요\n")
    fruit[wantToEat][0] -=1

print(" 각 과일 당 최소 5개는 되도록 구입합니다")
total = 0

fruitItem = list(fruit.items())

for item in fruitItem:
    if item[1][0]<5:
        total += (5-item[1][0]) * item[1][1]

print(" 구입에 필요한 총 금액은 : %d 원 입니다" %total)
