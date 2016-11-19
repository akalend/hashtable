import os
import random

f = open('test.file.txt', 'w')


for n in xrange(2000000):
    out_line = ''
    for i in xrange(10):
        out_line =  `random.randrange(1000000)` + ' ' + out_line

    f.write(out_line)
    f.write('\n')

f.close();
