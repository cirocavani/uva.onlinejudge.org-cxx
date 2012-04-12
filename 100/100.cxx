#include <iostream>
#include <vector>
#include <algorithm>

struct N
{

  int s, e, m;

  N() : s(1), e(1), m (1) { }

  friend std::istream& operator>>(std::istream& in, N& n)
  {
    return in >> n.s >> n.e >> std::ws;
  }

  friend std::ostream& operator<<(std::ostream& out, const N& n)
  {
    return out << n.s << " " << n.e << " " << n.m << std::endl;
  }

  int count(int n)
  {
    if (n == 1)
      return 1;

    int count = 2; // 1 and n
    while ((n = n % 2 == 0 ? n / 2 : 3 * n + 1) != 1)
      ++count;

    return count;
  }

  N& max()
  {
    m = 0;
    const int _s = std::min(s, e);
    const int _e = std::max(s, e);
    for (int i = _s; i <= _e; ++i)
      m = std::max(m, count(i));
    return *this;
  }

};

void evaluate(N* n)
{
  std::cout << n->max();
}

int main()
{
  std::vector<N*> v;

  while (std::cin.good())
    {
      N* n = new N();
      std::cin >> *n;
      v.push_back(n);
    }

  std::for_each(v.begin(), v.end(), evaluate);

  return 0;
}
