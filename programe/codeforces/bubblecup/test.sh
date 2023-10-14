
for i in $(seq 1 10000);
do
  echo $i | ./jgen.out > test.txt
  cat test.txt | ./j.out
  cat test.txt
done