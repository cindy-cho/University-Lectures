'''3by3행렬'''

def mulXY(X,Y):
    global XxY
    for i in range(3):
        for j in range(3):
            ijSum = 0
            for k in range(3):
                ijSum += X[i][k]* Y[k][j]
            XxY[i][j] = ijSum


X = [[1,2,3],[4,5,6],[7,8,9]]
Y = [[11,22,33],[44,55,66],[77,88,99]]
XxY = [[0,0,0],[0,0,0],[0,0,0]]

mulXY(X,Y)
print(XxY)
