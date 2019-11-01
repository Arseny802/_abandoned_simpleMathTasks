#!encoding utf-8

import random

amount = 100000
file = open("test-5.txt", "w") 

file.write(str(amount) + '\n')
for i in range(1, amount):
    file.write(str(random.randint(0, 2147483647)))
    file.write(' ')

file.write('\n42\n')
file.write('41 42 43')
file.close() 
