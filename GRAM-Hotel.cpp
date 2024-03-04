/* GRAM-Hotel-01
Manoela Macchion Martedi, Rafael Cabral, Arthur Bretas, Gustavo Kikuchi */

/*
REQ01-O programa deve permitir ao usuario visualizar a ocupacao dos apartamentos do hotel (mapa geral). 
REQ02-O programa deve permitir ao usuario fazer a reserva de um apartamento. 
REQ03-O programa deve permitir ao usuario realizar o checkin no hotel a partir de uma reserva realizada.
REQ04-O programa deve permitir ao usuario realizar o checkin no hotel de hospede que nao fez reserva.
REQ05-O programa deve permitir ao usuario realizar o checkout, ou seja, liberar o apartamento que estava ocupado.
REQ06-O programa deve permitir ao usuario cancelar uma reserva.
REQ07-O programa deve permitir ao usuario visualizar a as taxas de ocupacao e de reservas do hotel. 
REQ08-O programa deve permitir ao usuario cadastrar as informacoes do hospede (CPF, nome, endereco completo, telefone celular e e-mail) no checkin. 
REQ09-O programa deve permitir ao usuario visualizar a situacao de um apto. especifico, e caso esteja ocupado, todas as informações do hospede.

PRAZO 01 - 02/06
	1. Impressao do mapa
	2. Reserva do apartamento
		- fReserva >> entra com o nome e atualiza o valor do mapa do hotel
	3. Check in com reserva
		- fCheckIn >> se o caractere na posicao desejada for diferente de 'R', a reserva nao pode ser feita 

PRAZO 02- 09/06
	4. Checkin mesmo sem reserva
		- fCheckImediato >> apenas funciona com apartamentos vazios, sem reserva
	5. Checkout de apartamentos ocupados
		- fCheckOut >> apenas funciona com apartamentos com 'O'
	6. Cancelar reserva
		- fCancelar >> apenas funciona com apartamentos com 'R'
*/

#include <iostream>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define ANDAR 20
#define APT 14

//==================================================================

void fClear (); //limpa o buffer
void fTitulo (); //mostra o nome do hotel
void fMapa(); //visualizacao da ocupacao dos apartamentos do hotel
void fReserva(); //reserva um apartamento
void fCheckIn(); //faz check in em um apartamento COM reserva
void fCheckImediato(); //faz check in em um apartamento SEM reserva
void fCancelar(); //cancela uma reserva feita
void fCheckOut(); //faz check out de um apartamento
void fCadastro (int andar, int apto); //faz cadastro de um novo usuario
int fChecarCadastro(); //checa se existe cadastro naquele CPF
void fSituApt(); //visualiza a situacao de um apt e as informacoes do hospede
void fTaxa(); //calcula e imprime as taxas de ocupacao e reserva do hotel
int fMenu (); //visualizacao do menu

//==================================================================

typedef struct cliente //estrutura de dados para os clientes
{
	char CPF[12];
	char nome[50];
	char email[40];
	char telefone[15];
	char ender[60];
	
	float valorHosped;
	
} tipoCliente; //estrutura armazenada no tipo cliente

typedef struct apartamentos
{
	char status; //'O' = ocupado 'R' = reservado '.' = livre
	tipoCliente cliente; //cliente, do tipo tipoCliente, armazenado em cada apartamento
	
} tipoAptos; //estrutura armazenada no tipo aptos

//==================================================================

tipoAptos hotel[ANDAR][APT]; //inicializando a matriz hotel
int qtdClientes = 0; //inicializando a quantidade de clientes como 0 
int qtdReservas = 0; //inicializando a quantidade de reservas como 0 
int qtdOcupacoes = 0; //inicializando a quantidade de ocupacoes como 0 
int checkAndar, checkApto; //usadas para checar se ja existe cadastro (se sim, qual o andar e apartamento)

//==================================================================

