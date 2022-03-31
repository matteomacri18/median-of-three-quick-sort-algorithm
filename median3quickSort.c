#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SwapValue(int *A, int i, int j)
{
    int temp;
    temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

/* Algoritmo MedianOfThree */
int MedianOfThree(int *A, int i, int j, int k)
{
    if (A[i] > A[j])
    {
        if (A[j] >= A[k])
        {
            return j;
        }
        else if (A[i] < A[k])
        {
            return i;
        }
        else
        {
            return k;
        }
    }
    else
    {
        if (A[i] >= A[k])
        {
            return i;
        }
        else if (A[j] < A[k])
        {
            return j;
        }
        else
        {
            return k;
        }
    }
}

/* Algortimo MedianOfThreePartition */
int MedianOfThreePartition(int *A, int p, int r)
{
    int s, x, i, j;
    int mid = (p + r) / 2;
    s = MedianOfThree(A, p, r, mid); //pivot = mediana tra i 3 indici: e ora troviamo dove si mette nell'array
    SwapValue(A, s, r); //vogliamo il pivot sull'utlimo elemento dell array
    x = A[r];
    i = p - 1; //indice che si trova prima dell'inizio dell array
    for (j = p; j <= r - 1; j++)
    {
        if (A[j] <= x) //compariamo il pivot con il a[j] element e sel maggiore non fai niente
        {
            //se minore incrementiamo i e lo cambio con j, il valore di i=a[j] j=a[i]
            i++;
            SwapValue(A, i, j); 
        }
    }
    //quando j finisce di ciclare l'array e ha fatto i dovuti swap, poi abbiamo la posizione di i che si trova sull'elemento
    //minore dell'array
    SwapValue(A, i + 1, r); //metto il pivot nella posizione i+1 dell'array, sx less dx larger
    return i + 1;
    //poi si ripete l'operazione su un sotto-array
}

/* Algoritmo MedianOfThreeQuickSort */
void MedianOfThreeQuickSort(int *A, int p, int r)
{
    int q;
    if (p < r)
    {
        q = MedianOfThreePartition(A, p, r);
        MedianOfThreeQuickSort(A, p, q - 1);
        MedianOfThreeQuickSort(A, q + 1, r);
    }
}

/* ESPERIMENTO SINGOLO */
float singoloEsperimento(int len, int maxInstance)
{
    float timeTot = 0;
    float timeStart, timeEnd, timeElapsed;
    int A[len];
    for (int i = 0; i < maxInstance; i++)
    {

        for (int j = 0; j < len; j++)    // Generatore Array di numeri Casuali:
        {                                // tramite il metodo rand()%N, genera un numero tra 0 e N-1
            A[j] = 1 + rand() % 1000000; // e metto il numero generato nell'array
        }

        // printf("Non ordinato\n");
        // for (int j = 0; j < len; j++)
        // {
        //     printf("%d\n", A[j]);
        // }

        timeStart = clock(); //inzio tempo
        MedianOfThreeQuickSort(A, 0, len - 1);
        timeEnd = clock(); //fine tempo

        // printf("ordinato\n");
        // for (int j = 0; j < len; j++)
        // {
        //     printf("%d\n", A[j]);
        // }

        timeElapsed = timeEnd - timeStart; //tempo trascorso
        timeTot = timeTot + timeElapsed;
    }
    return timeTot / maxInstance;
}

/* ESPERIMENTO Median of 3 QuickSort */
void esperimento(int minLen, int maxLen)
{
    int maxInstances = 50; // numero di istanze array per tentativo della lunghezza dell'array
    int STEP = 10;         // mi aumenta numero di elementi dell'array
    float time;

    for (int i = minLen; i < maxLen; i = i + STEP)
    {
        time = singoloEsperimento(i, maxInstances);
        //printf("Tempo per %d elementi per array: %f\n\n", i, time);
        printf("%.2f \n", time);
    }
}

/* Funzione Main */
int main(int argc, char *argv[])
{
    srand(15); // come parametro si mette un SEED che serve per il pseudo-RNG
    int minLength = 5;
    int maxLength = 1000;
    esperimento(minLength, maxLength); // esperimento() mi da n.Tempi per tentativo
                                       // dove n = (maxLength - minLength) / Step

    return 0;
}