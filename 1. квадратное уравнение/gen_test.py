from random import uniform
f = open("tests_input.txt","w")
for i in range(100):
    print(uniform(-1000,1000),uniform(-1000,1000),uniform(-1000,1000),file=f)
f.close()