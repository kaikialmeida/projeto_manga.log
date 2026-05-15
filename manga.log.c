#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdio_ext.h>
#include <jansson.h>
int id=0;
#define n 50
struct local{
    int id; 
    char titulo[n];
    char tipo[n];
    unsigned int capitulo;
    char status[n];

};

int main (){
    setlocale(LC_ALL, "portuguese");
    typedef  struct local local;
    local manga;
    int key = 0, control=0;
    char salvamento;
    while (key != 3){
         system ("clear");
         if (control == 1){
             printf ("OS DADOS INFORMADOS FORAM SALVOS");
             control -=1;
        }
    printf ("\n========================================\n");
    printf ("\tescolha uma opção: \n ");
    printf ("\n opção [1] - adicionar obra nova\n opção [2] - atualizar informação de obra ja existente\n opção [3] - sair");
    printf ("\n========================================\n");
    scanf (" %d", &key);
    __fpurge(stdin);
   

  
    switch (key){
        case 1:
        system ("clear");
            printf ("\n========================================\n");
            printf ("\ninforme o nome da obra: ");
            fgets (manga.titulo, n, stdin);
            printf ("==========================================\n");
             printf ("\ninforme o tipo da obra: ");
             fgets (manga.tipo, n, stdin);
             printf ("===========================================\n");
             printf ("\ninforme o ultimo capitulo lido: ");
             scanf (" %d", &manga.capitulo);
             printf ("\n=========================================\n");
             __fpurge(stdin);
             printf ("\ninforme o status da obra: ");
             fgets (manga.status, n, stdin);
             printf ("\n===========================================\n");
             printf ("salvar? s/n\t R:");
             scanf (" %c", &salvamento);
             if (salvamento == 's'){
                manga.id = id++;
                control= 1;   
            }
        break;

        case 2:
        break;
        case 3:
        break;
        }
    }
    return 0;
}