main ()
{
	//----------------------------------------------------
	
	int i, j, opcMenu;
	
	//----------------------------------------------------
	
	//gerar tabela inicial
	for (i = 0; i < ANDAR; i++)
		for (j = 0; j < APT; j++)
			hotel[i][j].status = '.';
	
	//----------------------------------------------------
	
	fTitulo (); //imprime titulo
	
	do
	{
		
		putchar('\n');
		
		opcMenu = fMenu(); //guarda a opcao escolhida pelo usuario
		
		switch(opcMenu) //opcao para cada saida do menu
		{
			case 1: //mostrar mapa
				system("cls");
				fTitulo();
				fMapa();
				break;
			case 2: //reserva
				system("cls");
				fTitulo();
				fMapa();
				fReserva();
				break;
			case 3: //ocupacao
				system("cls");
				fTitulo();
				fMapa();
				fCheckIn();
				break;
			case 4: //ocupacao sem reserva
				system("cls");
				fTitulo();
				fMapa();
				fCheckImediato();
				break;
			case 5: //cancelar reserva
				system("cls");
				fTitulo();
				fMapa();
				fCancelar();
				break;
			case 6: //checkout
				system("cls");
				fTitulo();
				fMapa();
				fCheckOut();
				break;
			case 7: //situacao apt
				system("cls");
				fTitulo();
				fMapa();
				fSituApt();
				break;
			case 8: //taxa
				system("cls");
				fTitulo();
				fMapa();
				fTaxa();
				break;
			case 0: //sair do programa
				break;
			default:
				printf("Opcao invalida.\n\n");
				break;
		}
		
	} while (opcMenu != 0); //condicao de parada
	
	//----------------------------------------------------
	
	//fim main
	
}

//==================================================================

void fTitulo () //visualizacao do titulo
{
	
	printf("============================================================================================================\n");
	
	printf(" ________  ________  ________  _____ ______           ___  ___  ________  _________  _______   ___\n");
	printf("|\\   ____\\|\\   __  \\|\\   __  \\|\\   _ \\  _   \\        |\\  \\|\\  \\|\\   __  \\|\\___   ___\\\\  ___ \\ |\\  \\ \n");
	printf("\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\       \\ \\  \\\\\\  \\ \\  \\|\\  \\|___ \\  \\_\\ \\   __/|\\ \\  \\ \n");
	printf(" \\ \\  \\  __\\ \\   _  _\\ \\   __  \\ \\  \\\\|__| \\  \\       \\ \\   __  \\ \\  \\\\\\  \\   \\ \\  \\ \\ \\  \\_|/_\\ \\  \\ \n");
	printf("  \\ \\  \\|\\  \\ \\  \\\\  \\\\ \\  \\ \\  \\ \\  \\    \\ \\  \\       \\ \\  \\ \\  \\ \\  \\\\\\  \\   \\ \\  \\ \\ \\  \\_|\\ \\ \\  \\____ \n");
	printf("   \\ \\_______\\ \\__\\\\ _\\\\ \\__\\ \\__\\ \\__\\    \\ \\__\\       \\ \\__\\ \\__\\ \\_______\\   \\ \\__\\ \\ \\_______\\ \\_______\\ \n");
	printf("    \\|_______|\\|__|\\|__|\\|__|\\|__|\\|__|     \\|__|        \\|__|\\|__|\\|_______|    \\|__|  \\|_______|\\|_______|\n");
		
	printf("\n============================================================================================================\n");
	
}

//==================================================================

void fMapa() //mostra a tabela de andares
{
	
	int i, j;
	
	printf("\n    +------------------------------------------------------+");
	
	printf("\n    |   APTOS   ");
	
	for (j = 0; j < APT; j++)
	{
		printf("%2d ", j+1);
		if (j == 13)
			printf(" |");
	}
	
	printf("\n    |\t\t\t\t\t\t           |\n");
	
	for (i = ANDAR-1; i >= 0; i--)
		{
		printf("    |Andar %2d   ", i+1);
	
		for (j = 0; j < APT; j++)
			{
			printf(" %c ", hotel[i][j].status);
			if (j==APT-1)
				printf(" |");
			}
			
		printf("\n");
		}
	
	printf("    +------------------------------------------------------+\n\n");
	
}

//==================================================================

