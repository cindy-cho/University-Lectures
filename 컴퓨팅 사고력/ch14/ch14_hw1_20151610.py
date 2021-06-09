fp_r = open("L_In.txt","r")
fp_w = open("L_Out.txt","w")

index = int(fp_r.readline())
print("index = %d" %index, file = fp_w)

arr1 = list(int(x) for x in fp_r.readline().split())
arr2 = list(int(x) for x in fp_r.readline().split())
fp_w.write("A = ")
print(arr1,file=fp_w)
fp_w.write("B = ")
print(arr2,file=fp_w)
print("A[%d] + B[%d] = %d" %(index, index,arr1[index]+arr2[index]), file=fp_w)

fp_r.close()
fp_w.close()
