#
# The MIT License (MIT)
#
# Copyright (c) 2022 André Colatino (https://github.com/Colatino/picozoom)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# This file is part of the PicoZoom project.
#
import json
from pathlib import Path

# Header File name
header_name = "a1xfour.h"
file_path=Path('./src/beta/'+header_name)
header_file = open(file_path)

header_lines = header_file.readlines()
header_file.close()
print("File with "+str(len(header_lines))+" lines")

idx_start = header_lines.index('Effect effects[NEFFECTS] = {\n')
idx_end = header_lines.index('};\n')
print("There are "+str(idx_end - idx_start -1)+" effects")

lower_seek_id = 339000000
upper_seek_id = 340000000

change_count = 0
for l in range(idx_start+1,idx_end):
    aux = json.loads(header_lines[l].replace("{","[").replace("}","]").replace(',\n',''))
    if aux[1] >= lower_seek_id and aux[1] <= upper_seek_id:
        old = aux[1]
        # Apply a mask to change from 8 to 7 bytes
        aux[1] = aux[1] & 0x0fffffff
        print(old,aux[1])

        # Format the line to respect header file identation
        line = "  " + json.dumps(aux).replace("[","{ ").replace("]"," }") + ",\n" if l < idx_end-1 else "\n"

        # Change the line in memory
        header_lines[l] = line
        change_count += 1
        
print("Changed "+str(change_count)+" IDs")

if change_count > 0:
    # Write changed lines to original header file
    header_file = open(file_path,"w")
#     f = open("./src/beta/teste.h","w")
    header_file.writelines(header_lines)
    header_file.close()