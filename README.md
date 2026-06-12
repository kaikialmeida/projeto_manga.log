💻 PROJETO: MANGA.LOG

É uma aplicação de terminal desenvolvida em C para gerenciar e organizar o histórico de obras
como: manga, webtoons, manhuas, obras literarias, etc.

🛠️ Funcionalidades: 
O sistema conta com um menu interativo que oferece as seguintes opções:
Adicionar nova obra: Cadastrar um título gerando um ID único automaticamente.
Visualizar obras salvas:
Listar todas as obras cadastradas em formato de tabela organizada. Pesquisar obras por trechos do título.
Atualizar informações: Permite alterar individualmente o título, o capítulo atual, o tipo ou o status de leitura.
Deletar obra: Remove permanentemente um registro do banco de dados após confirmação.
Sair: Encerra o programa de forma segura.

🏗️ Estrutura do Código
O projeto está dividido de forma modular para facilitar a manutenção:

main.c: Contém o fluxo principal do programa, o laço do menu (while) e a estrutura de decisão (switch/case).
includes/libs.h: Onde estão definidas a estrutura dados (struct), as funções do sistema (CRUD) e a lógica de autoincremento de ID.
includes/includes.h: Centraliza todas as bibliotecas padrão do C e a biblioteca externa Jansson.
banco.json: Arquivo gerado automaticamente onde os dados são persistidos no formato: json
exemplo da estrutura struct:
  {
      "id": 1,
      "titulo": "One Piece",
      "tipo": "Manga",
      "ultimo capitulo lido": 1100,
      "status": "Lendo"
  }

⚒ PRÉ-REQUISITOS E COMO RODAR:
  Pré-requisitos:
    Para compilar e rodar este projeto, você precisará de:
         Um compilador C (como o gcc).
         Ambiente Linux/Unix (devido ao uso da biblioteca <stdio_ext.h> e do comando __fpurge).
         Biblioteca Jansson instalada no sistema.
COMO INSTALAR A BIBLIOTECA JANSSON (Ubuntu/Debian):
    aplique o seguinte comando no terminal: sudo apt-get install libjansson-dev
    (ao qual vai instalar os arquivos de desenvolvimento na sua maquina).
⚙️ COMPILAÇÃO E EXECUÇÃO: 
Abra o terminal na pasta raiz do projeto e execute os seguintes comandos:
 para Compilar o código:
    gcc main.c -o mangalog -ljansson
    (ou coloque manualmente la no task.json na parte de argumentos).
   (Nota: O parâmetro -ljansson é obrigatório para linkar a biblioteca JSON). 
 Executar a aplicação: 
   ./mangalog
  
