        #include <bits/stdc++.h>
        using namespace std;
        int main() {
            int n;
            cin>>n;
            int x;
            cin>>x;
            vector <int> mass(n);
            vector<int> cost(n);
            for(int i=0;i<n;i++) {
                cin>>mass[i];
            }
            for(int i=0;i<n;i++) {
                cin>>cost[i];
            }
        vector <vector<int>> have( n,vector<int>(x+1));
            vector <vector<int>> num( n,vector<int>(x+1));
            for(int i=0;i<n;i++) {
                for(int j=0;j<x+1;j++) {
                    have[i][j]=-1;
                    num[i][j]=-1;
                }
            }
            have[0][0]=0;
            num[0][0]=-1;
        for (int i=0;i<n;i++) {
            if (i!=0) {
                for(int j=0;j<x+1;j++) {
                    have[i][j]=have[i-1][j];
                    num[i][j]=num[i-1][j];
                }
            }
            int mas=mass[i];
            int c=cost[i];
            for (int j=x-mas;j>=0;j--) {
                if(have[i][j]!=-1 && have[i][j+mas]<have[i][j]+c) {
                    have[i][j+mas]=have[i][j]+c;
                    num[i][j+mas]=i;
                }
            }
        }





                int max_val=-1;int topw;int topi;
                for(int i=0;i<n;i++) {
                    for(int j=0;j<=x;j++) {

                        if (have[i][j]>max_val) {
                            max_val=have[i][j];
                            topw=j;
            topi=i;
                        }
                    }
                }

            int w=topw;
            int i=topi;
                vector<int> answer;

                while (w>0 && i>=0) {
    int now=num[i][w];
    if (now==-1) {
        break;
    }
                    answer.push_back(now);
           w-=mass[now];
                    i=now-1;
                    if (i<0) break;
                }

            for(int i=answer.size()-1;i>=0;i--) {
                cout<<answer[i]+1<<"\n";
            }


            return 0;
        }