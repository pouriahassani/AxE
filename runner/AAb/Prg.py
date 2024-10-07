
from defines import *

class Prg:
    
    def __init__(self, i, name, ec, ac, Int_pref, Float_pref ):
        
        self.i = i
        self.name = name
        
        self.Int_pref = Int_pref
        self.Float_pref = Float_pref
        
        self.c = []
        self.c.append( ec )
        self.c.append( ac )
        
        self.t = 0
        self.d = 0
        self.d_next = 0
        
        self.ready = False
        
        self.s = 0
        
    
    def pn( self ):
        
        return ( str(self.i) + " " + self.name[0:4] )
        
    
    def p( self ):
        
        return ( "prg" + self.pn() + "\tec: " + str(self.c[ARCH_EXACT]) + "\tac: " + str(self.c[ARCH_APPRX]) + "\tt: " + str(self.t) )
        
    
    def set_t( self, mult ):
        
        self.t = round( self.c[ARCH_EXACT] * mult, 2 )
        self.d = self.t 
        
    
