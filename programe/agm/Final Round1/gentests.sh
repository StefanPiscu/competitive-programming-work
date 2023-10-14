g++ ./gen.cpp -o gen.exe
g++ ./sol.cpp -o sol.exe
g++ ./solFinal.cpp -o solFinal.exe
for i in $(seq 1 2000)
do
	echo $i | ./gen.exe > "test$i.in" 
	cat "test$i.in" | ./sol.exe > "test$i.ok" 
	cat "test$i.in" | ./solFinal.exe > "test$i.out"
	if cmp --silent -- "test$i.ok" "test$i.out"; then
		rm "test$i.in"
		rm "test$i.out"
		rm "test$i.ok"
	else
  	echo "$i"
	fi	
done