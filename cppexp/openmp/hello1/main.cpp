#include <stdio.h>
#include <omp.h>
 
#define N 340000
 
int main(int argc, char *argv[])
{
  double a[N], b[N], c[N];
  long i;
  omp_set_dynamic(0);      // запретить библиотеке openmp менять число потоков во время исполнения
  omp_set_num_threads(1); // установить число потоков в 10
 
  // инициализируем массивы
  for (i = 0; i < N; i++)
  {
      a[i] = i * 1.0;
      b[i] = i * 2.0;
  }
 
  // вычисляем сумму массивов
#pragma omp parallel shared(a, b, c) private(i)
  {
#pragma omp for
    for (i = 0; i < N; i++)
      c[i] = a[i] + b[i];
  }
  for(i =  0; i < 11; i++)
  printf ("%f\n", c[i]);
  return 0;
}
