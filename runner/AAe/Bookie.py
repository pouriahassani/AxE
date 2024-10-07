
class Bookie:
    
    def __init__( self ):
        
        self.record = {}
        
    
    def record_entry( self, keys, value ):
        
        pass
        
    
    def record_entry_2_deep( self, key1, key2, value ):
        
        if key1 not in self.record:
            
            self.record[ key1 ] = {}
            
        
        if key2 not in self.record[ key1 ]:
            
            self.record[ key1 ][ key2 ] = []
            
        
        self.record[ key1 ][ key2 ].append( value )
        
    
    # ~ def min_entry_2_deep
