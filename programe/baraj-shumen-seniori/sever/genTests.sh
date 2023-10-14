g++ src/generator.cpp -o src/generator.exe
# N M Q
# N, Q < 5000
echo 1 500 10 500 | src/generator.exe > "grader_tests/grader_test1.in"
echo 2 5000 500 2000 | src/generator.exe > "grader_tests/grader_test2.in"
echo 3 5000 2000 5000 | src/generator.exe > "grader_tests/grader_test3.in"

# M < 100
echo 4 50000 10 50000 | src/generator.exe > "grader_tests/grader_test4.in"
echo 5 75000  50 75000| src/generator.exe > "grader_tests/grader_test5.in"
echo 6 150000 100 100000 | src/generator.exe > "grader_tests/grader_test6.in"
echo 7 200000 100 200000 | src/generator.exe > "grader_tests/grader_test7.in"

# N, M, Q < 50000
echo 8 25000 500 25000 | src/generator.exe > "grader_tests/grader_test8.in"
echo 9 25000  5000 25000| src/generator.exe > "grader_tests/grader_test9.in"
echo 10 30000 10000 30000 | src/generator.exe > "grader_tests/grader_test10.in"
echo 11 40000 15000 40000 | src/generator.exe > "grader_tests/grader_test11.in"
echo 12 50000 15000 50000 | src/generator.exe > "grader_tests/grader_test12.in"
echo 13 50000 20000 50000 | src/generator.exe > "grader_tests/grader_test13.in"
#Test cu lant mare
echo 14 50000 30000 50000 | src/generator.exe > "grader_tests/grader_test14.in"

# N, M, Q < 200000
echo 15 100000 5000 100000 | src/generator.exe > "grader_tests/grader_test15.in"
echo 16 200000 25000 200000 | src/generator.exe > "grader_tests/grader_test16.in"
echo 17 200000 50000 200000 | src/generator.exe > "grader_tests/grader_test17.in"
echo 18 200000 100000 200000 | src/generator.exe > "grader_tests/grader_test18.in"
echo 19 200000 150000 200000 | src/generator.exe > "grader_tests/grader_test19.in"
echo 20 200000 150000 200000 | src/generator.exe > "grader_tests/grader_test20.in"

