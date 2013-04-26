import sys
sys.setrecursionlimit(2000)

cache = {}
def walk(n, L, R, f=0):
    if n == 0: return f
    key = n, L, R, f
    if key not in cache:
        EL = walk(n-1, L, R, f+1) - 1
        E0 = walk(n-1, L, R, f)
        ER = walk(n-1, L, R, max(f-1, 0)) + 1
        cache[key] = L * EL + R * ER + (1-L-R) * E0
    return cache[key]

sys.stdout.write(str(walk(1,0.5,0.5)) + "\n")
sys.stdout.write(str(walk(4,0.5,0.5)) + "\n")
sys.stdout.write(str(walk(10,0.5,0.4)) + "\n")
sys.stdout.write(str(walk(1000,0.5,0.4)))
