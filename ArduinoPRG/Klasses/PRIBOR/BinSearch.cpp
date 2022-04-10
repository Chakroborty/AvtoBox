//---------------------------------------------------------------------------

#pragma hdrstop
#include <iostream>
#include <vector>
#include <algorithm>
#include "BinSearch.h"
#include <stdio.h>
//---------------------------------------------------------------------------
 BinSH::BinSH()
 {
	Polosa[0].DNdiap =0;
	Polosa[0].DFv =0;
	Polosa[0].DK1 =0;
	Polosa[0].DK2 =1;
	Polosa[0].Dndel =0;
	Polosa[0].DNSys =0;
	Polosa[0].DBad =0;

	Polosa[1].DNdiap =1;
	Polosa[1].DFv =1;
	Polosa[1].DK1 =1;
	Polosa[1].DK2 =8;
	Polosa[1].Dndel =1;
	Polosa[1].DNSys =1;
	Polosa[1].DBad =1;

	Polosa[2].DNdiap =2;
	Polosa[2].DFv =2;
	Polosa[2].DK1 =2;
	Polosa[2].DK2 =2;
	Polosa[2].Dndel =2;
	Polosa[2].DNSys =3;
	Polosa[2].DBad =2;

 }
 BinSH::~BinSH()
 {

 }
int BinSH::binary_search(double x, int l ,int r)
{
	while(r - l > 1)
	//пока результат не станет однозначным
	{
		int mid = (l + r) / 2;
		Polosa[120].DFv;//делим отрезок [l,r] пополам
		if(Polosa[mid].DFv<x)
		//прверяем где находимся
		{
            l = mid;
		}
        else
        {
            r = mid;
		}
	}

				if(Polosa[r].DBad)
	{
						r=r+1;
    }
	else
	{


	}
	//цикл нужен, чтобы не править код
	//в случае увелечения интервала
	//[l,r]
	//for(int i = l; i <= r; i++)
	//    if(a[i]==x)
			return r;
	//return -1; не нашли такого элемента

}

//int main()
//{
//
//	for(int i = 0; i < NMAX; i++)
//	{
//		a[i] = rand();
//	}
//	sort(a, a + NMAX);
//	cout << binary_search(a[5],0,NMAX-1);
//	return 0;
//}


#pragma package(smart_init)
