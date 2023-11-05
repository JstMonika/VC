c = 1
while True:
    s = input()
    n, k = s.split(' ')
    n = int(n)
    k = int(k)
    
    if (n == 0 and k == 0):
        break;
    
    sum = 0
    for i in range(0, n):
        tmp = int(input())
        sum += tmp
        
    print('Bill #' + str(c) + ' costs ' + str(sum) + ': each friend should pay ' + str(sum//k) + '\n')
    c += 1