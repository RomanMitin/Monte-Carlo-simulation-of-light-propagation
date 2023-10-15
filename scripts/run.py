#!/bin/env python3
import sys
import os
import re
import csv
import json
import statistics

binary_path = sys.argv[1]

num_to_run = int(sys.argv[2])
script_output_f = sys.argv[3]

need_to_handle_num_threads = False

if(len(sys.argv) > 4):
    num_threads = int(sys.argv[4])
    need_to_handle_num_threads = True

if(len(sys.argv) > 5):
    input = sys.argv[5]
else:
    input = "~/code/Monte-Carlo-simulation-of-light-propagation/input/two_layers.json"

if(len(sys.argv) > 6):
    output = sys.argv[6]
else:
    output = "/dev/null"

args = input + " " + output

with open(input, "r") as jsonFile:
    data = json.load(jsonFile)

    if need_to_handle_num_threads:
        data["State"]["Thread_num"] = num_threads

        with open(input, "w") as jsonFile:
            json.dump(data, jsonFile)
    else:
        num_threads = data["State"]["Thread_num"]

last_core = num_threads - 1
comand_to_run = "taskset -c 0-" + str(last_core) + " " + binary_path + " " + args

print("Runnig comand: ", comand_to_run)

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


    