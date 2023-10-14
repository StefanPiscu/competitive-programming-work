#include <bits/stdc++.h>
using namespace std;

// 7 8 9 10 A J Q K
// 0 1 2 3  4 5 6 7

int n, nrCards;
int cards[16];

struct State{
	unsigned long long cards :15;//bits hold cards 15 bits;
	unsigned long long topCard :3; //the cards to be attacked 3 bits; 
	unsigned long long playerToTake :2; // player to take the card; 2 bits
	unsigned long long playerToPlay :2; // player to play a card (or pass turn) 2 bits
	unsigned long long pointsOnTable :4; // nr of points on table 4 bits
	unsigned long long points0: 4; // points per player 4-4-4 bits
	unsigned long long points1: 4; // points per player 4-4-4 bits
	unsigned long long points2: 4; // points per player 4-4-4 bits

	long long nr(){
		return cards|(topCard<<15)|(playerToTake<<18)|(playerToPlay<<20)|(pointsOnTable<<22)|(points0<<26)|((long long)points1<<32)|((long long)points2<<36);
	};

	void print(){
		cout<<"Cards: "<<(bitset<15>)(cards)<<"\n";
		cout<<"Top Card: "<<topCard<<"\n";
		cout<<"Player to take: "<<playerToTake<<"\n";
		cout<<"Player to play: "<<playerToPlay<<"\n";
		cout<<"Points on table: "<<pointsOnTable<<"\n";
		cout<<"Points: "<<points0<<" "<<points1<<" "<<points2<<"\n";
		cout<<"---------------------------------------------------\n";
	}

};

unordered_map<long long, bool> whoWon;


bool getOutcome(State s){
	//s.print();
	if(whoWon.find(s.nr())!=whoWon.end()) return whoWon[s.nr()];
	if(s.points0>8) return whoWon[s.nr()]=1;
	else if(s.points1>=8||s.points2>=8) return whoWon[s.nr()]=0;
	int nrCards=__builtin_popcount(s.cards);
	if(nrCards==0){
		if(s.playerToTake==1) s.points0+=s.pointsOnTable;
		else if(s.playerToTake==2) s.points1+=s.pointsOnTable;
		else if(s.playerToTake==3) s.points2+=s.pointsOnTable;
		if(s.points0>s.points1&&s.points0>s.points2) return whoWon[s.nr()]=1;
		else return whoWon[s.nr()]=0;
	}
	int offset=s.playerToPlay*5;
	if(s.playerToTake!=0){
		int playerToTake=s.playerToTake-1;
		if(nrCards%3==0){
			if(playerToTake!=s.playerToPlay){
				for(int card=offset;card<offset+5;++card){
					if(s.cards&(1<<card)&&(cards[card]==s.topCard||(cards[card]==0))){
						// first player retakes
						State t=s;
						t.playerToTake=s.playerToPlay+1;	
						t.cards^=(1<<card);
						t.playerToPlay=(s.playerToPlay+1)%3;
						if(cards[card]==3||cards[card]==4) t.pointsOnTable++;
						if(s.playerToPlay==0){
							if(getOutcome(t)) return whoWon[s.nr()]=1;
						}
						else if(!getOutcome(t)) return whoWon[s.nr()]=0;

					}
				}
			}
			//currentPlayer passes/ can't play
			State t=s;
			t.playerToTake=0;
			t.playerToPlay=playerToTake;
			if(playerToTake==0) t.points0+=s.pointsOnTable;
			else if(playerToTake==1) t.points1+=s.pointsOnTable;
			else if(playerToTake==2) t.points2+=s.pointsOnTable;
			t.pointsOnTable=0;
			if(s.playerToPlay==0){
				if(getOutcome(t)) return whoWon[s.nr()]=1;
			}
			else if(!getOutcome(t)) return whoWon[s.nr()]=0;

		}
		else{
			for(int card=offset;card<offset+5;++card){
				if(s.cards&(1<<card)){
					//player playes card
					State t=s;
					t.playerToPlay=(s.playerToPlay+1)%3;
					t.cards^=(1<<card);
					if(cards[card]==3||cards[card]==4) t.pointsOnTable++;
					if(cards[card]==0||cards[card]==s.topCard){
						t.playerToTake=s.playerToPlay+1;
					}
					if(s.playerToPlay==0){
						if(getOutcome(t)) return whoWon[s.nr()]=1;
					}
					else if(!getOutcome(t)) return whoWon[s.nr()]=0;

				}
			}
		}
	}
	else{
		//first player plays card
		for(int card=offset;card<offset+5;++card){
			if(s.cards&(1<<card)){
				State t=s;
				t.playerToPlay=(s.playerToPlay+1)%3;
				t.cards^=(1<<card);
				t.playerToTake=s.playerToPlay+1;
				t.pointsOnTable=(cards[card]==3||cards[card]==4);
				t.topCard=cards[card];
				if(s.playerToPlay==0){
					if(getOutcome(t)) return whoWon[s.nr()]=1;
				}
				else if(!getOutcome(t)) return whoWon[s.nr()]=0;
			}
		}
	}
	//s.print();
	if(s.playerToPlay==0) return whoWon[s.nr()]=0;
	else return whoWon[s.nr()]=1;
}

int main(){
	int n, k;
	cin>>n>>k;
	int nrCards=n/3;
	for(int player=0;player<3;++player){
		for(int i=0;i<nrCards;++i){
			string x;
			cin>>x;
			if(x=="7") cards[player*5+i]=0;
			if(x=="8") cards[player*5+i]=1;
			if(x=="9") cards[player*5+i]=2;
			if(x=="10") cards[player*5+i]=3;
			if(x=="A") cards[player*5+i]=4;
			if(x=="J") cards[player*5+i]=5;
			if(x=="Q") cards[player*5+i]=6;
			if(x=="K") cards[player*5+i]=7;
		}
	}
	State initialState;
	initialState.playerToPlay=k;
	initialState.playerToTake=0;
	initialState.cards=0;
	initialState.topCard=0;
	for(int i=0;i<3;++i){
		for(int j=0;j<nrCards;++j){
			initialState.cards|=(1<<(i*5+j));
		}
	}
	initialState.points0=0;
	initialState.points1=0;
	initialState.points2=0;
	initialState.pointsOnTable=0;
	if(getOutcome(initialState)) cout<<"YEE!\n";
	else cout<<"OOH...\n";
	return 0;
}