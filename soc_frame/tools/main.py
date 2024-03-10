
import os
import json
import sys

import logging
import logging.handlers

from defines import *

from func_files import *
from func_addr import *

from memory import *
from simulator import *

from system import *
from system_spsoc import *
from system_mpsoc import *

from software import *
from software_program import *
from software_controller import *

os.system( "python3 run_mpsoc.py" + " " + sys.argv[1])

exit()
