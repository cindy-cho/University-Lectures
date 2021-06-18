'''proj3'''


fileR = open("Team_Assignment.txt","r")
# 선수이름 , 수비력, 공격력, 팀이름

players = {}

AltosDF = 0
AltosOF = 0

WebeeDF = 0
WebeeOF = 0

for lines in fileR :
    player, DF, OF, team = lines.split()
    DF = int(DF)
    OF = int(OF)
    if team == "Altos":
        players[player] = ["Altos",DF, OF]
        AltosDF += DF
        AltosOF += OF
    else :
        players[player] = ["Webee",DF, OF]
        WebeeDF += DF
        WebeeOF += OF


while True:
    print("**Altos** DF = %d OF = %d" %(AltosDF,AltosOF))
    for key in players :
        if players[key][0] == "Altos":
            print("%s:  DF = %d, OF = %d" %(key,players[key][1],players[key][2]))

    print()
    print("**Webee** DF = %d OF = %d" %(WebeeDF,WebeeOF))
    for key in players :
        if players[key][0] == "Webee":
            print("%s:  DF = %d, OF = %d" %(key,players[key][1],players[key][2]))

    print()
    
    names = input("Enter names to swap: ")
    if not names:
        break

    name1, name2 = names.split()
    
    if players.get(name1) == None or players.get(name2) == None :
        print("Player not exist!")

    else :
        if players[name1][0]=='Webee':
            players[name1][0] = 'Altos'
            players[name2][0] = 'Webee'
        else:
            players[name1][0] = 'Webee'
            players[name2][0] = 'Altos'
        
        
        
fileR.close()
