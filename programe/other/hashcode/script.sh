g++ main.cpp -O3 -std=c++14 -o main

echo "COMPILED"

cat a.txt | ./main 1> a.out 2> a.err
echo "A"
(cat b.txt | ./main 1> b.out 2> b.err)&
echo "B"
(cat c.txt | ./main 1> c.out 2> c.err)&
echo "C"
(cat d.txt | ./main 1> d.out 2> d.err)&
echo "D"
(cat e.txt | ./main 1> e.out 2> e.err)&
echo "E"
(cat f.txt | ./main 1> f.out 2> f.err)&
echo "F"