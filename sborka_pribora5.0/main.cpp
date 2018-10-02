5

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


using namespace std;

class Node{
public:
    int node;
    int met;
    int leaf;
        Node(int n){
        node = n;
        }
        void setmet(int m){
        met= m;
        }
    void setleaf(int l){
        leaf=l;
    }
    int getnode(){
        return node;
        }
    
};

const int N =200100;
int nums,n;
vector<Node> graph[N];
stack<int> stck;
int color[N],color1[N];
int arr[N];
int temp;
int lll[N];
int in_stack=0;
int ans=0;
vector<int > res;


void met(int v){
    stck.push(v);
    color[v]=1;
    for(auto i = graph[v].begin(); i<graph[v].end();i++){
        if(color[i->node]==0)
            met(i->node);
    }
    
    temp =stck.top();
    arr[stck.top()]+=1;
    stck.pop();
    if(stck.size()!=0)
    arr[stck.top()]+=arr[temp];
    color[v]=2;
}
void setmet(){
    for(int i =1;i<=n;i++)
        for(auto it = graph[i].begin();it<graph[i].end();it++)
            it->setmet(arr[it->getnode()]);
}

int ll(int v){
    sort(graph[v].begin(), graph[v].end(), [](const Node& a, const Node& b) {
    return a.met>b.met;
});
    int res = (graph[v].size() == 0 ? v : 200001);
    for (auto to : graph[v]) {
        int _ll = ll(to.node);
        if (to.met == graph[v][0].met) {
            res = min(res, _ll);
        }
        
    }
     return lll[v] = res;
}
void setleaf(){
    for(int i =1;i<=n;i++)
        for(auto it = graph[i].begin();it<graph[i].end();it++)
            it->setleaf(lll[it->getnode()]);
}

void sort1(int v){
    for (int i =0; i<=n; i++) {
    
    sort( graph[i].begin(), graph[i].end(), [](const Node& a,const Node& b){
        if(a.met!=b.met)
            return a.met > b.met;
        else
            return a.leaf<b.leaf;
    });
    }
    
}
void dfsmet1(int v){
    color1[v] = 1;
    for (vector<Node>::iterator i=graph[v].begin(); i<graph[v].end(); ++i){
        if (color1[(*i).node] == 0)
            dfsmet1((*i).node);
    }
        in_stack -= graph[v].size();
        in_stack++;
        ans += in_stack;
    
    color1[v] = 2;
    res.push_back(v);
}

int main(int argc, const char * argv[]) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int first;
    char a;
    cin>>n;
    cin>>first;
    for(int q =1;q<=n;q++){
        int i,j;
        cin>>i>>a>>nums;
        for(int k =1;k<=nums;k++){
            cin>>a>>j;
            graph[i].push_back(Node(j));
        }
    }
    
    met(first);
    setmet();
    ll(first);
    setleaf();
    sort1(first);
    dfsmet1(first);
    cout << ans - 1 << endl;
    for (int i = 0; i < res.size()-1; i++) {
        cout<<res[i]<<" ";
    }
    cout<<res[res.size()-1];
    
   
    return 0;
}
