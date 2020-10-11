#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ============== FUNÇÕES AUXILIARES ============== */
int sumPosition(int vet[],int inicio, int fim){
    int value =0;
    for(int i=inicio; i<fim; i++){
        value+=vet[i];
    }
    //printf("%d ",value);
    return value;
}
/* ============== ============== ============== */

int BF(int *dist, int n, int k){
    int *s;
    s = malloc((n+1) *sizeof(int));
    s[0] = 0;
    int tam=0;
    int result = 99999;
    while (1){
        if(s[tam]<k){
            s[tam+1] = s[tam]+1;
            tam+=1;
        }else{
            s[tam-1] +=1;
            tam-=1;
        }

        if(tam==0)
            break;
        
        if(tam+1==k){
            int aux[tam+1];
            int j=0;
            for( j=0; j<tam; j++)
                aux[j] = sumPosition(dist,s[j],s[j+1]);
            aux[j] = sumPosition(dist,s[j],k+1);
            int maxValueVet = 0;
            for(int j=0; j<tam+1; j++)
                if(maxValueVet<aux[j]) maxValueVet = aux[j];
            if(maxValueVet<result)
                result = maxValueVet;       
        }
    }
    free(s);
    return result;
}

int AG(int *dist, int n, int k){
    int cont, aux, aux2, max;
    aux = 0; aux2 = 0; max = 0;
    for (cont = 0; cont <= n; cont++){
        aux += dist[cont];
    }
    aux /= (k + 2);
    for (cont = 0; cont <= n; cont++){
        aux2 += dist[cont];
        if (aux2 >= aux){
            if (aux2 > max)
                max = aux2;
            aux2 = 0;
        }
    }
    return max;
}

int PD(int *dist, int n, int k){
    int cont, cont2, cont3, larg = 0;
    int aux[k + 1];
    for (cont = 0; cont <= k; cont++){
        aux[cont] = dist[cont];
    }

    for (cont = 0; cont <=n; cont++)
        if (dist[cont] > larg)
            larg = dist[cont];
    larg *= 2;
    for (cont = k + 1; cont <= n; cont ++){
        int edge = dist[cont];
        int small = larg, smallId = -1;
        for (cont2 = 1; cont2 <= k; cont2++){
            if (aux[cont2] + aux[cont2 - 1] < small){
                small = aux[cont2] + aux[cont2 - 1];
                smallId = cont2 - 1;
            }
        }
        if (aux[cont2] + edge < small)
            aux[cont2] = aux[cont2] + edge;
        else{
            aux[smallId] += aux[smallId + 1];
            for (cont3 = smallId + 1; cont3 < k; cont3++)
                aux[cont3] = aux[cont3 + 1];
            aux[k] = edge;
        }
    }

    larg = 0;
    for (cont = 0; cont <= k; cont++)
        if (aux[cont] > larg)
            larg = aux[cont];
    return larg;
}

int main(){
    int t, cont;
    scanf("%d", &t);
    for (cont = 0; cont < t; cont++) {
        int n, k, cont2;
        scanf("%d %d", &n, &k);
        int dist[n + 1];
        for (cont2 = 0; cont2 <= n; cont2++){
            int aux;
            scanf("%d", &aux);
            dist[cont2] = aux;
        }
        printf("\n%d", AG(dist, n, k));
        //printf("\n%d", BF(dist, n, k));
        //printf("\n%d\n", PD(dist, n, k));
    }
}