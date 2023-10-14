#include <bits/stdc++.h>
using namespace std;

int n;

string TRASH;
unordered_map<string, string> variables;

struct atom{
  string type;
  string content;
  string varname, varval;
  atom *jumpif=NULL, *jumpelse=NULL;
  atom *next=NULL;
  atom *postponed=NULL;
  void process();
};

string RETURNER;
deque<atom*> callstack;
string output;

bool isNumber(string s){
  int sign=0;
  if(s[0]=='-') sign=1;
  if(s[0+sign]=='0') return 0;
  for(int i=sign;i<s.size();++i) if(s[i]<'0'||'9'<s[i]) return 0;
  return 1;
}

string getType(string s){
    if(s=="true"||s=="false") return "boolean";
    else if(isNumber(s)) return "integer";
    else return "string";
}

int getNumber(string s){
  stringstream mystream(s);
  int val=0;
  mystream>>val;
  return val;
}

void atom::process(){
  //cout<<endl<<type<<" "<<content<<endl;
  if(type=="START") callstack.back()=callstack.back()->next;
  if(type=="POSTPONE"){
    callstack.push_back(postponed);
    int x=callstack.size()-2;
    while(x>=0&&callstack[x]!=NULL) swap(callstack[x], callstack[x+1]), x--;
    callstack.back()=callstack.back()->next;
  }
  if(type=="VAR"){
    if(variables.find(varname)!=variables.end()){
      while(!callstack.empty()) callstack.pop_back();
      output="ERROR";
      return;
    }
    string val=varval;
    if(variables.find(varval)!=variables.end()){
      string x=variables[varval];
      val=x;
    }
    variables[varname]=val;
    callstack.back()=callstack.back()->next;
  }
  if(type=="SET"){
    if(variables.find(varname)==variables.end()){
      while(!callstack.empty()) callstack.pop_back();
      output="ERROR";
      return;
    }
    string val=varval;
    if(variables.find(varval)!=variables.end()){
      string x=variables[varval];
      val=x;
    }
    variables[varname]=val;
    callstack.back()=callstack.back()->next;
  }
  if(type=="PRINT"){
    string val=content;
    if(variables.find(content)!=variables.end()){
      string x=variables[content];
      val=x;
    }
    output+=val;
    callstack.back()=callstack.back()->next;
  }
  if(type=="ELIF"){
    string val=content;
    if(variables.find(content)!=variables.end()){
      string x=variables[content];
      if(getType(x)!="boolean"){
        while(!callstack.empty()) callstack.pop_back();
        output="ERROR";
        return;
      }
      val=x;
    }
    //cout<<jumpif<<" "<<jumpelse<<endl;
    if(val=="true"){
      callstack.back()=callstack.back()->next;
      callstack.push_back(NULL);
      callstack.push_back(jumpif);
    }
    else{
      callstack.back()=callstack.back()->next;
      callstack.push_back(NULL);
      callstack.push_back(jumpelse);
    }
  }
  if(type=="END"){
    callstack.pop_back();
  }
  if(type=="RETURN"){
    string val=content;
    if(variables.find(content)!=variables.end()){
      string x=variables[content];
      val=x;
    }
    RETURNER=val;
    while(!callstack.empty()) callstack.pop_back();
  }
}


atom* read(){
  atom* sol=new atom;
  string oper;
  cin>>oper;
  if(oper=="") return NULL;
  //cout<<oper<<endl;

  if(oper=="start") sol->type="START";
  if(oper=="end") sol->type="END";
  if(oper=="var"){
    sol->type="VAR";
    cin>>sol->varname>>sol->varval;
  }
  if(oper=="set"){
    sol->type="SET";
    cin>>sol->varname>>sol->varval;
  }
  if(oper=="postpone"){
    sol->type="POSTPONE";
    sol->postponed=read();
  }
  if(oper=="print"){
    sol->type="PRINT"; 
    cin>>sol->content;
    //cout<<sol->content<<"*"<<endl;
  }
  if(oper=="if"){
    sol->type="ELIF";
    cin>>sol->content;
    sol->jumpif=read();
    cin>>TRASH;
    assert(TRASH=="else");
    //cout<<"___________"<<endl;
    sol->jumpelse=read();
  }
  if(oper=="return"){
    sol->type="RETURN";
    cin>>sol->content;  
    sol->next=read();
    sol->next=NULL;
  }
  if(sol->type!="END"&&sol->type!="RETURN") sol->next=read();
  return sol;
}

int main(){
  cin>>TRASH;
  vector<atom*> functions;
  while(true){
    atom* cr=read();
    if(cr==NULL) break;
    functions.push_back(cr);
  } 
  for(auto it:functions){
    output="";
    variables.clear();
    callstack.push_back(NULL);
    callstack.push_back(it);
    while(!callstack.empty()){
      if(callstack.back()==NULL) callstack.pop_back();
      else callstack.back()->process();
    }
    cout<<output<<endl;
  }
}