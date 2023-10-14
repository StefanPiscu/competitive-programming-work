g++ -Wall -std=c++17 -fsanitize=undefined,address,signed-integer-overflow m.cpp -o m.out
time cat input.txt | ./m.out > output.txt