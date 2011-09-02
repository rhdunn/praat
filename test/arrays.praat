echo arrays...

assert numberOfRows (zero# (5, 6)) = 5
assert numberOfColumns (zero# (5, 6)) = 6
a# = zero# (5, 6)
assert numberOfRows (a#) = 5
assert a# [3, 4] = 0

c# = linear# (0, 100, 101)
assert c# [98] = 97
c# = linear# (0, 100, 101, 0)
assert c# [98] = 97
c# = linear# (0, 100, 100, 1)
assert c# [98] = 97.5

d# = randomGauss# (c#, 20, 1)
a = d# [98]
b = d# [99]
c = d# [100]
printline 'a' 'b' 'c'

d# = randomUniform# (c#, 7, 10)
a = d# [98]
b = d# [99]
c = d# [100]
printline 'a' 'b' 'c'

d# = randomInteger# (c#, 7, 10)
a = d# [98]
b = d# [99]
c = d# [100]
printline 'a' 'b' 'c'

;e# = d# + c#

printline OK
