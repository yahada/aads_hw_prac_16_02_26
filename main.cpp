#include <iostream>
#include <cstddef>

template< class T >
T* merge2(const T* a, size_t sa, const T* b, size_t sb, T* c)
{
  size_t i = 0, j = 0, k = 0;
  while (i < sa && j < sb)
  {
    if (a[i] < b[j])
    {
      c[k++] = a[i++];
    } else
    {
      c[k++] = b[j++];
    }
  }

  while (i < sa)
  {
    c[k++] = a[i++];
  }

  while (j < sb)
  {
    c[k++] = b[j++];
  }

   return c;
}

template< class T >
T* merge(const T* const * a, size_t sa, const size_t * sai, T* c);

int main()
{
  int* a = new int[4]{1, 3, 5, 7};
  int* b = new int[4]{2, 4, 6, 8};
  int* c = new int[8];
  merge2(a, 4, b, 4, c);

  for (size_t i = 0; i < 8; ++i)
  {
    std::cout << c[i] << '\n';
  }
  delete[] a;
  delete[] b;
  delete[] c;
}