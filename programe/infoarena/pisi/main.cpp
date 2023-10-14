#include <bits/stdc++.h>
using namespace std;

// Functia ceruta

int n;
vector<array<int, 3>> v;
vector<int> sol;

bool cmp(int i, int j){
	int score=0;
	score=(v[i][0]>v[j][0])+(v[i][1]>v[j][1])+(v[i][2]>v[j][2]);
	return score>=2;
}

struct FenwickTree{
	int n;
	vector<int> val;

	FenwickTree(int _n){
		n=_n+1;
		val.resize(n+1, 1e9);
	}

	int query(int r){
		int sol=1e9;
		for(int i=r;i>0;i-=(i&-i)){
			sol=min(sol, val[i]);
		}
		//cout<<"query "<<r<<" "<<sol<<endl;
		return sol;
	}

	void update(int poz, int value){
		//cout<<"update"<<poz<<" "<<value<<endl;
		for(int i=poz;i<=n;i+=(i&-i)) val[i]=min(value, val[i]);
	}

};

std::vector<int> rank_cats(std::vector<int> p, std::vector<int> f, std::vector<int> d) {
	n=p.size();
	v.resize(n+1);
	for(int i=0;i<n;++i){
		v[p[i]][0]=i+1;
		v[f[i]][1]=i+1;
		v[d[i]][2]=i+1;
	}
	sol.resize(n);
	for(int i=0;i<n;++i) sol[i]=i+1;
	sort(sol.begin(), sol.end(), cmp);
	for(int tx=0;tx<3;++tx){
		for(int ty=tx+1;ty<3;++ty){
			FenwickTree DS(n);
			for(int i=0;i<n;++i){
				int x=v[sol[i]][tx], y=v[sol[i]][ty];
				int minY=DS.query(x); //min on prefix
				//cout<<x<<" "<<minY<<"**\n";
				if(minY<y){
					return std::vector<int>();
				};
				//cout<<x<<" "<<y<<"*****\n";
				DS.update(x, y); // set value - doesn't overide
			}
		}
	}
	reverse(sol.begin(), sol.end());
	return sol;
}

// Graderul comisiei. Ignora codul de aici in jos

#include <stdio.h>
#include <ctype.h>
#include <cstring>
 
class InParser {
private:
	FILE *fin;
	char *buff;
	int sp;
 
	char read_ch() {
		++sp;
		if (sp == 4096) {
			sp = 0;
			fread(buff, 1, 4096, fin);
		}
		return buff[sp];
	}
 
public:
	InParser(const char* nume) {
		fin = fopen(nume, "r");
		buff = new char[4096]();
		sp = 4095;
	}
	
	InParser& operator >> (int &n) {
		char c;
		while (!isdigit(c = read_ch()) && c != '-');
		int sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}
	
	InParser& operator >> (long long &n) {
		char c;
		n = 0;
		while (!isdigit(c = read_ch()) && c != '-');
		long long sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}
};
	
 
class OutParser {
private:
    FILE *fout;
    char *buff;
    int sp;
 
    void write_ch(char ch) {
        if (sp == 50000) {
            fwrite(buff, 1, 50000, fout);
            sp = 0;
            buff[sp++] = ch;
        } else {
            buff[sp++] = ch;
        }
    }
 
 
public:
    OutParser(const char* name) {
        fout = fopen(name, "w");
        buff = new char[50000]();
        sp = 0;
    }
    ~OutParser() {
        fwrite(buff, 1, sp, fout);
        fclose(fout);
    }
 
    OutParser& operator << (int vu32) {
        if (vu32 <= 9) {
            write_ch(vu32 + '0');
        } else {
            (*this) << (vu32 / 10);
            write_ch(vu32 % 10 + '0');
        }
        return *this;
    }
	
    OutParser& operator << (long long vu64) {
        if (vu64 <= 9) {
            write_ch(vu64 + '0');
        } else {
            (*this) << (vu64 / 10);
            write_ch(vu64 % 10 + '0');
        }
        return *this;
    }
 
    OutParser& operator << (char ch) {
        write_ch(ch);
        return *this;
    }
    OutParser& operator << (const char *ch) {
        while (*ch) {
            write_ch(*ch);
            ++ch;
        }
        return *this;
    }
};

int main() {
	int T;

	InParser fin("pisi.in");
	OutParser fout("pisi.out");
	
	fin >> T;
	while(T--) {
		int N, x;
		std::vector<int> p, f, d, rez;
		fin >> N;
		
		for(int i = 0; i < N; ++i) {
			fin >> x;
			p.push_back(x);
		}
		for(int i = 0; i < N; ++i) {
			fin >> x;
			f.push_back(x);
		}
		for(int i = 0; i < N; ++i) {
			fin >> x;
			d.push_back(x);
		}

		rez = rank_cats(p, f, d);
	
		if(rez.size() == 0)
			fout << "-1\n";
		else {
			for(auto it: rez)
				fout << it << ' ';
			fout << '\n';
		}
	}
	return 0;
}

