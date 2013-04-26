import sys, random, time

MAX_TIME = 115.0  # seconds permitted

def walk(n, l, r):
  (exp_rmax, runs, t1) = (0.0, 0, time.clock()+MAX_TIME)
  while time.clock() < t1:
    exp_rmax = (exp_rmax*runs + float(one_walk(n, l, r))) / (runs+1)
    runs += 1
  return exp_rmax  # mean

def one_walk(n, l, r):
  (pos, m) = (0, 0)
  for rnd in [random.random() for i in range(n)]:
    if rnd < l: pos -= 1
    elif rnd < l+r: pos += 1
    m = max(m, pos)
  return m

for (n,l,r) in [(1,.5,.5), (4,.5,.5), (10,.5,.4), (1000,.5,.4)]:
  print "%0.4f" % walk(n, l, r)