//INTERFACE CLIENTE//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include "function.c"
int retorno(void){																		//funcao para sair ou deslogar(voltar o menu(menu principal))
	int sair;
	do{
		printf("\n1-sair\n2-deslogar(voltando a tela de login)\n\nop��o:");
		scanf("%i",&sair);
		fflush(stdin);
		if(sair!=1 && sair!=2)
			printf(RED"Informe corretamente a op��o acima...\n"RESET);
	}while(sair!=1 && sair!=2);
	return sair;
}
int menuCliente(void) { 																	//MENU CRUD
	int op;
	do{
		printf("\t\t\t\t"YELLOW"1"RESET".CARDAIO \n");
		printf("\t\t\t\t"YELLOW"2"RESET".COMPRAR COMIDA \n");
		printf("\t\t\t\t"YELLOW"3"RESET".ULTIMAS COMPRAS \n");
		printf("\t\t\t\t"YELLOW"4"RESET".SALDO\n");
		printf("\t\t\t\t"YELLOW"0"RESET".SAIR\n\n");
		printf(YELLOW"\t\tDigite sua opcao: "RESET);											//VALIDA��O CRUD
		scanf("%i", &op);
		fflush(stdin);//evitar repeti��es
		if(op<0 || op>4){												
			printf(RED"op��o invalida, informe uma op��o correspondente a tabela a cima....\n"RESET);
			sleep(2);
			LIMPA_TELA
			inicialLogo(1);
		}
	}while(op<0 || op>4);
	return op;
}
void mostraSaldoCliente(void){														//SALDO DO CLIENTE
	int id;
	struct tCliente cliente;
	FILE *arq = fopen("Cliente.dat","rb");
	FILE *arqCliente= fopen("Idlogado.txt","r");									 //Abre para verificar qual login est� usando
	if (arq == NULL || arqCliente == NULL) {
		error();
		return;
	}
	LIMPA_TELA
	inicialLogo(1);
	fscanf(arqCliente,"%i",&id);
	while(fread(&cliente, sizeof(cliente), 1, arq)){
		if(cliente.id==id){
			puts(cliente.nome);
			printf("O seu saldo: %.2f\n",cliente.saldo);
		}									
	}
	fclose(arq);
	fclose(arqCliente);
}
int main (void){
	setlocale(LC_ALL,"");
	int opcao,sair;
	LIMPA_TELA
	do{
		inicialLogo(1);
		opcao = menuCliente();
		switch(opcao){
			case 1:
				LIMPA_TELA
				inicialLogo(1);
				listagemCardapio();
				system("pause");
				break;
			case 2:
				LIMPA_TELA
				inicialLogo(1);
				comprarComida();
				system("pause");
				break; 
			case 3:
				LIMPA_TELA
				inicialLogo(1);
				listarCompras();
				system("pause");
				break;
			case 4:
				LIMPA_TELA
				inicialLogo(1);
				mostraSaldoCliente();
				system("pause");
				break;
		}
		LIMPA_TELA
	}while (opcao != 0);
	LIMPA_TELA
	inicialLogo(1);
	sair=retorno();
	if(sair==1)														
		return 0;														//encerrar
	if(sair==2){														//voltar ao login
		system("start login"); 
		system("taskkill /im cliente.exe"); 
	}
	return 0;
}

