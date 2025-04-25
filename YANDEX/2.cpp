#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin>>t;
  for (int i = 0; i < t; i++) {

int n;
    cin>>n;
    vector<int> v(n);
    for (int j = 0; j < n; j++) {
      cin>>v[j];
    }
int min=1000000;
      vector<int> counts;
    int now=0;
for (int j = 0; j < n; j++) {
  if (now+1<=std::min(v[j],min)) {
    min=std::min(v[j],min);
    now++;
  }
  else {
    counts.push_back(now);
    now=0;
    min=1000000;
    if (now+1<=std::min(v[j],min)) {
      min=std::min(v[j],min);
      now++;
    }
  }
  if (j==n-1) {
    counts.push_back(now);
  }
}
cout<<counts.size()<<endl;
    for (int j = 0; j < counts.size(); j++) {
      cout<<counts[j]<<" ";
    }
    cout<<endl;
  }
  return 0;
}