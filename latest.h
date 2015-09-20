#include <cmath>
#include <vector>
#include <queue>
#include <string>
#include <random>
#include <cstdlib>
using namespace std;
const __int64 INF = 1LL << 57;

/*
	Бор
*/
struct letter{
	letter* next[26];
	letter(){
		for (int i = 0; i < 26; i++)
			next[i] = NULL;
	}
};
void add(letter **root, string new_str){
	letter *t = *root;
	for (int i = 0; i < new_str.length(); i++){
		if (t->next[new_str[i] - 'a'] != NULL){
			t = t->next[new_str[i] - 'a'];
		}
		else{
			letter* add = new letter();
			t->next[new_str[i] - 'a'] = add;
			t = add;
		}
	}
}
void print(letter **root, string ans){
	letter *t = *root;
	bool p = true;
	for (int i = 0; i < 26; i++){
		if (t->next[i] != NULL){
			p = false;
			print(&t->next[i], ans + char(i + 'a'));
		}
	}
	if (p)
		cout << ans << endl;
}

/*
	Односвязный список
*/
template<class type>
struct List{
	type data;
	List* next;
	List(){
	}
	List(type new_data){
		data = new_data;
		next = NULL;
	}
};
template<class type>
void Push(List<type>**begin, type add){
	List<type>* dat = new List<type>(add);
	if (*begin == NULL){
		*begin = dat;
		return;
	}
	if ((*begin)->data > dat->data){
		dat->next = *begin;
		*begin = dat;
		return;
	}
	List<type>*t1 = new List<type>();
	t1 = *begin;
	List<type>*t2 = new List<type>();
	t2 = t1->next;
	while (t2){
		if (t1->data <= dat->data && dat->data <= t2->data){
			t1->next = dat;
			dat->next = t2;
			return;
		}
		t1 = t1->next;
		t2 = t2->next;
	}
	t1->next = dat;
	return;
}
template<class type>
void PrintList(List<type>*begin){
	while (begin){
		cout << begin->data << " --> ";
		begin = begin->next;
	}
	cout << "NULL";
}
template<class type>
void Delete(List<type>**begin, type del){
	if (*begin == NULL){
		return;
	}
	List<type>*t1 = new List<type>();
	t1 = *begin;
	if (t1->data == del){
		*begin = t1->next;
		delete t1;
		return;
	}
	List<type>*t2 = new List<type>();
	t2 = t1->next;
	while (t2){
		if (t2->data == del){
			t1->next = t2->next;
			delete t2;
			return;
		}
		t1 = t1->next;
		t2 = t2->next;
	}
	return;
}
template<class type>
void Free(List<type>**begin){
	if (*begin == NULL)
		return;
	List<type>*p = *begin;
	List<type>*t;
	while (p){
		t = p;
		p = p->next;
		delete t;
	}
	*begin = NULL;
}

/*
Алгоритм Крускала
*/
//СНМ
__int64 p[1000000];//Изначально p[v]=v так как каждая вершина это отдельное мнодество
//Находит корень множества в котором находится этот элемент
__int64 find(__int64 x){
	return (p[x] == x ? x : p[x] = find(p[x]));
}
//Обьединение двух множеств
void Union(__int64 v1, __int64 v2){
	if(find(v1)!=find(v2))
		p[find(v1)] = find(v2);
}
//Структура ребро
struct edge{
	__int64 v, w, cost;
	edge(){}
	edge(__int64 a, __int64 b, __int64 c):v(a),w(b),cost(c){}
};
//Компаратор для сортировки рёбер по возрастанию
bool edge_sort(edge a, edge b){
	if (a.cost < b.cost)
		return true;
	return false;
}
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
node * merge(node *l, node *r){
	if (l == NULL)
		return r;
	if (r == NULL)
		return l;
	if (l->y > r->y){
		l->r = merge(l->r, r);
		return l;
	}
	else{
		r->l = merge(l, r->l);
		return r;
	}
}
void split(node *v, __int64 x, node *&l, node *&r){
	if (v == NULL){
		l = r = NULL;
		return;
	}
	if (v->x <= x){
		split(v->r, x, v->r, r);
		l = v;
	}
	else{
		split(v->l, x, l, v->l);
		r = v;
	}
}
void del(__int64 x){
	node *l, *m, *r;
	split(root, x - 1, l, m);
	split(m, x, m, r);
	root = merge(l, r);
}
bool find(__int64 x, node *r){
	if (r == NULL)
		return false;
	if (r->x == x)
		return true;
	if (r->x < x){
		return find(x, r->r);
	}
	else{
		return find(x, r->l);
	}
}
void insert(__int64 x){
	node *l, *r;
	node *v = new node;
	v->x = x;
	v->y = rand();
	v->l = NULL;
	v->r = NULL;
	split(root, x, l, r);
	root = merge(merge(l, v), r);
}

/*
Если prime[i] = false то i простое число
*/
bool prime[1000000];
void prime_fill(int n){
	prime[0] = true;
	prime[1] = true;
	for (__int64 i = 2; i <= n; i++)
		if (!prime[i])
			for (__int64 j = i+i; j <= n; j += i)
				prime[j] = true;
}

