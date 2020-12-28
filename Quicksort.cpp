#include <iostream>
#define Cutoff (3)

template <typename T>
static void InsertionSort(T Arr[], int n)
{
   int i, j;
   T temp;
   for (i = 1; i < n; i++)
   {
      temp = Arr[i];
      for (j = i; j >= 1 && Arr[j - 1] > temp; j--)
         Arr[j] = Arr[j - 1];
      Arr[j] = temp;
   }
}

class QuickSort
{
private:
   template <typename T>
   static void Swap(T *left, T *right)
   {
      T temp = *left;
      *left = *right;
      *right = temp;
   }

   template <typename T>
   static T medianOf3(T Arr[], size_t left, size_t right)
   {
      size_t middle = (left + right) / 2;
      if (Arr[left] > Arr[middle])
         Swap(&Arr[left], &Arr[middle]);
      if (Arr[left] > Arr[right])
         Swap(&Arr[left], &Arr[right]);
      if (Arr[middle] > Arr[right])
         Swap(&Arr[middle], &Arr[right]);
      Swap(&Arr[middle], &Arr[right - 1]); // Hide pivot
      return Arr[right - 1];               // Return pivot
   }
   template <typename T>
   static void QSortMedianOf3(T Arr[], size_t left, size_t right)
   {
      size_t i, j;
      T pivot;
      if (left + Cutoff <= right)
      {
         pivot = medianOf3(Arr, left, right);
         i = left;
         j = right - 1;
         while (1)
         {
            while (Arr[++i] < pivot)
               ;
            while (Arr[--j] > pivot)
               ;
            if (i < j)
               Swap(&Arr[i], &Arr[j]);
            else
               break;
         }
         Swap(&Arr[i], &Arr[right - 1]); // Renew pivot
         QSortMedianOf3(Arr, left, i - 1);
         QSortMedianOf3(Arr, i + 1, right);
      }
      else
      {
         InsertionSort(
             Arr + left,
             right - left + 1); // If subarray is small sort it via Insertion sort
      }
   }

   // QuickSort Pivot=First element
   template <typename T>
   static void QSortFirstElement(T Arr[], size_t left, size_t right)
   {
      size_t i, j;
      i = left + 1;
      j = right;
      if (left >= right)
         return;
      while ((i <= j) && (i <= right) && (j > left))
      {
         while ((Arr[i] < Arr[left]) && (i <= right))
            i++;
         while ((Arr[j] > Arr[left]) && (j > left))
            j--;
         if (i < j)
         {
            Swap(&Arr[i], &Arr[j]);
         }
      }
      if (i > right)
      { // pivot is the biggest in array
         Swap(&Arr[left], &Arr[right]);
         QSortFirstElement(Arr, left, right - 1);
      }
      else if (j <= left)
      { // pivot is the smallest in array
         QSortFirstElement(Arr, left + 1, right);
      }
      else
      { // pivot is somewhere in the middle
         Swap(&Arr[left], &Arr[j]);
         QSortFirstElement(Arr, left, j - 1);
         QSortFirstElement(Arr, j + 1, right);
      }
   }

public:
   enum PivotStrategy
   {
      FirstElement = 1,
      MedianOf3
   };

   template <typename T>
   static void Sort(T Arr[], size_t n, PivotStrategy strategy)
   {
      if (strategy == PivotStrategy::MedianOf3)
         QSortMedianOf3(Arr, 0, n - 1);
      else if (strategy == PivotStrategy::FirstElement)
         QSortFirstElement(Arr, 0, n - 1);
   }
};