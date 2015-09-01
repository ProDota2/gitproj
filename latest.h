#include <cmath>
#include <vector>
#include <queue>
#include <string>
using namespace std;
const int INF = 1<<29;

/*
Алгоритм Крускала
*/

int find(int x){
	return (p[x] == x ? x : p[x] = find(p[x]));
}
void Union(int v1, int v2){
	p[find(v1)] = find(v2);
}
struct edge{
	int v, w, cost;
	void r(){
		cin >> v >> w >> cost;
	}
	void write(){
		cout << v << ' ' << w << ' ' << cost << endl;
	}
};
edge make_edge(int a, int b, int c){
	edge new_edge;
	new_edge.v = a;
	new_edge.w = b;
	new_edge.cost = c;
	return new_edge;
}
bool edge_sort(edge a, edge b){
	if (a.cost < b.cost)
		return true;
	return false;
}
//Example
//Выводит минимальное остовное дерево 
cin >> x >> y;
for (int i = 0; i < x;i++)
	p[i] = i;
for (int i = 0; i < y;i++){
	int a, b, c;
	cin >> a >> b >> c;
	g.push_back(make_edge(a, b, c));
	g.push_back(meke_edge(b, a, c));
}
int ans = 0;
sort(g.begin(), g.end(), edge_sort);
for (int i = 0i < g.size();i++){
	int v, w;
	v = g[i].v;
	w = g[i].w;
	if (find(v) != find(w)){
		Union(v, w);
		ans += g[i].cost;
	}
}
cout << ans;
/*
Декартово дерево 
merge - обьединяет два дерева
split - разделяет на два дерева по Х
del = delete
insert и find - поймёте сами
*/

struct node{
	int x, y;
	node *l, *r;
};
node *root;
node * merge(node *l,node *r){
	if(l==NULL)
		return r;
	if(r==NULL)
		return l;
	if(l->y > r->y){
		l->r=merge(l->r,r);
		return l;
	}else{
		r->l=merge(l,r->l);
		return r;
	}
}
void split(node *v,int x,node *&l,node *&r){
	if(v==NULL){
		l=r=NULL;
		return;
	}
	if(v->x<=x){
		split(v->r,x,v->r,r);
		l=v;
	}else{
		split(v->l,x,l,v->l);
		r=v;
	}
}
void del(int x){
	node *l,*m,*r;
	split(root,x-1,l,m);
	split(m,x,m,r);
	root=merge(l,r);
}
bool find(int x,node *r){
	if (r == NULL)
		return false;
	if(r->x==x)
		return true;	
	if (r->x < x){
		return find(x, r->r);
	}else{
		return find(x, r->l);
	}
}
void insert(int x){
	node *l, *r;
	node *v=new node;
	v->x = x;
	v->y = rand();
	v->l = NULL;
	v->r = NULL;
	split(root, x, l, r);
	root = merge(merge(l, v),r);
}

/*
Если prime[i] = false то i простое число
*/
bool prime[10000000];
prime[0] = prime[1] = true;
for (long long i=2; i<=n; i++)
		if (!prime[i])
			for (long long j=i*i; j<=r; j+=i)
				prime[j] = true;

/*
Hash-функция с несколькими модулями
*/
int AmountOfMods=3;
int mods[5]={1000000007,1000000009,524287,107,101};
int p=129;
struct hash
{
	int Eq_Mod[5];
};
void StringToHash(string s,hash *ans){
	for(int i=0;i<(int)s.length();i++){
		int chr=s[i];
		for(int mod=0;mod<AmountOfMods;mod++){
			ans[i].Eq_Mod[mod]=ans[max(i-1,0)].Eq_Mod[mod];
			ans[i].Eq_Mod[mod]+=chr;
			ans[i].Eq_Mod[mod]%=mods[mod];
		}
	}
}
bool hash_equals(hash a,hash b){
	for(int mod=0;mod<AmountOfMods;mod++)
		if(a.Eq_Mod[mod]!=a.Eq_Mod[mod])
			return false;
	return true;
}

