
from defines import *
import os
import shutil 
from Arch import *
from Node import *
from Prg import *
from Configuration import *
# import matplotlib.pyplot as plt
from Runner import *

# ~ 4757098
e_mw = 9.175
# ~ a_mw = 4.93
a_mw = 8.735

NONE = 4.25
I1 = 5.07
I2 = 4.76
F_Units_1 = 4.141
F_Units_2 = 4.011

# Power consumption of different core settings

# No multiplication
I0_F0_mw = NONE
# Only Exact Int
I1_F0_mw = I1 
# Only Approximate int
I2_F0_mw = I2
# Only Exact Float
I0_F1_mw = NONE + F_Units_1
# Only approximate Float
I0_F2_mw = NONE + F_Units_2
# Exact Int and Exact Float
I1_F1_mw = I1 + F_Units_1
# Exact Int and Approximate Float
I1_F2_mw = I1 + F_Units_2
# Approximate Int and Exact Float
I2_F1_mw = I2 + F_Units_1
# Approximate Int and Approximate Float
I2_F2_mw = I2 + F_Units_2

# Create the architecture and assign Names and power
arch_I0_F0      = Arch( 0,I0_F0_mw,0,0 )            # No multiplication
arch_I1_F0      = Arch( 0,I1_F0_mw,1,0 )            # Only Exact Int
arch_I2_F0      = Arch( 1,I2_F0_mw,2,0 )            # Only Approximate int
arch_I0_F1      = Arch( 0,I0_F1_mw,0,1 )            # Only Exact Float
arch_I0_F2      = Arch( 0,I0_F2_mw,0,2 )            # Only approximate Float
arch_I1_F1      = Arch( 0,I1_F1_mw,1,1 )            # Exact Int and Exact Float
arch_I1_F2      = Arch( 0,I1_F2_mw,1,2 )            # Exact Int and Approximate Float
arch_I2_F1      = Arch( 1,I2_F1_mw,2,1 )            # Approximate Int and Exact Float
arch_I2_F2      = Arch( 1,I2_F2_mw,2,2 )            # Approximate Int and Approximate Float



archs = [arch_I0_F0,
         arch_I1_F0,
         arch_I2_F0,
         arch_I0_F1,
         arch_I0_F2,
         arch_I1_F1,
         arch_I1_F2,
         arch_I2_F1,
         arch_I2_F2]

configurations = []
configurations.append( Configuration( "FF", "FF", archs ) )
configurations.append( Configuration( "BF", "BF", archs ) )
configurations.append( Configuration( "WF", "WF", archs ) )
#configurations.append( Configuration( 1, "10", [arch_a, arch_e] ) )
# ~ configurations.append( Configuration( 2, "11", [arch_a, arch_a] ) )

prgs = []

# ~ prgs.append( Prg( 10, "sharpen_mul"  , 95.57   , 78.07   ) )
# ~ prgs.append( Prg(  9, "qsort"        , 26.93   , 5.22    ) )
# ~ prgs.append( Prg(  8, "grayscale"    , 89.83   , 25.55   ) )
# ~ prgs.append( Prg(  7, "aes"          , 1651.60 , 1651.60 ) )
# ~ prgs.append( Prg(  6, "blowfish"     , 397.57  , 397.57  ) )
# ~ prgs.append( Prg(  5, "square_mmult" , 9.61    , 7.67    ) )
# ~ prgs.append( Prg(  4, "sha256"       , 50.50   , 50.44   ) )
# ~ prgs.append( Prg(  3, "primes"       , 2.69    , 2.69    ) )
# ~ prgs.append( Prg(  2, "norx"         , 57.09   , 57.09   ) )
# ~ prgs.append( Prg(  1, "msort"        , 21.45   , 21.45   ) )
# ~ prgs.append( Prg(  0, "dhrystone"    , 26.63   , 26.52   ) )

