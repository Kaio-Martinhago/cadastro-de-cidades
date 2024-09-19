#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_STRING 100
#define FIM 0

typedef char string[100];

typedef struct dados_cidade {
    string nome;
    int estado_cidade;
    float renda_per_capita;
    float media_renda_familiar;
    long int qtd_entrevistados;
    long int qtd_filhos_menos_18;
    long int qtd_brancos;
    long int qtd_pardos;
    long int qtd_pretos;
    struct dados_cidade *prox;
}dados_cidade;

typedef struct cidade_excluir {
  dados_cidade* cidade;
  dados_cidade* anterior;
}cidade_excluir;

//FUNÇÕES AUXILIARES
dados_cidade* nova_cidade();
dados_cidade* localiza_cidade_por_nome_e_estado(dados_cidade* lista, string nome, int estado);
cidade_excluir excluir_cidade(string nome, dados_cidade *lista);
void bubble_sort_qtd_entrevistados(dados_cidade* inicio);
void qtd_p_e_b_cidade_menor_rendapc(dados_cidade* lista);
void qtd_filhos_menor_cidade_menor_renda(dados_cidade* lista);
void listar_cidades_maior_qtd_entrevistados(dados_cidade* lista);
void criar_arquivo(char *nome_arq);
void incluir_nova_cidade(dados_cidade** lista, dados_cidade* nova);
void mostrar_cidade(dados_cidade* cidade);
void mostrar_todas_cidades(dados_cidade* lista);
void remover_enter_toupper(string str);
void salvar_dados_arquivo_binario(dados_cidade *lista, int qtd_cidades);
void importar_dados_arquivo_binario(dados_cidade **lista, int *qtd_cidades);
void salvar_todas_cidades(dados_cidade *lista, string nome_arq);
void menu_estados();
void alterar_dados(dados_cidade* cidade, string nome, int estado, float renda_pc, 
    float renda_fam, long int qtd_entrevistados, long int qtd_filhos_menos_18,
    long int qtd_brancos, long int qtd_pardos, long int qtd_pretos);
void listar_por_renda_per_capita(dados_cidade* lista, float inicio, float fim);
void listar_por_renda_familiar(dados_cidade* lista, float inicio, float fim);
dados_cidade* copia_dados(dados_cidade *lista_original);
void listar_cidade_por_estado(dados_cidade *lista, int estado);
int verifica_renda_pc(dados_cidade* lista, float inicio, float fim);
int verifica_estado(dados_cidade *lista, int estado);
int verifica_renda_familiar(dados_cidade* lista, float inicio, float fim);
int menu_relatorios_estatisticos();
void bubble_sort_renda_pc(dados_cidade* inicio);
void bubble_sort_renda_pc2(dados_cidade **inicio, int qtd_cidades);
void listar_cidades_maior_rendapc(dados_cidade* lista);
void bubble_sort_renda_fam(dados_cidade* inicio);
void salvar_por_renda_familiar(dados_cidade* lista, float inicio, float fim, string nome_arq);
void salvar_por_renda_pc(dados_cidade* lista, float inicio, float fim, string nome_arq);
void salvar_por_cidade(dados_cidade* lista, string nome, int estado, string nome_arq);
void salvar_cidade_por_estado(dados_cidade *lista, int estado, string nome_arq);
void salvar_relatorio1(dados_cidade* lista, string nome_arq);
void salvar_relatorio2(dados_cidade* lista, string nome_arq);
void salvar_relatorio3(dados_cidade* lista, string nome_arq);
void salvar_relatorio4(dados_cidade* lista, string nome_arq);
void salvar_relatorio5(dados_cidade* lista, string nome_arq);
int menu_sim_nao();
int menu();
int menu_arq_texto();

