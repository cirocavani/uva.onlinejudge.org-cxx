#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

struct N;
typedef std::vector<N> U;
typedef std::vector<U> V;

struct N
{

  int i, x, y;

  N(const int _i = -1) : i(_i), x(_i), y(0) { }

  friend std::ostream& operator<<(std::ostream& out, const N& n)
  {
    return out << n.i;
  }

};

struct W
{

  U u;

  V v;

  W(const int n) : u(n), v(n)
  {
    for (int i = 0; i < n; ++i)
      {
	N o(i);
	u[i] = o;
	v[i].push_back(o);
      }
  }

  friend std::ostream& operator<<(std::ostream& out, const W& w)
  {
    for (std::size_t i = 0; i < w.v.size(); ++i)
      {
	out << i << ":";
	const U& k = w.v[i];
	for (std::size_t j = 0; j < k.size(); ++j)
	  out << " " << k[j];
	out << std::endl;
      }
    return out;
  }

  void moveonto(const int i, const int j)
  {
    try
      {
	assertNotEqual(i, j);

	const N& ni = u[i];
	const N& nj = u[j];
	assertNotEqual(ni.x, nj.x);

	const N& nix = u[ni.x];
	const N& njx = u[nj.x];
	assertNotOver(nix, ni);
	assertNotOver(njx, ni);
	assertNotOver(nix, nj);
	assertNotOver(njx, nj);

	moveback(ni.x, ni.y);
	moveback(nj.x, nj.y);
	move(ni.i, nj.x);
      }
    catch (const std::exception& e)
      {
	// no-op
      }
  }

  void moveover(const int i, const int j)
  {
    try
      {
	assertNotEqual(i, j);

	const N& ni = u[i];
	const N& nj = u[j];
	assertNotEqual(ni.x, nj.x);

	const N& nix = u[ni.x];
	assertNotOver(nix, ni);

	moveback(ni.x, ni.y);
	move(ni.i, nj.x);
      }
    catch (const std::exception& e)
      {
	// no-op
      }
  }

  void pileonto(const int i, const int j)
  {
    try
      {
	assertNotEqual(i, j);

	const N& ni = u[i];
	const N& nj = u[j];
	assertNotEqual(ni.x, nj.x);

	const N& njx = u[nj.x];
	assertNotOver(njx, nj);

	moveback(nj.x, nj.y);
	movepile(ni.i, nj.x);
      }
    catch (const std::exception& e)
      {
	// no-op
      }
  }

  void pileover(const int i, const int j)
  {
    try
      {
	assertNotEqual(i, j);

	const N& ni = u[i];
	const N& nj = u[j];
	assertNotEqual(ni.x, nj.x);

	movepile(ni.i, nj.x);
      }
    catch (const std::exception& e)
      {
	// no-op
      }
  }

private:

  void assertNotEqual(const int i, const int j)
  {
    if (i == j) throw std::exception();
  }

  void assertNotOver(const N& nx, const N& n)
  {
    if (nx.x == n.x && nx.y > n.y) throw std::exception();
  }

  void moveback(const int x, const std::size_t y)
  {
    U& k = v[x];
    while (k.size() > y + 1)
      {
	int i = k.back().i;
	k.pop_back();
	put(u[i], i);
      }
  }

  void move(const int i, const int x)
  {
    N& n = u[i];
    U& k = v[n.x];
    k.erase(k.begin() + n.y);
    put(n, x);
  }

  void movepile(const int i, const int x)
  {
    const N& n = u[i];
    U& k = v[n.x];
    for (U::iterator p = k.begin() + n.y; p != k.end(); p = k.erase(p))
      put(u[p->i], x);
  }

  void put(N& n, int x)
  {
    U& m = v[x];
    n.x = x;
    n.y = m.size();
    m.push_back(n);
  }

};

struct M
{

  std::string m1, m2;

  int i, j;

};

int main()
{
  int n;

  std::cin >> n;

  W w(n);

  std::vector<M> v;

  while (true)
    {
      std::string m0;
      std::cin >> m0;

      if (m0 == "quit")
	break;

      M m;
      m.m1 = m0;
      std::cin >> m.i >> m.m2 >> m.j >> std::ws;

      v.push_back(m);
    }

  for (std::vector<M>::iterator p = v.begin(); p != v.end(); ++p)
    {
      if (p->m1 == "move" && p->m2 == "onto")
	w.moveonto(p->i, p->j);
      else if (p->m1 == "move" && p->m2 == "over")
	w.moveover(p->i, p->j);
      else if (p->m1 == "pile" && p->m2 == "onto")
	w.pileonto(p->i, p->j);
      else if (p->m1 == "pile" && p->m2 == "over")
	w.pileover(p->i, p->j);
    }

  std::cout << w;

  return 0;
}
