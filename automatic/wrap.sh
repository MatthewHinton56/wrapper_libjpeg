#/bin/bash
input_header=$1
gcc -E -x c -P -C -traditional-cpp -I . $input_header > $1.pre
python extract.py $1.pre