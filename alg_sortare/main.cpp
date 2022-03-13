#include <iostream>
#include <fstream>
#include <random>
#include <limits>
#include <algorithm>
#include <chrono>
#include <vector>
#include<bits/stdc++.h>
using namespace std::chrono;
using namespace std;

vector<long long> v1;
vector<long long> v2;
vector<long long> vaux;
vector<long long> w(5), u(5);
vector<long long> w1(7), u1(7);

void mergesort(vector<long long> &v, long long n, long long st, long long dr)
{
    long long i, j, m, aux, k;
	if(st < dr)
	{
        m = (st + dr) / 2;
		mergesort(v, n, st , m);
		mergesort(v, n, m + 1 , dr);
		i = st, j = m + 1, k = 0;
		while(i <= m && j <= dr)
			if(v[i] < v[j])
				vaux[k++] = v[i++];
			else
				vaux[k++] = v[j++];
        if(i <= m)
            for(aux = i; aux <= m; aux++)
                vaux[k++] = v[aux];
        if(j <= dr)
            for(aux = j; aux <= dr; aux++)
                vaux[k++] = v[aux];
        j = 0;
		for(i = st; i <= dr; i++)
            v[i] = vaux[j++];
	}
}

void shellsort(vector<long long> &v, long long n)
{
    long long d, i, aux, j;
	for (d = n / 2; d > 0; d /= 2)
	{
		for (i = d; i < n; i += 1)
		{
			aux = v[i];
			for (j = i; j >= d && v[j - d] > aux; j -= d)
				v[j] = v[j - d];
			v[j] = aux;
		}
	}
}

void shellsort_knuth(vector<long long> &v, long long n)
{
    long long d, i = 1, aux, j;
    while(i < n) i = i * 3 + 1;
	d = i;
	while(d > 0)
	{
		for (i = d; i < n; i += 1)
		{
			aux = v[i];
			for (j = i; j >= d && v[j - d] > aux; j -= d)
				v[j] = v[j - d];
			v[j] = aux;
		}
		d -= 1;
		d /= 3;
	}
}

void radixsort(vector<long long> &v, long long n, long long mx)
{
    long long i, p;
    vector <long long> aux(n);
	for (p = 1; mx / p > 0; p *= 10)
    {
        vector<long long> f(10, 0);
        for (i = 0; i < n; i++)
            f[(v[i] / p) % 10]++;
        for (i = 1; i < 10; i++)
            f[i] += f[i - 1];
        for (i = n - 1; i >= 0; i--)
        {
            aux[f[(v[i] / p) % 10] - 1] = v[i];
            f[(v[i] / p) % 10]--;
        }
        for (i = 0; i < n; i++)
            v[i] = aux[i];
    }
}

void radixsort28(vector<long long> &v, long long n, long long mx)
{
    long long i, p;
    vector <long long> aux(n);
        for (p = 1; mx / p > 0; p = p << 8)
        {
            vector<long long> f(256, 0);
            for (i = 0; i < n; i++)
                f[(v[i] / p) % 256]++;
            for (i = 1; i < 256; i++)
                f[i] += f[i - 1];
            for (i = n - 1; i >= 0; i--)
            {
                aux[f[(v[i] / p) % 256] - 1] = v[i];
                f[(v[i] / p) % 256]--;
            }
            for (i = 0; i < n; i++)
                v[i] = aux[i];
        }
}

void radixsort210(vector<long long> &v, long long n, long long mx)
{
    long long i, p;
    vector <long long> aux(n);
        for (p = 1; mx / p > 0; p = p << 10)
        {
            vector<long long> f(1024, 0);
            for (i = 0; i < n; i++)
                f[(v[i] / p) % 1024]++;
            for (i = 1; i < 1024; i++)
                f[i] += f[i - 1];
            for (i = n - 1; i >= 0; i--)
            {
                aux[f[(v[i] / p) % 1024] - 1] = v[i];
                f[(v[i] / p) % 1024]--;
            }
            for (i = 0; i < n; i++)
                v[i] = aux[i];
        }
}

