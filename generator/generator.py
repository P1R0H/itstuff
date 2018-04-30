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
from lxml import etree

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
        if overwrite in {'Yes', 'yes', 'Y', 'y'}:
            break
        elif overwrite in {'No', 'no', 'N', 'n'}:
            print('File was not modified. To change output file name, run the script with proper argument.\n')
            sys.exit(0)
        else:
            overwrite = input('Invalid input. Valid input is either "Yes" or "No" (alternatively "Y" or "N") ')
    
# Opening files
table_ = csv.reader(open(input_path, "r", encoding='utf-8'), delimiter=',')
config_file = open("ctypes.conf", "r", encoding='utf-8')
config_ = csv.reader(config_file, delimiter=',')

root = etree.Element('reflector', ring_size="1024")

for row in table_:
    for conf_line in config_:
        if row[2] == conf_line[0]:
            root.append(etree.Comment(' GLOBAL-'+row[1]+' '+conf_line[3]+' kbps '))

            # Sources
            tmp = etree.SubElement(root, 'source', id=('source-' + row[3] + '-' + conf_line[1]))
            tmp.set('type', 'ts')
            tmp.set('synchronized_group', row[3])
            etree.SubElement(tmp, 'udp', url='udp:://'+conf_line[2]+row[0]+':1234').set('buffersize', str(BUFFER_SIZE))

            # Sinks
            tmp = etree.SubElement(root, 'sink', id=('sink-' + row[3] + '-' + conf_line[1]))
            tmp.set('source', 'source-'+row[3]+'-'+conf_line[1])
            tmp.set('profile_equivalent_ctype', conf_line[1])
            etree.SubElement(tmp, 'hls', variant_id=row[3]).set('profile_equivalent', conf_line[1])

    config_file.seek(0)
tree = etree.ElementTree(root)
tree.write(output_path)
