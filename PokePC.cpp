/**
 * Olá! Espero que esteja tudo bem com você!
 * Fico feliz que tenha acessado esse código!
 *
 * ## Sobre o Programa:
 * Este programa foi desenvolvido na linguagem C++ como uma atividade avaliativa da disciplina
 * de Introdução aos Algoritmos no meu 1º período.
 *
 * ## Temática:
 * A inspiração para esse programa são os PCs que existem nos jogos de Pokémon, onde são
 * guardados os Pokémon que o jogador não pode levar consigo, mas não quer soltar. Seria como
 * um depósito que o jogador consegue acessar em qualquer lugar, como um armazenamento em nuvem.
 *
 * ## Utilização do Programa:
 * Inicialmente, é necessário possuir um arquivo CSV ou binário em um diretório no mesmo
 * local que o arquivo de execução desse programa. O arquivo deve possuir 5 tipos de dados separados
 * por virgulas e um limite máximo de 32.765 linhas (capacidade do tipo ShortInt).
 *
 * ## Formato do Arquivo:
 * O arquivo deve ter as colunas separadas por vírgulas ','.
 *
 * ## Informações Adicionais:
 * Código feito por: Samuel Moreira Abreu
 * Cursando Graduação em Sistemas de Informação pela Universidade Federal de Lavras
 * Data da criação do programa: 22/07/2023
 * Nota na avaliação desse código: 90%
 * Feedback recebido: Programa possui problemas na adição de novos dados e na leitura de
 * arquivos binários. (problemas resolvidos após o feedback para publicação)
 *
 * Conceitos de algoritmos utilizados:
 * - Variáveis e tipos de dados
 * - Entradas e saídas em terminal e arquivos externos
 * - Alocação dinâmica de memória
 * - Conceitos de ordenação de dados
 * - Conceitos de busca sequencial e binária
 */

// Bibliotecas utilizadas
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

// Função para saber em qual sistema operacional está rodando o programa
#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

using namespace std;

// Definição da struct Pokemon com os dados a serem manipulados
struct Pokemon{
     short identidade;
     char nomePokemon[15];
     char sexoPokemon;
     char pokeballPokemon[15];
     char naturePokemon[10];
};

// declaração de funções para uso anterior a sua aplicação
void redimensionarListaPokemon(Pokemon *&listaPokemons, int quantidade, int &capacidade, int novoTamanho);
void limparListaPokemon(int &quantidade, int &capacidade);


void lerCSV(Pokemon *&listaPokemons, int &quantidade, int &capacidade){
     string nomeArquivo;
     cout << "##################################" << endl;
     cout << "Digite o nome do arquivo CSV: " << endl;
     cout << "##################################" << endl;
     cin.ignore();
     getline(cin, nomeArquivo);
     nomeArquivo += ".csv";
     ifstream arquivo(nomeArquivo);
     if (!arquivo.is_open()){
          cout << "###############################" << endl;
          cout << "    Erro ao abrir o arquivo    " << endl;
          return;
     }


     // Limpar a lista de Pokemons antes de fazer a leitura    
     limparListaPokemon(quantidade, capacidade);

     // leitura do arquivo csv
     string linha;
     while (getline(arquivo, linha)){
          if (quantidade == capacidade - 1){
               redimensionarListaPokemon(listaPokemons, quantidade, capacidade, capacidade + 2);
          }

          stringstream ss(linha);
          string item;
          // Leitura dos dados do arquivo CSV
          getline(ss, item, ',');
          listaPokemons[quantidade].identidade = stoi(item);

          getline(ss, item, ',');
          strcpy(listaPokemons[quantidade].nomePokemon, item.c_str());

          getline(ss, item, ',');
          listaPokemons[quantidade].sexoPokemon = item[0];

          getline(ss, item, ',');
          strcpy(listaPokemons[quantidade].pokeballPokemon, item.c_str());

          getline(ss, item, ',');
          strcpy(listaPokemons[quantidade].naturePokemon, item.c_str());

          quantidade++;
     }

     cout << "###############################" << endl;
     cout << "Dados lidos com sucesso!" << endl;
}



