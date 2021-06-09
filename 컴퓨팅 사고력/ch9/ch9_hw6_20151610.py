'''CH9_HW6'''
N = int(input("Enter N (0 < N < 10) : "))
if N >=10 or N <= 0 :
    print("ERROR : N must be 0 < N < 10.")

elif N%2==0:
    for i in range (1,N+1):
        for j in range(1,i+1):
            print(j,end="")
        print()
    for i in range (N,0,-1):
        for j in range(1,i+1):
            print(j,end="")
        print()


else:
    for i in range (1,N+1):
        for j in range(1,i+1):
            print(j,end="")
        print()
    for i in range (N-1,0,-1):
        for j in range(1,i+1):
            print(j,end="")
        print()
