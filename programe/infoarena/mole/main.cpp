#include <vector>
using namespace std;


// Antetul functiei. Nu apela functia ask de aici in sus
int ask(std::vector<int> guess);



// Functia ceruta
std::vector<int> find_standings(int N) {
	vector<int> position(N+1);
	vector<int> toAsk(N);
	for(int i=1;i<=N;++i){
		int cr=0;
		toAsk[cr++]=i;
		for(int j=1;j<=N;++j){
			if(j==i) continue;
			toAsk[cr++]=j;
		}
		int a=ask(toAsk);
		for(int i=0;i+1<N;++i){
			swap(toAsk[i], toAsk[i+1]);
		}
		int b=ask(toAsk);
		// a = nr de elemente mai mici + inversiuni intre restul
		// b = nr de elemnte mai mari + inversiuni intre restul
		// a-b = nr de elemente mai mici - nr de elemente mai mari
		// n-1 = nr de elemente mai mici + nr de elemente mai mari
		// a-b+n-1 = 2*nr de elemente mai mici
		// pozitia = (a-b+N-1)/2
		position[i]=(a-b+N-1)/2;
	}
	vector<int> solution(N);
	for(int i=1;i<=N;++i) solution[position[i]]=i;
	return solution;
}

// Graderul comisiei. Ignora codul de aici in jos

#include <iostream>

int ask(std::vector<int> guess) {
	int rez;
	std::cout << "1 ";
	for(auto it: guess)
		std::cout << it << ' ';
	std::cout << std::endl;

	std::cin >> rez;
	
	if(rez == -1)
		exit(0);

	return rez;
}

int main() {
	int N;
	std::vector<int> rez;
	
	std::cin >> N;
	rez = find_standings(N);

	std::cout << "0 ";
	for(auto it: rez)
		std::cout << it << " ";
	std::cout << std::endl;
	
	return 0;
}

