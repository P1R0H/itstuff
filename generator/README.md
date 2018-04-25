# Reflector XML generator
simple python script generating XML document for reflectors from sources structured as csv table. 
@author Andrej Dravecky
```
Python v3 or above required,
configuration file "ctypes.conf" has to be present in the working directory

First argument contains input file path (or filename if in working dir)
Second argument contains output file path (optional, default output file is "reflector.xml")

!!!SCRIPT OVERWRITES PREVIOUS OUTPUT FILE WITH THE SAME NAME, BACK IT UP OR YOU WILL LOOSE DATA!!!

install dependencies:
$ apt-get update && apt-get install python3

run script: 
$ python3 generator.py example_input.csv (optional_output.xml)
```