// Função para ler os dados de um arquivo Binario e preencher a lista de
// Pokemons
void lerBinario(Pokemon *&listaPokemons, int &quantidade, int &capacidade){
     string nomeArquivo;
     cout << "##################################" << endl;
     cout << "Digite o nome do arquivo binario: " << endl;
     cout << "##################################" << endl;
     cin.ignore();
     getline(cin, nomeArquivo);

     nomeArquivo += ".bin";
     ifstream arquivo(nomeArquivo, ios::binary);
     if (!arquivo.is_open()){
          cout << "################################" << endl;
          cout << "Erro ao abrir o arquivo binario " << endl;
          return;
     }

     // Limpar a lista de Pokemons antes de fazer a leitura
     limparListaPokemon(quantidade, capacidade);
     // Ler a quantidade de Pokemons do arquivo
     arquivo.read(reinterpret_cast<char *>(&quantidade), sizeof(quantidade));
     // Alocar memória para a lista de Pokemons
     listaPokemons = new Pokemon[quantidade - 1];
     capacidade = quantidade + 1;

     // Ler os dados dos Pokemons do arquivo
     arquivo.read(reinterpret_cast<char *>(listaPokemons), quantidade * sizeof(Pokemon));

     arquivo.close();
     cout << "###########################################" << endl;
     cout << "Dados lidos do arquivo binario com sucesso!" << endl;
}

// Função para imprimir os dados de um Pokemon
void imprimirPokemon(const Pokemon &pokemon){
     cout << "###############################" << endl;
     cout << "Identidade: " << pokemon.identidade << endl;
     cout << "Nome do Pokemon: " << pokemon.nomePokemon << endl;
     cout << "Sexo do Pokemon: " << pokemon.sexoPokemon << endl;
     cout << "Pokeball do Pokemon: " << pokemon.pokeballPokemon << endl;
     cout << "Nature do Pokemon: " << pokemon.naturePokemon << endl;
}

// Função para intercalar dois subarrays no MergeSort iterativo
void intercalar(Pokemon arr[], int inicio, int meio, int fim, bool ordenarPorIdentidade){
     int n1 = meio - inicio + 1;
     int n2 = fim - meio;

     Pokemon *esquerda = new Pokemon[n1];
     Pokemon *direita = new Pokemon[n2];

     for (int i = 0; i < n1; i++){
          esquerda[i] = arr[inicio + i];
     }
     for (int j = 0; j < n2; j++){
          direita[j] = arr[meio + 1 + j];
     }

     int i = 0, j = 0, k = inicio;
     while (i < n1 && j < n2){
          if ((ordenarPorIdentidade && esquerda[i].identidade <= direita[j].identidade) ||
               (!ordenarPorIdentidade && strcmp(esquerda[i].nomePokemon, direita[j].nomePokemon) <= 0)){
               arr[k] = esquerda[i];
               i++;
          }
          else{
               arr[k] = direita[j];
               j++;
          }
          k++;
     }

     while (i < n1){
          arr[k] = esquerda[i];
          i++;
          k++;
     }
     while (j < n2){
          arr[k] = direita[j];
          j++;
          k++;
     }

     delete[] esquerda;
     delete[] direita;
}

// Função de ordenação MergeSort iterativo
void mergeSort(Pokemon arr[], int n, bool ordenarPorIdentidade)
{
     for (int tamanho_atual = 1; tamanho_atual <= n - 1; tamanho_atual = 2 * tamanho_atual){
          for (int inicio = 0; inicio < n - 1; inicio += 2 * tamanho_atual){
               int meio = min(inicio + tamanho_atual - 1, n - 1);
               int fim = min(inicio + 2 * tamanho_atual - 1, n - 1);
               intercalar(arr, inicio, meio, fim, ordenarPorIdentidade);
          }
     }
}