void radixsort216(vector<long long> &v, long long n, long long mx)
{
    long long i, p;
    vector <long long> aux(n);
        for (p = 1; mx / p > 0; p = p << 16)
        {
            vector<long long> f(65536, 0);
            for (i = 0; i < n; i++)
                f[(v[i] / p) % 65536]++;
            for (i = 1; i < 65536; i++)
                f[i] += f[i - 1];
            for (i = n - 1; i >= 0; i--)
            {
                aux[f[(v[i] / p) % 65536] - 1] = v[i];
                f[(v[i] / p) % 65536]--;
            }
            for (i = 0; i < n; i++)
                v[i] = aux[i];
        }
}

void quicksort3(vector<long long> &v, long long st, long long dr)
{
    long long a, b, c, m;
    long long aux;
	if(st < dr)
	{
		a = rand() %(dr-st+1)+st;
		b = rand() %(dr-st+1)+st;
		c = rand() %(dr-st+1)+st;
		m = (st + dr) / 2;
		if(v[c] < v[a] && v[a] < v[b] || v[b] < v[a] && v[a] < v[c])
        {
            aux = v[a];
            v[a] = v[m];
            v[m] = aux;
        }
        else if(v[a] < v[b] && v[b] < v[c] || v[c] < v[b] && v[b] < v[a])
        {
            aux = v[b];
            v[b] = v[m];
            v[m] = aux;
        }
        else
        {
            aux = v[c];
            v[c] = v[m];
            v[m] = aux;
        }
		int i = st , j = dr, d = 0;
		while(i < j)
		{
			if(v[i] > v[j])
			{
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
				d = 1 - d;
			}
			i += d;
			j -= 1 - d;
		}
		quicksort3(v, st , i - 1);
		quicksort3(v, i + 1 , dr);
	}
}

void quicksort5(vector<long long> &v, long long st, long long dr)
{
    long long a, b, c, m, i, x, j;
    long long aux;
	if(st < dr)
	{
		for(i = 0; i < 5; i++)
        {
            x = rand() %(dr-st+1)+st;
            w[i] = v[x];
            u[i] = x;
        }
        for(i = 0; i < 4; i++)
            for(j = i + 1; j < 5; j++)
                if(w[i] > w[j])
                {
                    aux = w[i];
                    w[i] = w[j];
                    w[j] = aux;
                    aux = u[i];
                    u[i] = u[j];
                    u[j] = aux;
                }
        m = (st + dr) / 2;
        aux = v[u[2]];
        v[u[2]] = v[m];
        v[m] = aux;
		int i = st , j = dr, d = 0;
		while(i < j)
		{
			if(v[i] > v[j])
			{
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
				d = 1 - d;
			}
			i += d;
			j -= 1 - d;
		}
		quicksort5(v, st , i - 1);
		quicksort5(v, i + 1 , dr);
	}
}

void quicksort7(vector<long long> &v, long long st, long long dr)
{
    long long a, b, c, m, i, x, j;
    long long aux;
	if(st < dr)
	{
		for(i = 0; i < 7; i++)
        {
            x = rand() %(dr-st+1)+st;
            w1[i] = v[x];
            u1[i] = x;
        }
        for(i = 0; i < 6; i++)
            for(j = i + 1; j < 7; j++)
                if(w1[i] > w1[j])
                {
                    aux = w1[i];
                    w1[i] = w1[j];
                    w1[j] = aux;
                    aux = u1[i];
                    u1[i] = u1[j];
                    u1[j] = aux;
                }
        m = (st + dr) / 2;
        aux = v[u1[3]];
        v[u1[3]] = v[m];
        v[m] = aux;
		int i = st , j = dr, d = 0;
		while(i < j)
		{
			if(v[i] > v[j])
			{
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
				d = 1 - d;
			}
			i += d;
			j -= 1 - d;
		}
		quicksort7(v, st , i - 1);
		quicksort7(v, i + 1 , dr);
	}
}

void ajust_heap(vector <long long> &v, long long n, long long i)
{
	long long rad, aux;
	rad = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && v[l] > v[rad])
		rad = l;
	if (r < n && v[r] > v[rad])
		rad = r;
	if (rad != i)
    {
        aux = v[i];
        v[i] = v[rad];
        v[rad] = aux;
		ajust_heap(v, n, rad);
	}
}

