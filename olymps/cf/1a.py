N, M, A = [int(x) for x in raw_input().split(' ')]
f = lambda x, y: x/y + (1 if x%y>0 else 0)
print((f(N, A)) * f(M, A))
