#include <iostream>
#include <vector>
#include <cmath>

struct V
{
  double h, m, k, n;
  V(double _h, double _m) : h(_h), m(_m), k(0.0), n(0.0) { }

  void operator()()
  {
    if (m == 1.0)
      {
        k = std::log(h) / std::log(2.0);
        n = 1.0;
      }
    else if (h - m == 1.0)
      {
        k = 1.0;
        n = m;
      }
    else
      {
	for (double _k = 2.0, mk = std::log(h) / std::log(2.0); _k < mk; ++_k)
	  {
	    double kr = 1.0 / _k;

	    double _nm = std::pow(m, kr);

	    double _nh = std::pow(h, kr) - 1.0;

	    if (std::abs(_nh - _nm) < 0.01)
	      {
		k = _k;
		n = _nm;
		break;
	      }
	  }
      }
  }

  double ms() const
  {
    return n == 1.0 ? k : (std::pow(n, k) - 1.0) / (n - 1.0);
  }
  double hs() const
  {
    double q = n / (n + 1.0);
    return h * (std::pow(q, k) - 1.0) / (q - 1.0) + m;
  }
};

class W
{
  std::vector<V> v;
public:
  W() { }
  inline friend std::istream& operator>>(std::istream& in, W& w)
  {
    double h, m;
    in >> h >> m >> std::ws;

    if (h == 0 && m == 0)
      {
	in.setstate(std::ios::eofbit);
	return in;
      }

    w.v.push_back(V(h, m));
    
    return in;
  }
  inline friend std::ostream& operator<<(std::ostream& out, const W& w)
  {
    out.precision(0);
    for (std::vector<V>::const_iterator i = w.v.begin(); i != w.v.end(); ++i)
      {
	out << std::fixed << i->ms();
	out << " ";
	out << std::fixed << i->hs();
	out << std::endl;
      }
    return out;
  }
  inline void operator()()
  {
    for (std::vector<V>::iterator i = v.begin(); i != v.end(); ++i)
      (*i)();
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
