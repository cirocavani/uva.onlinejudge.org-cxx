#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

struct N;
typedef std::vector<std::const_mem_fun_t<int, N> > F;

struct N
{

  int b, g, c;

  N(const int _b = 0, const int _g = 0, const int _c = 0) : b(_b), g(_g), c(_c) { }

  friend std::istream& operator>>(std::istream& in, N& n)
  {
    return in >> n.b >> n.g >> n.c;
  }

  int value_b() const { return b; }

  int value_g() const { return g; }

  int value_c() const { return c; }

};

struct W
{

  N n1, n2, n3;

  int m;

  std::string t;

  W() : m(0) { }

  friend std::istream& operator>>(std::istream& in, W& w)
  {
    return in >> w.n1 >> w.n2 >> w.n3 >> std::ws;
  }

  friend std::ostream& operator<<(std::ostream& out, const W& w)
  {
    return out << w.t << " " << w.m << std::endl;
  }

  std::string str(const std::vector<std::string>& s, const std::vector<std::size_t>& i) const
  {
    std::string out;
    for (std::vector<std::size_t>::const_iterator p = i.begin(); p != i.end(); ++p)
      out += s[*p];
    return out;
  }

  W& min()
  {
    std::vector<N*> v;
    v.push_back(&n1);
    v.push_back(&n2);
    v.push_back(&n3);

    F f;
    f.push_back(std::mem_fun(&N::value_b));
    f.push_back(std::mem_fun(&N::value_g));
    f.push_back(std::mem_fun(&N::value_c));

    std::vector<std::string> s(f.size());
    s[0] = "B";
    s[1] = "G";
    s[2] = "C";

    std::vector<std::size_t> fi(f.size());
    for (std::size_t i = 0; i < fi.size(); ++i)
      fi[i] = i;

    m = 0;
    t = "";

    do
      {
	int n = 0;
	for (std::size_t i = 0; i < fi.size(); ++i)
	  for (std::size_t j = 0; j < v.size(); ++j)
	    n += i == j ? 0 : f[fi[i]](v[j]);

	if (m == 0 || m > n || (m == n && t > str(s, fi)))
	  {
	    m = n;
	    t = str(s, fi);
	  }
      }
    while (std::next_permutation(fi.begin(), fi.end()));

    return *this;
  }

};

void evaluate(W* w)
{
  std::cout << w->min();
}

int main()
{
  std::vector<W*> v;

  while (std::cin.good())
    {
      W* w = new W();
      std::cin >> *w;
      v.push_back(w);
    }

  std::for_each(v.begin(), v.end(), evaluate);

  return 0;
}