int main(){
    dados_cidade *lista = NULL;
    dados_cidade *lista_copia_pc = NULL;
    dados_cidade *lista_copia_qtd_entrevistados = NULL;
    dados_cidade *lista_copia_fam = NULL;
	dados_cidade *novo = NULL;
	dados_cidade *excluir_nome = NULL;
	cidade_excluir excluir;
	string nome_localizar, nome_excluir;
    int estado_localizar, estado_excluir;
	int opc, opcao3;
    float inicio_renda_pc, fim_renda_pc;
    float inicio_renda_fam, fim_renda_fam;

    string nome_arq_mostrar_cidades, nome_arq_relatorio_cidade, nome_arq_relatorio_rendapc, nome_arq_relatorio_rendafam, nome_arq_listar_estados;

    string nome_relatorio1, nome_relatorio2, nome_relatorio3, nome_relatorio4, nome_relatorio5;

    int opcao_relatorios;

    // Variáveis para a função "alteracao_de_dados"
    dados_cidade *cidade_alterar = NULL;
    string nome_alt;
    string localiza_nome_alterar;
    int estado_alt, opcao2, estado_alterar;
    float renda_capita_alt, renda_familar_alt;
    long int qtd_entrevistados_alt, qtd_brancos_alt, qtd_pardos_alt;
    long int qtd_pretos_alt, qtd_filhos_menos_18_alt;

    // Variável para a função "listar_cidade_por_estado"
    int estado_filtra;

    int qtd_cidades = 0;

    int opcao_excel;

    criar_arquivo("dados_cidades.bin");
	importar_dados_arquivo_binario(&lista, &qtd_cidades);
    lista_copia_fam = copia_dados(lista);

    printf("Quantidade de cidades: %i\n", qtd_cidades);

    do {
		opc = menu();

		switch (opc) {

		  	case 1: incluir_nova_cidade(&lista, nova_cidade());
                    qtd_cidades++;
				break;

		  	case 2: printf("Insira o nome da cidade que deseja excluir: ");
					fgets(nome_excluir, TAMANHO_STRING, stdin);
					remover_enter_toupper(nome_excluir);
                    printf("Digite o estado da cidade que deseja excluir: ");
                    scanf("%i", &estado_excluir);
                    getchar();
					excluir_nome = localiza_cidade_por_nome_e_estado(lista, nome_excluir, estado_excluir);
					if (excluir_nome == NULL){
						printf("\nCidade nao encontrada.\n");
					}
					else{
						excluir = excluir_cidade(nome_excluir, lista);
						printf("\nExcluindo cidade...\n\n");
						if (excluir.cidade == excluir.anterior) {
							lista = excluir.cidade->prox;
						}
						else {
							excluir.anterior->prox = excluir.cidade->prox;
						}
						printf("Cidade excluida!...\n");
                        qtd_cidades--;
						free(excluir.cidade);
					}
			    break;

            case 3: printf("Digite o nome da cidade que deseja alterar: ");
                    fgets(localiza_nome_alterar, TAMANHO_STRING, stdin);
                    remover_enter_toupper(localiza_nome_alterar);
                    printf("Digite o estado da cidade que deseja alterar: ");
                    scanf("%i", &estado_alterar);
                    getchar();
                    printf("\nAlterando cidade...... \n\n");
                    cidade_alterar = localiza_cidade_por_nome_e_estado(lista, localiza_nome_alterar, estado_alterar);

                    if(cidade_alterar != NULL){
                        printf("Deseja alterar o nome da cidade? ");
                        opcao2 = menu_sim_nao();
                        if(opcao2 == 1){
                            printf("Digite o novo nome: ");
                            fgets(nome_alt, TAMANHO_STRING, stdin);
                            remover_enter_toupper(nome_alt);
                        }
                        else{
                            strcpy(nome_alt, cidade_alterar->nome);
                        }
                        printf("Deseja alterar o estado da cidade? ");
                        opcao2 = menu_sim_nao();
                        if(opcao2 == 1){
                            menu_estados();
                            printf("Digite o novo estado: ");
                            scanf("%i", &estado_alt);
                            getchar();
                        }
                        else{
                            estado_alt = cidade_alterar->estado_cidade;
                        }
                        printf("Deseja alterar a renda per capita? ");
                        opcao2 = menu_sim_nao();
                        if(opcao2 == 1){
                            printf("Digite a nova renda per capita: ");
                            scanf("%f", &renda_capita_alt);
                            getchar();
                        }
                        else{
                            renda_capita_alt = cidade_alterar->renda_per_capita;
                        }
                        printf("Deseja alterar a renda familiar? ");
                        opcao2 = menu_sim_nao();
                        if(opcao2 == 1){
                            printf("Digite a nova renda familiar: ");
                            scanf("%f", &renda_familar_alt);
                            getchar();
                        }
                        else{
                            renda_familar_alt = cidade_alterar->media_renda_familiar;
                        }
                        printf("Deseja alterar a quantidade de entrevistados? ");
                        opcao2 = menu_sim_nao();
                        if(opcao2 == 1){
                            printf("Digite a nova quantidade de entrevistados: ");
                            scanf("%li", &qtd_entrevistados_alt);
                            getchar();
                        }
                        else{
                            qtd_entrevistados_alt = cidade_alterar->qtd_entrevistados;
                        }
                        printf("Deseja alterar a quantidade de filhos menores de 18? ");
                        opcao2 = menu_sim_nao();
                        if(opcao2 == 1){
                            printf("Digite a nova quantidade de filhos: ");
                            scanf("%li", &qtd_filhos_menos_18_alt);
                            getchar();
                        }
                        else{
                            qtd_filhos_menos_18_alt = cidade_alterar->qtd_filhos_menos_18;
                        }
                        printf("Deseja alterar a quantidade de brancos? ");
                        opcao2 = menu_sim_nao();
                        if(opcao2 == 1){
                            printf("Digite a nova quantidade de brancos: ");
                            scanf("%li", &qtd_brancos_alt);
                            getchar();
                        }
                        else{
                            qtd_brancos_alt = cidade_alterar->qtd_brancos;
                        }
                        printf("Deseja alterar a quantidade de pardos? ");
                        opcao2 = menu_sim_nao();
                        if(opcao2 == 1){
                            printf("Digite a nova quantidade de pardos: ");
                            scanf("%li", &qtd_pardos_alt);
                            getchar();
                        }
                        else{
                            qtd_pardos_alt = cidade_alterar->qtd_pardos;
                        }
                        printf("Deseja alterar a quantidade de pretos? ");
                        opcao2 = menu_sim_nao();
                        if(opcao2 == 1){
                            printf("Digite a nova quantidade de pretos: ");
                            scanf("%li", &qtd_pretos_alt);
                            getchar();
                        }
                        else{
                            qtd_pretos_alt = cidade_alterar->qtd_pretos;
                        }

                        alterar_dados(cidade_alterar, nome_alt, estado_alt, 
                        renda_capita_alt, renda_familar_alt, qtd_entrevistados_alt, 
                        qtd_filhos_menos_18_alt, qtd_brancos_alt, qtd_pardos_alt, 
                        qtd_pretos_alt);
                        printf("\nDados da cidade de %s foram alterados.\n", localiza_nome_alterar);
                    }
                    else{
                        printf("A cidade %s nao foi encontrada! \n", localiza_nome_alterar);
                    }

                break;

		 	case 4: printf("Deseja filtrar as cidades por estado?\n");
                    printf("DIGITE 1 PARA SIM E 2 PARA NAO\n");
                    printf("::? ");
                    scanf("%i", &opcao3);
                    getchar();
                    if(opcao3 != 1){
                        if(lista != NULL){
                            do{
                                opcao_excel = menu_arq_texto();
                                switch (opcao_excel){
                                    case 1: printf("Relatorio de cidades......\n\n");
                                            mostrar_todas_cidades(lista);
                                            break;
                                    case 2: printf("Digite o nome do arquivo: ");
                                            fgets(nome_arq_mostrar_cidades, TAMANHO_STRING, stdin);
                                            remover_enter_toupper(nome_arq_mostrar_cidades);
                                            strcat(nome_arq_mostrar_cidades, ".csv");
                                            printf("Salvando em excel...\n\n");
                                            salvar_todas_cidades(lista, nome_arq_mostrar_cidades);
                                            printf("Dados salvos!\n");
                                            break;
                                    case 0: printf("Voltando...");
                                            break;
                                    default: printf("Opcao Invalida!!\n");
                                            break;
                                }
                            }while(opcao_excel != FIM);
                        }
                        else printf("Nao ha cidades cadastradas!\n");
                    }
                    if(opcao3 == 1){
                        menu_estados();
                        printf("\nInsira o estado: ");
                        scanf("%i", &estado_filtra);
                        if(verifica_estado(lista, estado_filtra) == -1){
                            printf("\nNao ha cidades cadastradas com esse estado!\n");
                        }
                        else{
                            do{
                                opcao_excel = menu_arq_texto();
                                switch (opcao_excel){
                                    case 1: printf("\nListando cidades......\n\n");
                                            listar_cidade_por_estado(lista, estado_filtra);
                                            break;
                                    case 2: printf("Digite o nome do arquivo: ");
                                            fgets(nome_arq_listar_estados, TAMANHO_STRING, stdin);
                                            remover_enter_toupper(nome_arq_listar_estados);
                                            strcat(nome_arq_listar_estados, ".csv");
                                            printf("Salvando em excel...\n\n");
                                            salvar_cidade_por_estado(lista, estado_filtra, nome_arq_listar_estados);
                                            printf("Dados salvos!\n");
                                            break;
                                    case 0: printf("Voltando...");
                                            break;
                                    default: printf("Opcao Invalida!!\n");
                                            break;
                                }
                            }while(opcao_excel != FIM);
                        }
                    }
			    break;

            case 5: printf("Insira o nome da cidade: ");
					fgets(nome_localizar, TAMANHO_STRING, stdin);
					remover_enter_toupper(nome_localizar);
                    printf("Digite o estado da cidade que deseja localizar: ");
                    scanf("%i", &estado_localizar);
                    getchar();
					novo = localiza_cidade_por_nome_e_estado(lista, nome_localizar, estado_localizar);
					if (novo == NULL){
						printf("\nA cidade de %s nao foi encontrada.\n", nome_localizar);
					}
					else{
                        do{
                            opcao_excel = menu_arq_texto();
                            switch (opcao_excel){
                                case 1: printf("\n");
                                        mostrar_cidade(novo);
                                        break;
                                case 2: printf("Digite o nome do arquivo: ");
                                        fgets(nome_arq_relatorio_cidade, TAMANHO_STRING, stdin);
                                        remover_enter_toupper(nome_arq_relatorio_cidade);
                                        strcat(nome_arq_relatorio_cidade, ".csv");
                                        printf("Salvando em excel...\n\n");
                                        salvar_por_cidade(lista, nome_localizar, estado_localizar, nome_arq_relatorio_cidade);
                                        printf("Dados salvos!\n");
                                        break;
                                case 0: printf("Voltando...");
                                        break;
                                default: printf("Opcao Invalida!!\n");
                                        break;
                                }
                            }while(opcao_excel != FIM);  
					}
                break;

            case 6: printf("Insira o inicio da renda per capita: ");
                    scanf("%f", &inicio_renda_pc);
                    printf("Insira o fim da renda per capita: ");
                    scanf("%f", &fim_renda_pc);
                    printf("\n");
                    if(inicio_renda_pc < fim_renda_pc){
                        if(verifica_renda_pc(lista, inicio_renda_pc, fim_renda_pc) == 1){
                            do{
                            opcao_excel = menu_arq_texto();
                            switch (opcao_excel){
                                case 1: listar_por_renda_per_capita(lista, inicio_renda_pc, fim_renda_pc);
                                        break;
                                case 2: printf("Digite o nome do arquivo: ");
                                        fgets(nome_arq_relatorio_rendapc, TAMANHO_STRING, stdin);
                                        remover_enter_toupper(nome_arq_relatorio_rendapc);
                                        strcat(nome_arq_relatorio_rendapc, ".csv");
                                        printf("Salvando em excel...\n\n");
                                        salvar_por_renda_pc(lista, inicio_renda_pc, fim_renda_pc, nome_arq_relatorio_rendapc);
                                        printf("Dados salvos!\n");
                                        break;
                                case 0: printf("Voltando...");
                                        break;
                                default: printf("Opcao Invalida!!\n");
                                        break;
                                }
                            }while(opcao_excel != FIM);  
                        }
                        else printf("Nao ha cidades dentro dos parametros informados!\n");
                    }
                    else{
                        if(verifica_renda_pc(lista, fim_renda_pc, inicio_renda_pc) == 1){
                            do{
                            opcao_excel = menu_arq_texto();
                            switch (opcao_excel){
                                case 1: listar_por_renda_per_capita(lista, fim_renda_pc, inicio_renda_pc);
                                        break;
                                case 2: printf("Digite o nome do arquivo: ");
                                        fgets(nome_arq_relatorio_rendapc, TAMANHO_STRING, stdin);
                                        remover_enter_toupper(nome_arq_relatorio_rendapc);
                                        strcat(nome_arq_relatorio_rendapc, ".csv");
                                        printf("Salvando em excel...\n\n");
                                        salvar_por_renda_pc(lista, fim_renda_pc, inicio_renda_pc, nome_arq_relatorio_rendapc);
                                        printf("Dados salvos!\n");
                                        break;
                                case 0: printf("Voltando...");
                                        break;
                                default: printf("Opcao Invalida!!\n");
                                        break;
                                }
                            }while(opcao_excel != FIM);  
                        }
                        else printf("Nao ha cidades dentro dos parametros informados!\n");
                    }
                break;

            case 7: printf("Insira o inicio da renda familiar: ");
                    scanf("%f", &inicio_renda_fam);
                    printf("Insira o fim da renda familiar: "); 
                    scanf("%f", &fim_renda_fam);
                    printf("\n");
                    if(inicio_renda_fam < fim_renda_fam){
                        if(verifica_renda_familiar(lista, inicio_renda_fam, fim_renda_fam) == 1){
                            do{
                            opcao_excel = menu_arq_texto();
                            switch (opcao_excel){
                                case 1: listar_por_renda_familiar(lista, inicio_renda_fam, fim_renda_fam);
                                        break;
                                case 2: printf("Digite o nome do arquivo: ");
                                        fgets(nome_arq_relatorio_rendafam, TAMANHO_STRING, stdin);
                                        remover_enter_toupper(nome_arq_relatorio_rendafam);
                                        strcat(nome_arq_relatorio_rendafam, ".csv");
                                        printf("Salvando em excel...\n\n");
                                        salvar_por_renda_familiar(lista, inicio_renda_fam, fim_renda_fam, nome_arq_relatorio_rendafam);
                                        printf("Dados salvos!\n");
                                        break;
                                case 0: printf("Voltando...");
                                        break;
                                default: printf("Opcao Invalida!!\n");
                                        break;
                                }
                            }while(opcao_excel != FIM);  
                        }
                        else printf("Nao ha cidades dentro dos parametros informados!\n");
                    }
                    else{
                        if(verifica_renda_familiar(lista, fim_renda_fam, inicio_renda_fam) == 1){
                            do{
                            opcao_excel = menu_arq_texto();
                            switch (opcao_excel){
                                case 1: listar_por_renda_familiar(lista, fim_renda_fam, inicio_renda_fam);
                                        break;
                                case 2: printf("Digite o nome do arquivo: ");
                                        fgets(nome_arq_relatorio_rendafam, TAMANHO_STRING, stdin);
                                        remover_enter_toupper(nome_arq_relatorio_rendafam);
                                        strcat(nome_arq_relatorio_rendafam, ".csv");
                                        printf("Salvando em excel...\n\n");
                                        salvar_por_renda_familiar(lista, fim_renda_fam, inicio_renda_fam, nome_arq_relatorio_rendafam);
                                        printf("Dados salvos!\n");
                                        break;
                                case 0: printf("Voltando...");
                                        break;
                                default: printf("Opcao Invalida!!\n");
                                        break;
                                }
                            }while(opcao_excel != FIM);
                        }
                        else printf("Nao ha cidades dentro dos parametros informados!\n");
                    }
                break;

            case 8: do{
                        opcao_relatorios = menu_relatorios_estatisticos();

                        switch(opcao_relatorios){
                            case 1: if(qtd_cidades >= 1){
                                        do{
                                        opcao_excel = menu_arq_texto();
                                            switch (opcao_excel){
                                            case 1: lista_copia_fam = copia_dados(lista); 
                                                    qtd_filhos_menor_cidade_menor_renda(lista_copia_fam);
                                                    free(lista_copia_fam);
                                                    break;

                                            case 2: lista_copia_fam = copia_dados(lista); 
                                                    printf("Digite o nome do arquivo: ");
                                                    fgets(nome_relatorio1, TAMANHO_STRING, stdin);
                                                    remover_enter_toupper(nome_relatorio1);
                                                    strcat(nome_relatorio1, ".csv");
                                                    printf("Salvando em excel...\n\n");
                                                    salvar_relatorio1(lista_copia_fam, nome_relatorio1);
                                                    printf("Dados salvos!\n");
                                                    free(lista_copia_fam);
                                                    break;

                                            case 0: printf("Voltando...\n");
                                                    break;

                                            default: printf("Opcao Invalida!!\n");
                                                    break;
                                            }
                                        }while(opcao_excel != FIM);  
                                    }
                                    else printf("Nao ha cidades cadastradas!\n\n");
                                break;

                            case 2: if(qtd_cidades >= 1){
                                        do{
                                        opcao_excel = menu_arq_texto();
                                            switch (opcao_excel){
                                            case 1: lista_copia_pc = copia_dados(lista);
                                                    qtd_p_e_b_cidade_menor_rendapc(lista_copia_pc);
                                                    free(lista_copia_pc);
                                                    break;

                                            case 2: lista_copia_pc = copia_dados(lista);
                                                    printf("Digite o nome do arquivo: ");
                                                    fgets(nome_relatorio2, TAMANHO_STRING, stdin);
                                                    remover_enter_toupper(nome_relatorio2);
                                                    strcat(nome_relatorio2, ".csv");
                                                    printf("Salvando em excel...\n\n");
                                                    salvar_relatorio2(lista_copia_pc, nome_relatorio2);
                                                    printf("Dados salvos!\n");
                                                    free(lista_copia_pc);
                                                    break;

                                            case 0: printf("Voltando...\n");
                                                    break;

                                            default: printf("Opcao Invalida!!\n");
                                                    break;
                                            }
                                        }while(opcao_excel != FIM);
                                    }
                                    else printf("Nao ha cidades cadastradas!\n\n");
                                break;

                            case 3: if(qtd_cidades >= 1){
                                    do{
                                        opcao_excel = menu_arq_texto();
                                            switch (opcao_excel){
                                            case 1: lista_copia_fam = copia_dados(lista);
                                                    bubble_sort_renda_fam(lista_copia_fam);
                                                    printf("\nCidade com maior renda familiar:\n");
                                                    printf("%s - %.2f\n", lista_copia_fam->nome, lista_copia_fam->media_renda_familiar);
                                                    printf("\n");
                                                    free(lista_copia_fam);
                                                    break;

                                            case 2: lista_copia_fam = copia_dados(lista);
                                                    printf("Digite o nome do arquivo: ");
                                                    fgets(nome_relatorio3, TAMANHO_STRING, stdin);
                                                    remover_enter_toupper(nome_relatorio3);
                                                    strcat(nome_relatorio3, ".csv");
                                                    printf("Salvando em excel...\n\n");
                                                    salvar_relatorio3(lista_copia_fam, nome_relatorio3);
                                                    printf("Dados salvos!\n");
                                                    free(lista_copia_fam);
                                                    break;

                                            case 0: printf("Voltando...\n");
                                                    break;

                                            default: printf("Opcao Invalida!!\n");
                                                    break;
                                            }
                                        }while(opcao_excel != FIM);
                                    }
                                    else printf("Nao ha cidades cadastradas!\n\n");
                                break;

                            case 4: if(qtd_cidades >= 3){
                                    do{
                                        opcao_excel = menu_arq_texto();
                                            switch (opcao_excel){
                                            case 1: lista_copia_pc = copia_dados(lista);
                                                    listar_cidades_maior_rendapc(lista_copia_pc);
                                                    free(lista_copia_pc);
                                                    printf("\n");
                                                    break;

                                            case 2: lista_copia_pc = copia_dados(lista);
                                                    printf("Digite o nome do arquivo: ");
                                                    fgets(nome_relatorio4, TAMANHO_STRING, stdin);
                                                    remover_enter_toupper(nome_relatorio4);
                                                    strcat(nome_relatorio4, ".csv");
                                                    printf("Salvando em excel...\n\n");
                                                    salvar_relatorio4(lista_copia_pc, nome_relatorio4);
                                                    printf("Dados salvos!\n");
                                                    free(lista_copia_pc);
                                                    break;

                                            case 0: printf("Voltando...\n");
                                                    break;

                                            default: printf("Opcao Invalida!!\n");
                                                    break;
                                            }
                                        }while(opcao_excel != FIM);
                                    }
                                    else printf("Cadastre no minimo 3 cidades!\n\n");                            
                                break;

                            case 5: if(qtd_cidades >= 3){ 
                                        do{
                                        opcao_excel = menu_arq_texto();
                                            switch (opcao_excel){
                                            case 1: lista_copia_qtd_entrevistados = copia_dados(lista);
                                                    listar_cidades_maior_qtd_entrevistados(lista_copia_qtd_entrevistados);
                                                    free(lista_copia_qtd_entrevistados);
                                                    printf("\n");
                                                    break;

                                            case 2: lista_copia_qtd_entrevistados = copia_dados(lista);
                                                    printf("Digite o nome do arquivo: ");
                                                    fgets(nome_relatorio5, TAMANHO_STRING, stdin);
                                                    remover_enter_toupper(nome_relatorio5);
                                                    strcat(nome_relatorio5, ".csv");
                                                    printf("Salvando em excel...\n\n");
                                                    salvar_relatorio5(lista_copia_qtd_entrevistados, nome_relatorio5);
                                                    printf("Dados salvos!\n");
                                                    free(lista_copia_qtd_entrevistados);
                                                    break;

                                            case 0: printf("Voltando...\n");
                                                    break;

                                            default: printf("Opcao Invalida!!\n");
                                                    break;
                                            }
                                        }while(opcao_excel != FIM);
                                    }
                                    else printf("Cadastre no minimo 3 cidades!\n\n");
                                break;

                            case 0: printf("Voltando ao inicio...\n");
                                break;

                            default: printf("Opcao invalida!\n");
                                break;
                        }

                    } while(opcao_relatorios != FIM);
                break;

		  	case 0: salvar_dados_arquivo_binario(lista, qtd_cidades);
		  		  printf("Tchau!!\n");
		  		break;

		  	default: printf("Opcao Invalida!\n");
		  		break;
		}
	} while (opc != 0);

    return 0;
}

