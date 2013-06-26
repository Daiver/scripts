
import sys

from CF.FlagReader import FlagReader

freader = FlagReader(sys.argv[1:])

print freader.flags

print freader.flags['t']

print freader.lastparams

print freader.firstparams