int fMenu() //visualizacao do menu
{
	int opc;

	printf("\n+-------------------------------------------------------+\n");
	printf("| \t      Seja bem vindo ao Gram Hotel! \t\t| \n");
	printf("| 1. Mostrar mapa. \t\t           \t\t|\n");
	printf("| 2. Reserva de quartos. \t        \t\t|\n");
	printf("| 3. Ocupacao de quartos reservados. \t\t\t|\n");
	printf("| 4. Ocupacao sem reserva. \t          \t\t|\n");
	printf("| 5. Cancelar reserva. \t\t          \t\t|\n");
	printf("| 6. Check out. \t\t          \t\t|\n");
	printf("| 7. Visualizar situacao de um apartamento.\t\t|\n");
	printf("| 8. Taxa de ocupacao do GRAM. \t        \t\t|\n");
	printf("| \t    Digite '0' para sair do programa.       \t|");
	printf("\n+-------------------------------------------------------+\n\n");

	printf("Digite uma opcao: ");
	scanf("%d", &opc);

	return(opc);
}

//==================================================================

void fCadastro(char cpf[12], int andar, int apto)
{
	
	system("cls");
	fTitulo();
	char checkS[2]; //string para armazenar a resposta do cliente posteriormente
	
	printf("\t\t+---------------------+\n");
	printf("\t\t|    Novo Cadastro    |\n");
	printf("\t\t+---------------------+\n\n");
	
	while (1)
	{
		fflush(stdin);
		
		printf("Como devemos chama-lo, usuario? "); 
		gets(hotel[andar][apto].cliente.nome); //armazena o nome de usuario
	
		if (hotel[andar][apto].cliente.nome[0] == '\0') //caso o usuario nao tenha escrito nome
		{
			printf("Digite um nome.\n");
			continue;
		}
		
		break;
	}
	
	while (1)
	{
		fflush(stdin);
		
		printf("Digite um numero de telefone com DDD: "); //armazena o telefone do usuario
		gets(hotel[andar][apto].cliente.telefone);
	
		if (strlen(hotel[andar][apto].cliente.telefone) > 12 || strlen(hotel[andar][apto].cliente.telefone) < 10)
		{
			printf("Numero invalido.\n");
			continue;
		}
		
		break;
	}
	
	while (1)
	{
		fflush(stdin);
		
		printf("Deseja cadastrar usando o CPF de numero %s? (s/n)\n", cpf); //verifica o cpf para cadastro
		gets(checkS);
		
		checkS[0] = toupper(checkS[0]);
		
		if (checkS[0] == 'S') //sim
			break;
		else if (checkS[0] == 'N') //nao
		{
			fflush(stdin); //limpa o buffer
		
			printf("Digite seu CPF: ");
			gets(cpf);
		
			if (strlen(cpf) != 11)
			{
				printf("CPF invalido.\n");
				continue;
			}
			
			break;
		}
		else
		{
			printf("Resposta invalida.\n");
			continue;
		}
	}
	
	strcpy(hotel[andar][apto].cliente.CPF, cpf); //copia a string cpf em hotel[andar][apto].cliente.cpf
	
	while (1)
	{
		fflush(stdin);
		
		printf("Digite seu endereco: "); //endereco
		gets(hotel[andar][apto].cliente.ender);
	
		if (hotel[andar][apto].cliente.ender[0] == '\0')
		{
			printf("Endereco invalido.\n");
			continue;
		}
		
		break;
	}
	
	while (1)
	{
		fflush(stdin);
		
		printf("Digite um email para contato: "); //email
		gets(hotel[andar][apto].cliente.email);
	
		if (hotel[andar][apto].cliente.email[0] == '\0')
		{
			printf("Endereco de email invalido.\n");
			continue;
		}
		
		break;
	}
	
	printf("\nProcessando cadastro");
	
	for (int i = 0; i < 3; i++)
	{
		sleep(1); //"pausa" para, depois, printar os .
		printf(".");
	}
	
	sleep(3); //pausa de 3 segundos
	
	printf("\n");
	
    qtdClientes++; //aumenta a quantidade total de cadastros
	
	system("cls");
	fTitulo();
	
	printf("\tUsuario de nome %s cadastrado com sucesso!\n\n", hotel[andar][apto].cliente.nome);
	
	sleep(2);
	
	return;
	
}

