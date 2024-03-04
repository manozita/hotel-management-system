/* GRAM-Hotel-01
Manoela Macchion Martedi, Rafael Cabral, Arthur Bretas, Gustavo Kikuchi */

/*
•REQ01-O programa deve permitir ao usuário visualizar a ocupação dos apartamentos do hotel (mapa geral). 
•REQ02-O programa deve permitir ao usuário fazer a reserva de um apartamento. 
•REQ03-O programa deve permitir ao usuário realizar o checkin no hotel a partir de uma reserva realizada.
•REQ04-O programa deve permitir ao usuário realizar o checkin no hotel de hospede que não fez reserva.
•REQ05-O programa deve permitir ao usuário realizar o checkout, ou seja, liberar o apartamento que estava ocupado.
•REQ06-O programa deve permitir ao usuário cancelar uma reserva.
•REQ07-O programa deve permitir ao usuário visualizar a as taxas de ocupação e de reservas do hotel. 
•REQ08-O programa deve permitir ao usuário cadastrar as informações do hospede (CPF, nome, endereço completo, telefone celular e e-mail) no checkin. 
•REQ09-O programa deve permitir ao usuário visualizar a situação de um apto. específico, e caso esteja ocupado, todas as informações do hospede.

PRAZO 01 - 02/06
	1. Impressao do mapa
	2. Reserva do apartamento
		- fReserva >> entra com o nome e atualiza o valor do mapa do hotel
	3. Check in com reserva
		- fCheckIn >> se o caractere na posicao desejada for diferente de 'R', a reserva nao pode ser feita 
		
*/

#include <iostream>

void fTitulo (); //mostra o nome do hotel
void fMapa(char apt[20][14]); //visualizacao da ocupacao dos apartamentos do hotel
void fReserva(char apt[20][14]); //reserva um apartamento
void fCheckIn(char apt[20][14]); //faz check in em um apartamento
int fMenu(); //visualizacao do menu

main ()
{
	//MODEL --------------------------------------------------------------
	
	char hotel[20][14];
	int i, j, opcMenu;
	
	//CONTROL ------------------------------------------------------------
	
	//gerar tabela inicial
	for (i = 0; i < 20; i++)
		for (j = 0; j < 14; j++)
			hotel[i][j] = '.';
	
	//VIEW ----------------------------------------------------------------
	
	do
	{
		fTitulo (); //imprime titulo
		
		putchar('\n');
		
		opcMenu = fMenu(); //guarda a opcao escolhida pelo usuario
		
		switch(opcMenu)
		{
			case 1: //reserva
				fTitulo();
				fMapa(hotel);
				fReserva(hotel);
				break;
			case 2: //ocupacao
				fTitulo();
				fMapa(hotel);
				fCheckIn(hotel);
				break;
			case 0: //sair do programa
				break;
			default:
				printf("Opcao invalida.\n\n");
				system("Pause.");
				break;
		}
		
	} while (opcMenu != 0); //condicao de parada
	
}

/////////////////////////////////

void fTitulo () //visualizacao do titulo
{
	
	system("cls");
	
	printf("==========================================================\n");
	
	printf("\n\t\t\tGRAM HOTEL\t\t\t\n");
	
	printf("\n==========================================================\n");
	
}

void fMapa(char apt[20][14]) //mostra a tabela de andares
{
	
	int i, j;
	
	printf("\n    +------------------------------------------------+");
	
	printf("\n    |     ");
	
	for (j = 0; j < 14; j++)
	{
		printf("%2d ", j+1);
		if (j == 13)
			printf(" |");
	}
	
	printf("\n    |\t\t\t\t\t\t     |\n");
	
	for (i = 19; i >= 0; i--)
		{
		printf("    |%2d   ", i+1);
	
		for (j = 0; j < 14; j++)
			{
			printf(" %c ", apt[i][j]);
			if (j==13)
				printf(" |");
			}
	
	
		printf("\n");
		}
	
	printf("    +------------------------------------------------+\n\n");
	
}

/////////////////////////////////

void fReserva(char apt[20][14]) //reserva um apartamento
{
	int nAndar, nApt;
	
	checkAndar:
		
	printf("\nDigite o andar de reserva (0 para voltar ao menu principal): ");
	scanf("%d", &nAndar);
	
	if (nAndar == 0)
		return;
	else if (nAndar < 1 || nAndar > 20)
	{
		printf("Andar invalido.\n");
		goto checkAndar;
	}
	
	checkApt:
		
	printf("\nDigite o apartamento de sua preferencia (0 para voltar ao menu principal): ");
	scanf("%d", &nApt);
	
	if (nApt == 0)
		return;			
	else if (nApt < 1 || nApt > 14)
	{
		printf("Apartamento invalido.\n");
		goto checkApt;
	}
	
	nAndar--; nApt--;
	
	if (apt[nAndar][nApt] == 'R')
	{
		printf("Apartamento ja reservado.\n");
		goto checkApt;
	}
			
	apt[nAndar][nApt] = 'R';
	
	fTitulo(); fMapa(apt);
	
	printf("Reserva realizada.\n\n");
	
	system("pause");
	
}

/////////////////////////////////

void fCheckIn(char apt[20][14]) //check in do apartamento
{
	
	int nAndar, nApt;
	int i, check;
	
	checkAndar:	
	
	printf("\nDigite o andar de check in (0 para voltar ao menu principal): ");
	scanf("%d", &nAndar);
	
	check = 0;
	
	if (nAndar == 0)
		return;	
	else if (nAndar < 1 || nAndar > 20)
	{
		printf("Andar invalido.\n");
		goto checkAndar;
	}
	
	nAndar--;
		
	for (i = 0; i < 14; i++)
	{
		if (apt[nAndar][i] == 'R')
			check = 1;
	}
		
	if (check == 0)
	{
		printf("Andar nao possui reservas.\n");
		goto checkAndar;
	}
	
	
	checkApt:
		
	check = 0;

	printf("\nDigite o apartamento de check in: ");
	scanf("%d", &nApt);
		
	if (nApt < 1 || nApt > 14)
	{
		printf("Apartamento invalido.\n");
		goto checkApt;
	}
	
	nApt--;

	if (apt[nAndar][nApt] == 'R')
	{
		apt[nAndar][nApt] = 'O';
		
		fTitulo(); fMapa(apt);
		
		printf("Disponivel para ocupacao.\n");
	}
	else
		printf("\nNecessaria a reserva antes da ocupacao.\n\n");
	
	system("pause");
	
}

/////////////////////////////////

int fMenu() //visualizacao do menu
{
	int opc;
	
	printf("\n+-------------------------------------------------------+\n");
	printf("| \t      Seja bem vindo ao Gram Hotel! \t\t| \n");
	printf("| 1. Reserva de quartos. \t        \t\t|\n");
	printf("| 2. Ocupacao de quartos reservados. \t\t\t|\n");
	printf("| \t    Digite '0' para sair do programa.       \t|");
	printf("\n+-------------------------------------------------------+\n\n");

	printf("Digite uma opcao: ");
	scanf("%d", &opc);
	
	return(opc);
}