// Função para adicionar um novo Pokemon na lista
void adicionarPokemon(Pokemon listaPokemons[], int &quantidade, int &capacidade){
     // Verifica se é preciso alocar mais memória para a adição
     if (quantidade == capacidade - 1){
          redimensionarListaPokemon(listaPokemons, quantidade, capacidade, capacidade + 2);
     }

     string nome, pokeball, nature;
     char sexo;

     // Adiciona o ID do novo pokemon
     int novaIdentidade = listaPokemons[quantidade - 1].identidade + 1;
     listaPokemons[quantidade].identidade = novaIdentidade;

     // Restante dos dados informado pelo usuário
     cout << "###############################" << endl;
     cout << "    Digite o nome do Pokemon:  " << endl;
     cout << "###############################" << endl;
     cin.ignore();
     getline(cin, nome);
     strncpy(listaPokemons[quantidade].nomePokemon, nome.c_str(), sizeof(listaPokemons[quantidade].nomePokemon));
     cout << "###############################" << endl;
     cout << "    Digite o sexo do Pokemon:  " << endl;
     cout << "###############################" << endl;
     cin >> sexo;
     listaPokemons[quantidade].sexoPokemon = sexo;
     cout << "###############################" << endl;
     cout << " Digite a Pokeball do Pokemon: " << endl;
     cout << "###############################" << endl;
     cin.ignore();
     getline(cin, pokeball);
     strncpy(listaPokemons[quantidade].pokeballPokemon, pokeball.c_str(), sizeof(listaPokemons[quantidade].pokeballPokemon));
     cout << "###############################" << endl;
     cout << "   Digite a nature do Pokemon: " << endl;
     cout << "###############################" << endl;
     cin >> nature;
     strncpy(listaPokemons[quantidade].naturePokemon, nature.c_str(), sizeof(listaPokemons[quantidade].naturePokemon));

     // Incrementa a quantidade de pokemons após adicionar o novo pokemon
     quantidade += 1;
}

// Função para excluir um Pokemon da lista
void excluirPokemon(Pokemon listaPokemons[], int &quantidade){
     int identidadeExcluir;
     cout << "###################################################" << endl;
     cout << "Digite a identidade do Pokemon que deseja excluir: " << endl;
     cout << "###################################################" << endl;
     cin >> identidadeExcluir;

     int indiceExcluir = -1;
     bool sentinela = false;
     for (int i = 0; !sentinela && i < quantidade; i++){
          if (listaPokemons[i].identidade == identidadeExcluir){
               indiceExcluir = i;
               sentinela = true;
          }
     }
     // Passa todos os dados após o pokemon a ser excluido, uma posição de
     // memória para trás e subtrai 1 da quantidade.
     if (indiceExcluir != -1){
          for (int i = indiceExcluir; i < quantidade - 1; i++){
               listaPokemons[i] = listaPokemons[i + 1];
          }
          quantidade--;
     }else{
          cout << "##################################################" << endl;
          cout << "Pokemon com a identidade fornecida nao encontrado." << endl;
     }
}

// Função para editar os dados de um Pokemon
void editarPokemon(Pokemon &pokemon)
{
     cout << "###############################" << endl;
     cout << "O que deseja editar:" << endl;
     cout << "1 - Nome do Pokemon" << endl;
     cout << "2 - Sexo do Pokemon" << endl;
     cout << "3 - Pokeball do Pokemon" << endl;
     cout << "4 - Nature do Pokemon" << endl;
     cout << "###############################" << endl;

     int opcaoEditar;
     cin >> opcaoEditar;

     switch (opcaoEditar){
          case 1:
               cout << "###############################" << endl;
               cout << "Digite o novo nome do Pokemon: " << endl;
               cout << "###############################" << endl;
               cin.ignore(); // Limpar o buffer antes de ler a string
               cin.getline(pokemon.nomePokemon, sizeof(pokemon.nomePokemon));
               break;
          case 2:
               cout << "###############################" << endl;
               cout << "Digite o novo sexo do Pokemon: " << endl;
               cout << "###############################" << endl;
               cin >> pokemon.sexoPokemon;
               break;
          case 3:
               cout << "###################################" << endl;
               cout << "Digite a nova Pokeball do Pokemon: " << endl;
               cout << "###################################" << endl;
               cin.ignore(); // Limpar o buffer antes de ler a string
               cin.getline(pokemon.pokeballPokemon, sizeof(pokemon.pokeballPokemon));
               break;
          case 4:
               cout << "#################################" << endl;
               cout << "Digite a nova nature do Pokemon: " << endl;
               cout << "#################################" << endl;
               cin >> pokemon.naturePokemon;
               break;
          default:
               cout << "###############################" << endl;
               cout << "         Opcao invalida        " << endl;
     }
}

