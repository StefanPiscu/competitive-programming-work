#include <fstream>
#include <chrono>
#include <random>

std::ifstream cin("secv8.in");
std::ofstream cout("secv8.out");

#include <chrono>
#include <random>

namespace Treap{
  template <typename Node>
  class Treap{
    static std::mt19937 rng;

    struct TreapNode{
      Node data;
      std::uint32_t prio=rng();
      int cnt=0;

      TreapNode *leftSon = nullptr, *rightSon = nullptr;
      bool isReversed = false;

      TreapNode();
      TreapNode(Node _data): data(_data), cnt(1){};
      ~TreapNode(){
        if(leftSon != nullptr) delete leftSon;
        if(rightSon != nullptr) delete rightSon;
      };


      void updateCount();
      void pushLazy(){
        if(isReversed){
          std::swap(leftSon, rightSon);
          if(leftSon!=nullptr) leftSon->isReversed^=1;
          if(rightSon!=nullptr) rightSon->isReversed^=1;
          isReversed^=1;
        }
      }
    };
    typedef struct TreapNode * TreapTree;
    static int count(TreapTree root){
      if(root==nullptr) return 0;
      return root->cnt;
    }
    
    std::pair<TreapTree, TreapTree> split(TreapTree root, int poz){
      if(root == nullptr) return {nullptr, nullptr};
      root->pushLazy();
      if(poz <= count(root->leftSon)){ //poz in left son - strictly
        auto aux=split(root->leftSon, poz);
        root->leftSon=aux.second;
        root->updateCount();
        return {aux.first, root};
      }
      if(poz == 1+count(root->leftSon)){//poz is in root
        std::pair<TreapTree, TreapTree> aux={root->leftSon, root};
        root->leftSon=nullptr;
        root->updateCount();
        return aux;
      }
      //poz in right son - strictly
      auto aux=split(root->rightSon, poz-1-count(root->leftSon));
      root->rightSon=aux.first;
      root->updateCount();
      return {root, aux.second};
    }

    TreapTree join(TreapTree root1, TreapTree root2){
      if(root1==nullptr) return root2;
      if(root2==nullptr) return root1;
      root1->pushLazy();
      root2->pushLazy();
      if(root1->prio >= root2->prio){
        root1->rightSon=join(root1->rightSon, root2);
        root1->updateCount();
        return root1;
      }
      root2->leftSon=join(root1, root2->leftSon);
      root2->updateCount();
      return root2;

    }

    TreapTree insert(TreapTree root, Node val, int poz){
      TreapTree toInsert = new TreapNode(val);
      auto aux=split(root, poz);
      return join(aux.first, join(toInsert, aux.second));
    }

    TreapTree erase(TreapTree root, int poz){
      auto aux=split(root, poz+1);
      auto aux2=split(aux.first, poz);
      if(aux2.second!=nullptr) delete aux2.second;
      return join(aux2.first, aux.second);
    };

    TreapTree erase(TreapTree root, int left, int right){
      auto aux=split(root, right+1);
      auto aux2=split(aux.first, left);
      if(aux2.second!=nullptr) delete aux2.second;
      return join(aux2.first, aux.second);
    }

    TreapTree reverse(TreapTree root, int left, int right){
      auto aux=split(root, right+1);
      auto aux2=split(aux.first, left);
      aux2.second->isReversed^=1;
      return join(join(aux2.first, aux2.second), aux.second);
    }

    Node get(TreapTree root, int poz){
      Node ret;
      if(root==nullptr) return ret;
      root->pushLazy();
      if(poz==count(root->leftSon)+1) return root->data;
      if(poz<=count(root->leftSon)) return get(root->leftSon, poz);
      return get(root->rightSon, poz-count(root->leftSon)-1);
    }

    void print(TreapTree root){
      if(root==nullptr) return;
      root->pushLazy();
      print(root->leftSon);
      cout<<root->data<<" ";
      print(root->rightSon);
    }

  TreapTree root=nullptr;

  public:
    void insert(Node val, int poz){
      root=insert(root, val, poz);
    }
    void erase(int poz){
      root=erase(root, poz);
    }
    void erase(int left, int right){
      root=erase(root, left, right);
    }
    void reverse(int left, int right){
      root=reverse(root, left, right);
    }
    Node get(int poz){
      return get(root, poz);
    }
    void print(){
      print(root);
      cout<<"\n";
    }
  };
  template <typename Node>
  std::mt19937 Treap<Node>::rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());
  template <typename Node>
  void Treap<Node>::TreapNode::updateCount(){
    cnt=1+count(leftSon)+count(rightSon);
  }
}

int main(){
  Treap::Treap<int> myTreap;
  int n, cer;
  cin>>n>>cer;
  while(n--){
    char t;
    int a, b;
    cin>>t;
    if(t=='I'){
      cin>>a>>b;
      myTreap.insert(b, a);
    }
    else if(t=='A'){
      cin>>a;
      cout<<myTreap.get(a)<<"\n";
    }
    else if(t=='R'){
      cin>>a>>b;
      myTreap.reverse(a, b);
    }
    else{
      cin>>a>>b;
      myTreap.erase(a, b);
    }
  }
  myTreap.print();
  return 0;
}