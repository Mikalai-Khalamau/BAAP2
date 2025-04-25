#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
    int m;
  cin>>n;
 cin>>m;
    vector <int> kids;
    vector <int> cabs;
    vector <int> kids2;
    map <int,int> mkids;
    map <int,int> mcabs;
    for(int i=0;i<n;i++) {
        int q;
        cin>>q;
        mkids[i+1]=q;
        kids.push_back(q);
        kids2.push_back(q);
    }

    for(int i=0;i<m;i++) {
        int y;
        cin>>y;
        mcabs[i+1]=y-1;
        cabs.push_back(y-1);
    }

    vector <int> final(n);
    int sum=0;
sort(kids.begin(),kids.end());
    sort(cabs.begin(),cabs.end());
    int i=0;
    int j=0;
    while(i<kids.size() && j<cabs.size()) {
        if (kids[i]<=cabs[j]) {
            int deti=kids[i];
            int audi=cabs[j];
            int ss;
            int yy;
            for (const auto& pair : mkids) {
                if (pair.second == deti && final[pair.first-1]==0) {
                    ss=pair.first;
                    break;
                }
            }
            for (const auto& pair : mcabs) {
                if (pair.second == audi) {
                    int f=0;
                    for (int i=0;i<n;i++) {
                        if (final[i]==pair.first) {
                            f++;
                        }
                    }
                    if (f==0) {
                        yy=pair.first;
                        break;
                    }

                }
            }
            final[ss-1]=yy;
            sum++;

            i++;
            j++;
        }
        else  {
            j++;
        }
    }
    cout<<sum<<endl;
    for (int i=0;i<n;i++) {
        cout<<final[i]<<" ";
    }
 return 0;
}