//==================================================================

int fChecarCadastro(char cpf[12])
{
	
	for (int i = 0; i < ANDAR; i++)
	{
		for (int j = 0; j < APT; j++)
		{
			if (hotel[i][j].status != '.')
			{
				if (strcmp(hotel[i][j].cliente.CPF, cpf) == 0) 
					{
						checkAndar = i;
						checkApto = j;
						return(1); //se 1, significa que ha reserva
					}
			}
		}
	}
	
	//checa em cada andar e apartamento, ate encontrar um igual
	
	return(0); //se 0, nao ha reserva
	
}

//==================================================================

void fReserva() //reserva um apartamento
{
	int nAndar, nApt, checkI;
	char checkS[2];
	char cpf[12];
		
	do
	{
		printf("\nDigite o andar de reserva (0 para voltar ao menu principal): ");
		scanf("%d", &nAndar);
		
		if (nAndar == 0)
			return;
		else if (nAndar < 1 || nAndar > ANDAR) //andar fora dos limites estabelecidos
			{
				printf("Andar invalido.\n");
				continue;
			}
				
		nAndar--; //indice iniciado como zero	
		
		break; //sai da repeticao
		
	} while (1); //enquanto verdadeiro

	do
	{
		printf("\nDigite o apartamento de sua preferencia (0 para voltar ao menu principal): ");
		scanf("%d", &nApt);
		
		if (nApt == 0)
			return;
		else if (nApt < 1 || nApt > APT) //fora dos limites estabelecidos
		{
			printf("Apartamento invalido.\n");
			continue;
		}

		nApt--; //indice iniciado como zero

		if (hotel[nAndar][nApt].status == 'R') //se ja houver reserva neste apartamento
		{
			printf("Apartamento ja reservado.\n\nInformacoes da reserva:\nNome: %s\nCPF: %s\n", hotel[nAndar][nApt].cliente.nome, hotel[nAndar][nApt].cliente.CPF);
			return;
		}
		else if (hotel[nAndar][nApt].status == 'O') //se ja houver ocupacao neste apartamento
		{
			printf("Apartamento ja ocupado.\n\nInformacoes da ocupacao:\nNome: %s\nCPF: %s\n", hotel[nAndar][nApt].cliente.nome, hotel[nAndar][nApt].cliente.CPF);
			return;
		}
			
		break; //quebra do ciclo

	} while (1); //verdadeiro 
	
	do
	{
		fflush(stdin);
		
		printf("\nDigite seu CPF (0 para voltar ao menu principal): "); //digitar o cpf
		gets(cpf);
		
		if (cpf[0] == '0')
			return;
		else if (strlen(cpf) != 11)
		{
			printf("\nCPF invalido.");
			continue;
		}
		
		break;
		
	} while (1);
	
	checkI = fChecarCadastro(cpf); //checa se existe cadastro
	
	system("cls");
	fTitulo();
	fMapa();
	
	if (checkI == 0)
	{
		while (1)
		{
			
			fflush(stdin);
			
			printf("Usuario de CPF %s nao cadastrado.\nDeseja realizar o cadastro? (s/n)\n", cpf);
			gets(checkS);
			
			if (checkS[0] == 's')
				fCadastro(cpf, nAndar, nApt);
			else if (checkS[0] == 'n')
			{
				system("cls");
				fMapa();
				return;
			}
			else
			{
				printf("Resposta invalida.\n");
				continue;
			}
			
			break;
		}
	}
	else
		hotel[nAndar][nApt].cliente = hotel[checkAndar][checkApto].cliente; 
		
	//checkAndar e checkApto armazenam o andar e apartamento no qual ha o cadastro deste cliente.
	
	printf("\n\t%s // CPF: %s\n\n", hotel[nAndar][nApt].cliente.nome, hotel[nAndar][nApt].cliente.CPF);

	hotel[nAndar][nApt].status = 'R'; //alterando o valor para reservado
	
	qtdReservas++; //aumento na quantidade total de reservas
	
	system("cls");
	
	fTitulo(); fMapa();
	
	printf("Realizada reserva no andar %d, apartamento %d para %s.\n", nAndar+1, nApt+1, hotel[nAndar][nApt].cliente.nome);
	
	return;
	
}

