#include "algo.h"
#include <QVector>
#include <algorithm>
Algo::Algo() {}

QVector<double> Algo::Med(QVector<int> a)
{
    QVector <double> n;
    int l=a.size()-a.size()%3;
    for (int i=0;i<l;i+=3)
    {
        QVector <int> q{a[i],a[i+1],a[i+2]};
        std::sort(q.begin(),q.end());
        int p=q[1];
        n.push_back(p);
    }
    if (a.size()%3==1)
    {
        n.push_back(a[a.size()-1]);
    }
    if (a.size()%3==2)
    {
        n.push_back((a[a.size()-1]+a[a.size()-2])/2.0);
    }
    return n;
}
