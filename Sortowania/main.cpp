//		Dla testow nalezy na warunkowej kompilacji wypisac np pierwzych 50 elementow (po 10 w linii) - funkcja
//    Testowo wypisac przed i po sortow - testowac dla malych tablic np 20 elem -czy samo sortowanie dziala

#include "sort.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX	50
#define MAXCOL 10

//#define _DEBUG_
int CreateTab( int** pT, int n );
void RandTab(int* pTab, int n);
void PrintTab( int* pT, int n );
void DeleteTab( int** pp );
typedef void (*pf)( int*, int );


int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		printf( "Program usage: %s <array size>.\n", argv[0] );
		return 4;
	}

	// BubbleSort InsertSort wybieranie mieszane (bablekowe) polowkowe stogowe szybkie
	// 2. w pliku z main() zdefiniowac typ wskaznikowy na funckje sortujace
	// 3. w main() zdefiniowac lokalna tablice pSortTab (bez rozmiaru - []) i zainicjowana
	//    od razu na adresy funkcji sortujacych (nazwy)
	pf SortTab[] = { BubbleSort, InsertSort, SelectSort, MixSort, HalfSort, HeapSort, QuickSort };


	// 4. w main() zdefiniowac tablice napisow - nazw tych sortowan (do wypisywania)
	const char* names[] = { "Bubble Sort", "Insertion Sort", "Selection Sort",
									"Mix Sort", "Half Sort", "Heapsort", "Quicksort" };


	// 5. Zainicjowac losowo dynamicznie stworzona tablice wzorcowa
	int n = atoi( argv[1] );

	int* pTab = NULL;
	if( !CreateTab( &pTab, n ) )
	{
		perror( "\aError allocating \"to be sorted\" list\n" );
		return 2;
	}

	RandTab( pTab, n );

	//wydruk kontrolny
	#ifdef _DEBUG_
	printf( "\n Tablica odczytana:\n" );
	PrintTab( pTab, ( n < MAX ) ? n : MAX );
	#endif

	int* pCopy = NULL;
	if( !CreateTab( &pCopy, n ) )
	{
		perror( "\aError allocating copied list\n" );
		return 3;
	}


	//		ktora bedzie kopiowana (memcpy() -<memory.h>) przed kazdym sortowaniem do tablicy sortowanej
	//		i w petli sortowac ja  i wypisac jakie sortowanie i ile czasu zajmuje
	//    Oczywiscie sortowania sa wywolywane poprzez tablice adresow do funkcji!!!!

	int nFun = sizeof( SortTab ) / sizeof( pf );

	for( int i = 0; i < nFun; i++ )
	{
		memcpy( pCopy, pTab, n * sizeof( int ) );
		//to ni¿ej by³o do sprawdzenia czy tablica dobrze siê kopiuje
		//printf( "\n\n\n Tablica (skopiowana) przed sortowaniem %s.\n ", names[i] );
		//PrintTab( pCopy, n);

		double start = clock();
		(SortTab[i])( pCopy, n );
		//stop  = clock();
		double total = clock() - start;
		printf( "\n\n  Czas sortowania %s: %.3f s.\n", names[i], (double)(clock() - start) / CLOCKS_PER_SEC );
      #ifdef _DEBUG_
		   printf( "  Tablica po sortowaniu %s.\n", names[i] );
		   PrintTab( pCopy, ( n < MAX ) ? n : MAX );
      #endif
	}

	DeleteTab( &pTab );
	DeleteTab( &pCopy );

	return 1;
}

void RandTab( int* pTab, int n )
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++) *pTab++ = rand();
	return;
}

int CreateTab( int** pT, int n )
{
	*pT = (int*)malloc( n * sizeof( int ) );
	if( !*pT ) return 0;
	memset( *pT, 0, n * sizeof( int ) );
	return 1;
}

void PrintTab( int* pT, int n )
{
	for( int i = 0; i < n; i++ )
	{
		printf( "%6d ", *pT++ );
		if( ( ( i + 1 ) % MAXCOL ) == 0 ) printf("\n");
	}
}

void DeleteTab( int** pp )
{
	free( *pp );
	*pp = NULL;
}