//==================================================================

void fCheckIn() //check in do apartamento
{
	int nAndar, nApt, checkI;
	char checkS[2];
	char cpf[12];
		
	do
	{
		printf("\nDigite o andar para check in (0 para voltar ao menu principal): ");
		scanf("%d", &nAndar);
		
		if (nAndar == 0)
			return;
		else if (nAndar < 1 || nAndar > ANDAR) //andar fora dos limites estabelecidos
			{
				printf("Andar invalido.\n");
				continue;
			}
				
		nAndar--; //indice iniciado como zero	
		
		break; //sai da repeticao
		
	} while (1); //enquanto verdadeiro

	do
	{
		printf("\nDigite o apartamento de sua preferencia (0 para voltar ao menu principal): ");
		scanf("%d", &nApt);
		
		if (nApt == 0)
			return;
		else if (nApt < 1 || nApt > APT) //fora dos limites estabelecidos
		{
			printf("Apartamento invalido.\n");
			continue;
		}

		nApt--; //indice iniciado como zero

		if (hotel[nAndar][nApt].status == '.') //se nao houver reserva neste apartamento
		{
			printf("Apartamento vazio.\n");
			return;
		}
		else if (hotel[nAndar][nApt].status == 'O') //se ja houver ocupacao neste apartamento
		{
			printf("Apartamento ja ocupado.\n\nInformacoes da ocupacao:\nNome: %s\nCPF: %s\n", hotel[nAndar][nApt].cliente.nome, hotel[nAndar][nApt].cliente.CPF);
			return;
		}
			
		break; //quebra do ciclo

	} while (1); //verdadeiro 
	
	do
	{
		fflush(stdin);
		
		printf("\nDigite seu CPF (0 para voltar ao menu principal): ");
		gets(cpf);
		
		if (cpf[0] == '0')
			return;
		else if (strlen(cpf) != 11)
		{
			printf("\nCPF invalido.");
			continue;
		}
		
		break;
		
	} while (1);
	
	system("cls");
	fTitulo();
	fMapa();
	
	checkI = fChecarCadastro(cpf);
	
	if (checkI == 0)
	{
		printf("Nao existe cadastro no CPF %s.\n", cpf); //aqui, nao e realizado o cadastro novo.
		return;
	}
	
	printf("\n\t%s // CPF: %s\n\n", hotel[checkAndar][checkApto].cliente.nome, hotel[checkAndar][checkApto].cliente.CPF);
	
	if (strcmp(hotel[checkAndar][checkApto].cliente.CPF, hotel[nAndar][nApt].cliente.CPF) != 0) //se as strings forem diferentes
	{
		printf("O apartamento %d, andar %d nao esta cadastrado em nome de %s.", nApt+1, nAndar+1, hotel[checkAndar][checkApto].cliente.nome);
		return;
	}
	
	hotel[nAndar][nApt].cliente = hotel[checkAndar][checkApto].cliente;

	hotel[nAndar][nApt].status = 'O'; //alterando o valor para ocupado
	
	qtdOcupacoes++;
	qtdReservas--; //aumentam as ocupacoes, mas diminuem as reservas
	
	system("cls");
	
	fTitulo(); fMapa();
	
	printf("Check in realizado no andar %d, apartamento %d para %s.\n", nAndar+1, nApt+1, hotel[nAndar][nApt].cliente.nome);
	
	return;

}

//==================================================================