/*
Hash-функция с несколькими модулями
*/
__int64 AmountOfMods = 3;
__int64 mods[5] = { 1000000007, 1000000009, 524287, 107, 101 };
__int64 pri = 129;
struct hsh
{
	__int64 Eq_Mod[5];
};
void StringToHash(string s, hsh *ans){
	for (__int64 i = 0; i<(__int64)s.length(); i++){
		__int64 chr = s[i];
		for (__int64 mod = 0; mod<AmountOfMods; mod++){
			ans[i].Eq_Mod[mod] = ans[max(i - 1, 0LL)].Eq_Mod[mod] * pri;
			ans[i].Eq_Mod[mod] += chr;
			ans[i].Eq_Mod[mod] %= mods[mod];
		}
	}
}
//Сравнение хэшей
bool equals(hsh a, hsh b){
	for (__int64 mod = 0; mod<AmountOfMods; mod++)
	if (a.Eq_Mod[mod] != a.Eq_Mod[mod])
		return false;
	return true;
}

/*
Дейкстра с priority_queue
Граф задан в виде массива ветров пар
O(NlogN)
*/
void Dijxtra(__int64 countOfElements, __int64 start, vector<pair<__int64, __int64> > *g){
	vector<__int64>d;
	d.resize((unsigned int)countOfElements, INF);
	vector<bool>used;//Есть ли этот элемент в множестве А
	used.resize((unsigned int)countOfElements);
	priority_queue<pair<__int64, __int64> >q;
	d[(unsigned int)start] = 0;
	q.push(make_pair(0, start));
	while (!q.empty()){
		__int64 v = q.top().second;
		q.pop();
		if (used[(unsigned int)v])
			continue;
		if (d[(unsigned int)v] == INF)
			break;
		used[(unsigned int)v] = true;//Добавление в А
		for (__int64 i = 0; i<g[v].size(); i++){
			__int64 to = g[(unsigned int)v][(unsigned int)i].first;
			if (d[(unsigned int)to] > d[(unsigned int)v] + g[(unsigned int)v][(unsigned int)i].second){
				d[(unsigned int)to] = d[(unsigned int)v] + g[(unsigned int)v][(unsigned int)i].second;
				q.push(make_pair(-d[(unsigned int)to], to));
			}
		}
	}
}

/*
Геометрия
*/
struct point{
	double x, y;
	point(){}
	point(double x, double y) :x(x), y(y){}
};
//Расстояние между двумя точками
double operator + (point a, point b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
//Векторное произедение |a|*|b|*sin(o)
double operator * (point a, point b){
	return a.x*b.y - a.y*b.x;
}
//Скалярное произведение |a|*|b|*cos(o)
double operator % (point a, point b){
	return a.x*b.x + a.y*b.y;
}
//Вычитание из одного вектора другого или из одной точки вторую(для построения вектора)
point operator - (point a, point b){
	point ans;
	ans.x = a.x - b.x;
	ans.y = a.y - b.y;
	return ans;
}
//Сортировка относительно начала координат 
point rot(0, 0);
bool cmp(point a, point b){
	if ((a - rot)*(b - rot) > 0)
		return true;
	if ((a - rot)*(b - rot) < 0)
		return false;
	if (a + rot > b + rot)
		return true;
	return false;
}
//Поворот на угол с синусом sina и косинусом cosa
point px(point a, double sina, double cosa){
	point ans;
	ans.x = a.x*cosa - a.y*sina;
	ans.y = a.x*sina + a.y*cosa;
	return ans;
}
//Поворот на 90,180,270 градусов
point p90(point a){
	return point(-a.y, a.x);
}
point p180(point a){
	return point(-a.x, -a.y);
}
point p270(point a){
	return point(a.y, -a.x);
}
//Структура круг
struct circle{
	point o;
	double r;
};
//Структура линия
struct line{
	double a, b, c;
	line(){};
	line(point e, point f){
		a = e.y - f.y;
		b = f.x - e.x;
		c = -(a*e.x + b*e.y);
	}
};
double equa(double a, double b, double c, double d) {
	return a * d - b * c;
}
//Нахождение точки пересечения прямых
point operator * (line m,line n){
	double zn = equa(m.a, m.b, n.a, n.b);
	point ans;
	ans.x = -equa(m.c, m.b, n.c, n.b) / zn;
	ans.y = -equa(m.a, m.c, n.a, n.c) / zn;
	return ans;
}
/*
Реализация стека с динамической длинной
push(x) - добавляет элемент x
pop() - удаляет элемент
get_top() - возвращает верхний элемент
Для созданея стека нужно написать Stack<тип переменных в стеке> название стека
*/
template<class type>
struct Stack{
	vector<type>st;
	int top;
	void push(type x){
		if (top >= st.size())
			st.push_back(type());
		st[top++] = x;
	}
	void pop(){
		top = (top == 0 ? top : top - 1);
	}
	type get_top(){
		return (top == 0 ? 0 : st[top - 1]);
	}
};

/*
Example:
Stack<int>a;
a.pop();
a.push();
a.get_top();
*/

/*
Дерево отрезков
build(v,l,r,*A) - строит дерево по массиву A (build(0,0,x,A))
push(v,l,r) - нужно для обновления дерева после каких либо действий на отрезке
modify(from,to,value,v,l,r) - присваевает елементам [from , to) значение value (modify(from,to,value,0,x))
sum(from,to,v,l,r) - вщзвращает сумму на [from , to) (sum(from,to,0,0,x))
*/
class tree_section{
private:
	__int64 INF = 1LL << 57;
public:
	__int64 NONE = -INF;
private:
	__int64 tree[1000000];
	__int64 upd[1000000];
public:
	void build(__int64 v, __int64 l, __int64 r, __int64 *a){
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
	__int64 sum(__int64 from, __int64 to, __int64 v, __int64 l, __int64 r){
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