void heapsort(vector <long long> &v, long long n)
{
    long long aux;
	for (int i = n / 2 - 1; i >= 0; i--)
		ajust_heap(v, n, i);
	for (int i = n - 1; i > 0; i--)
    {
        aux = v[0];
        v[0] = v[i];
        v[i] = aux;
		ajust_heap(v, i, 0);
	}
}

bool test_sort(vector<long long> v2, vector<long long>& v1, long long n)
{
    sort(v2.begin(), v2.end());
    for(int i = 0; i < n; i++)
        if(v2[i] != v1[i]) return false;
    return true;
}

void generare(vector<long long> &v, long long mx){
    mt19937_64 gen(time(NULL));

    uniform_int_distribution<long long> random(0, mx);

    for(auto i = v.begin(); i!=v.end(); i++){
        *i = random(gen);
    }
}

long long timp(int i, long long n, long long mx, vector <long long> v)
{
        if(i == 1)
            {
                auto start2 = high_resolution_clock::now();
                radixsort(v, n, mx);
                auto stop2 = high_resolution_clock::now();
                auto duration2 = duration_cast<microseconds>(stop2 - start2);
                return duration2.count();
            }
        else if(i == 2)
            {
                auto start3 = high_resolution_clock::now();
                radixsort28(v, n, mx);
                auto stop3 = high_resolution_clock::now();
                auto duration3 = duration_cast<microseconds>(stop3 - start3);
                return duration3.count();
            }
        else if(i == 3)
            {
                auto start12 = high_resolution_clock::now();
                radixsort210(v, n, mx);
                auto stop12 = high_resolution_clock::now();
                auto duration12 = duration_cast<microseconds>(stop12 - start12);
                return duration12.count();
            }
        else if(i == 4)
            {
                auto start13 = high_resolution_clock::now();
                radixsort216(v, n, mx);
                auto stop13 = high_resolution_clock::now();
                auto duration13 = duration_cast<microseconds>(stop13 - start13);
                return duration13.count();
            }
        else if(i == 5)
            {
                auto start4 = high_resolution_clock::now();
                vaux = vector<long long>(n);
                mergesort(v, n, 0, n-1);
                auto stop4 = high_resolution_clock::now();
                auto duration4 = duration_cast<microseconds>(stop4 - start4);
                return duration4.count();

            }
        else if(i == 6)  {
                auto start5 = high_resolution_clock::now();
                shellsort(v, n);
                auto stop5 = high_resolution_clock::now();
                auto duration5 = duration_cast<microseconds>(stop5 - start5);
                return duration5.count();
            }
        else if(i == 7)
            {
                auto start6 = high_resolution_clock::now();
                shellsort_knuth(v, n);
                auto stop6 = high_resolution_clock::now();
                auto duration6 = duration_cast<microseconds>(stop6 - start6);
                return duration6.count();
            }
        else if(i == 8)
            {
                auto start7 = high_resolution_clock::now();
                quicksort3(v, 0, n-1);
                auto stop7 = high_resolution_clock::now();
                auto duration7 = duration_cast<microseconds>(stop7 - start7);
                return duration7.count();

            }
        else if(i == 9)
            {
                auto start8 = high_resolution_clock::now();

                quicksort5(v, 0, n-1);
                auto stop8 = high_resolution_clock::now();
                auto duration8 = duration_cast<microseconds>(stop8 - start8);
                return duration8.count();

            }
        else if(i == 10)
            {
                auto start9 = high_resolution_clock::now();
                w1 = vector<long long>(7, 0);
                u1 = vector<long long>(7, 0);
                quicksort7(v, 0, n-1);
                auto stop9 = high_resolution_clock::now();
                auto duration9 = duration_cast<microseconds>(stop9 - start9);
                return duration9.count();
            }
        else if(i == 11)
            {
                auto start10 = high_resolution_clock::now();
                heapsort(v, n);
                auto stop10 = high_resolution_clock::now();
                auto duration10 = duration_cast<microseconds>(stop10 - start10);
                return duration10.count();
            }
        else if(i == 12)
            {
                auto start11 = high_resolution_clock::now();
                sort(v.begin(), v.end());
                auto stop11 = high_resolution_clock::now();
                auto duration11 = duration_cast<microseconds>(stop11 - start11);
                return duration11.count();
            }
        }


