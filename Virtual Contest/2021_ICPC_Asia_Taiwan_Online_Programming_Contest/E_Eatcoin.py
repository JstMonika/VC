import math
from re import S

def sum(n):
    return n * n * (n+1) * (n+1) * (2*n*n + 2*n - 1) // 12

p, q = map(int, input().split())

d = math.floor(math.pow(p / q, 0.2))

if (d == 0):
    x = p;
else:
    x = p * d - sum(d) + p;
    
L = 1
R = 2

while (x + q * sum(R) - p * R < 10**99):
    R = R * 2;
    L = L * 2;
    
# print(R)

ans = R
idx = 0

while (L <= R):
    # print(L, ' ', R)
    
    M = int((L+R) // 2);
    # print((L+R) // 2);
    # print(M)
    
    
    if (x + q * sum(M) - p * M < 10**99):
        L = M+1;
    else:
        ans = min(ans, M);
        R = M-1;
    
print(x)
print(ans)