#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using ll = long long;

std::vector<std::pair<int,ll>> events;

std::set<std::pair<ll,ll>> initVal;
std::vector<std::pair<ll,ll>> distVal;


void record(ll start, ll val) {
  if(1 <= val) {
    auto it = initVal.find({val, start});
    if(it == initVal.end()) {
      initVal.insert({val, start});
      record(start, val / 2);
      record(start, val - 1 - val / 2);
    }
  }
}

void simulate(int n, int q) {
  std::set<ll> myset;
  myset.insert(0);
  myset.insert(n + 1);
  initVal.insert({n + 2, 0});
  record(0, n);

  for(int i = 0; i < q; i++) {
    if(events[i].first == 1) {
      ll pos = events[i].second;
      auto it = myset.lower_bound(pos);
      if((*it) == pos) {
        myset.erase(it);
      } else {
        ll y = (*it);
        it--;
        ll x = (*it);
        record(x, pos - x - 1);
        record(pos, y - pos - 1);
        myset.insert(pos);
      }
    }
  }
  distVal = std::vector<std::pair<ll,ll>>(initVal.begin(), initVal.end());
  std::sort(distVal.begin(), distVal.end(), 

  [&](std::pair<ll, ll> x , std::pair<ll, ll> y)
  {
    if(x.first != y.first)
      return x.first > y.first;
    else
      return x.second < y.second;
  }
  );

  /*
  std::cout << "Distval: " << distVal.size() << ":" ;
  for(int i = 0; i < distVal.size(); i++)
    std::cout << distVal[i].first << " " << distVal[i].second << ": ";
  std::cout << std::endl;
  //*/

}

class FenwickTree{
  private:
    std::vector<ll> aib; 
    int n;
  public:
    FenwickTree(int n_) {
      n = n_;
      aib.resize(1 + n);
    }
    void update(int pos, ll val) {
      //std::cout << "update: " << distVal[pos].first << " " << distVal[pos].second << " " << pos << " " << val << std::endl;
      for(int x = pos; x <= n; x += ((x & (x - 1)) ^ x))
        aib[x] += val;
    }
    ll query(int pos) {
      ll result = 0;
      for(int x = pos; 0 < x; x = (x & (x - 1)))
        result += aib[x];
      //std::cout << "query: " << pos << " " << result << std::endl;
      return result;
    }
    int findFirst(ll target) {
      int x= 0;
      for(int jump = (1 << 20); 0 < jump; jump /= 2)
        if(x + jump <= n && aib[x + jump] < target) {
          target -= aib[x + jump];
          x += jump;
        }
      //std::cout << "FindfirsT: " << target << " " << x << '\n';
      return x + 1;
    }
};

std::map<ll, ll> quickSolve;

ll findElement(ll x, ll y, ll &k, ll target) {
  ll score = y - x - 1;
  if(score < target)
    return -1;
  if(score == target) {
    
    if(k == 1) {
      k--;
      return (x + y) / 2;
    } else {
      k--;
      return -1;
    }
  } else {
    auto it = quickSolve.find(score);
    if(it == quickSolve.end()) {
      ll mid = (x + y) / 2;
      ll answer = findElement(x, mid, k, target);
      if(answer != -1)
        return answer;
      answer = findElement(mid, y, k, target);
      if(answer != -1)
        return answer;
      quickSolve[score] = quickSolve[mid - x - 1] + quickSolve[y - mid - 1];
      return -1;
    } else {
      if(it->second < k) {
        k -= it->second;
        return -1;
      } else {
        ll mid = (x + y) / 2;
        ll answer = findElement(x, mid, k, target);
        if(answer != -1)
          return answer;
        else
          return findElement(mid, y, k, target);
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  int n, q;
  std::cin >> n >> q;
  events.resize(q);
  for(int i = 0;i < q; i++) {
    std::cin >> events[i].first >> events[i].second;
  }
  simulate(n, q);
  int lim = distVal.size();
  FenwickTree aib(lim);

  std::set<ll> myset;
  myset.insert(0);
  myset.insert(n + 1);

  auto addSection = [&](ll x, ll y, ll sign) {
    ll start = x;
    ll target = y - x - 1;
    //std::cout << "Addsection: " << x << " " << y << " " << sign << '\n';

    std::vector<std::pair<ll, ll>> updates;
    updates.push_back({target, sign});
    for(int i = 0; i < updates.size(); i++) {
      if(1 < updates[i].first) {
        ll coef = updates[i].second;

        ll xval = (updates[i].first - 1) / 2;
        ll yval = updates[i].first - 1 - xval;
        if(0 < yval) {
          if(updates.back().first == yval)
            updates.back().second += coef;
          else
            updates.push_back({yval, coef});
        }

        if(0 < xval) {
          if(updates.back().first == xval)
            updates.back().second += coef;
          else
            updates.push_back({xval, coef});
        }
      }
    }
    //std::cout << updates.size() << '\n';

    for(int i = 0; i < updates.size(); i++) 
      aib.update(std::lower_bound(distVal.begin(), distVal.end(), std::make_pair(updates[i].first, start),
  [&](std::pair<ll, ll> x , std::pair<ll, ll> y)
  {
    if(x.first != y.first)
      return x.first > y.first;
    else
      return x.second < y.second;
  }

      ) - distVal.begin(), updates[i].second);
  };
  int active = 0;
  addSection(0, n + 1, 1);

  for(int i = 0; i < q; i++) {
   // std::cout << events[i].first << " " << events[i].second << std::endl;
    if(events[i].first == 1) {
      ll pos = events[i].second;
      auto it = myset.lower_bound(pos);
      if((*it) == pos) {
        myset.erase(it++);
        ll y = *it;
        it--;
        ll x = *it;
        addSection(x, pos, -1);
        addSection(pos, y, -1);
        addSection(x, y, 1);
        active--;
      } else {
        ll y = *it;
        it--;
        ll x = *it;

        addSection(x, y, - 1);
        addSection(x, pos, 1);
        addSection(pos, y, 1);
        myset.insert(pos);
        active++;
      }
    } else {
      ll k = events[i].second;
      if(n < k + active)
        std::cout << -1 << '\n';
      else {

        int pos = aib.findFirst(k);
        ll start = distVal[pos].second;
        //std::cout << aib.query(pos - 1) << '\n';
        k -= aib.query(pos - 1);

        ll sz = distVal[pos].first;
        ll send = *myset.upper_bound(start);
        //std::cout << "LastStep: " << start << " " << send << " " << sz << " " << k << '\n';
        quickSolve.clear();
        quickSolve[sz] = 1;
        std::cout << findElement(start, send, k, sz) << '\n';
      }
    }
  }

  return 0;
}