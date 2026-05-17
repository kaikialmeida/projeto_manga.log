#include "includes/libs.h"
#include "includes/includes.h"
    
int main (){
    setlocale(LC_ALL, "portuguese");
    json_t *lista_manga = json_load_file ("banco.json", 0, NULL);
    
    if (!lista_manga){
        system ("clear");
        printf  ("- BANCO DE DADOS NÃO ENCONTRADO. \n- criando um novo banco de dados para o sistema!\n");
        lista_manga =json_array();
        json_dump_file(lista_manga, "banco.json",   JSON_INDENT (4));
        printf ("- NOVO BANCO DE DADOS CRIADO COM SUCESSO!\n\n pressione enter para continuar");

        getchar();

    }
    dados manga; 
    int key = 0, control=0;

    char salvamento;

    while (key != 5){
         system ("clear");

         if (control == 1){
            printf ("OS DADOS INFORMADOS FORAM SALVOS!");
            control -=1;
        }

    menu (&key); //libs.h linha 31

  
       switch (key){
          case 1:
            system ("clear");
            manga.id = verificacao_id (lista_manga); //libs.h linha 14
            printf ("\n====== ID DA OBRA: %d =======\n", manga.id);
            printf ("\ninforme o titulo da obra: ");
                fgets (manga.titulo, n, stdin);
                      manga.titulo[strcspn(manga.titulo, "\n")] = '\0';
            printf ("==========================================\n");
             printf ("\ninforme o tipo da obra: ");
                fgets (manga.tipo, n, stdin);
                      manga.tipo[strcspn(manga.tipo, "\n")] = '\0';
             printf ("===========================================\n");
            printf ("qualquer letra informada resultara nulo no banco! ");
            printf ("\ninforme o ultimo capitulo lido: ");
                 scanf (" %d", &manga.capitulo);
             printf ("\n=========================================\n");
                    __fpurge(stdin);
            printf ("\ninforme o status da obra(lendo)(hiato)(finalizada): ");
                fgets (manga.status, n, stdin);
                      manga.status[strcspn(manga.status, "\n")] = '\0';
             printf ("\n===========================================\n");
            printf ("salvar? S/n\t R:");
                scanf (" %c", &salvamento);
                   __fpurge(stdin);

            if (salvamento == 's' || salvamento == 'S'){
                control= 1;   
                json_t *dados_novo_manga = json_pack ("{s:i, s:s, s:s, s:i, s:s}",
                            "id", manga.id, 
                            "titulo", manga.titulo,
                            "tipo", manga.tipo, 
                            "ultimo capitulo lido", manga.capitulo,
                            "status", manga.status
                );
                json_array_append_new (lista_manga, dados_novo_manga);
                json_dump_file (lista_manga, "banco.json", JSON_INDENT(4));
            }
           break;

          case 2:
            system ("clear");
            __fpurge(stdin);
            printf ("===========================================\n");
            printf ("\t\tLISTA DE OBRAS\n");
            printf ("===========================================\n");
                if (!lista_manga || json_array_size (lista_manga)== 0){
                    printf ("infelizmente no momento não há obras cadastradas no seu banco de dados! :(\n");
                    printf ("pressione enter para continuar\n");
                       getchar();
                    break;
                }
            else{
                __fpurge(stdin);
                key = 0;
                while (key!= 3){
                    system ("clear");
                    printf ("opcão 1 - listar todas as obras\nopcão 2 - pesquisar por titulo\nopção 3 - para voltar ao menu principal\nR:");
                    scanf (" %d", &key);
                    __fpurge (stdin);
                    switch (key){
                        case 1: 
                            lista_obras (lista_manga, &manga); //libs.h linha 40
                            break;
                        case 2:
                            lista_pesquisa (lista_manga, &manga);
                            break;
                        case  3:
                        break;
                        default:
                        system ("clear");
                        printf ("OPÇÃO SELECIONADA INVALIDA!\ntente novamente");
                        break;
                    }
                }
            }
            break;
          case 3:
            __fpurge (stdin); 
            break;
        
          default: 
            printf ("OPÇÃO SELECIONADA INVALIDA! tente novamente");

          break;
        }
    }
    return 0;
}