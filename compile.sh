#!/bin/bash
cpp_to_executable=( \
	"brute_force.cpp		BFwilliam" \
	"sort_flags.cpp			SFwilliam" \
	"verify_red.cpp			DSwilliam" \
	"break_segments.cpp		BSwilliam" \
	"get_above_below.cpp		ABwilliam"		
)

mkdir -p build

for str in "${cpp_to_executable[@]}"; do 
	str_arr=($str) # convert string to array to separate white space
	file=${str_arr[0]}
	executable=${str_arr[1]}
	g++ $file -std=c++17 -o build/$executable
done