// Função para buscar um Pokemon por identidade
void buscarPorIdentidade(const Pokemon listaPokemons[], int quantidade){
     int identidadeBusca;
     cout << "##################################################" << endl;
     cout << "Digite a identidade do Pokemon que deseja buscar: " << endl;
     cout << "##################################################" << endl;
     cin >> identidadeBusca;
     bool encontrado = false;
     for (int i = 0; !encontrado && i < quantidade; i++){
          if (listaPokemons[i].identidade == identidadeBusca){
               imprimirPokemon(listaPokemons[i]);
               encontrado = true;
          }
     }
     if (!encontrado){
          cout << "##################################################" << endl;
          cout << "Pokemon com a identidade fornecida nao encontrado " << endl;
     }
}

// Função para buscar um Pokemon por nome
void buscarPorNome(const Pokemon listaPokemons[], int quantidade){
     string nomeBusca;
     cout << "############################################" << endl;
     cout << "Digite o nome do Pokemon que deseja buscar: " << endl;
     cout << "############################################" << endl;
     cin.ignore();
     getline(cin, nomeBusca);

     bool encontrado = false;
     for (int i = 0; i < quantidade; i++){
          if (strcmp(listaPokemons[i].nomePokemon, nomeBusca.c_str()) == 0){
               imprimirPokemon(listaPokemons[i]);
               encontrado = true;
          }
     }

     if (!encontrado){
          cout << "############################################" << endl;
          cout << "Pokemon com o nome fornecido nao encontrado " << endl;
     }
}

// Função para buscar um Pokemon por sexo
void filtrarPorSexo(const Pokemon listaPokemons[], int quantidade){
     char sexoBusca;
     cout << "#######################################" << endl;
     cout << "Digite o sexo do Pokemon para filtrar: " << endl;
     cout << "#######################################" << endl;
     cin >> sexoBusca;

     bool encontrado = false;
     for (int i = 0; i < quantidade; i++){
          if (listaPokemons[i].sexoPokemon == sexoBusca){
               imprimirPokemon(listaPokemons[i]);
               encontrado = true;
          }
     }
     if (!encontrado){
          cout << "############################################" << endl;
          cout << "Pokemon com o sexo fornecido nao encontrado " << endl;
     }
}

// Função para buscar um Pokemon por pokeball
void filtrarPorPokeball(const Pokemon listaPokemons[], int quantidade){

  string pokeballBusca;
  cout << "###########################################" << endl;
  cout << "Digite a Pokeball do Pokemon para filtrar: " << endl;
  cout << "###########################################" << endl;
  cin.ignore();
  getline(cin, pokeballBusca);

  bool encontrado = false;
  for (int i = 0; i < quantidade; i++){
    if (strcmp(listaPokemons[i].pokeballPokemon, pokeballBusca.c_str()) == 0){
      imprimirPokemon(listaPokemons[i]);
      encontrado = true;
    }
  }

  if (!encontrado){
    cout << "################################################" << endl;
    cout << "Pokemon com a Pokeball fornecida nao encontrado " << endl;
  }
}

