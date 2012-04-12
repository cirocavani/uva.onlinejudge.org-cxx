#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <functional>

struct Q;
typedef std::vector<Q*> S;

struct SizeCmp : public std::binary_function<S, S, bool>
{

  bool operator() (const S& v1, const S& v2) const
  {
    return v1.size() < v2.size();
  }

};

struct Q
{

  int p;

  std::vector<int> v;

  Q(int i, int n) : p(i), v(n) {}

  friend std::istream& operator>>(std::istream& in, Q& q)
  {
    for (std::vector<int>::iterator i = q.v.begin(); i != q.v.end(); ++i)
      in >> *i >> std::ws;
    return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const Q& q)
  {
    for (std::vector<int>::const_iterator i = q.v.begin(); i != q.v.end(); ++i)
      out << (i == q.v.begin() ? "" : " ") << *i;
    return out;
  }

  friend bool operator<(const Q& q1, const Q& q2)
  {
    return q1.v.front() < q2.v.front();
  }

  Q& sort()
  {
    std::sort(v.begin(), v.end(), rev_cmp);
    return *this;
  }

  static bool rev_cmp(int v1, int v2)
  {
    return v1 < v2;
  }

  bool fit(const Q& q)
  {
    for (size_t i = 0; i < v.size(); ++i)
      if (v[i] >= q.v[i])
	return false;

    return true;
  }

};

struct W
{

  int n;

  std::vector<Q> u;

  std::vector<int> v;

  friend std::istream& operator>>(std::istream& in, W& w)
  {
    int k;
    in >> k >> w.n >> std::ws;

    w.u = std::vector<Q>();

    for (int i = 0; i < k; ++i)
      {
	Q q = Q(i + 1, w.n);
	in >> q >> std::ws;
        w.u.push_back(q.sort());
      }

    return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const W& w)
  {
    out << w.v.size() << std::endl;
    for (std::vector<int>::const_iterator i = w.v.begin(); i != w.v.end(); ++i)
      out << (i == w.v.begin() ? "" : " ") << *i;
    
    return out;
  }

  W& operator()()
  {
    std::sort(u.begin(), u.end());

    std::list<S> stacks;
    
    for (std::vector<Q>::iterator i = u.begin(); i != u.end(); ++i)
      {
	std::priority_queue<S, std::vector<S>, SizeCmp> max;
	
	for (std::list<S>::iterator s = stacks.begin(); s != stacks.end(); ++s)
	  if (s->back()->fit(*i))
	    {
	      S v = *s; // copy
	      v.push_back(&(*i));
	      max.push(v);
	    }

	if (!max.empty())
	  stacks.push_back(max.top());

	S stack;
	stack.push_back(&(*i));

	stacks.push_back(stack);
      }

    S& stack = *std::max_element(stacks.begin(), stacks.end(), SizeCmp());

    trace(stack);

    return *this;
  }
  
  void trace(const S& stack)
  {
    v.clear();
    for (S::const_iterator i = stack.begin(); i != stack.end(); i++)
      v.push_back((*i)->p);
  }

};

void evaluate(W& w)
{
  std::cout << w() << std::endl;
}

int main()
{
  std::vector<W> v;

  while (std::cin.good())
    {
      W w;
      std::cin >> w;
      v.push_back(w);
    }

  std::for_each(v.begin(), v.end(), evaluate);

  return 0;
}
