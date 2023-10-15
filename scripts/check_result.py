#!/bin/env python3
import struct
import numpy as np

def normalize(arr):
    max_val = max(arr)
    arr /= max_val

def get_data_from_file(path):
    with open(path, mode='rb') as file:
        fileContent = file.read()
    corteg_size = struct.unpack("QQ", fileContent[:16])
    size = corteg_size[0] * corteg_size[1]

    arr = np.zeros(size)
    for i in range(0, size):
        start = i * 8 + 16
        end = i * 8 + 24
        num = struct.unpack("d", fileContent[start:end])
        arr[i] = num[0]
    return arr

def get_distance(first : np.array, sec : np.array):
    diff = abs(first - sec)
    count = 0.0
    for elem in diff:
        count += elem
    return count

    
    

def check_result(path_to_etalon, path_to_new_res):
    etalon = get_data_from_file(path_to_etalon)
    new_res = get_data_from_file(path_to_new_res)

    if(etalon.size != new_res.size):
        return False
    
    normalize(etalon)
    normalize(new_res)
    max_diff = abs(etalon - new_res).max()
    dist = get_distance(etalon, new_res)
    # print("Check distance =", dist)
    return dist <= 25, dist


if __name__ == "__main__":
    res = check_result("/home/roman/code/Monte-Carlo-simulation-of-light-propagation/output/two_layers_etalon_double.bin", 
                 "/home/roman/code/Monte-Carlo-simulation-of-light-propagation/output/two_layers_wrong_double.bin")
    
    # print("Check result =", res)