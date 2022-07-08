//implementacje sortowan oraz dodatkowych funkcji

// - babelkowe
// - wstawianie
// - wybieranie
// - mieszane (bablekowe)
// - polowkowe (modyfikacja wstawiania o wyszukiwanie polowkowe)
// - stogowe 
// - szybkie
void Update( int* t, int i, int j );
void Sortuj( int* t, int l, int p );

void BubbleSort( int* t, int n )
{
	int p = 0;
	for( int i = 1; i < n; i++ )
	{
		for( int j = 0; j < n - i; j++ )
		{
			if( t[j] > t[j + 1] )
			{
				p = t[j];
				t[j] = t[j + 1];
				t[j + 1] = p;
			}
		}
	}
	return;
}

void InsertSort( int* t, int n )
{
	int p = 0;
	int j = 0;
	for( int i = 1; i < n; i++ )
	{
		p = t[i];
		j = i - 1;
		while( ( j >= 0 ) && ( t[j] > p ) ) t[j + 1] = t[j--];
		t[j + 1] = p;
	}
	return;
}

void SelectSort( int* a, int n )
{
	for( int i = 0; i < n; i++ )
	{
		int k = i;
		int x = a[i];
		for( int j = i + 1; j < n; j++ )
			if( a[j] < x )
			{
				k = j;
				x = a[j];
			}
		a[k] = a[i];
		a[i] = x;
	}
}

void MixSort( int* t, int n )
{
	int l = 1;
	int p = n - 1;
	int k = n;
	do
	{
		for( int j = p; j >= l; j-- )
		{
			if( t[j - 1] > t[j] )
			{
				int x = t[j - 1];
				t[j - 1] = t[j];
				t[j] = x;
				k = j;
			}
		}
		l = k + 1;
		for( int j = l; j <= p; j++ )
		{
			if( t[j - 1] > t[j] )
			{
				int x = t[j - 1];
				t[j - 1] = t[j];
				t[j] = x;
				k = j;
			}
		}
		p = k - 1;
	} while( l <= p );
	return;
}

void HalfSort( int* a, int n )
{
	for( int i = 1; i < n; i++ )
	{
		int x = a[i];
		int l = 0;
		int p = i - 1;
		while( l <= p )
		{
			int m = ( l + p ) / 2;
			if( x < a[m] ) p = m - 1;
			else l = m + 1;
		}
		for( int j = i - 1; j >= l; j-- ) a[j+1] = a[j];
		a[l] = x;
	}
	return;
}
//--------------------------------------
// Sortowanie Shell'a
//int k = 0;
//int s = 0;
//int x = 0;
//int j = 0;
//const int p = 4;
//int h[p] = { 9, 5, 3, 1 };
//for (int m = 0; m < p; m++)
//{
//	k = h[m];
//	s = -k;
//	for (int i = k; i < n; i++)
//	{
//		x = t[i];
//		j = i - k;
//		while (x < t[j] && j > -1)
//		{
//			t[j + k] = t[j];
//			j -= k;
//		}
//		t[j + k] = x;
//	}
//}
//return;

void HeapSort( int* t, int n )
{
	int x = 0;
	for( int l = n / 2 + 1; l > 0; )
	{
		l--;
		Update( t, l, n - 1 );
	}
	for( int p = n - 1; p > 0; )
	{
		x = t[0];
		t[0] = t[p];
		t[p] = x;
		p--;
		Update( t, 0, p );
	}
}

void Update( int* t, int l, int p )
{
	if( l >= p ) return;
	int i = l;
	int j = 2 * i + 1;
	int x = t[i];
	while( j <= p )
	{
		if( j < p ) if( t[j] < t[j + 1] ) j++;
		if( x >= t[j] ) break;
		t[i] = t[j];
		i = j;
		j = 2 * i + 1;
	}
	t[i] = x;
}

void QuickSort( int* t, int n )
{
	Sortuj( t, 0, n-1 );
}

void Sortuj( int* t, int l, int p )
{
	int i = l;
	int j = p;
	int x = t[( l + p ) / 2];
	do
	{
		while( t[i] < x ) i++;
		while( x < t[j] ) j--;
		if( i <= j )
		{
			int w = t[i];
			t[i] = t[j];
			t[j] = w;
			i++;
			j--;
		}
	} while( !( i > j ) );
	if( l < j ) Sortuj( t, l, j );
	if( i < p ) Sortuj( t, i, p );
}