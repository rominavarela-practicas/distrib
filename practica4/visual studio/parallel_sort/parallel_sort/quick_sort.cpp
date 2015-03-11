#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <omp.h>

// Elementos a ordenar
#define N 20000000
int	arr[N];

// Methods
int	errors(	int	*numbers, int elems);
void initArr(int *numbers, int elems);
void SortArr ( int *numbers);

int	main()
{
	int	n;
	clock_t start,stop;

	initArr(arr,N);
	
	start=clock();
	SortArr	(arr);
	stop=clock();

	if((n=errors(arr,N)))
		printf("Se encontrarin %d errores\n",n);
	else
		printf("%d elementos ordenados en %1.2f segundos\n",N,((float)stop-(float)start)/1000.0);

	Sleep(3000);
}

void initArr(int*numbers,int elems)
{
	int i;
	for (i=0;i<elems;i++)
		numbers[i]=rand()*rand()%N;
}

int	errors(	int	*numbers,int elems)
{
	int i;
	int	errs=0;
	for(i=0;i<elems-1;i++)
		if(numbers[i]>numbers[i+1])
			errs++;
	return
		(errs);
}

void swap(int *array, int i1, int i2)
{
		int aux=array[i1];
		array[i1]=array[i2];
		array[i2]=aux;
}

int quickSortPartition(int *array, int left, int right)
{
		int pivote = array[right];
		int lPointer = left;
		int rPointer = right - 1;
		
		while(true) 
		{
			//until the left pointer contains something bigger than pivote
			while(lPointer <  right && array[lPointer] < pivote)
				lPointer ++;
			
			//until the right pointer contains something bigger than pivote
			while(rPointer >= left  && array[rPointer] > pivote)
				rPointer --;
			
			//if L&R crash, finish
			if(lPointer >= rPointer)
			{
				swap(array, lPointer, right);
				break;
			}
			//else, swap
			else 
			{
				swap(array, lPointer, rPointer);
				lPointer ++;
				rPointer --;
			}
		}
		
		//in this case lPointer is the right most pointer
		return lPointer;
	}

void quickSort(int *array, int left, int right)
{
	if(right - left <= 0)
        return;

	int p = quickSortPartition(array, left, right);

	#pragma omp parallel sections
	{
		#pragma omp section
		quickSort(array, left, p - 1);
		#pragma omp section
		quickSort(array, p + 1, right);
	}
}

void SortArr(int *numbers)
{
	quickSort(numbers,0,N);
}