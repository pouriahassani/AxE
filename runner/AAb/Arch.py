
from defines import *

class Arch:
    
    def __init__(self,i,mw, Int_Type,Float_Type):
        self.i = i
        self.name = "I" + str(Int_Type) + "_F" + str(Float_Type)
        self.mw = mw
        self.Int_Type  = Int_Type
        self.Float_Type  = Float_Type
        
    def get_Int_Type(self):
        return self.IntType
    
    def get_Float_Type(self):
        return self.Float_Type
    
    def p( self ):
        
        return ( "arch " + str(self.i) + " " + self.name + " mw: " + str(self.mw) )
        
    
    def get_up( self, prg ):
        
        # print( str(prg.c[ self.i ]) + " / " + str(prg.t) + " = " + str(prg.c[ self.i ] / prg.t) )
        
        return self.get_c( prg ) / prg.t
        
    
    def get_ue( self, prg ):
        
        e = self.get_e( prg )
        return e / prg.t
        
    
    def get_c( self, prg ):
        
        return prg.c[ self.i ]
        
    
    def get_e( self, prg ):
        
        return ( prg.c[ self.i ] * self.mw )
        
    

