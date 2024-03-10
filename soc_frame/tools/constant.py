
from func_files import *

# setting defines works for c as well as for verilog headers.

# --------------------------------------------------------------------------
# G E T _ D E F I N E
# --------------------------------------------------------------------------

# TODO
# get_constant and set_constant share a lot of code

def get_constant( file_path, var ):
    
    define_lst = file_readlines( file_path )
    
    # ever line is split by spaces " ".
    # the second element is the var. this is true for c as well as for verilog
    # header files.
    # the value is whatever is between the first open bracket "(" and -2 chars.
    # these 2 chars at the end is the newline and the clsoing bracket.
    
    for l in define_lst:
        
        l_split = l.split(" ")
        
        # it is necessary to check the length as the file might contain comments
        
        if ( 1 < len(l_split) ) and ( l_split[ 1 ] == var ):
            
            # get substring:
            # from first occurance of "(" + 1
            # to the end; -1 because of "\n"; -1 because of ")"
            # strip whitespace from both ends
            
            return l[ l.find( "(" )+1:-2 ].strip()
            
        
    

# --------------------------------------------------------------------------
# S E T _ D E F I N E
# --------------------------------------------------------------------------

def set_constant( file_path, var, val ):
    
    define_lst = file_readlines( file_path )
    
    for i,l in enumerate(define_lst):
        
        l_split = l.split(" ")
        
        if ( 1 < len(l_split) ) and ( l_split[ 1 ] == var ):
            
            define_lst[ i ] = l_split[0] + " " + var + " ( " + val + " )\n"
            #~ define_lst[ i ] = "`define " + var + " ( " + val + " )\n"
            break;
            
        
    
    file_writelines( file_path, define_lst )
    