// Implementação das funções auxiliares
void criar_arquivo(char *nome_arq){
    FILE *arquivo = fopen(nome_arq, "ab");
    if (arquivo != NULL) {
        fclose(arquivo);
    } else {
        printf("Erro ao criar o arquivo %s.\n", nome_arq);
    }
}

dados_cidade* nova_cidade(){
	dados_cidade *nova;

	nova = (dados_cidade*)malloc(sizeof(dados_cidade));

	printf("Nome..........................: ");
	fgets(nova->nome, TAMANHO_STRING, stdin);
	remover_enter_toupper(nova->nome);
	menu_estados();
    printf("\nInsira o numero correspondente ao estado: ");
    scanf("%i", &nova->estado_cidade);
    while(nova->estado_cidade > 27 || nova->estado_cidade <= 0){
        printf("Estado Invalido!");
        printf("\nInsira o numero correspondente ao estado: ");
        scanf("%i", &nova->estado_cidade);
    }
    getchar();
    printf("Renda per capita..........: ");
    scanf("%f", &nova->renda_per_capita);
    getchar();
    printf("Renda familiar media......: ");
    scanf("%f", &nova->media_renda_familiar);
    getchar();
    printf("Pessoas entrevistadas.....: ");
    scanf("%li", &nova->qtd_entrevistados);
    getchar();
    printf("Quantidade de filhos < 18.: ");
    scanf("%li", &nova->qtd_filhos_menos_18);
    getchar();
    printf("Quantidade de brancos.....: ");
    scanf("%li", &nova->qtd_brancos);
    getchar();
    printf("Quantidade de pardos......: ");
    scanf("%li", &nova->qtd_pardos);
    getchar();
    printf("Quantidade de pretos......: ");
    scanf("%li", &nova->qtd_pretos);
    getchar();
	nova->prox = NULL;

	return nova;
}

