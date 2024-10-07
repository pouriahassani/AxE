
import os
import sys

import math

# open file

path = sys.argv[1]

f = open( path, "r" )
lines = f.readlines()
f.close()

# remove header

i = 0
new_line = ""
new_lines = []

for line in lines:
    
    new_line += line[:-1] + "\t"
    
    i += 1
    
    if i == 3:
        
        # ~ print( new_line )
        
        new_lines.append( new_line )
        i = 0
        new_line = ""
        
    

lines_str = ""

for line in new_lines:
    
    lines_str += line + "\n"
    

f = open( "new.csv", "w" )
f.write( lines_str )
f.close()
