#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin>>n;
  int x;
  cin>>x;
  vector <int> mas(n);
  vector<int> have(x+1);
  vector<int> c(n);
  for(int i=0;i<n;i++) {
    cin>>mas[i];
  }
  for(int i=0;i<n;i++) {
    cin>>c[i];
  }
 for (int i=0;i<=x;i++) {
   have[i]=-1;
 }
  have[0]=0;
  for(int i=0;i<n;i++) {
    int m=mas[i];
for (int j=x-m;j>=0;j--) {
  if (have[j]!=-1 && have[j+m]<have[j]+c[i]) {
    have[j+m]=(have[j]+c[i]);
  }
}
  }
  int q=0;
for (int i=x;i>=0;i--) {
  if (have[i]>q) {
    q=have[i];
  }
}
  cout<<q;
  return 0;
}