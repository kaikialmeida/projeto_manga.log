#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdio_ext.h>
#include <jansson.h>
#include <stdlib.h>
#define n 50
struct dados{
    unsigned int id; 
    char titulo[n];
    char tipo[n];
    unsigned int capitulo;
    char status[n];

};
 typedef  struct dados dados;

int verificacao_id(json_t *lista_manga){
    if (!lista_manga || json_array_size(lista_manga) == 0){
        return 1;
    }
      int maior_id = 0;
      size_t posicao_lista;
      json_t *posicao_atual;
      json_array_foreach (lista_manga, posicao_lista, posicao_atual){
            json_t *id_json = json_object_get (posicao_atual, "id");
            int id_atual = json_integer_value(id_json);
            if (id_atual > maior_id){
                maior_id = id_atual;
            }
      }
      return ++maior_id;
}

int main (){
    setlocale(LC_ALL, "portuguese");
    json_error_t erro;
    json_t *lista_manga = json_load_file ("banco.json", 0, &erro);
    if (!lista_manga){
        printf ("erro ao carregar o arquivo!\nmotivo: %s\nlinha: %d | coluna: %d\n", erro.text, erro.line, erro.column);
    }
    dados manga;
    int key = 0, control=0;
    char salvamento;

    while (key != 5){
         system ("clear");
         if (control == 1){
             printf ("OS DADOS INFORMADOS FORAM SALVOS");
             control -=1;
        }

    printf ("\n========================================\n");
    printf ("\t\tMENU \n ");
    printf ("\n opção [1] - adicionar obra nova\n opção [2] - ver obras salvas\n opção [3] - atualizar informação de obra ja existente\n opção [4] - deletar obra\n opção [5] - sair\n");
    printf ("\n========================================\n");
    scanf (" %d", &key);
    __fpurge(stdin);
   

  
    switch (key){
        case 1:
        system ("clear");
            manga.id = verificacao_id (lista_manga);
            printf ("\n====== ID DA OBRA: %d =======\n", manga.id);
            printf ("\ninforme o titulo da obra: ");
            fgets (manga.titulo, n, stdin);
            manga.titulo[strcspn(manga.titulo, "\n")] = '\0';
            printf ("==========================================\n");
             printf ("\ninforme o tipo da obra: ");
             fgets (manga.tipo, n, stdin);
            manga.tipo[strcspn(manga.tipo, "\n")] = '\0';
             printf ("===========================================\n");
             printf ("\ninforme o ultimo capitulo lido: ");
             scanf (" %d", &manga.capitulo);
             printf ("\n=========================================\n");
             __fpurge(stdin);
             printf ("\ninforme o status da obra: ");
             fgets (manga.status, n, stdin);
              manga.status[strcspn(manga.status, "\n")] = '\0';
             printf ("\n===========================================\n");
             printf ("salvar? s/n\t R:");
             scanf (" %c", &salvamento);
             if (salvamento == 's'){
                control= 1;   
                json_t *dados_novo_manga = json_pack ("{s:i, s:s, s:s, s:i, s:s}",
                            "id", manga.id, 
                            "nome", manga.titulo,
                            "tipo", manga.tipo, 
                            "ultimo capitulo", manga.capitulo,
                            "status", manga.status
                );
            json_array_append_new (lista_manga, dados_novo_manga);
            json_dump_file (lista_manga, "banco.json", JSON_INDENT(4));
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