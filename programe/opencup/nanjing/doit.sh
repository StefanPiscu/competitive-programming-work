g++ d.cpp -o d.out
g++ dgen.cpp -o dgen.out
g++ dtest.cpp -o dtest.out

for i in $(seq 1 20);
do
  echo "$i" | ./dgen.out > test.txt
  cat test.txt

  cat test.txt | ./dtest.out > ans.txt
  cat test.txt | ./d.out > response.txt
  #cat ans.txt
  #cat response.txt
  diff -q $dst $new > /dev/null
  if ($status) then cat test.txt
done