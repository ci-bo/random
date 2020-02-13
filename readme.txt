Files under /startrek/ were trimmed from https://www-cs-faculty.stanford.edu/~zelenski/rsg/
Thanks to Julie Zelenski for the inspiration and concept, and to Karl Brown for the example.

Instructions (run in a Windows command line):

.\random.exe (filename you'd like to generate from) -o (output file to save results) -c (number of times) -a

-o, -c, and -a are optional.
By default no file will be generated. If unspecified, the program will be run once.
One file will be generated per run. To add results to a single file instead, use "-a" or "--append".

Try:

.\random.exe .\startrek\start -o new_trek -c 1 -a

.\random.exe .\name70k -o outputname -c 3 -a