void fCheckImediato() //check in em apartamento SEM reserva
{
	int nAndar, nApt, checkI;
	char checkS[2];
	char cpf[12];
		
	do
	{
		printf("\nDigite o andar de check in (0 para voltar ao menu principal): ");
		scanf("%d", &nAndar);
		
		if (nAndar == 0)
			return;
		else if (nAndar < 1 || nAndar > ANDAR) //andar fora dos limites estabelecidos
			{
				printf("Andar invalido.\n");
				continue;
			}
				
		nAndar--; //indice iniciado como zero	
		
		break; //sai da repeticao
		
	} while (1); //enquanto verdadeiro

	do
	{
		printf("\nDigite o apartamento de sua preferencia (0 para voltar ao menu principal): ");
		scanf("%d", &nApt);
		
		if (nApt == 0)
			return;
		else if (nApt < 1 || nApt > APT) //fora dos limites estabelecidos
		{
			printf("Apartamento invalido.\n");
			continue;
		}

		nApt--; //indice iniciado como zero

		if (hotel[nAndar][nApt].status == 'R') //se ja houver reserva neste apartamento
		{
			printf("Apartamento ja reservado.\n\nInformacoes da reserva:\nNome: %s\nCPF: %s\n", hotel[nAndar][nApt].cliente.nome, hotel[nAndar][nApt].cliente.CPF);
			return;
		}
		else if (hotel[nAndar][nApt].status == 'O') //se ja houver ocupacao neste apartamento
		{
			printf("Apartamento ja ocupado.\n\nInformacoes da ocupacao:\nNome: %s\nCPF: %s\n", hotel[nAndar][nApt].cliente.nome, hotel[nAndar][nApt].cliente.CPF);
			return;
		}
			
		break; //quebra do ciclo

	} while (1); //verdadeiro 
	
	do
	{
		fflush(stdin);
		
		printf("\nDigite seu CPF (0 para voltar ao menu principal): ");
		gets(cpf);
		
		if (cpf[0] == '0')
			return;
		else if (strlen(cpf) != 11)
		{
			printf("\nCPF invalido.");
			continue;
		}
		
		break;
		
	} while (1);
	
	checkI = fChecarCadastro(cpf);
	
	system("cls");
	fTitulo();
	fMapa();
	
	if (checkI == 0)
	{
		while (1)
		{
			fflush(stdin);
			
			printf("Usuario de CPF %s nao cadastrado.\nDeseja realizar o cadastro? (s/n)\n", cpf);
			scanf(checkS);
			
			if (checkS[0] == 's')
				fCadastro(cpf, nAndar, nApt);
			else if (checkS[0] == 'n')
			{
				system("cls");
				fMapa();
				return;
			}
			else
			{
				printf("Resposta invalida.\n");
				continue;
			}
			
			break;
		}
	}
	else
		hotel[nAndar][nApt].cliente = hotel[checkAndar][checkApto].cliente;
	
	printf("\n\t%s // CPF: %s\n\n", hotel[checkAndar][checkApto].cliente.nome, hotel[checkAndar][checkApto].cliente.CPF);

	hotel[nAndar][nApt].status = 'O'; //alterando o valor para ocupado
	
	qtdOcupacoes++;
	
	system("cls");
	
	fTitulo(); fMapa();
	
	printf("Check in realizado no andar %d, apartamento %d para %s.\n", nAndar+1, nApt+1, hotel[nAndar][nApt].cliente.nome);
	
	return;
	
}

//==================================================================

