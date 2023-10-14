#include <bits/stdc++.h>
using namespace std;

int getSec(string s){
  int val=0;
  val+=(s[0]-'0')*6000;
  val+=(s[1]-'0')*600;
  val+=(s[3]-'0')*100;
  val+=(s[4]-'0')*10;
  val+=(s[6]-'0');
  return val;
}

string getTime(int val){
  string sol="00:00.0";
  sol[6]=val%10+'0';
  val/=10;
  sol[4]=val%10+'0';
  val/=10;
  sol[3]=val%6+'0';
  val/=6;
  sol[1]=val%10+'0';
  val/=10;
  sol[0]=val%10+'0';
  return sol;
}

int cr[3];
int nr[3];
int nrs[3];
int t[6][6];

struct event{
  int time;
  int team;
  int type; //0 minor ,1 major, 2 goal, 3 minor over 4 major over
  void process();
  bool operator<(const event &ot) const{
    return time>ot.time;
  }
};
priority_queue<event> events;
int crtime=0;

void event::process(){
  t[cr[1]][cr[2]]+=(time-crtime);
  crtime=time;
  //cout<<getTime(time)<<" "<<team<<" "<<type<<" "<<cr[1]<<"x"<<cr[2]<<"\n";
  if(type==-1){
    while(!events.empty()){
      events.pop();
    }
  }
  if(type==0){
    cr[team]--;
    nr[team]++;
    events.push({time+2*600, team, 3});
  }
  if(type==1){
    cr[team]--;
    events.push({time+5*600, team, 4});
  }
  if(type==2){
    if(cr[3-team]<cr[team]&&(nr[3-team]>nrs[3-team])) nrs[3-team]++, cr[3-team]++;
  }
  if(type==3){
    if(nrs[team]) nrs[team]--;
    else cr[team]++;
    nr[team]--;
  }
  if(type==4){
    cr[team]++;
  }
}



int main(){
  int n;
  cin>>n;
  cr[1]=5;
  cr[2]=5;
  for(int i=1;i<=n;++i){
    string s;
    int team;
    string tip;
    cin>>s>>team>>tip;
    event x;
    x.time=getSec(s);
    x.team=team;
    if(tip=="minor") x.type=0;
    if(tip=="major") x.type=1;
    if(tip=="goal") x.type=2;
    events.push(x);
  }
  events.push({getSec("60:00.0"), 0, -1});
  while(!events.empty()){
    event x=events.top();
    events.pop();
    x.process();
  } 
  for(int i=0;i<=5;++i){
    for(int j=0;j<=5;++j){
      if(t[i][j]) cout<<i<<"x"<<j<<" "<<getTime(t[i][j])<<"\n";
    }
  }
  return 0;
}