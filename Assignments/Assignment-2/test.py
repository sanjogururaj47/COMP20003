import os
import pandas as pd
import sys
import subprocess

total = 19017
i = 0
f2 = open('stdout.txt', 'w')

cmd = 'make'
os.system(cmd)

df_read = pd.read_csv("datasets/CLUEdata2018_sortx.csv")

while(i<total):
    f = open('myinput.txt', 'w')
    

    i+=100
    df = df_read.sample(i)
    df.to_csv('clue_sample.csv', index=False)
    
    req = df.sample(1)
    input_str = str(req.get_value(req.index[0], 'x coordinate')) + ' ' + str(req.get_value(req.index[0], 'y coordinate')) + '\n'
    f.write(input_str)
    
    cmd2 = './map1 clue_sample.csv outputfile.txt < myinput.txt'
    os.system(cmd2)
    #f2.write(subprocess.check_output(cmd2, shell = True))
    
    f.close()
    
f2.close()