void incluir_nova_cidade(dados_cidade** lista, dados_cidade* nova){
  dados_cidade* ptr;
  if (*lista == NULL) {
        *lista = nova;
        nova->prox = NULL;
    } else {
        ptr = *lista;
        while (ptr->prox != NULL) {
            ptr = ptr->prox;
        }
        ptr->prox = nova;
        nova->prox = NULL;
    }
}

void mostrar_cidade(dados_cidade* cidade){
	printf("Nome da cidade............: %s\n", cidade->nome);
	printf("Estado....................: %i\n", cidade->estado_cidade);
    printf("Renda per capita..........: %.2f\n", cidade->renda_per_capita);
    printf("Media renda familiar......: %.2f\n", cidade->media_renda_familiar);
    printf("Pessoas entrevistadas.....: %li\n", cidade->qtd_entrevistados);
    printf("Quant de filhos < 18......: %li\n", cidade->qtd_filhos_menos_18);
    printf("Quantidade de brancos.....: %li\n", cidade->qtd_brancos);
    printf("Quantidade de pardos......: %li\n", cidade->qtd_pardos);
    printf("Quantidade de pretos......: %li\n", cidade->qtd_pretos);
    printf("\n");
}

void mostrar_todas_cidades(dados_cidade* lista){
  while (lista) {
		mostrar_cidade(lista);
		lista = lista->prox;
  }
}

