#include <cmath>
#include <vector>
#include <queue>
#include <string>
using namespace std;
const __int64 INF = 1LL<<57;

/*
Алгоритм Крускала
*/

__int64 find(__int64 x){
	return (p[x] == x ? x : p[x] = find(p[x]));
}
void Union(__int64 v1, __int64 v2){
	p[find(v1)] = find(v2);
}
struct edge{
	__int64 v, w, cost;
	void r(){
		cin >> v >> w >> cost;
	}
	void write(){
		cout << v << ' ' << w << ' ' << cost << endl;
	}
};
edge make_edge(__int64 a, __int64 b, __int64 c){
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
for (__int64 i = 0; i < x;i++)
	p[i] = i;
for (__int64 i = 0; i < y;i++){
	__int64 a, b, c;
	cin >> a >> b >> c;
	g.push_back(make_edge(a, b, c));
	g.push_back(meke_edge(b, a, c));
}
__int64 ans = 0;
sort(g.begin(), g.end(), edge_sort);
for (__int64 i = 0i < g.size();i++){
	__int64 v, w;
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
	__int64 x, y;
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
void split(node *v,__int64 x,node *&l,node *&r){
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
void del(__int64 x){
	node *l,*m,*r;
	split(root,x-1,l,m);
	split(m,x,m,r);
	root=merge(l,r);
}
bool find(__int64 x,node *r){
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
void insert(__int64 x){
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
for (__int64 i=2; i<=n; i++)
		if (!prime[i])
			for (__int64 j=i*i; j<=r; j+=i)
				prime[j] = true;

/*
Hash-функция с несколькими модулями
*/
__int64 AmountOfMods=3;
__int64 mods[5]={1000000007,1000000009,524287,107,101};
__int64 p=129;
struct hash
{
	__int64 Eq_Mod[5];
};
void StringToHash(string s,hash *ans){
	for(__int64 i=0;i<(__int64)s.length();i++){
		__int64 chr=s[i];
		for(__int64 mod=0;mod<AmountOfMods;mod++){
			ans[i].Eq_Mod[mod]=ans[max(i-1,0)].Eq_Mod[mod];
			ans[i].Eq_Mod[mod]+=chr;
			ans[i].Eq_Mod[mod]%=mods[mod];
		}
	}
}
bool hash_equals(hash a,hash b){
	for(__int64 mod=0;mod<AmountOfMods;mod++)
		if(a.Eq_Mod[mod]!=a.Eq_Mod[mod])
			return false;
	return true;
}

/*
Дейкстра с priority_queue 
O(NlogN)
*/
__int64 Dijxtra(__int64 countOfElements,__int64 start,__int64 finish,vector<pair<__int64,__int64> > *g){
	vector<__int64>d;
	d.resize(countOfElements,INF);
	vector<bool>used;
	used.resize(countOfElements);
	priority_queue<pair<__int64,__int64> >q;
	d[start]=0;
	q.push(make_pair(0,start));
	while(!q.empty()){
		__int64 v=q.top().second;
		q.pop();
		if(used[v])
			continue;
		if(d[v]==INF)
			break;
		used[v]=true;
		if(v==finish){
			return d[v];
		}
		for(__int64 i=0;i<g[v].size();i++){
			__int64 to=g[v][i].first;
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
struct po__int64{
	double x, y;
	void r(){
		cin >> x >> y;
	}
	void write(){
		cout << x << " " << y << endl;
	}
	po__int64(){}
	po__int64(__int64 x, __int64 y) :x(x), y(y){}
};
double operator + (po__int64 a, po__int64 b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
__int64 operator * (po__int64 a, po__int64 b){
	return a.x*b.y - a.y*b.x;
}
double operator % (po__int64 a, po__int64 b){
	return a.x*b.x + a.y*b.y;
}
po__int64 operator - (po__int64 a, po__int64 b){
	po__int64 ans;
	ans.x = a.x - b.x;
	ans.y = a.y - b.y;
	return ans;
}
po__int64 root(0, 0);
bool cmp(po__int64 a, po__int64 b){
	if ((a - root)*(b - root) > 0)
		return true;
	if ((a - root)*(b - root) < 0)
		return false;
	if (a + root > b + root)
		return true;
	return false;
}
po__int64 p90(po__int64 a){
	return po__int64(-a.y, a.x);
}
po__int64 p180(po__int64 a){
	return po__int64(-a.x, -a.y);
}
po__int64 p270(po__int64 a){
	return po__int64(a.y, -a.x);
}

struct circle{
	po__int64 o;
	__int64 r;
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
	__int64 st[100000000];
	__int64 top;
public:
	void push(__int64 x){
		st[top++]=x;
	}
	void pop(){
		top--;
	}
	__int64 get_top(){
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
	__int64 INF = 1 << 29;
public:
	__int64 NONE = -INF;
private:
	__int64 tree[1000000];
	__int64 upd[1000000];
public:
	void build(__int64 v, __int64 l, __int64 r,__int64 *a){
		upd[v] = NONE;
		if (r - l == 1){
			tree[v] = a[l];
		}
		else{
			__int64 m = (l + r) / 2;
			build(2 * v + 1, l, m, a);
			build(2 * v + 2, m, r, a);
			tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
		}
	}
	void push(__int64 v, __int64 l, __int64 r){
		if (upd[v] == NONE)
			return;
		__int64 m = (l + r) / 2;
		tree[2 * v + 1] = upd[v] * (m - l);
		tree[2 * v + 2] = upd[v] * (r - m);
		upd[2 * v + 1] = upd[v];
		upd[2 * v + 2] = upd[v];
		upd[v] = NONE;
	}
	void modify(__int64 from, __int64 to, __int64 value, __int64 v, __int64 l, __int64 r){
		if (to <= l || from >= r)
			return;
		if (from <= l && r <= to)
		{
			tree[v] = value*(r - l);
			upd[v] = value;
			return;
		}
		push(v, l, r);
		__int64 m = (l + r) / 2;
		modify(from, to, value, 2 * v + 1, l, m);
		modify(from, to, value, 2 * v + 2, m, r);
		tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
	}
	__int64 sum(__int64 from,__int64 to,__int64 v,__int64 l,__int64 r){
		if (from <= l && r <= to){
			return tree[v];
		}
		if (to <= l || from >= r){
			return 0;
		}
		push(v, l, r);
		__int64 m = (l + r) / 2;
		return sum(from, to, 2 * v + 1, l, m) + sum(from, to, 2 * v + 2, m, r);
	}
};