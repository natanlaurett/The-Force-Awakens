#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
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
        if(s[tam]<n){
            s[tam+1] = s[tam]+1;
            tam+=1;
        }else{
            s[tam-1] +=1;
            tam-=1;
        }
        if(tam==0)
            break;

        if(tam==k){
            int aux[tam+1];
            int j=0;
            for( j=0; j<tam; j++){
                aux[j] = sumPosition(dist,s[j],s[j+1]);
            }
            aux[j] = sumPosition(dist,s[j],n+1);
            int maxValueVet = 0;
            for(int r=0; r<j+1; r++){
                if(maxValueVet<aux[r]) maxValueVet = aux[r];
            }
            if(maxValueVet<result){
                result = maxValueVet;
            }      
        }
    }
    free(s);
    return result;
}

int AG(int *dist, int n, int k){
    int cont, aux, aux2, contdiv, max;
    aux = 0; aux2 = 0; contdiv = 0; max = 0;
    for (cont = 0; cont <= n; cont++)
        aux += dist[cont];

    aux /= (k + 1);
    for (cont = 0; cont <= n; cont++){
        if (aux2 + dist[cont] > aux && contdiv < k){
            if (aux2 + dist[cont] - aux <= aux - aux2){
                aux2 += dist[cont];
                 if (aux2 > max)
                    max = aux2;
                aux2 = 0;
                contdiv++;
            }else{
                if (aux2 > max)
                    max = aux2;
                aux2 = dist[cont];
                contdiv++;
            }   
        }else
            aux2 += dist[cont];
    }
    if (aux2 > max)
        max = aux2;
        
    return max;
}

int PD(int *dist, int n, int k){
    int aux[n + 1][k + 1];
    int max[n + 1][k + 1];
    int cont1, cont2, cont3, cont4;
    aux[0][0] = dist[0];
    max[0][0] = dist[0];
    for (cont1 = 1; cont1 <=n; cont1++){
        aux[cont1][0] = aux[cont1 - 1][0] + dist[cont1]; 
        max[cont1][0] = aux[cont1][0];
    }

    for (cont1 = 1; cont1 <= n; cont1++){
        for (cont2 = 1; cont2 <= k; cont2++){
            if (cont2 > cont1){
                aux[cont1][cont2] = aux[cont1][cont2 - 1];
                max[cont1][cont2] = max[cont1][cont2 - 1];
                continue;
            }
            int maxesc = INT_MAX;
            int auxesc = INT_MAX;
            int auxIter, auxIter2, maxIter, distMax;
            for (cont3 = cont2 - 1; cont3 < cont1; cont3++){
                maxIter = max[cont3][cont2 - 1];
                auxIter = aux[cont3][cont2 - 1];
                distMax = aux[cont3][cont2 - 1];
                for (cont4 = cont3 + 1; cont4 <= cont1; cont4++)
                    distMax += dist[cont4];
                for (cont4 = cont3 + 1; cont4 <= cont1; cont4++){
                    auxIter2 = distMax - auxIter;
                    if (auxIter2 > auxIter){
                        if (auxIter2 > maxIter){
                            if (auxIter2 < maxesc){
                                maxesc = auxIter2;
                                auxesc = auxIter2;
                            }
                        }else{
                           if (maxIter < maxesc){
                                maxesc = maxIter;
                                auxesc = auxIter2;
                            } 
                        }
                        
                    }else{
                        if (auxIter > maxIter){
                            if (auxIter < maxesc){
                                maxesc = auxIter;
                                auxesc = auxIter2;
                            }
                        }else{
                            if (maxIter < maxesc){
                                maxesc = maxIter;
                                auxesc = auxIter2;
                            }
                        }
                        
                    }
                    auxIter += dist[cont4];
                }  
            }

            aux[cont1][cont2] = auxesc;
            max[cont1][cont2] = maxesc;
        }
    }
    return max[n][k];
}

int main(int argc, char* argv[]){
    int t;
    scanf("%d", &t);
    for (int cont = 0; cont < t; cont++) {
        int n, k;
        scanf("%d %d", &n, &k);
        if(n==0) break;
        int* dist = malloc((n+1) *sizeof(int));

        for(int cont2=0; cont2<=n; cont2++){
            int aux;
            scanf("%d", &aux);
            dist[cont2] = aux;
        }
        if(strcmp(argv[1],"PD")==0)
            printf("%d\n", PD(dist, n, k));
        else if(strcmp(argv[1],"AG")==0)
            printf("%d\n", AG(dist, n, k));
        else if(strcmp(argv[1],"BF")==0)
            printf("%d\n", BF(dist, n, k));
        free(dist);
    }
    return 0;
}