void remover_enter_toupper(string str){
	int i, t = strlen(str);
	str[t-1] = '\0';

	for (i = 0; i < t-1; i++) {
		str[i] = toupper(str[i]);
	}
}

int menu(){
	int opc;

	printf("\n");
    printf("1.Inclusao de dados\n");
    printf("2.Exclusao de dados\n");
    printf("3.Alteracao dados\n");
    printf("4.Mostrar cidades cadastradas\n");
    printf("5.Relatorio de dados por cidade\n");
    printf("6.Relatorio renda per capita\n");
    printf("7.Relatorio por renda familiar\n");
    printf("8.Relatorios estatisticos\n");
    printf("0.Sair\n");
	printf("::? ");
	scanf("%i", &opc);
	getchar();
	printf("\n");

	return opc;
}

void menu_estados(){
    printf("\n");
    printf("|AC-1|  |AL-2|  |AP-3|  |AM-4|  |BA-5|  |CE-6|  |DF-7|  |ES-8|  |GO-9|\n");
    printf("|MA-10| |MT-11| |MS-12| |MG-13| |PA-14| |PB-15| |PR-16| |PE-17| |PI-18|\n");
    printf("|RJ-19| |RN-20| |RS-21| |RO-22| |RR-23| |SC-24| |SP-25| |SE-26| |TO-27|");
    printf("\n");

}

void salvar_dados_arquivo_binario(dados_cidade *lista, int qtd_cidades){
	FILE *fp;

	fp = fopen("dados_cidades.bin", "wb");

    fwrite(&qtd_cidades, sizeof(int), 1, fp);

	while (lista) {
		fwrite(lista, sizeof(dados_cidade), 1, fp);
		lista = lista->prox;
	}
	fclose(fp);
}

void importar_dados_arquivo_binario(dados_cidade **lista, int *qtd_cidades){
	FILE *fp;
	dados_cidade *p_cidade = NULL;

	fp = fopen("dados_cidades.bin", "rb");

    if (fp == NULL) {
        *qtd_cidades = 0;
        *lista = NULL;
        return;
    }

    fread(qtd_cidades, sizeof(int), 1, fp);

	while (!feof(fp)) {
		p_cidade = (dados_cidade*)malloc(sizeof(dados_cidade));
		fread(p_cidade, sizeof(dados_cidade), 1, fp);
		p_cidade->prox = NULL;
		if (!feof(fp)) {
			incluir_nova_cidade(lista, p_cidade);
		}
		else {
			free(p_cidade);
		}
	}
	fclose(fp);
}

void salvar_todas_cidades(dados_cidade *lista, string nome_arq){
	FILE *fp;
    dados_cidade *aux = lista;

    fp = fopen(nome_arq, "w");
    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        exit(0);
    }
    else{
        while(aux){
            fprintf(fp, "Nome da cidade............: %s\n", aux->nome);
            fprintf(fp, "Estado....................: %i\n", aux->estado_cidade);
            fprintf(fp, "Renda per capita..........: %.2f\n", aux->renda_per_capita);
            fprintf(fp, "Media renda familiar......: %.2f\n", aux->media_renda_familiar);
            fprintf(fp, "Pessoas entrevistadas.....: %li\n", aux->qtd_entrevistados);
            fprintf(fp, "Quant de filhos < 18......: %li\n", aux->qtd_filhos_menos_18);
            fprintf(fp, "Quantidade de brancos.....: %li\n", aux->qtd_brancos);
            fprintf(fp, "Quantidade de pardos......: %li\n", aux->qtd_pardos);
            fprintf(fp, "Quantidade de pretos......: %li\n", aux->qtd_pretos);
			fprintf(fp, "\n");
            aux = aux->prox;
        }
        fclose(fp);
    }
}