void fCancelar() //cancela uma reserva feita
{
	int nAndar, nApt, checkI;
	char checkS[2];
	char cpf[12];
		
	do
	{
		printf("\nDigite o andar para cancela (0 para voltar ao menu principal): ");
		scanf("%d", &nAndar);
		
		if (nAndar == 0)
			return;
		else if (nAndar < 1 || nAndar > ANDAR) //andar fora dos limites estabelecidos
			{
				printf("Andar invalido.\n");
				continue;
			}
				
		nAndar--; //indice iniciado como zero	
		
		break; //sai da repeticao
		
	} while (1); //enquanto verdadeiro

	do
	{
		printf("\nDigite o apartamento para cancela (0 para voltar ao menu principal): ");
		scanf("%d", &nApt);
		
		if (nApt == 0)
			return;
		else if (nApt < 1 || nApt > APT) //fora dos limites estabelecidos
		{
			printf("Apartamento invalido.\n");
			continue;
		}

		nApt--; //indice iniciado como zero

		if (hotel[nAndar][nApt].status == '.') //se nao houver reserva neste apartamento
		{
			printf("Apartamento vazio.\n");
			return;
		}
		else if (hotel[nAndar][nApt].status == 'O') //se ja houver ocupacao neste apartamento
		{
			printf("Apartamento ja ocupado.\n\nInformacoes da ocupacao:\nNome: %s\nCPF: %s\n", hotel[nAndar][nApt].cliente.nome, hotel[nAndar][nApt].cliente.CPF);
			return;
		}
			
		break; //quebra do ciclo

	} while (1); //verdadeiro 
	
	do
	{
		fflush(stdin);
		
		printf("\nDigite seu CPF (0 para voltar ao menu principal): ");
		gets(cpf);
		
		if (cpf[0] == '0')
			return;
		else if (strlen(cpf) != 11)
		{
			printf("\nCPF invalido.");
			continue;
		}
		
		break;
		
	} while (1);
	
	system("cls");
	fTitulo();
	fMapa();
	
	checkI = fChecarCadastro(cpf);
	
	if (checkI == 0)
	{
		printf("Nao existe cadastro no CPF %s.\n", cpf);
		return;
	}
	
	printf("\n\t%s // CPF: %s\n\n", hotel[checkAndar][checkApto].cliente.nome, hotel[checkAndar][checkApto].cliente.CPF);
	
	if (strcmp(hotel[checkAndar][checkApto].cliente.CPF, hotel[nAndar][nApt].cliente.CPF) != 0)
	{
		printf("O apartamento %d, andar %d nao esta cadastrado em nome de %s.", nApt+1, nAndar+1, hotel[checkAndar][checkApto].cliente.nome);
		return;
	}

	hotel[nAndar][nApt].status = '.'; //alterando o valor para ocupado
	
	qtdReservas--;
	
	system("cls");
	
	fTitulo(); fMapa();
	
	printf("Reserva no andar %d, apartamento %d para %s cancelada.\n", nAndar+1, nApt+1, hotel[nAndar][nApt].cliente.nome);
	
	return;

}

//==================================================================

void fCheckOut() //check out em apartamento
{
	int nAndar, nApt, checkI;
	char checkS[2];
	char cpf[12];
		
	do
	{
		printf("\nDigite o andar para checkout (0 para voltar ao menu principal): ");
		scanf("%d", &nAndar);
		
		if (nAndar == 0)
			return;
		else if (nAndar < 1 || nAndar > ANDAR) //andar fora dos limites estabelecidos
			{
				printf("Andar invalido.\n");
				continue;
			}
				
		nAndar--; //indice iniciado como zero	
		
		break; //sai da repeticao
		
	} while (1); //enquanto verdadeiro

	do
	{
		printf("\nDigite o apartamento para checkout (0 para voltar ao menu principal): ");
		scanf("%d", &nApt);
		
		if (nApt == 0)
			return;
		else if (nApt < 1 || nApt > APT) //fora dos limites estabelecidos
		{
			printf("Apartamento invalido.\n");
			continue;
		}

		nApt--; //indice iniciado como zero

		if (hotel[nAndar][nApt].status == '.') //se nao houver reserva neste apartamento
		{
			printf("Apartamento vazio.\n");
			return;
		}
		else if (hotel[nAndar][nApt].status == 'R') //se ja houver ocupacao neste apartamento
		{
			printf("Apartamento apenas reservado.\n\nInformacoes da reserva:\nNome: %s\nCPF: %s\n", hotel[nAndar][nApt].cliente.nome, hotel[nAndar][nApt].cliente.CPF);
			return;
		}
			
		break; //quebra do ciclo

	} while (1); //verdadeiro 
	
	do
	{
		fflush(stdin);
		
		printf("\nDigite seu CPF (0 para voltar ao menu principal): ");
		gets(cpf);
		
		if (cpf[0] == '0')
			return;
		else if (strlen(cpf) != 11)
		{
			printf("\nCPF invalido.");
			continue;
		}
		
		break;
		
	} while (1);
	
	system("cls");
	fTitulo();
	fMapa();
	
	checkI = fChecarCadastro(cpf);
	
	if (checkI == 0)
	{
		printf("Nao existe cadastro no CPF %s.\n", cpf);
		return;
	}
	
	printf("\n\t%s // CPF: %s\n\n", hotel[checkAndar][checkApto].cliente.nome, hotel[checkAndar][checkApto].cliente.CPF);
	
	if (strcmp(hotel[checkAndar][checkApto].cliente.CPF, hotel[nAndar][nApt].cliente.CPF) != 0)
	{
		printf("O apartamento %d, andar %d nao esta ocupado em nome de %s.", nApt+1, nAndar+1, hotel[checkAndar][checkApto].cliente.CPF);
		return;
	}

	hotel[nAndar][nApt].status = '.'; //alterando o valor para ocupado
	
	qtdOcupacoes--;
	
	system("cls");
	
	fTitulo(); fMapa();
	
	printf("Checkout no andar %d, apartamento %d para %s feito com sucesso.\n", nAndar+1, nApt+1, hotel[nAndar][nApt].cliente.nome);
	
	return;

}

