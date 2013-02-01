name = raw_input()
dct = {}
for s in name:dct[s] = 1
print "CHAT WITH HER!" if len(dct) % 2 == 0 else "IGNORE HIM!"