void salvar_por_renda_familiar(dados_cidade* lista, float inicio, float fim, string nome_arq){
    FILE *fp;
    dados_cidade *aux = lista;

    fp = fopen(nome_arq, "w"); 

    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        exit(0);
    }

    fprintf(fp, "Nome da cidade:;");
    fprintf(fp, "Estado:;");
    fprintf(fp, "Renda per capita:;");
    fprintf(fp, "Media renda familiar:;");
    fprintf(fp, "Pessoas entrevistadas:;");
    fprintf(fp, "Quant de filhos < 18:;");
    fprintf(fp, "Quantidade de brancos:;");
    fprintf(fp, "Quantidade de pardos:;");
    fprintf(fp, "Quantidade de pretos:;");
    fprintf(fp, "\n");

    while(aux != NULL){
        if(aux->media_renda_familiar >= inicio && aux->media_renda_familiar <= fim){
                    fprintf(fp, "\n");
                    fprintf(fp, "%s;", aux->nome);
                    fprintf(fp, "%i;", aux->estado_cidade);
                    fprintf(fp, "%.2f;", aux->renda_per_capita);
                    fprintf(fp, "%.2f;", aux->media_renda_familiar);
                    fprintf(fp, "%li;", aux->qtd_entrevistados);
                    fprintf(fp, "%li;", aux->qtd_filhos_menos_18);
                    fprintf(fp, "%li;", aux->qtd_brancos);
                    fprintf(fp, "%li;", aux->qtd_pardos);
                    fprintf(fp, "%li;", aux->qtd_pretos);
                    fprintf(fp, "\n");
        }   
        aux = aux->prox;
    }
    fclose(fp);
}

void salvar_por_renda_pc(dados_cidade* lista, float inicio, float fim, string nome_arq){
    FILE *fp;
    dados_cidade *aux = lista;

    fp = fopen(nome_arq, "w"); 

    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        exit(0);
    }

    while(aux != NULL){
        if(aux->renda_per_capita >= inicio && aux->renda_per_capita <= fim){
                    fprintf(fp, "Nome da cidade............: %s\n", aux->nome);
                    fprintf(fp, "Estado....................: %i\n", aux->estado_cidade);
                    fprintf(fp, "Renda per capita..........: %.2f\n", aux->renda_per_capita);
                    fprintf(fp, "Media renda familiar......: %.2f\n", aux->media_renda_familiar);
                    fprintf(fp, "Pessoas entrevistadas.....: %li\n", aux->qtd_entrevistados);
                    fprintf(fp, "Quant de filhos < 18......: %li\n", aux->qtd_filhos_menos_18);
                    fprintf(fp, "Quantidade de brancos.....: %li\n", aux->qtd_brancos);
                    fprintf(fp, "Quantidade de pardos......: %li\n", aux->qtd_pardos);
                    fprintf(fp, "Quantidade de pretos......: %li\n", aux->qtd_pretos);
                    fprintf(fp, "\n");
        }   
        aux = aux->prox;
    }
    fclose(fp);
}

void salvar_por_cidade(dados_cidade* lista, string nome, int estado, string nome_arq){
    FILE *fp;
    dados_cidade *aux = lista;

    fp = fopen(nome_arq, "w"); 

    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        exit(0);
    }

    while(aux!=NULL){
		if(strcmp(aux->nome, nome) == 0 && aux->estado_cidade == estado){
			fprintf(fp, "Nome da cidade............: %s\n", aux->nome);
            fprintf(fp, "Estado....................: %i\n", aux->estado_cidade);
            fprintf(fp, "Renda per capita..........: %.2f\n", aux->renda_per_capita);
            fprintf(fp, "Media renda familiar......: %.2f\n", aux->media_renda_familiar);
            fprintf(fp, "Pessoas entrevistadas.....: %li\n", aux->qtd_entrevistados);
            fprintf(fp, "Quant de filhos < 18......: %li\n", aux->qtd_filhos_menos_18);
            fprintf(fp, "Quantidade de brancos.....: %li\n", aux->qtd_brancos);
            fprintf(fp, "Quantidade de pardos......: %li\n", aux->qtd_pardos);
            fprintf(fp, "Quantidade de pretos......: %li\n", aux->qtd_pretos);
            fprintf(fp, "\n");
		}
		aux = aux->prox;
	}
    fclose(fp);
}

dados_cidade* localiza_cidade_por_nome_e_estado(dados_cidade* lista, string nome, int estado){
	dados_cidade *aux;
	aux = lista;

	while(aux!=NULL){
		if(strcmp(aux->nome, nome) == 0 && aux->estado_cidade == estado){
			return aux;
		}
		aux = aux->prox;
	}
	return NULL;
}

cidade_excluir excluir_cidade(string nome, dados_cidade *lista){
	cidade_excluir registro_dados;
	dados_cidade *aux, *anterior;

	aux = anterior = lista;

	if (lista == NULL) {
		registro_dados.cidade = NULL;
		registro_dados.anterior = NULL;
	}
	else {
		while (aux) {
			if (!strcmp(aux->nome, nome)) {
				if (aux == lista) {
					registro_dados.cidade = aux;
					registro_dados.anterior = anterior;
					break;
				}
				else {
  				registro_dados.cidade = aux;
					registro_dados.anterior = anterior;
					break;
				}
			}
			anterior = aux;
			aux = aux->prox;
		}
	}
	return registro_dados;
}

void listar_cidade_por_estado(dados_cidade *lista, int estado){
    dados_cidade *aux;
	aux = lista;

	while(aux != NULL){
		if(aux->estado_cidade == estado){
			mostrar_cidade(aux);
		}
		aux = aux->prox;
	}
}

void salvar_cidade_por_estado(dados_cidade *lista, int estado, string nome_arq){
	FILE *fp;
    dados_cidade *aux = lista;

    fp = fopen(nome_arq, "w"); 

    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        exit(0);
    }

	while(aux != NULL){
		if(aux->estado_cidade == estado){
			fprintf(fp, "Nome da cidade............: %s\n", aux->nome);
            fprintf(fp, "Estado....................: %i\n", aux->estado_cidade);
            fprintf(fp, "Renda per capita..........: %.2f\n", aux->renda_per_capita);
            fprintf(fp, "Media renda familiar......: %.2f\n", aux->media_renda_familiar);
            fprintf(fp, "Pessoas entrevistadas.....: %li\n", aux->qtd_entrevistados);
            fprintf(fp, "Quant de filhos < 18......: %li\n", aux->qtd_filhos_menos_18);
            fprintf(fp, "Quantidade de brancos.....: %li\n", aux->qtd_brancos);
            fprintf(fp, "Quantidade de pardos......: %li\n", aux->qtd_pardos);
            fprintf(fp, "Quantidade de pretos......: %li\n", aux->qtd_pretos);
            fprintf(fp, "\n");
		}
		aux = aux->prox;
	}
    fclose(fp);
}

