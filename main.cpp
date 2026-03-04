#include <iostream>
#include <cstddef>

//ВАРИАНТ III

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

  return c + sa + sb;
}

template< class T >
T* mergeN(const T* const * a, size_t sa, const size_t * sai, T* c)
{
  size_t s = sai[0];

  for (size_t i = 0; i < s; ++i)
  {
    c[i] = a[0][i];
  }

  for (size_t i = 1; i < sa; ++i)
  {
    T* tmp = nullptr;

    try
    {
      T* tmp = new T[sai[i] + s];
      merge2(c, s, a[i], sai[i], tmp);
      for(size_t k = 0; k < sai[i] + s; ++k)
      {
        c[k] = tmp[k];
      }
    } catch (...)
    {
      delete[] tmp;
      throw;
    }

    s += sai[i];

    delete[] tmp;
  }

  return c + s;
}

/*
НЕЯВНЫЙ ИНТЕРФЕЙС:
-Конструктор по умолчанию
-Присвыивающий оператор копирования
-Оператор сравнения(<)

НЕДОСТАТКИ ЯВНОГО ИНТЕРФЕЙСА:
-Дополнительное создание нового списка в цикле, а также из-за этого появление блока try/catch там же
*/

// Демонстрационная программа
int main()
{
  int* a = new int[4]{1, 2, 9, 10};
  int* b = new int[4]{3, 4, 6, 8};
  int* d = new int[3]{5, 7, 11};
  int** e = new int*[3]{a, b, d};
  size_t* f = new size_t[3]{4, 4, 3};
  int* c = new int[11];
  size_t errCode = 0;
  try
  {
    mergeN(e, 3, f, c);
  } catch (...)
  {
    errCode = 1;
  }

  if (!errCode)
  {
    for (size_t i = 0; i < 11; ++i)
    {
      std::cout << c[i] << '\n';
    }
  }

  delete[] a;
  delete[] b;
  delete[] d;
  delete[] e;
  delete[] f;
  delete[] c;
}