//==================================================================

void fTaxa()
{
	char check[2];
	float taxa;
	
	system("cls");
	fTitulo();
	fMapa();
	
	taxa = (qtdOcupacoes/(float)(ANDAR*APT))*100; //ocupacoes divididas pelo total de apartamentos vezes 100
	printf("A taxa de ocupacao do GRAM e de %.2f%%.\n", taxa);
	
	taxa = (qtdReservas/(float)(ANDAR*APT))*100; //reservas divididas pelo total de apartamentos vezes 100
	printf("A taxa de reservas e de %.2f%%.\n", taxa);
	
	return;

}

//==================================================================

void fSituApt()
{
	int nAndar, nApt;
		
	do
	{
		printf("\nDigite um andar (0 para voltar ao menu principal): ");
		scanf("%d", &nAndar);
		
		if (nAndar == 0)
			return;
		else if (nAndar < 1 || nAndar > ANDAR) //andar fora dos limites estabelecidos
			{
				printf("Andar invalido.\n");
				continue;
			}
				
		nAndar--; //indice iniciado como zero	
		
		break; //sai da repeticao
		
	} while (1); //enquanto verdadeiro

	do
	{
		printf("\nDigite um apartamento (0 para voltar ao menu principal): ");
		scanf("%d", &nApt);
		
		if (nApt == 0)
			return;
		else if (nApt < 1 || nApt > APT) //fora dos limites estabelecidos
		{
			printf("Apartamento invalido.\n");
			continue;
		}
		
		break;
		
	} while (1); //verdadeiro 

		nApt--; //indice iniciado como zero

		if (hotel[nAndar][nApt].status == 'R') //houver reserva neste apartamento
		{
			printf("\nApartamento reservado.\n\nInformacoes da reserva:\nNome: %s\nCPF: %s\nEndereco: %s\nTelefone: %s\nEmail: %s\n\n", hotel[nAndar][nApt].cliente.nome, hotel[nAndar][nApt].cliente.CPF, hotel[nAndar][nApt].cliente.ender, hotel[nAndar][nApt].cliente.telefone, hotel[nAndar][nApt].cliente.email);
			return;
		}
		else if (hotel[nAndar][nApt].status == 'O') //houver ocupacao neste apartamento
		{
			printf("\nApartamento ocupado.\n\nInformacoes da ocupacao:\nNome: %s\nCPF: %s\nEndereco: %s\nTelefone: %s\nEmail: %s\n\n", hotel[nAndar][nApt].cliente.nome, hotel[nAndar][nApt].cliente.CPF, hotel[nAndar][nApt].cliente.ender, hotel[nAndar][nApt].cliente.telefone, hotel[nAndar][nApt].cliente.email);
			return;
		}
		else
		{
			printf("\nApartamento vazio.\n\n");
		}
		
	return;
			
}

//==================================================================

/* /////////////////////////////////

void fClear ()
{
	char carac;
	while ((carac = fgetc(stdin)) != EOF && carac != '\n') {}
}

///////////////////////////////// */

//==================================================================