# ~ prgs.append( Prg(  0, "dhrystone"    , 26.63   , 26.52   ) )
# ~ prgs.append( Prg(  1, "msort"        , 21.45   , 21.45   ) )
# ~ prgs.append( Prg(  2, "norx"         , 57.09   , 57.09   ) )
# ~ prgs.append( Prg(  3, "primes"       , 2.69    , 2.69    ) )
# ~ prgs.append( Prg(  4, "sha256"       , 50.50   , 50.44   ) )
# ~ prgs.append( Prg(  5, "square_mmult" , 9.61    , 7.67    ) )
# ~ prgs.append( Prg(  6, "blowfish"     , 397.57  , 397.57  ) )
# ~ prgs.append( Prg(  7, "aes"          , 1651.60 , 1651.60 ) )
# ~ prgs.append( Prg(  8, "grayscale"    , 89.83   , 25.55   ) )
# ~ prgs.append( Prg(  9, "qsort"        , 26.93   , 5.22    ) )
# ~ prgs.append( Prg( 10, "sharpen_mul"  , 95.57   , 78.07   ) )
# #######
prgs.append( Prg(  0, "susan"        , 146710  , 144603.93  , 2,2 ) )
prgs.append( Prg(  9, "dhrystone"    , 26.63   , 26.52      , 2,0 ) )
prgs.append( Prg( 10, "sharpen_mul"  , 95.57   , 78.07      , 2,0 ) )
prgs.append( Prg( 11, "square_mmult" , 9.61    , 7.67       , 2,0 ) )
prgs.append( Prg( 12, "grayscale"    , 89.83   , 25.55      , 2,0 ) )
prgs.append( Prg(  1, "FFT"          , 709308  , 709308     , 0,2    ) )
prgs.append( Prg(  2, "basicmath"    , 55010   , 55010      , 1,1  ) )
prgs.append( Prg(  3, "crc32"        , 23686   , 23686      , 0,0    ) )
prgs.append( Prg(  4, "aes"          , 1651.60 , 1651.60    , 0,0    ) )
prgs.append( Prg(  5, "stringsearch" , 530     , 530        , 0,0    ) )
prgs.append( Prg(  6, "blowfish"     , 397.57  , 397.57     , 0,0    ) )
prgs.append( Prg(  7, "sha256"       , 50.50   , 50.44      , 1,0  ) )
prgs.append( Prg(  8, "qsort"        , 26.93   , 5.22       , 1,0  ) )
prgs.append( Prg( 13, "msort"        , 21.45   , 21.45      , 0,0    ) )
prgs.append( Prg( 14, "norx"         , 57.09   , 57.09      , 0,0    ) )
prgs.append( Prg( 15, "primes"       , 2.69    , 2.69       , 0,0    ) )


######
 

# ~ prgs.append( Prg(  6, "grayscale"    , 89.83   , 25.55   , PREF_APPROX ) )
# ~ prgs.append( Prg(  7, "qsort"        , 26.93   , 5.22    , PREF_EXACT  ) )
# ~ prgs.append( Prg(  8, "sharpen_mul"  , 95.57   , 78.07   , PREF_APPROX ) )

# prgs = sorted(prgs, key=lambda Prg: Prg.c[0])
# prgs.reverse()
runner = Runner()

bookie = Bookie()


# void = runner.run_once( configurations, prgs, 5, 10 )
# ~ void = runner.run_until_succ( configurations, prgs, 5, 10 )
# ~ void = runner.run_100( configurations, prgs, 5, 10 )
# void = runner.run_ranges( configurations, prgs, 0.25, 0.25, 5, 5, bookie )

# ~ void = runner.run_multi_ranges( configurations, prgs, 0.5, 0.25, 5, 5, 1000, bookie )
prgs.reverse()
for i in prgs:
    print(i.name)
void = runner.run_multi_ranges( configurations, prgs, 1, 0.25, 15, 5, 1, bookie )

for conf_record in bookie.record:
    # Create directory
    directory_name = "./../" + conf_record
    if os.path.exists(directory_name):
        shutil.rmtree(directory_name)

    # Recreate the directory
    os.makedirs(directory_name)
    for per_record in bookie.record[ conf_record ]:
        file_name = directory_name + "/" +str(per_record)
        with open(file_name, "w") as file:
            for idx in bookie.record[ conf_record ][ per_record ]:
                file.write(f"{idx}\n")