int menu_sim_nao(){
    int opcao;

    printf("\n");
    printf("1.SIM\n");
    printf("2.NAO\n");
    printf("::? ");
    scanf("%i", &opcao);
    getchar();
    printf("\n");

    return opcao;
}

void alterar_dados(dados_cidade* cidade, string nome, int estado, float renda_pc, 
float renda_fam, long int qtd_entrevistados, long int qtd_filhos_menos_18,
long int qtd_brancos, long int qtd_pardos, long int qtd_pretos){

    strcpy(cidade->nome, nome);
    cidade->estado_cidade = estado;
    cidade->renda_per_capita = renda_pc;
    cidade->media_renda_familiar = renda_fam;
    cidade->qtd_entrevistados = qtd_entrevistados;
    cidade->qtd_filhos_menos_18 = qtd_filhos_menos_18;
    cidade->qtd_brancos = qtd_brancos;
    cidade->qtd_pardos = qtd_pardos;
    cidade->qtd_pretos = qtd_pretos;
}

void listar_por_renda_per_capita(dados_cidade* lista, float inicio, float fim){
    dados_cidade* aux = lista;

    while(aux != NULL){
        if(aux->renda_per_capita >= inicio && aux->renda_per_capita <= fim){
            mostrar_cidade(aux);
        }
        aux = aux->prox;
    }
}

void listar_por_renda_familiar(dados_cidade* lista, float inicio, float fim){
    dados_cidade* aux = lista;

    while(aux != NULL){
        if(aux->media_renda_familiar >= inicio && aux->media_renda_familiar <= fim){
            mostrar_cidade(aux);
        }
        aux = aux->prox;
    }
}

int verifica_renda_familiar(dados_cidade* lista, float inicio, float fim){
    dados_cidade* aux = lista;
     while(aux != NULL){
        if(aux->media_renda_familiar >= inicio && aux->media_renda_familiar <= fim){
            return 1;
        }
        aux = aux->prox;
    }
    return -1;
}

int verifica_renda_pc(dados_cidade* lista, float inicio, float fim){
    dados_cidade* aux = lista;
     while(aux != NULL){
        if(aux->renda_per_capita >= inicio && aux->renda_per_capita <= fim){
            return 1;
        }
        aux = aux->prox;
    }
    return -1;
}

int verifica_estado(dados_cidade *lista, int estado){
    dados_cidade *aux;
    aux = lista;
    while(aux != NULL){
		if(aux->estado_cidade == estado){
			return 1;
		}
		aux = aux->prox;
	}
    return -1;
}

int menu_arq_texto(){
    int opc;

	printf("\n");
    printf("1.Prosseguir com visualizacao\n");
	printf("2.Salvar em excel\n");
    printf("0.Voltar\n");
	printf("::? ");
	scanf("%i", &opc);
	getchar();
	printf("\n");

	return opc;
}

int menu_relatorios_estatisticos(){
    int opcao;

    printf("1.Quantidade de filhos menores de 18 na cidade com menor renda familiar\n");
    printf("2.Quantidade de pretos, brancos e pardos na cidade com menor renda per capita\n");
    printf("3.Cidade com a maior renda familiar\n");
    printf("4.Listar as 3 cidades com a maior renda per capita\n");
    printf("5.Listar as 3 cidades com mais pessoas entrevistadas\n");
    printf("0.Voltar ao inicio\n");
    printf("::? ");
    scanf("%i", &opcao);
    getchar();
    printf("\n");

    return opcao;
}

dados_cidade *copia_dados(dados_cidade *lista_original) {
    dados_cidade *copia = NULL;
    dados_cidade *atual_original = lista_original;
    dados_cidade *cidade_nova;

    while (atual_original != NULL) {
        cidade_nova = (dados_cidade *)malloc(sizeof(dados_cidade));
        if (cidade_nova != NULL) {
            strcpy(cidade_nova->nome, atual_original->nome);
            cidade_nova->estado_cidade = atual_original->estado_cidade;
            cidade_nova->renda_per_capita = atual_original->renda_per_capita;
            cidade_nova->media_renda_familiar = atual_original->media_renda_familiar;
            cidade_nova->qtd_entrevistados = atual_original->qtd_entrevistados;
            cidade_nova->qtd_filhos_menos_18 = atual_original->qtd_filhos_menos_18;
            cidade_nova->qtd_brancos = atual_original->qtd_brancos;
            cidade_nova->qtd_pardos = atual_original->qtd_pardos;
            cidade_nova->qtd_pretos = atual_original->qtd_pretos;
            cidade_nova->prox = NULL;
        }
        else{
            printf("Erro: falha na alocacao de memoria.");
        }
        incluir_nova_cidade(&copia, cidade_nova);
        atual_original = atual_original->prox;
    }
    return copia;
}

void bubble_sort_renda_pc(dados_cidade* inicio){
    int trocado;
    dados_cidade* ptr;
    dados_cidade* ptr2 = NULL;

    float renda_pc_alt;
    string nome_alt;
    int qtd_pretos_alt, qtd_brancos_alt, qtd_pardos_alt;

    if(inicio == NULL){
        return;
    }
    do {
        trocado = 0;
        ptr = inicio;

        while (ptr->prox != ptr2) {
            if (ptr->renda_per_capita < ptr->prox->renda_per_capita) {
                renda_pc_alt = ptr->renda_per_capita;
                ptr->renda_per_capita = ptr->prox->renda_per_capita;
                ptr->prox->renda_per_capita = renda_pc_alt;

                strcpy(nome_alt, ptr->nome);
                strcpy(ptr->nome, ptr->prox->nome);
                strcpy(ptr->prox->nome, nome_alt);

                qtd_pretos_alt = ptr->qtd_pretos;
                ptr->qtd_pretos = ptr->prox->qtd_pretos;
                ptr->prox->qtd_pretos = qtd_pretos_alt;

                qtd_brancos_alt = ptr->qtd_brancos;
                ptr->qtd_brancos = ptr->prox->qtd_brancos;
                ptr->prox->qtd_brancos = qtd_brancos_alt;

                qtd_pardos_alt = ptr->qtd_pardos;
                ptr->qtd_pardos = ptr->prox->qtd_pardos;
                ptr->prox->qtd_pardos = qtd_pardos_alt;

                trocado = 1;
            }
            ptr = ptr->prox;
        }
        ptr2 = ptr;
    } while (trocado);
}

