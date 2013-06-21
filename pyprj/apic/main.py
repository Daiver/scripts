# -*- coding: utf-8 *-*
import os

import logging
logging.basicConfig(level=logging.DEBUG)

from core.ProgramManager import ProgramManager

pm = ProgramManager(os.path.dirname(__file__))
pm.LoadAllPlugins()
pm.RegAllPlugins()
print pm.API
pm.run()
