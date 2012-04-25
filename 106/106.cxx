#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

const int N_MAX = 1000000;

inline int gcd(int a, int b)
{
  int t;
  while (b != 0)
    {
      t = b;
      b = a % b;
      a = t;
    }
  return a;
}

struct V
{
  int n, p, q;
  V(int _n)
    : n(_n), p(0), q(_n) { }
  inline void operator()(int _p, int _q)
  {
    p = _p;
    q -= _q;
  }
};

struct T
{
  int c, b, a;
  bool prime;
  T(int _c, int _b, int _a, bool _p = false)
    : c(_c), b(std::max(_a,_b)), a(std::min(_a,_b)), prime(_p) { }
  inline bool operator<(const T& o) const
  {
    return c < o.c;
  }
  inline T operator*(int k) const
  {
    return T(k * c, k * b, k * a);
  }
};

struct Q
{
private:
  std::vector<bool> v;
  int _size;
  inline void count(int i)
  {
    if (v[i])
      return;
 
    v[i] = true;
    ++_size;
  }
public:
  Q() : _size(0), v(N_MAX + 1, false) { }
  inline int size() const
  {
    return _size;
  }
  inline void operator+=(const T& t)
  {
    count(t.a);
    count(t.b);
    count(t.c);
  }
};

class W
{
  std::vector<int> u;
  std::map<int, V> v;
  int ux;
public:
  W() : ux(0) { }
  inline friend std::istream& operator>>(std::istream& in, W& w)
  {
    int n;
    in >> n >> std::ws;

    w.u.push_back(n);
    w.v.insert(std::make_pair(n, V(n)));

    if (n > w.ux)
      w.ux = n;

    return in;
  }
  inline friend std::ostream& operator<<(std::ostream& out, const W& w)
  {
    for (std::vector<int>::const_iterator i = w.u.begin(); i != w.u.end(); ++i)
      {
	const V& vn = w.v.find(*i)->second; 
	out << vn.p << " " << vn.q << std::endl;
      }
    return out;
  }
  inline void operator()()
  {
    std::vector<T> t;

    for (int m = 2, m2 = 4; m2 < ux; ++m, m2 = m * m)
      {
	for (int n = m % 2 + 1; n < m; n += 2)
	  {
	    if (gcd(m, n) != 1)
	      continue;

	    int n2 = n * n;

	    int c = m2 + n2;

	    if (c > ux)
	      break;

	    int a = m2 - n2;
	    int b = 2 * m * n;

	    T tp(c, b, a, true); 
	    t.push_back(tp);
	    for (int k = 2, kx = ux / c; k <= kx; ++k)
	      t.push_back(tp * k);
	  }
      }
 
    std::map<int,V>::iterator vp = v.begin();
    V* vn = &vp->second;
 
    int np = 0;
    Q nq;

    std::sort(t.begin(), t.end());
    for (std::vector<T>::iterator i = t.begin(); i != t.end(); ++i)
      {
	while (i->c > vn->n)
	  {
	    (*vn)(np, nq.size());
	    vn = &(++vp)->second;
	  }

	if (i->prime)
	  ++np;

	nq += *i;
      }

    (*vn)(np, nq.size());
  }
};

int main()
{
  W w;

  while (std::cin.good())
    std::cin >> w;

  w();

  std::cout << w;

  return 0;
}
