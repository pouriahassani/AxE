
def get_power_from_line( line ):
    
    line_arr = line.split( ";" )
    power_str = line_arr[ 4 ]
    
    power_str = power_str.replace(",", "")
    
    power_value = float( power_str[ :-1 ] )
    
    return power_value
    

steps = 5;

f = open( "efHomeTux_11_03_2021.csv", "r" )

l = f.readlines()

# remove newlines

for index, line in enumerate( l ):
    
    l[ index ] = line[ :-1 ]
    

# reorder the dataset

l.reverse()


# get the original values

#~ for line in l:
    
    #~ power_value = get_power_from_line( line )
    
    #~ print( str( power_value ) )

#~ exit()

power_arr = []

power_values_n = len( l )

i = 0

while i < ( power_values_n-1 ):
    
    power_start = get_power_from_line( l[ i   ] )
    power_end   = get_power_from_line( l[ i+1 ] )
    
    power_diff = power_start - power_end
    power_step = power_diff / steps
    
    power_rising = power_start <= power_end
    
    if ( power_step < 0 ):
        power_step *= -1
    
    power_curr = power_start
    
    j = 0
    
    while j < steps:
        
        if power_rising:
            power_curr += power_step
        else:
            power_curr -= power_step
        
        power_arr.append( round( power_curr, 8 ) )
        
        j += 1
        
    
    i += 1
    

# sub min value from every measured point

min_val = min( power_arr )

for index, line in enumerate( power_arr ):
    
    power_arr[ index ] = line - min_val
    

# normalize

max_val = max( power_arr )

for index, line in enumerate( power_arr ):
    
    power_arr[ index ] = round( (line/max_val), 8 )
    

# fix for smaller cell

max_val_cell = 0.25

for index, line in enumerate( power_arr ):
    
    power_arr[ index ] = round( (line*max_val_cell), 6 )
    

# W to microwatts

#~ for index, line in enumerate( power_arr ):
    
    #~ power_arr[ index ] = round( line*1000000 )
    


# W to milliwatts

for index, line in enumerate( power_arr ):
    
    power_arr[ index ] = round( line*1000 )
    

# milliwatts to millijouls

# 1s = 1000ms

for index, line in enumerate( power_arr ):
    
    power_arr[ index ] = round( line*1000 )
    

# remove start and end

power_arr_new = []

for index, line in enumerate( power_arr ):
    
    if ( 500 < index ) and ( index < 1100 ):
        
        power_arr_new.append( line )
        
    
#~ power_arr_new = []

#~ for index, line in enumerate( power_arr ):
    
    #~ if ( 400 > index ) :
        
        #~ power_arr_new.append( line )
        
    

for line in power_arr_new:
    
    print( line )
    


