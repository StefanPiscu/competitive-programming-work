g++ generator.cpp -o generator.exe
#g++ brut.cpp -o brut.exe
#g++ brut2.cpp -o brut2.exe
g++ sol100.cpp -o sol100.exe
g++ sqrt.cpp -o sqrt.exe


for i in $(seq 1 10)
do
	echo $i
	echo $i 50000 10000 50000 | ./generator.exe > "tests/test$i.in"
	#cat "tests/test$i.in" | ./brut.exe > "tests/test$i.out_brut"
	#cat "tests/test$i.in" | ./brut.exe > "tests/test$i.out_brut2"
	cat "tests/test$i.in" | ./sol100.exe > "tests/test$i.out_sol"
	cat "tests/test$i.in" | ./sqrt.exe > "tests/test$i.out_sqrt"
	if cmp -s  tests/test$i.out_sqrt  tests/test$i.out_sol  
	then
		:
		#rm "tests/test$i.in"
		#rm "tests/test$i.out_sol"
		#rm "tests/test$i.out_brut"
		#rm "tests/test$i.out_brut2"
		#rm "tests/test$i.out_sqrt"
	else 
		echo $i
	fi
done