/*
Дейкстра с priority_queue 
O(NlogN)
*/
int Dijxtra(int countOfElements,int start,int finish,vector<pair<int,int> > *g){
	vector<int>d;
	d.resize(countOfElements,INF);
	vector<bool>used;
	used.resize(countOfElements);
	priority_queue<pair<int,int> >q;
	d[start]=0;
	q.push(make_pair(0,start));
	while(!q.empty()){
		int v=q.top().second;
		q.pop();
		if(used[v])
			continue;
		if(d[v]==INF)
			break;
		used[v]=true;
		if(v==finish){
			return d[v];
		}
		for(int i=0;i<g[v].size();i++){
			int to=g[v][i].first;
			if(d[to] > d[v] + g[v][i].second){
				d[to]=d[v] + g[v][i].second;
				q.push(make_pair(-d[to],to));
			}
		}
	}
	return INF;
}

/*
Геометрия
*/
struct point{
	double x, y;
	void r(){
		cin >> x >> y;
	}
	void write(){
		cout << x << " " << y << endl;
	}
	point(){}
	point(long long x, long long y) :x(x), y(y){}
};
double operator + (point a, point b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
long long operator * (point a, point b){
	return a.x*b.y - a.y*b.x;
}
double operator % (point a, point b){
	return a.x*b.x + a.y*b.y;
}
point operator - (point a, point b){
	point ans;
	ans.x = a.x - b.x;
	ans.y = a.y - b.y;
	return ans;
}
point root(0, 0);
bool cmp(point a, point b){
	if ((a - root)*(b - root) > 0)
		return true;
	if ((a - root)*(b - root) < 0)
		return false;
	if (a + root > b + root)
		return true;
	return false;
}
point p90(point a){
	return point(-a.y, a.x);
}
point p180(point a){
	return point(-a.x, -a.y);
}
point p270(point a){
	return point(a.y, -a.x);
}

struct circle{
	point o;
	int r;
};

/*
Реализация стека
push(x) - добавляет элемент x
pop() - удаляет элемент
get_top() - возвращает верхний элемент 
*/
class My_Stack
{
private:
	int st[100000000];
	int top;
public:
	void push(int x){
		st[top++]=x;
	}
	void pop(){
		top--;
	}
	int get_top(){
		return st[top-1];
	}
};

/*
Дерево отрезков
build(v,l,r,*A) - строит дерево по массиву A (build(0,0,x,A))
push(v,l,r) - нужно для обновления дерева после каких либо действий на отрезке
modify(from,to,value,v,l,r) - присваевает елементам [from , to) значение value (modify(from,to,value,0,x))
sum(from,to,v,l,r) - вщзвращает сумму на [from , to) (sum(from,to,0,0,x))
*/
class tree_section{
private:
	int INF = 1 << 29;
public:
	int NONE = -INF;
private:
	int tree[1000000];
	int upd[1000000];
public:
	void build(int v, int l, int r,int *a){
		upd[v] = NONE;
		if (r - l == 1){
			tree[v] = a[l];
		}
		else{
			int m = (l + r) / 2;
			build(2 * v + 1, l, m, a);
			build(2 * v + 2, m, r, a);
			tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
		}
	}
	void push(int v, int l, int r){
		if (upd[v] == NONE)
			return;
		int m = (l + r) / 2;
		tree[2 * v + 1] = upd[v] * (m - l);
		tree[2 * v + 2] = upd[v] * (r - m);
		upd[2 * v + 1] = upd[v];
		upd[2 * v + 2] = upd[v];
		upd[v] = NONE;
	}
	void modify(int from, int to, int value, int v, int l, int r){
		if (to <= l || from >= r)
			return;
		if (from <= l && r <= to)
		{
			tree[v] = value*(r - l);
			upd[v] = value;
			return;
		}
		push(v, l, r);
		int m = (l + r) / 2;
		modify(from, to, value, 2 * v + 1, l, m);
		modify(from, to, value, 2 * v + 2, m, r);
		tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
	}
	int sum(int from,int to,int v,int l,int r){
		if (from <= l && r <= to){
			return tree[v];
		}
		if (to <= l || from >= r){
			return 0;
		}
		push(v, l, r);
		int m = (l + r) / 2;
		return sum(from, to, 2 * v + 1, l, m) + sum(from, to, 2 * v + 2, m, r);
	}
};