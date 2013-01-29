import time

f = open("find_the_mintxt.txt")
t = int(f.readline())

for case in range( t ): 
    n,k = (int(x) for x in f.readline().split())
    a,b,c,r = (int(x) for x in f.readline().split())
    t = a
    l = [t]
    
    for i in range(k-1):
        t = (b * t + c) % r
        l.append(t)

    t = {}
    tv = {}
    for i in range(k):
        if l[i] <= i or l[i] == i+1:
            t[l[i]] = i+1
    for i in t:
        tv[t[i]] = i


    circle = [-1] * (k+1)
    pos = 0
    for val in range(k+1):
        if val in t:
            circle[t[val]] = val
        else:
            while pos in tv: pos += 1
            circle[pos] = val
            pos += 1
    
    length = n - k
    rd = length / k
    m = (length % k)-1
    pos = m - rd%(k+1)
    res = circle[pos]
    print 'Case #{0}: {1}'.format(case+1, res)