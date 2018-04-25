"""
Reflector XML generator
simple python script generating XML document for reflectors from csv table. 
@author Andrej Dravecky

Python v3 or above required,
configuration file "ctypes.conf" has to be present in the working directory

First argument contains input file path (or filename if in working dir)
Second argument contains output file path (optional, default output file is "reflector.xml")

!!!SCRIPT OVERWRITES PREVIOUS OUTPUT FILE WITH THE SAME NAME, BACK IT UP OR YOU WILL LOOSE DATA!!!

install dependencies:
$ apt-get update && apt-get install python3

run script: 
$ python3 generator.py example_input.csv (optional_output.xml)
"""

import csv
import os
import sys

BUFFER_SIZE = 8388608

# Testing files, arguments etc...
if not 2 <= len(sys.argv) <= 3:
    sys.exit("Invalid number of arguments! (1 or 2 expected, " + str((len(sys.argv) - 1)) + " given)\n")

input_path = sys.argv[1]
if not os.path.isfile(input_path):
    sys.exit("File " + input_path + " does not exist!\n")
if not os.path.isfile("ctypes.conf"):
    sys.exit("Config file missing!\n")

output_path = "reflector.xml"
if len(sys.argv) == 3:
    output_path = sys.argv[2]

if os.path.isfile(output_path):
    overwrite = input("Output file already exists. Overwrite? [yes/no] ")
    while True:
        if overwrite in  {'Yes', 'yes', 'Y', 'y'}:
            break
        elif overwrite in {'No', 'no', 'N', 'n'}:
            print('File was not modified. To change output file name, run the script with proper argument.\n')
            sys.exit(0)
        else:
            overwrite = input('Invalid input. Valid input is either "Yes" or "No" (alternatively "Y" or "N") ')
    
# Opening files
table_ = csv.reader(open(input_path, "r", encoding='utf-8'), delimiter=',')
out_ = open(output_path, "w", encoding='utf-8')

# Header
out_.write('<?xml version="1.0" encoding="utf-8"?>\n'
           '<!DOCTYPE reflector SYSTEM "/etc/tve/reflector.dtd">\n'
           '<reflector ring_size="1024">\n\n')

for row in table_:
    config_ = csv.reader(open("ctypes.conf", "r", encoding='utf-8'), delimiter=',')
    for conf_line in config_:
        if row[3] == conf_line[0]:

            # Sources
            out_.write('<!-- GLOBAL-' + row[0] + ' ' + conf_line[3] + ' kbps -->\n'
                       '<source id="source-' + row[1] + '-' + conf_line[1] +
                       '" type="ts" synchronized_group="' + row[1] + '" >\n'
                       '\t<udp url="udp://' + conf_line[2] + row[2] +
                       ':1234" buffersize="' + str(BUFFER_SIZE) + '"/>\n</source>\n\n')

            # Sinks
            out_.write('<sink id="sink-' + row[1] + '-' + conf_line[1] +
                       '" source="source-' + row[1] + '-' + conf_line[1] + '" >\n'
                       '\t<hls variant_id="' + row[1] + '" profile_equivalent_ctype="' +
                       conf_line[1] + '"/>\n</sink>\n\n')

# Reflector closure
out_.write('</reflector>\n\n')

print('SUCCESS\n')