void generare_csv(long long n_mn, long long n_mx, long long pas, long long mx){
    ofstream g("timpi.csv");
    g<<",Radix Sort(Base 10),Radix Sort(Base 2^16),Merge Sort,Shell Sort,Shell Sort Knuth's Sequence,Quick Sort(Median of Three),Quick Sort(Median of Five),Quick Sort(Median of Seven),Heap Sort,STL Sort\n";
    for(long long k = n_mn; k<=n_mx; k+=pas){
        g<<k;
        vector<long long> v(k);
        generare(v, mx);
        for(int i=1;i<=4;i++){
            g<<","<<timp(i, k, mx, v);
        }
        g<<"\n";
    }

    g.close();
}

int main()
{int nr, j, o;
long long n, mx, i, n_mn, n_mx, pas;
cout << "Alegeti una dintre cele doua optiuni:\n1 - Afisarea timpilor de rulare obtinuti pe teste cu numarul de elemente cuprins intr-un interval. Introduceti capetele intervalului, pasul de parcurgere si valoarea elementului maxim din sir.\n2 - Testarea algoritmilor de sortare pe un numar (nr) de teste, care se citesc din fisierul 'teste.in', sub forma a nr perechi de forma (nr_elemente, val max).";
cin >> o;
if (o == 1)
{
    cout << "capat interval stanga: "; cin >> n_mn;
    cout << "capat interval dreapta: "; cin >> n_mx;
    cout << "pas parcurgere interval: "; cin >> pas;
    cout << "valoarea maxima din sir: "; cin >> mx;
    generare_csv(n_mn, n_mx, pas, mx);
}
else
{
ifstream f("teste.in");
f >> nr;

for(j = 0; j < nr; j++)
{
    f >> n >> mx;
    vector<long long> v1(n), v2(n);
    v1 = vector<long long>(n);
    v2 = vector<long long>(n);

    generare(v1, mx);
    /*for(i = 0; i < n; i++)
        cout << v1[i] << ' ';*/
    for(i = 0; i < n; i++)
        v2[i] = v1[i];
    /*for(i = 0; i < n; i++)
        cout << v1[i] << ' ';
    cout << '\n';*/
    cout << "n = " << n << " mx = " << mx << '\n';
    auto start2 = high_resolution_clock::now();
    radixsort(v1, n, mx);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout << "Radix Sort Base 10: " << duration2.count() << " test_sort: "  << test_sort(v2, v1, n) << '\n';
    /*for(i = 0; i < n; i++)
        cout << v1[i] << ' ';
    cout << '\n';*/
    for(i = 0; i < n; i++)
        v1[i] = v2[i];
    if(mx >= 1000000000000000) cout << "Nu se poate sorta cu RadixSort\n.";
    else
    {
        auto start3 = high_resolution_clock::now();
        radixsort216(v1, n, mx);
        auto stop3 = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(stop3 - start3);
        cout << "Radix Sort Base 2^16: " << duration3.count() << " test_sort: "  << test_sort(v2, v1, n) << '\n';
        for(i = 0; i < n; i++)
            v1[i] = v2[i];
    }

    for(i = 0; i < n; i++)
        v1[i] = v2[i];
    if(mx >= 1000000000000000) cout << "Nu se poate sorta cu RadixSort\n.";
    else
    {
        auto start9 = high_resolution_clock::now();
        radixsort28(v1, n, mx);
        auto stop9 = high_resolution_clock::now();
        auto duration9 = duration_cast<microseconds>(stop9 - start9);
        cout << "Radix Sort Base 2^8: " << duration9.count() << " test_sort: "  << test_sort(v2, v1, n) << '\n';
        for(i = 0; i < n; i++)
            v1[i] = v2[i];
    }

    for(i = 0; i < n; i++)
        v1[i] = v2[i];
    if(mx >= 1000000000000000) cout << "Nu se poate sorta cu RadixSort\n.";
    else
    {
        auto start10 = high_resolution_clock::now();
        radixsort210(v1, n, mx);
        auto stop10 = high_resolution_clock::now();
        auto duration10 = duration_cast<microseconds>(stop10 - start10);
        cout << "Radix Sort Base 2^10: " << duration10.count() << " test_sort: "  << test_sort(v2, v1, n) << '\n';
        for(i = 0; i < n; i++)
            v1[i] = v2[i];
    }

    auto start = high_resolution_clock::now();
    vaux = vector<long long>(n);
    mergesort(v1, n, 0, n - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Merge Sort: " << duration.count() << " test_sort: "  << test_sort(v2, v1, n) << '\n';
    /*for(i = 0; i < n; i++)
        cout << v1[i] << ' ';
    cout << '\n';*/
    for(i = 0; i < n; i++)
        v1[i] = v2[i];
    auto start1 = high_resolution_clock::now();
    shellsort(v1, n);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout << "Shell Sort Basic: " << duration1.count() << " test_sort: "  << test_sort(v2, v1, n) << '\n';
    /*for(i = 0; i < n; i++)
        cout << v1[i] << ' ';
    cout << '\n';*/
    for(i = 0; i < n; i++)
        v1[i] = v2[i];
    auto start9 = high_resolution_clock::now();
    shellsort(v1, n);
    auto stop9 = high_resolution_clock::now();
    auto duration9 = duration_cast<microseconds>(stop9 - start9);
    cout << "Shell Sort Knuth: " << duration9.count() << " test_sort: "  << test_sort(v2, v1, n) << '\n';
   /* for(i = 0; i < n; i++)
        cout << v1[i] << ' ';
    cout << '\n';*/
    for(i = 0; i < n; i++)
        v1[i] = v2[i];
    auto start4 = high_resolution_clock::now();
    quicksort3(v1, 0, n - 1);
    auto stop4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(stop4 - start4);
    cout << "Quick Sort Median of 3: " << duration4.count() << " test_sort: "  << test_sort(v2, v1, n) << '\n';
    /*for (i = 0; i < n; i++)
        cout << v1[i] << ' ';
    cout << '\n';*/
    for(i = 0; i < n; i++)
        v1[i] = v2[i];
    auto start5 = high_resolution_clock::now();
    quicksort5(v1, 0, n - 1);
    auto stop5 = high_resolution_clock::now();
    auto duration5 = duration_cast<microseconds>(stop5 - start5);
    cout << "Quick Sort Median of 5: " << duration5.count() << " test_sort: "  << test_sort(v2, v1, n) << '\n';
    /*for (i = 0; i < n; i++)
        cout << v1[i] << ' ';
    cout << '\n';*/
    for(i = 0; i < n; i++)
        v1[i] = v2[i];
    auto start6 = high_resolution_clock::now();
    quicksort7(v1, 0, n - 1);
    auto stop6 = high_resolution_clock::now();
    auto duration6 = duration_cast<microseconds>(stop6 - start6);
    cout << "Quick Sort Median of 7: " << duration6.count() << " test_sort: "  << test_sort(v2, v1, n) << '\n';
    /*for (i = 0; i < n; i++)
        cout << v1[i] << ' ';
    cout << '\n';*/
    for(i = 0; i < n; i++)
        v1[i] = v2[i];
    auto start7 = high_resolution_clock::now();
    heapsort(v1, n);
    auto stop7 = high_resolution_clock::now();
    auto duration7 = duration_cast<microseconds>(stop7 - start7);
    cout << "Heap Sort: " << duration7.count() << " test_sort: "  << test_sort(v2, v1, n) << '\n';
    /*for (i = 0; i < n; i++)
        cout << v1[i] << ' ';
    cout << '\n';*/
    for(i = 0; i < n; i++)
        v1[i] = v2[i];
    auto start8 = high_resolution_clock::now();
    sort(v1.begin(), v1.end());
    auto stop8 = high_resolution_clock::now();
    auto duration8 = duration_cast<microseconds>(stop8 - start8);
    cout << "STL Sort: " << duration8.count();
}
}
return 0;
}