// Função para buscar um Pokemon por nature
void filtrarPorNature(const Pokemon listaPokemons[], int quantidade){

     string natureBusca;
     cout << "#########################################" << endl;
     cout << "Digite a nature do Pokemon para filtrar: " << endl;
     cout << "#########################################" << endl;
     cin.ignore();
     getline(cin, natureBusca);

     bool encontrado = false;
     for (int i = 0; i < quantidade; i++){
          if (strcmp(listaPokemons[i].naturePokemon, natureBusca.c_str()) == 0){
               imprimirPokemon(listaPokemons[i]);
               encontrado = true;
          }
     }

     if (!encontrado){
          cout << "##############################################" << endl;
          cout << "Pokemon com a nature fornecida nao encontrado " << endl;
     }
}

// Função para salvar os dados em um arquivo CSV
void salvarCSV(Pokemon *&listaPokemons, int quantidade, const string &nomeArquivo){
     ofstream arquivo(nomeArquivo);
     if (!arquivo.is_open()){
          cout << "###############################" << endl;
          cout << "  Erro ao criar o arquivo CSV  " << endl;
          return;
     }

     for (int i = 0; i < quantidade; i++){
          arquivo << listaPokemons[i].identidade << ",";
          arquivo << listaPokemons[i].nomePokemon << ",";
          arquivo << listaPokemons[i].sexoPokemon << ",";
          arquivo << listaPokemons[i].pokeballPokemon << ",";
          arquivo << listaPokemons[i].naturePokemon << endl;
     }

     arquivo.close();
     cout << "###############################" << endl;
     cout << " Arquivo CSV salvo com sucesso!" << endl;
}

// Função para salvar os dados em um arquivo binário
void salvarBinario(Pokemon *&listaPokemons, int quantidade, const string &nomeArquivo){
     ofstream arquivo(nomeArquivo, ios::binary);
     if (!arquivo.is_open()){
          cout << "################################" << endl;
          cout << "Erro ao criar o arquivo binario " << endl;
          return;
     }

     arquivo.write(reinterpret_cast<const char *>(&quantidade), sizeof(quantidade));
     arquivo.write(reinterpret_cast<const char *>(listaPokemons), quantidade * sizeof(Pokemon));

     arquivo.close();
     cout << "##################################" << endl;
     cout << "Arquivo binario salvo com sucesso!" << endl;
}

// Função para redimensionar a lista de Pokemons
// Alocação dinamica de memória!
void redimensionarListaPokemon(Pokemon *&listaPokemons, int quantidade, int &capacidade, int novoTamanho){
     if (novoTamanho < quantidade){
          cout << "erro: tamanho maior que quantidade";
          return;
     }
     capacidade = novoTamanho;
     Pokemon *temp = new Pokemon[capacidade];
     for (int i = 0; i < quantidade; i++){
          temp[i] = listaPokemons[i];
     }
     delete[] listaPokemons;
     listaPokemons = temp;
}

// Função para encontrar o maior ID na lista de Pokémons, necessário para não ocorrer
// que 2 Pokémons terem o mesmo identificador.
// Sempre que adicionado um pokemon, seu identificador será (MaiorID + 1)
int encontrarMaiorIdentidade(const Pokemon listaPokemons[], int quantidade){
     int maiorIdentidade = -1;
     for (int i = 0; i < quantidade; i++){
          if (listaPokemons[i].identidade > maiorIdentidade){
               maiorIdentidade = listaPokemons[i].identidade;
          }
     }
     return maiorIdentidade;
}

// Função para caso o usuário abrir um novo arquivo, não aparecer
// os dados do arquivo anterior. Não exclui os dados anteriores, apenas
// não serão visiveis aos usuarios.
void limparListaPokemon(int &quantidade, int &capacidade){
     capacidade = 50;
     quantidade = 0;
}