void bubble_sort_qtd_entrevistados(dados_cidade* inicio){
    int trocado;
    dados_cidade* ptr;
    dados_cidade* ptr2 = NULL;

    float qtd_entrevistados_alt;
    string nome_alt;

    if(inicio == NULL){
        return;
    }
    do {
        trocado = 0;
        ptr = inicio;

        while (ptr->prox != ptr2) {
            if (ptr->qtd_entrevistados < ptr->prox->qtd_entrevistados) {
                qtd_entrevistados_alt = ptr->qtd_entrevistados;
                ptr->qtd_entrevistados = ptr->prox->qtd_entrevistados;
                ptr->prox->qtd_entrevistados = qtd_entrevistados_alt;

                strcpy(nome_alt, ptr->nome);
                strcpy(ptr->nome, ptr->prox->nome);
                strcpy(ptr->prox->nome, nome_alt);

                trocado = 1;
            }
            ptr = ptr->prox;
        }
        ptr2 = ptr;
    } while (trocado);
}

void listar_cidades_maior_qtd_entrevistados(dados_cidade* lista){
    int i = 0;
    bubble_sort_qtd_entrevistados(lista);
    dados_cidade *aux = lista;
    printf("\nAs 3 cidades com maior numero de entrevistados sao:\n");
    while (aux != NULL && i < 3) {
        printf("%s - %li entrevistados\n", aux->nome, aux->qtd_entrevistados);
        aux = aux->prox;
        i++;
    }
}

void qtd_filhos_menor_cidade_menor_renda(dados_cidade* lista){
    bubble_sort_renda_fam(lista);
    dados_cidade *aux = lista;
    while(aux->prox != NULL){
        aux = aux->prox;
    }

    printf("%s: \n", aux->nome);
    printf("Media renda familiar: %.2f\n", aux->media_renda_familiar);
    printf("Quantidade de filhos menores de 18: %li\n", aux->qtd_filhos_menos_18);
}

void bubble_sort_renda_fam(dados_cidade* inicio){
    int trocado;
    dados_cidade* ptr;
    dados_cidade* ptr2 = NULL;

    float renda_fam_alt;
    string nome_alt;
    int qtd_filhos_menos_18_alt;

    if(inicio == NULL){
        return;
    }
    do {
        trocado = 0;
        ptr = inicio;

        while (ptr->prox != ptr2) {
            if (ptr->media_renda_familiar < ptr->prox->media_renda_familiar) {
                renda_fam_alt = ptr->media_renda_familiar;
                ptr->media_renda_familiar = ptr->prox->media_renda_familiar;
                ptr->prox->media_renda_familiar = renda_fam_alt;

                strcpy(nome_alt, ptr->nome);
                strcpy(ptr->nome, ptr->prox->nome);
                strcpy(ptr->prox->nome, nome_alt);

                qtd_filhos_menos_18_alt = ptr->qtd_filhos_menos_18;
                ptr->qtd_filhos_menos_18 = ptr->prox->qtd_filhos_menos_18;
                ptr->prox->qtd_filhos_menos_18 = qtd_filhos_menos_18_alt;

                trocado = 1;
            }
            ptr = ptr->prox;
        }
        ptr2 = ptr;
    } while (trocado);
}

void listar_cidades_maior_rendapc(dados_cidade* lista){
    int i = 0;
    bubble_sort_renda_pc(lista);
    dados_cidade *aux = lista;
    printf("\nAs 3 cidades com maior renda per capita sao:\n");
    while (aux != NULL && i < 3) {
        printf("%s - %.2f\n", aux->nome, aux->renda_per_capita);
        aux = aux->prox;
        i++;
    }
}

void qtd_p_e_b_cidade_menor_rendapc(dados_cidade* lista){
    bubble_sort_renda_pc(lista);
    dados_cidade *aux = lista;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
        printf("%s: \n", aux->nome);
        printf("Quantidade de Brancos: %li\n", aux->qtd_brancos);
        printf("Quantidade de Pardos: %li\n", aux->qtd_pardos);
        printf("Quantidade de Pretos: %li\n", aux->qtd_pretos);
}

void salvar_relatorio1(dados_cidade* lista, string nome_arq){
    FILE *fp;
    bubble_sort_renda_fam(lista);
    dados_cidade *aux = lista;

    fp = fopen(nome_arq, "w"); 

    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        exit(0);
    }
    while(aux->prox != NULL){
        aux = aux->prox;
    }

    fprintf(fp, "%s: \n", aux->nome);
    fprintf(fp, "Media renda familiar: %.2f\n", aux->media_renda_familiar);
    fprintf(fp, "Quantidade de filhos menores de 18: %li\n", aux->qtd_filhos_menos_18);
    fprintf(fp, "\n");

    fclose(fp);
}

void salvar_relatorio2(dados_cidade* lista, string nome_arq){
    FILE *fp;
    bubble_sort_renda_pc(lista);
    dados_cidade *aux = lista;

    fp = fopen(nome_arq, "w"); 

    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        exit(0);
    }
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    fprintf(fp, "%s: \n", aux->nome);
    fprintf(fp, "Quantidade de Brancos: %li\n", aux->qtd_brancos);
    fprintf(fp, "Quantidade de Pardos: %li\n", aux->qtd_pardos);
    fprintf(fp, "Quantidade de Pretos: %li\n", aux->qtd_pretos);

    fclose(fp);
}

void salvar_relatorio3(dados_cidade* lista, string nome_arq){
    FILE *fp;
    bubble_sort_renda_fam(lista);
    dados_cidade *aux = lista;

    fp = fopen(nome_arq, "w"); 

    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        exit(0);
    }

    fprintf(fp, "\nCidade com maior renda familiar:\n");
    fprintf(fp, "%s - %.2f\n", aux->nome, aux->media_renda_familiar);
    fprintf(fp, "\n");

    fclose(fp);
}

void salvar_relatorio4(dados_cidade* lista, string nome_arq){
    FILE *fp;
    int i = 0;
    bubble_sort_renda_pc(lista);
    dados_cidade *aux = lista;

    fp = fopen(nome_arq, "w"); 

    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        exit(0);
    }

    fprintf(fp, "\nAs 3 cidades com maior renda per capita sao:\n");
    while (aux != NULL && i < 3) {
        fprintf(fp, "%s - %.2f\n", aux->nome, aux->renda_per_capita);
        aux = aux->prox;
        i++;
    }

    fclose(fp);
}

void salvar_relatorio5(dados_cidade* lista, string nome_arq){
    FILE *fp;
    int i = 0;
    bubble_sort_qtd_entrevistados(lista);
    dados_cidade *aux = lista;

    fp = fopen(nome_arq, "w"); 

    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        exit(0);
    }
    fprintf(fp, "\nAs 3 cidades com maior numero de entrevistados sao:\n");
    while (aux != NULL && i < 3) {
        fprintf(fp, "%s - %li entrevistados\n", aux->nome, aux->qtd_entrevistados);
        aux = aux->prox;
        i++;
    }
    fclose(fp);
}
