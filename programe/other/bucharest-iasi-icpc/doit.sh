g++ hgen.cpp -o hgen.out
g++ checker.cpp -o checker.out


rm ans.txt
for i in $(seq 1 10)
do
  echo $i | ./hgen.out > test.txt
  cat test.txt | ./h.out >> ans.txt
  cat test.txt | ./h2.out >> ans.txt
  echo "-------" >> ans.txt
done
cat ans.txt