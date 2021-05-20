fib1 = 1 # Vars
fib2 = 1 
n = int(input())
i = 0
while i < n - 2: # Exec of simple algo
#
    fibsum = fib1 + fib2
    print(fibsum)
    fib1 = fib2
    fib2 = fibsum
    i = i + 1
print(n,"- ое число фибонначи:",fib2)

