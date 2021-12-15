#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) 
{
	if (mat->r != mat->c)
	{
		return 2;
	}
	if (x->r != mat->r)
	{
		return 2;
	}
	if(b->r != mat->r)
	{
		return 2;
	}	
	for(int i = mat->r-1; i >= 0;i--)// pętla po wierszach "idąca od dołu" 
	{
		double s=0;
		for(int j = i+1; j < mat->r; j++) //pętla po kolumnach 
		{
			s+=(mat->data[i][j])*(x->data[j][0]);
		}
		if (mat->data[i][i] == 0) //dzielenie przez 0
		{
			return(1);
		}
		x->data[i][0]=(b->data[i][0] - s) / (mat->data[i][i]);
	}

	/* To ponizej jest przepisaniem b do x. Nalezy to poprawic! */
/*
	int l;
	for (l =0;l < x->r; l++) 
	{
		x->data[l][0] = b->data[l][0];
	}
*/
	return 0;
}


