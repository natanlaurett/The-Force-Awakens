#include <stdio.h>
#include <stdlib.h>

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
    for (cont = 0; cont <= n; cont++){
        aux += dist[cont];
    }
    aux /= (k + 1);
    for (cont = 0; cont <= n; cont++){
        printf("%d %d\n", aux2, dist[cont]);
        if (aux2 + dist[cont] > aux && contdiv < k){
            
            if (aux2 > max){
                max = aux2;
            }
            aux2 = dist[cont];
            contdiv++;
                   
        }else
            aux2 += dist[cont];
    }
    if (aux2 > max)
        max = aux2;
        
    return max;
}

int PD_rec(int *dist, int n, int k, int aux, int max, int start){
    if (start > n)
        return max;
    int res1, res2, arg;

    aux += dist[start];
    if (aux > max)
        max = aux;
    res1 = PD_rec(dist, n, k, aux, max, start + 1);

    if (k > 0){
        aux = 0;
        res2 = PD_rec(dist, n, k - 1, aux, max, start + 1);
        if (res2 < res1)
            return res2;
    }
    return res1;
}

int PD(int *dist, int n, int k){
    PD_rec(dist, n, k, 0, 0, 0);
}

int main(){
    FILE* arqTeste;
    arqTeste = fopen("testes.txt","r");
    int t, cont;
    //fscanf(arqTeste,"%d",&t);
    scanf("%d", &t);
    for (cont = 0; cont < t; cont++) {
        int n, k, cont2;
        //fscanf(arqTeste,"%d %d",&n, &k);
        scanf("%d %d", &n, &k);
        int dist[n + 1];
        for (cont2 = n; cont2 >= 0; cont2--){
            //fscanf(arqTeste,"%d",&aux);
            int aux;
            scanf("%d", &aux);
            dist[cont2] = aux;
        }
        /*for(cont2=0; cont2<=n; cont2++){
            dist[cont2] = cont2+1;
        }*/

        //k = 6;
        printf("%d\t", PD(dist, n, k));
        //printf("%d\t", AG(dist, n, k));
        printf("%d\n", BF(dist, n, k));
    }
    return 0;
}