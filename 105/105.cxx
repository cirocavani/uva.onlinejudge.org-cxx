#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

struct N
{
  int l;
  int r;
  int h;
  N(int _l = 0, int _r = 0, int _h = 0) : l(_l), r(_r), h(_h) { }
};

class M
{

  int w;

  std::vector<N> n;

  std::vector<int> v;
    
public:

  M() : w(0) { }

  friend std::istream& operator>>(std::istream& in, M& m)
  {
    int l, h, r;
    in >> l >> h >> r >> std::ws;

    m.n.push_back(N(l, r, h));

    if (m.w < r)
      m.w = r;
  }

  friend std::ostream& operator<<(std::ostream& out, const M& m)
  {
    if (m.v.empty())
      return out;

    std::vector<int>::const_iterator i = m.v.begin();
    out << *i;
    while (++i != m.v.end())
      {
	out << " " << *i;
      }

    return out << std::endl;
  }

  M& operator()()
  {
    std::vector<int> h(w, 0);

    for (std::vector<N>::iterator i = n.begin(); i != n.end(); ++i)
      {
	std::binder2nd<std::less<int> > hidden(std::less<int>(), i->h);
        std::replace_if(&h[i->l], &h[i->r], hidden, i->h);
      }

    int _h = 0;
    for (int i = 0; i < h.size(); ++i)
      {
        if (_h != h[i])
	  {
	    v.push_back(i);
	    v.push_back(_h = h[i]);
	  }
      }
  
    v.push_back(w);
    v.push_back(0);

    return *this;
  }

};

int main()
{
  M m;

  while (std::cin.good())
    {
      std::cin >> m;
    }

  m();

  std::cout << m;

  return 0;
}
