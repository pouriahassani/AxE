
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

arch_e = Arch( ARCH_EXACT, "exact", e_mw )
arch_a = Arch( ARCH_APPRX, "apprx", a_mw )

archs = []
archs.append( arch_e )
archs.append( arch_a )

configurations = []
# configurations.append( Configuration( 0, "00", [arch_e, arch_e] ) )
configurations.append( Configuration( 1, "10", [arch_a, arch_e] ) )
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
prgs.append( Prg(  0, "susan"        , 146710  , 144603.93  , PREF_APPROX ) )
prgs.append( Prg(  9, "dhrystone"    , 26.63   , 26.52      , PREF_APPROX ) )
prgs.append( Prg( 10, "sharpen_mul"  , 95.57   , 78.07      , PREF_APPROX ) )
prgs.append( Prg( 11, "square_mmult" , 9.61    , 7.67       , PREF_APPROX ) )
prgs.append( Prg( 12, "grayscale"    , 89.83   , 25.55      , PREF_APPROX ) )
prgs.append( Prg(  1, "FFT"          , 709308  , 709308     , PREF_APPROX    ) )
prgs.append( Prg(  2, "basicmath"    , 55010   , 55010      , PREF_EXACT  ) )
prgs.append( Prg(  3, "crc32"        , 23686   , 23686      , PREF_ANY    ) )
prgs.append( Prg(  4, "aes"          , 1651.60 , 1651.60    , PREF_ANY    ) )
prgs.append( Prg(  5, "stringsearch" , 530     , 530        , PREF_ANY    ) )
prgs.append( Prg(  6, "blowfish"     , 397.57  , 397.57     , PREF_ANY    ) )
prgs.append( Prg(  7, "sha256"       , 50.50   , 50.44      , PREF_EXACT  ) )
prgs.append( Prg(  8, "qsort"        , 26.93   , 5.22       , PREF_EXACT  ) )
prgs.append( Prg( 13, "msort"        , 21.45   , 21.45      , PREF_ANY    ) )
prgs.append( Prg( 14, "norx"         , 57.09   , 57.09      , PREF_ANY    ) )
prgs.append( Prg( 15, "primes"       , 2.69    , 2.69       , PREF_ANY    ) )





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
void = runner.run_multi_ranges( configurations, prgs, 10, 0.5, 12, 5, 1, bookie )
# Create directory
directory_name = "./data_AAe"
if os.path.exists(directory_name):
    shutil.rmtree(directory_name)

# Recreate the directory
os.makedirs(directory_name)
for conf_record in bookie.record:
    for per_record in bookie.record[ conf_record ]:
        
        s = ""
        
        s += str( conf_record ) + "\t" + str( per_record ) + "\t"
        
        s += str( min( bookie.record[ conf_record ][ per_record ] ) ) + "\t"
        s += str( max( bookie.record[ conf_record ][ per_record ] ) )
        
        # print( s )

for conf_record in bookie.record:


    for per_record in bookie.record[ conf_record ]:
        # if("_success" in per_record or "_no" in per_record or "_fail" in per_record):
        #     file_name = directory_name + "/" + str(conf_record) + "_Success_fail_no"
        #     with open(file_name, "w") as file:
        #          file.write(f"{per_record}\t:{bookie.record[ conf_record ][ per_record ]}")
                   

        # else:
        file_name = directory_name + "/" + str(conf_record) + '_' +str(per_record)
        with open(file_name, "w") as file:
            for idx in bookie.record[ conf_record ][ per_record ]:
                file.write(f"{idx}\n")

#         if "run_idx" in per_record:
#             file_name = str(conf_record) + str(per_record) 
#             with open(file_name, "w") as file:
#                 for idx in bookie.record[ conf_record ][ per_record ]:
#                     file.write(f"{idx}\n")
        
#         if "run_idx" in per_record:
#             file_name = str(conf_record) + "time"
#             with open(file_name, "w") as file:
#                 for idx in bookie.record[ conf_record ][ per_record ]:
#                     file.write(f"{idx}\n")

#         if "run_idx" in per_record:
#             file_name = str(conf_record) + "_fail"
#             with open(file_name, "w") as file:
#                 for idx in bookie.record[ conf_record ][ per_record ]:
#                     file.write(f"{idx}\n")

#         if "run_idx" in per_record:
#             file_name = str(conf_record) + "_no_choices"
#             with open(file_name, "w") as file:
#                 for idx in bookie.record[ conf_record ][ per_record ]:
#                     file.write(f"{idx}\n")

            # s = ""
            # s += str( conf_record ) + "\t" + str( per_record ) + "\t"
            # # for up in 
            # s += str( min( bookie.record[ conf_record ][ per_record ] ) ) + "\t"
            # s += str( max( bookie.record[ conf_record ][ per_record ] ) )
            # if(len( bookie.record[ conf_record ][ per_record ] ) != 0):
            #     s += "\navg" + str( sum( bookie.record[ conf_record ][ per_record ] ) / len( bookie.record[ conf_record ][ per_record ] ) )
            
            #     file.write(f"{s}\n")
            
            # print( s )
        
    

# ~ for configuration in configurations:
    # ~ print( configuration.report() )

# ~ for configuration in configurations:
    # ~ print( configuration.p() )

# ~ for configuration in configurations:
    # ~ print( configuration.report() )

# ~ for prg in prgs:
    # ~ print( prg.p() )
