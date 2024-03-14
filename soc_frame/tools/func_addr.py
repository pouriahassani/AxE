
def addr_to_index( addr ):
    
    addr_int = int( addr, 16 )
    
    if ( (addr_int%4) != 0 ):
        
        print( "byte alignment error!" )
        exit()
        
    
    # no float!
    return int( addr_int/4 )
    

def index_to_addr( index ):
    
    return hex( index*4 )
    
