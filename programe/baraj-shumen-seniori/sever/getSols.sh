g++ src/sol100.cpp -o src/sol100.exe

for i in $(seq 1 20)
do
	cat "grader_tests/grader_test$i.in" | src/sol100.exe > "grader_tests/grader_test$i.ok"
done