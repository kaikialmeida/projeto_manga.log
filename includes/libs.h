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
    if (scanf (" %d", key) != 1){
        __fpurge(stdin);
        *key = -1;
     }
     else {
            getchar();
        }
} // manga.log linha 22
void lista_obras(json_t *lista_manga, dados *manga){
    system ("clear");
    size_t posicao_lista;
    json_t *posicao_atual;
    const char *t_titulo = NULL;
    const char *t_tipo = NULL;
    const char *t_status = NULL;
      printf ("========================================================= LISTA DE OBRAS ===================================================================\n\n");
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
      printf ("======================================================= MENU DE PESQUISA ================================================================\n");
    printf  ("informe o título da obra: ");
        fgets (titulo_pesquisa,sizeof(titulo_pesquisa), stdin);
            titulo_pesquisa [strcspn (titulo_pesquisa, "\n")] =  '\0';
    system ("clear");
    printf ("TÍTULO INFORMADO: %s\n", titulo_pesquisa);
    printf ("======================================================== RESULTADOS DA PESQUISA ===========================================================\n\n");
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
void atualizacao_lista (json_t *lista_manga, dados *manga){
    int controle_alteracao =0;
     __fpurge (stdin);
    system ("clear");
    unsigned int id_atualizacao =0, encontrado= 0;
    size_t posicao_lista;
    json_t *posicao_atual;
    const char *t_titulo = NULL;
    const char *t_tipo = NULL;
    const char *t_status = NULL;
    printf ("\n================ painel de atualização de informação ==================\n");
    printf ("digite o id da obra: ");
    scanf (" %d", &id_atualizacao);
    json_array_foreach (lista_manga, posicao_lista, posicao_atual){
           json_unpack (posicao_atual, "{s:i, s:s, s:s, s:i, s:s}",
           "id",      &manga->id, 
            "titulo",  &t_titulo,
            "tipo",    &t_tipo, 
            "ultimo capitulo lido", &manga->capitulo, 
            "status",   &t_status
        );
        if (manga->id){
                if ((manga-> id  == id_atualizacao) ){
                    encontrado++;
                    system ("clear");
                    int key_id=1;
                        while (key_id != 5){
                            system ("clear");
                            printf ("ID: %-3d | TÍTULO: %-50s | TIPO: %-30s | CAP: %-4d | STATUS: %s\n", manga->id, t_titulo, t_tipo, manga-> capitulo, t_status);
                            printf ("===========================================================================================================================================\n");
                            if (controle_alteracao == 1){
                                printf ("ALTERAÇÃO SALVA!");
                                controle_alteracao = 0;
                            }
                            printf ("\n========================================\n");
                            printf ("opção [1] - alterar titulo\nopção [2] - alterar capitulo\nopção [3] - alterar tipo\nopção [4] - alterar status\nopção [5] - voltar ao menu principal\n");
                            printf ("========================================\nR: ");
                            if (scanf (" %d", &key_id) != 1){
                               __fpurge(stdin);
                                key_id = -1;
                            }

                            switch (key_id){
                                case 1:
                                  __fpurge (stdin);
                                  system ("clear");
                                    printf ("digite o novo titulo: ");
                                    fgets (manga->titulo, n, stdin );
                                         manga->titulo[strcspn(manga->titulo, "\n")] = '\0';
                                    json_object_set_new (posicao_atual, "titulo", json_string (manga->titulo));
                                    json_dump_file (lista_manga, "banco.json", JSON_INDENT(4));
                                    __fpurge (stdin);
                                    t_titulo = manga->titulo;
                                    controle_alteracao++;
                                break;
                                case 2:
                                  system ("clear");
                                  __fpurge (stdin);
                                  printf ("ATENÇÃO! A DIGITAÇÃO DE LETRA OU CARACTERES ESPECIAIS RESULTARA EM NULO.\n");
                                   printf ("digite o novo capitulo: ");
                                    scanf ("%d", &manga->capitulo);
                                     __fpurge (stdin);
                                    json_object_set_new (posicao_atual, "ultimo capitulo lido", json_integer (manga->capitulo));
                                    json_dump_file (lista_manga, "banco.json", JSON_INDENT(4));
                                    controle_alteracao++;
                                break;
                                case 3:
                                  system ("clear");
                                __fpurge (stdin);
                                 printf ("digite o novo tipo: ");
                                    fgets (manga->tipo, n, stdin );
                                         manga->tipo[strcspn(manga->tipo, "\n")] = '\0';
                                    json_object_set_new (posicao_atual, "tipo", json_string (manga->tipo));
                                    json_dump_file (lista_manga, "banco.json", JSON_INDENT(4));
                                    __fpurge (stdin);
                                    controle_alteracao++;
                                    t_tipo = manga->tipo;
                                break;
                                case 4:
                                  system ("clear");
                                  __fpurge (stdin);
                                  printf ("digite o novo status: ");
                                    fgets (manga->status, n, stdin );
                                         manga->status[strcspn(manga->status, "\n")] = '\0';
                                    json_object_set_new (posicao_atual, "status", json_string (manga->status));
                                    json_dump_file (lista_manga, "banco.json", JSON_INDENT(4));
                                    __fpurge (stdin);
                                    controle_alteracao++;
                                    t_status = manga->status;
                                break;
                                case 5:
                                  __fpurge (stdin);
                                    printf ("OS DADOS ALTERADOS FORAM SALVOS!");
                                break;
                                default:
                                  __fpurge (stdin);
                                printf ("OPÇÃO SELECIONADA INVALIDA!\npressione enter para tentar novamente\n");
                                   getchar();
                                break;
                            }

                        }
                        break;
                }
        }
    }
    if (encontrado == 0){
            system ("clear");
            printf ("NENHUMA OBRA COM O ID: %d FOI ENCONTRADO! :(\n", id_atualizacao);
            getchar();

        }
}
void exclusao_obra (json_t *lista_manga, dados *manga){
    int controle_exclusao =0, encontrado_exclusao =0;
    char certeza;
    __fpurge (stdin);
    system ("clear");
    unsigned int id_exclusao= 0;
    size_t posicao_lista;
    json_t *posicao_atual;
    const char *t_titulo = NULL;
    const char *t_tipo = NULL;
    const char *t_status = NULL;
    printf ("\n================ painel de exclusão de obra ==================\n");
    printf ("informe o id da obra que deseja deletar: ");
    scanf (" %d", &id_exclusao);
    __fpurge(stdin);
    json_array_foreach (lista_manga, posicao_lista, posicao_atual){
           json_unpack (posicao_atual, "{s:i, s:s, s:s, s:i, s:s}",
           "id",      &manga->id, 
            "titulo",  &t_titulo,
            "tipo",    &t_tipo, 
            "ultimo capitulo lido", &manga->capitulo, 
            "status",   &t_status
        );

    
    if (manga->id){
        if ((manga-> id  == id_exclusao) ){
            encontrado_exclusao = 1;
            system ("clear");
            printf ("ID: %-3d | TÍTULO: %-50s | TIPO: %-30s | CAP: %-4d | STATUS: %s\n", manga->id, t_titulo, t_tipo, manga-> capitulo, t_status);
            printf ("===========================================================================================================================================\n");
              printf  ("tem certeza que voce deseja excluir essa obra do seu banco?\n S/n : ");
              scanf ( " %c", &certeza);
              __fpurge(stdin);
                if (certeza == 's' || certeza == 'S'){
                    system ("clear");
                    json_array_remove(lista_manga, posicao_lista);
                    json_dump_file (lista_manga, "banco.json", JSON_INDENT(4));
                    __fpurge (stdin);
                    printf ("EXCLUIDA COM SUCESSO!\npressione enter para voltar ao menu principal\n");
                    getchar();
                break;
                }
                else{
                    system("clear");
                    printf("EXCLUSÃO CANCELADA!\npressione enter para voltar ao menu principal");
                    getchar();
                    break;
                } 
                
        }
    }
    }
        if (encontrado_exclusao == 0){
            system ("clear");
            printf ("NENHUMA OBRA COM O ID: %d FOI ENCONTRADA! :(\n", id_exclusao);
            getchar();

      }
}

#endif