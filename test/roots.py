a = int(input())
b = int(input())
c = int(input())

if a == 0:
    if b != 0:
        print(-c/b)
    else:
        if c != 0:
            print(0) 
        else:
            print(-1)
else:
    D = b**2 - 4*a*c
    if D > 0:
        x1 = (-b - D**(1/2))/(2*a)
        x2 = (-b + D**(1/2))/(2*a)
        if x1 < x2:
            print(x1, x2)
        else:
            print(x2, x1)
    else: 
        if D == 0 :
            print(-b/(2*a))
        else:
            print(0)
