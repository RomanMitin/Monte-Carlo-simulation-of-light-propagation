#!/bin/env python3
import sys
import os
import subprocess

binary_path = sys.argv[1]
num_to_run = int(sys.argv[2])
output_folder_name = sys.argv[3]
max_thread_pow = int(sys.argv[4])

os.mkdir(output_folder_name)

for num_threads in [2**pow for pow in range(0, max_thread_pow + 1)]:
    output_file_name = output_folder_name + "/run_" + str(num_threads) + ".csv"
    args_to_run = binary_path + " " + str(num_to_run) + " " + output_file_name + " " + str(num_threads)
    print("--------------- Running with ", num_threads, " threads -----------------")
    subprocess.run(["python3", "../scripts/run.py", binary_path, str(num_to_run), output_file_name, str(num_threads)])

