def countAlphabets(inputSentence):
    '''사용된 문자의 개수 Count
        return 값 : 문자의 개수 저장한 dict'''
    alphaCount = {}
    lowered = inputSentence.lower()
    for Sen in lowered:
        if Sen == ' ' :
            continue
        if alphaCount.get(Sen) == None :
            alphaCount[Sen] = 1
        else :
            alphaCount[Sen] += 1
    
    return alphaCount
    

inputSentence = input("문자열 입력 : ")
alphaCount = countAlphabets(inputSentence)
for key, value in alphaCount.items():
        print(key,":",value)
