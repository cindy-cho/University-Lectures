'''CH9_HW4'''
import math as m
data = input("Enter data : \n").split()

N = len(data)
M2 = 0.0
E2 = 0.0
for d in data:
    M2 += float(d)**2
    E2 += float(d)

M2 = M2/N
E2 = (E2/N)**2
std_dev = m.sqrt(M2 - E2)
print("Standard deviation = %.5f" %(std_dev))
