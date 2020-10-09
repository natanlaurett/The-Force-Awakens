#include <stdio.h>


int AG(int *dist, int n, int k){
    int cont, cont2, cont3, larg = 0;
    int aux[k + 1];
    for (cont = 0; cont <= k; cont++){
        aux[cont] = dist[cont];
    }

    for (cont = 0; cont <=n; cont++)
        if (dist[cont] > larg)
            larg = dist[cont] + 1;
    
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

        printf("\n%d\n", AG(dist, n, k));
    }
}