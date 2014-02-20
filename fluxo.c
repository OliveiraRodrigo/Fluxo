#include <stdio.h>
#include <stdlib.h>

#define bool  char
#define False 0
#define True  1
#define x     0
#define y     1

struct temp{
    int lin;
    int col;
    int size;
};

int main(int argc, char** argv) {
    
    int a, c, i, j, k, p, t;
    //na proxima vez ja ponho o alfabeto inteiro!
    int fonte, dreno, numHosts, numLinks, *doneHosts;
    int size, atualFluxo, totalFluxo;
    int **links;
    struct temp* pilha;
    
    scanf("%d", &numHosts);
    
    if(numHosts < 1){
        printf("%d\n", 0);
        return (EXIT_SUCCESS);
    }
    
    scanf("%d %d %d", &fonte, &dreno, &numLinks);
    
    if(fonte < 1 || dreno > numHosts){
        return (EXIT_FAILURE);
    }
    fonte--;
    dreno--;
    
    links     = (int**) malloc(numHosts * sizeof(int*));
    doneHosts = (int*)    malloc(numHosts * sizeof(int));
    for(i = 0; i < numHosts; i++){
        links[i] = (int*) malloc(numHosts * sizeof(int));
        for(j = 0; j < numHosts; j++){
            links[i][j] = 0;
        }
        doneHosts[i] = False;
    }
    
    for(a = 0; a < numLinks; a++){
        scanf("%d %d %d", &i, &j, &size);
        if(i > numHosts || j > numHosts || i < 1 || j < 1){
            return (EXIT_FAILURE);
        }
        i--;
        j--;
        links[i][j] = size;
        links[j][i] = size;
    }
    
    pilha = (struct temp*) malloc(numLinks * sizeof(struct temp));
    
    i = fonte;
    j = 0;
    atualFluxo = 0;
    totalFluxo = 0;
    while(j < numHosts){
        
        p = 0;
        doneHosts[i] = True;
        
        if(j == dreno){
            //ja pode somar direto
            totalFluxo += links[i][j];
            links[i][j] = 0;
            j++;
        }
        else{
            
            if(links[i][j] != 0){
                pilha[p].lin = i;
                pilha[p].col = j;
                pilha[p].size = links[i][j];
                atualFluxo = links[i][j];
                links[i][j] = 0;
                c = j;
                doneHosts[c] = True;
                do{
                    k = 0;
                    while((doneHosts[k] || links[c][k] == 0) && (k < numHosts-1)){
                        k++;
                    }
                    if(doneHosts[k] || links[c][k] == 0){
                        for(t = p-1; t >= 0; t--){
                            links[pilha[t].lin][pilha[t].col] = pilha[t].size;
                            t--;
                        }
                        atualFluxo = 0;
                        break;
                    }
                    if(links[c][k] < atualFluxo){
                        atualFluxo = links[c][k];
                        for(t = p; t >= 0; t--){
                            links[pilha[t].lin][pilha[t].col] = pilha[t].size - atualFluxo;
                            t--;
                        }
                    }
                    p++;
                    pilha[p].lin = c;
                    pilha[p].col = k;
                    pilha[p].size = links[c][k];
                    links[c][k] -= atualFluxo;
                    
                    doneHosts[k] = True;
                    c = k;
                }
                while(k != dreno);
                
                totalFluxo += atualFluxo;
                
                p = 0;
                for(k = 0; k < numHosts; k++){
                    doneHosts[k] = False;
                }
            }
            else{
                j++;
            }
        }
    }
    
    printf("%d\n", totalFluxo);
    return (EXIT_SUCCESS);
}