int main(){
     Pokemon *listaPokemons = new Pokemon[50];
     int quantidade = 0;
     int capacidade = 50;

     cout << "##############################################" << endl;
     cout << "Bem vindo ao POKEPC!" << endl;
     cout << "Ola! Espero que esteja tudo bem com voce!" << endl;
     cout << "Fico feliz que tenha acessado esse programa!" << endl
          << endl;
     cout << "Desenvolvido por: Samuel Moreira Abreu" << endl
          << endl;
     cout << "## Sobre o Programa:" << endl;
     cout << "Este programa foi desenvolvido na linguagem" << endl;
     cout << "C++ como uma atividade avaliativa da disciplina" << endl;
     cout << "de Introducao aos Algoritmos no meu 1o periodo." << endl;
     cout << "##############################################" << endl;
     cout << "Precione 'enter' para continuar!" << endl;
     cout << "##############################################" << endl;
     cin.ignore();
     cin.get();
     system(CLEAR_COMMAND);

     cout << "##############################################" << endl;
     cout << "## Tematica:" << endl;
     cout << "A inspiracao para esse programa sao os PCs " << endl;
     cout << "que existem nos jogos de Pokemon, onde sao " << endl;
     cout << "guardados os Pokemon que o jogador nao pode " << endl;
     cout << "levar consigo, mas nao quer soltar. Seria " << endl;
     cout << "como um deposito que o jogador consegue " << endl;
     cout << "acessar em qualquer lugar que tenha o PC," << endl;
     cout << " como um armazenamento em nuvem!" << endl;
     cout << "##############################################" << endl;
     cout << "Precione 'enter' para continuar!" << endl;
     cout << "##############################################" << endl;
     cin.ignore();
     cin.get();
     system(CLEAR_COMMAND);

     cout << "##############################################" << endl;
     cout << "## Utilizacao do Programa:" << endl;
     cout << "Inicialmente, e necessario possuir um arquivo " << endl;
     cout << "CSV ou binario em um diretorio no mesmo" << endl;
     cout << "local que o arquivo de execucao desse programa." << endl;
     cout << "O arquivo deve possuir 5 tipos de dados separados" << endl;
     cout << "por virgulas e um limite maximo de 32.765 linhas" << endl
          << endl;
     cout << "Para utilizar as funcoes do programa, e so" << endl;
     cout << "digitar o numero que aparece no inico da frase e" << endl;
     cout << "precionar 'enter' para confirmar!" << endl;
     cout << "##############################################" << endl;
     cout << "Precione 'enter' para continuar!" << endl;
     cout << "##############################################" << endl;
     cin.ignore();
     cin.get();
     system(CLEAR_COMMAND);

     int opcaoEntrada = 0;
     cout << "##############################################" << endl;
     cout << "Qual o tipo do arquivo que voce quer abrir?" << endl;
     cout << "1 - Arquivo CSV" << endl;
     cout << "2 - Arquivo binario" << endl;
     cout << "##############################################" << endl;
     cin >> opcaoEntrada;

     if (opcaoEntrada == 1){
          lerCSV(listaPokemons, quantidade, capacidade);
     }
     else if (opcaoEntrada == 2){
          lerBinario(listaPokemons, quantidade, capacidade);
     }
     else{
          cout << "Tipo de arquivo nao encontrado!";
     return 0;
     }
     // Identificação do sistema operacional e limpeza da tela
     system(CLEAR_COMMAND);

     int opcao = -1;
     
     
     do{
          // Menu para o usuário escolher o que fazer
          cout << "###################################" << endl;
          cout << "1 - Abrir arquivo externo" << endl;
          cout << "2 - Imprimir dados" << endl;
          cout << "3 - Ordenar dados" << endl;
          cout << "4 - Adicionar novo Pokemon" << endl;
          cout << "5 - Excluir Pokemon" << endl;
          cout << "6 - Editar dados de um Pokemon" << endl;
          cout << "7 - Buscar dados" << endl;
          cout << "8 - Salvar arquivo" << endl;
          cout << "0 - Sair" << endl;
          cout << "Escolha uma opcao: " << endl;
          cout << "###################################" << endl;
          cin >> opcao;

          switch (opcao){
          
               // abrir arquivo binario
               case 1:{
                    int opcaoArquivo = 0;

                    cout << "##############################################" << endl;
                    cout << "Qual o tipo do arquivo que voce quer abrir?" << endl;
                    cout << "1 - Arquivo CSV" << endl;
                    cout << "2 - Arquivo binario" << endl;
                    cout << "##############################################" << endl;
                    cin >> opcaoArquivo;

                    switch (opcaoArquivo){
                         case 1:{
                              lerCSV(listaPokemons, quantidade, capacidade);
                              break;
                         }
                         case 2:{
                              lerBinario(listaPokemons, quantidade, capacidade);
                              break;
                         }
                         default:{
                              cout << "Tipo de arquivo nao encontrado!" << endl;
                              break;
                         }
                    }
                    break;
               }

               // imprimir dados
               case 2:{

                    // Menu para escolher a opção de impressão
                    int opcaoImprimir;
                    cout << "##################################" << endl;
                    cout << "Escolha a opcao de impressao:" << endl;
                    cout << "1 - Imprimir todos os dados" << endl;
                    cout << "2 - Imprimir dados em um intervalo" << endl;
                    cout << "Escolha uma opcao: " << endl;
                    cout << "##################################" << endl;
                    cin >> opcaoImprimir;
                    system(CLEAR_COMMAND);
                    if (opcaoImprimir == 1){
                         for (int i = 0; i < quantidade; ++i){
                              imprimirPokemon(listaPokemons[i]);
                         }
                    }
                    else if (opcaoImprimir == 2){
                         int inicio, fim;
                         cout << "################################" << endl;
                         cout << "Digite o intervalo (de 1 a " << quantidade << "): " << endl;
                         cout << "################################" << endl;
                         cout << "-Valores separados por espaco" << endl;
                         cin >> inicio >> fim;
                         if (inicio >= 0 && fim - 1 < quantidade && inicio <= fim - 1){
                              for (int i = (inicio - 1); i <= (fim - 1); ++i){
                                   imprimirPokemon(listaPokemons[i]);
                              }
                         } else{
                              cout << "###############################" << endl;
                              cout << "       Intervalo invalido      " << endl;
                         }
                    }else {
                         cout << "###############################" << endl;
                         cout << "        Opcao invalida         " << endl;
                    }
                    break;
               }

               // switch ordenação
               case 3:{
                    int opcaoOrdenar;
                    cout << "###############################" << endl;
                    cout << "1 - Ordenar por Identidade     " << endl;
                    cout << "2 - Ordenar Nome do Pokemon    " << endl;
                    cout << "###############################" << endl;
                    cin >> opcaoOrdenar;

                    switch (opcaoOrdenar){
                         case 1:{
                              // Ordenar por Identidade usando o MergeSort iterativo
                              mergeSort(listaPokemons, quantidade, true);
                              cout << "###############################" << endl;
                              cout << "Dados ordenados por Identidade:" << endl;
                              cout << "###############################" << endl;
                              for (int i = 0; i < quantidade; ++i){
                                   imprimirPokemon(listaPokemons[i]);
                              }
                              break;
                         }
                         case 2:{
                              // Ordenar por nomePokemon usando o MergeSort iterativo
                              mergeSort(listaPokemons, quantidade, false);
                              cout << "################################" << endl;
                              cout << "Dados ordenados por nomePokemon:" << endl;
                              cout << "################################" << endl;
                              for (int i = 0; i < quantidade; ++i){
                                   imprimirPokemon(listaPokemons[i]);
                              }
                              break;
                         }
                         default:
                         cout << "###############################" << endl;
                         cout << "        Opcao invalida         " << endl;
                         break;
                         }
                         break;
               }

               // adicionar pokemon
               case 4:{
                    // Adicionar novo Pokemon
                    adicionarPokemon(listaPokemons, quantidade, capacidade);
                    cout << "####################################" << endl;
                    cout << "Novo Pokemon adicionado com sucesso!" << endl;
                    break;
               }

               // excluir dados
               case 5:{
                    // Excluir Pokemon
                    excluirPokemon(listaPokemons, quantidade);
                    cout << "###############################" << endl;
                    cout << " Pokemon excluido com sucesso! " << endl;

                    break;
               }

               // editar dados de um pokemon
               case 6:{
                    // Editar dados de um Pokemon
                    int identidadeEditar;
                    cout << "##################################################" << endl;
                    cout << "Digite a identidade do Pokemon que deseja editar: " << endl;
                    cout << "##################################################" << endl;
                    cin >> identidadeEditar;

                    int indiceEditar = -1;
                    for (int i = 0; i < quantidade; i++){
                         if (listaPokemons[i].identidade == identidadeEditar){
                              indiceEditar = i;
                              break;
                         }
                    }

                    if (indiceEditar != -1){
                         editarPokemon(listaPokemons[indiceEditar]);
                         cout << "######################################" << endl;
                         cout << "Dados do Pokemon editados com sucesso!" << endl;
                    }else{
                         cout << "##################################################" << endl;
                         cout << "Pokemon com a identidade fornecida nao encontrado." << endl;
                    }
                    break;
               }

               // busca e filtragem
               case 7:{
                    // Menu para escolher a opção de busca
                    int opcaoBuscar;
                    cout << "###############################" << endl;
                    cout << "    Escolha a opcao de busca:  " << endl
                         << endl;
                    cout << "1 - Buscar por Identidade" << endl;
                    cout << "2 - Buscar por nomePokemon" << endl;
                    cout << "3 - Buscar por sexoPokemon" << endl;
                    cout << "4 - Buscar por pokeballPokemon" << endl;
                    cout << "5 - Buscar por naturePokemon" << endl;
                    cout << "###############################" << endl;
                    cin >> opcaoBuscar;

                    switch (opcaoBuscar){
                         case 1:{
                              buscarPorIdentidade(listaPokemons, quantidade);
                              break;
                         }
                         case 2:{
                              buscarPorNome(listaPokemons, quantidade);
                              break;
                         }
                         case 3:{
                              filtrarPorSexo(listaPokemons, quantidade);
                              break;
                         }
                         case 4:{
                              filtrarPorPokeball(listaPokemons, quantidade);
                              break;
                         }
                         case 5:{
                              filtrarPorNature(listaPokemons, quantidade);
                              break;
                         }
                         default:
                              cout << "###############################" << endl;
                              cout << "         Opcao invalida.       " << endl;
                         }
                         break;
               }

               // salvar arquivo
               case 8:{
                    // Menu para escolher a opção de salvamento
                    int opcaoSalvar;
                    cout << "###############################" << endl;
                    cout << "Escolha a opcao de salvamento:" << endl;
                    cout << "1 - Salvar como arquivo CSV" << endl;
                    cout << "2 - Salvar como arquivo binario" << endl;
                    cout << "       Escolha uma opcao:      " << endl;
                    cout << "###############################" << endl;
                    cin >> opcaoSalvar;

                    string nomeArquivo;
                    cout << "###############################" << endl;
                    cout << "    Digite o nome do arquivo:  " << endl;
                    cout << "###############################" << endl;
                    cin.ignore();
                    getline(cin, nomeArquivo);

                    if (opcaoSalvar == 1){
                         salvarCSV(listaPokemons, quantidade, nomeArquivo + ".csv");
                    }else if (opcaoSalvar == 2){
                         salvarBinario(listaPokemons, quantidade, nomeArquivo + ".bin");
                    }else{
                         cout << "###############################" << endl;
                         cout << "        Opcao invalida.        " << endl;
                    }
                    break;
               }

               // sair
               case 0:{
                    cout << "###############################" << endl;
                    cout << "            Saindo...          " << endl;
                    cout << "###############################" << endl;
                    break;
               }

               // default
               default:{
                    cout << "###############################" << endl;
                    cout << "        Opcao invalida.        " << endl;
               }
          }

          // Aguardar o usuário pressionar Enter para limpar a tela
          cout << "#################################" << endl;
          cout << "Precione Enter para continuar..." << endl;
          cout << "#################################" << endl;
          cin.ignore();
          cin.get();

          // Limpeza da tela
          system(CLEAR_COMMAND);

     } while (opcao != 0);

     delete[] listaPokemons;

     return 0;
}
