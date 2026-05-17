#ifndef LIBS_H
#define LIBS_H
#include "includes.h"
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
}//manga.log linha 28

void menu (int *key){
     printf ("\n========================================\n");
    printf ("\t\tMENU \n ");
    printf ("\n opção [1] - adicionar obra nova\n opção [2] - ver obras salvas\n opção [3] - atualizar informação de obra ja existente\n opção [4] - deletar obra\n opção [5] - sair\n");
     printf ("\n========================================\n");
    scanf (" %d", key);
    __fpurge(stdin);
   
} // manga.log linha 22
void lista_obras(json_t *lista_manga, dados *manga){
    system ("clear");
    size_t posicao_lista;
    json_t *posicao_atual;
    const char *t_titulo = NULL;
    const char *t_tipo = NULL;
    const char *t_status = NULL;
    json_array_foreach (lista_manga, posicao_lista, posicao_atual){
    json_unpack (posicao_atual, "{s:i, s:s, s:s, s:i, s:s}",
        "id", &manga->id, 
        "titulo", &t_titulo,
        "tipo", &t_tipo, 
        "ultimo capitulo lido", &manga->capitulo, 
        "status", &t_status
         );
        if (t_titulo){
            strcpy(manga->titulo, t_titulo);
            strcpy(manga->tipo, t_tipo);
            strcpy(manga->status, t_status);
         }
        printf ("ID: %-3d | NOME: %-50s | TIPO: %-30s | CAP: %-4d | STATUS: %s\n", manga->id, manga->titulo, manga->tipo, manga->capitulo, manga->status);
        printf ("===========================================================================================================================================\n");
    }
     printf ("pressione enter para voltar ao menu principal\n");   
     getchar ();
} //manga.log linha 77
void lista_pesquisa (json_t *lista_manga, dados *manga){
    system("clear");
    char titulo_pesquisa [n];
    size_t posicao_lista;
    json_t *posicao_atual;
    int encontrado = 0;  
    printf  ("informe o título da obra: ");
        fgets (titulo_pesquisa,sizeof(titulo_pesquisa), stdin);
            titulo_pesquisa [strcspn (titulo_pesquisa, "\n")] =  '\0';
    system ("clear");
    printf ("TÍTULO INFORMADO: %s\n", titulo_pesquisa);
    printf ("======================================================== RESULTADOS DA PESQUISA ===========================================================\n");
    json_array_foreach (lista_manga, posicao_lista, posicao_atual){
        const char *t_titulo = NULL;
        const char *t_tipo = NULL;
        const char *t_status = NULL;
        json_unpack (posicao_atual, "{s:i, s:s, s:s, s:i, s:s}",
           "id",      &manga->id, 
            "titulo",  &t_titulo,
            "tipo",    &t_tipo, 
            "ultimo capitulo lido", &manga->capitulo, 
            "status",   &t_status
        );
        if (t_titulo){
        strcpy(manga->titulo, t_titulo);
        strcpy(manga->tipo, t_tipo);
        strcpy(manga->status, t_status);
            
            if (strstr (manga-> titulo, titulo_pesquisa) != NULL ){
                printf ("ID: %-3d | NOME: %-50s | TIPO: %-30s | CAP: %-4d | STATUS: %s\n", manga->id,manga->titulo, manga->tipo, manga->capitulo, manga->status);
                printf ("===========================================================================================================================================\n");
                encontrado++;
            }
        }
    } 
    if (encontrado == 0){
        printf ("nenhuma obra encontrada com o título: %s\n", titulo_pesquisa);
    }
    else {
        printf ("foram encontrado %d obra(s) na pesquisa\n", encontrado);
    }
    printf ("\npressione enter para voltar ao menu anterior\n");
    getchar();
    __fpurge(stdin);
}

#endif