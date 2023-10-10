#!/bin/env python
import sys
import os
import re
import csv
import statistics

binary_path = sys.argv[1]

num_to_run = int(sys.argv[2])
script_output_f = sys.argv[3]

if(len(sys.argv) > 4):
    input = sys.argv[4]
else:
    input = "~/code/Monte-Carlo-simulation-of-light-propagation/input/two_layers.json"

if(len(sys.argv) > 5):
    output = sys.argv[5]
else:
    output = "/dev/null"

args = input + " " + output

print("Running ", binary_path)
print("With args ", args)

comand_to_run = "taskset -c 0-7 " + binary_path + " " + args

res_list = []

for i in range(0, num_to_run):
    print("Run: ", i)
    stream = os.popen(comand_to_run)
    matches = re.findall("\d+\.\d*", stream.read())
    res_list.append(float(matches[1]))

mean = statistics.mean(res_list)
stdev = statistics.stdev(res_list)

with open(script_output_f, "w", newline='') as resultFile:
    wr = csv.writer(resultFile, dialect='excel')
    for ind, var in enumerate(res_list):
        wr.writerow([ind, var])
    wr.writerow([])
    wr.writerow(["mean", mean])
    wr.writerow(["stdev", stdev])


    