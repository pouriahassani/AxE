
import os

import json

# ------------------------------------------------------------------------------
# 
# ------------------------------------------------------------------------------

# read a file and return all the lines as a lsit

def file_readlines( path ):
    
    f = open( path, "r" )
    l = f.readlines()
    f.close()
    
    return l
    

# ------------------------------------------------------------------------------
# 
# ------------------------------------------------------------------------------

def file_writelines( path, lines ):
    
    f = open( path, "w" )
    
    for l in lines:
        
        f.write( l )
        
    
    f.close()
    

# ------------------------------------------------------------------------------
# 
# ------------------------------------------------------------------------------

def read_dict_from_json( path ):
    
    f = open( path, "r" )
    j = f.read()
    
    # progs
    
    dic = json.loads( j )
    
    f.close()
    
    return dic

# ------------------------------------------------------------------------------
# 
# ------------------------------------------------------------------------------

def write_dict_to_json( dic, path ):
    
    with open(path, 'w', encoding='utf-8') as f:
        json.dump(dic, f, ensure_ascii=False, indent=4)
    
