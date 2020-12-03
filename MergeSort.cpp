#include <iostream>
using namespace std;

template <typename T>
static void MergeArrays(T A[], T helperA[], size_t leftPos,
                        size_t rightPos, size_t rightEnd)
{
   size_t i, leftEnd, numOfElements, helperPos;
   leftEnd = rightPos - 1;
   helperPos = leftPos;
   numOfElements = rightEnd - leftPos + 1;
   while (leftPos <= leftEnd && rightPos <= rightEnd)
   {
      if (A[leftPos] <= A[rightPos])
         helperA[helperPos++] = A[leftPos++];
      else
         helperA[helperPos++] = A[rightPos++];
   }
   while (leftPos <= leftEnd)
      helperA[helperPos++] = A[leftPos++]; // copy the remainder of the first half

   while (rightPos <= rightEnd)
      helperA[helperPos++] = A[rightPos++]; // copy the remainder of the second half

   for (i = 0; i < numOfElements; i++, rightEnd--)
      A[rightEnd] = helperA[rightEnd]; // copy temporary array back to the
                                       // original array
}

template <typename T>
static void MergeRecursive(T A[], T helperA[], size_t left,
                           size_t right)
{
   size_t middle;
   if (left < right)
   {
      middle = (left + right) / 2;
      MergeRecursive(A, helperA, left, middle);
      MergeRecursive(A, helperA, middle + 1, right);
      MergeArrays(A, helperA, left, middle + 1, right);
   }
}
template <typename T>
static void MergeSort(T A[], size_t n)
{
   T *helperArray;
   helperArray = new (nothrow) T[n];
   if (helperArray != nullptr)
   {
      MergeRecursive(A, helperArray, 0, n - 1);
      delete[] helperArray;
   }
   else
      throw bad_alloc();
}