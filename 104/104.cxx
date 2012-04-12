#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

class T
{

  const std::vector<float>& n;

  const T* t;

  int i;

  int s;

  float m;

  float _value;

public:

  T(const T& _t, int _i, float _r) : n(_t.n), t(&_t),
      i(_i), s(_t.s + 1), m(_t.m * _r), _value(m * n[i])
  { }
  T(int i0, const std::vector<float>& _n) : n(_n), t(0),
      i(i0), s(1), m(1.0)
  { }

  friend std::ostream& operator<<(std::ostream& out, const T& t)
  {
    std::list<int> u;

    for (const T* k = &t; k != 0; k = k->t)
      u.push_back(k->i + 1);

    for (std::list<int>::reverse_iterator i = u.rbegin(); i != u.rend(); ++i)
      out << *i << " ";
    
    return out << u.back();
  }

  int index() const { return i; }

  int size() const { return s; }

  float value() const { return _value; }

  bool loss() const { return _value == m && _value <= 1.0; }

};

class R
{

  std::vector<float> _vt;

  std::vector<float> _vr;

  std::vector<int> p;

public:

  R(int n) : _vt(n), _vr(n), p(n) { for (int i = 0; i < n; ++i) p[i] = i; }

  bool operator()(int i, int j) { return _vt[i] > _vt[j]; }

  float operator[](int i) const { return _vt[i]; }
 
  void vt(int i, float v) { _vt[i] = v; }
  void vr(int i, float v) { _vr[i] = v; }
  const std::vector<float>& vr() const { return _vr; }

  void sort() { std::sort(p.begin(), p.end(), *this); }
  std::vector<int>::iterator pbegin() { return p.begin(); }
  std::vector<int>::iterator pend() { return p.end(); }

};

class W
{

  int n;

  std::vector<R> u;

  T* t;

  T* search()
  {
    std::list<T*> m;

    for (int i = 0; i < n; ++i) m.push_back(new T(i, u[i].vr()));
 
    for (std::list<T*>::iterator mi = m.begin(); mi != m.end(); ++mi)
      {
	T* tn = *mi;
	
	if (tn->size() == n) break;

	R& r = u[tn->index()];

	for (std::vector<int>::iterator pi = r.pbegin(); pi != r.pend(); ++pi)
	  {
	    int i = *pi;

	    if (tn->index() == i) continue;

	    T* tx = new T(*tn, i, r[i]);
	    
	    if (tx->loss()) continue;
	    if (tx->value() > 1.01) return tx;

	    m.push_back(tx);
	  }
      }

    return 0;
  }
 
public:

  W() : t(0) { }

  friend std::istream& operator>>(std::istream& in, W& w)
  {
    in >> w.n >> std::ws;

    for (int i = 0; i < w.n; ++i) w.u.push_back(R(w.n));

    for (int i = 0; i < w.n; ++i)
      {
	R& r = w.u[i];

	for (int j = 0; j < w.n; ++j)
	  {
	    if (j == i)
	      {
		r.vt(i, 1.0);
		r.vr(i, 1.0);
		continue;
	      }

	    float _v;
	    in >> _v >> std::ws;
	    r.vt(j, _v);

	    R& _r = w.u[j];
	    _r.vr(i, _v);
	  }
      }

    std::for_each(w.u.begin(), w.u.end(), std::mem_fun_ref(&R::sort));

    return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const W& w)
  {
    return w.t == 0 ? out << "no arbitrage sequence exists" : out << *w.t;
  }

  W& operator()()
  {
    t = search();
    return *this;
  }

};

void print(W& w)
{
  std::cout << w << std::endl;
}

int main()
{
  std::list<W> v;

  while (std::cin.good())
    {
      W w;
      std::cin >> w;
      v.push_back(w());
    }

  std::for_each(v.begin(), v.end(), print);

  return 0;
}
