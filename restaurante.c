#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include "function.c"
int menuRestaurante(void) { 																	
	int op;
	do{
		printf("\t\t\t\t"AZUL"1"RESET". INCLUIR COMIDA\n");										//Inclusão de comida
		printf("\t\t\t\t"AZUL"2"RESET". CARDAPIO\n");											//Listagem de comida    Exclusivo no "Cardapio.dat"
		printf("\t\t\t\t"AZUL"3"RESET". ALTERAR COMIDA\n");										//Alteração de comida
		printf("\t\t\t\t"AZUL"4"RESET". EXCLUIR COMIDA\n");										//excluir a comida
		printf("\t\t\t\t"AZUL"5"RESET". ALTERAR ENDEREÇO\n");									//Altera o endereço do restaureante ou estabelecimento
		printf("\t\t\t\t"AZUL"6"RESET". EXCLUIR RESTAURANTE\n");									//excluir o do restaureante ou estabelecimento
		printf("\t\t\t\t"AZUL"7"RESET". SALDO \n");
		printf("\t\t\t\t"AZUL"8"RESET". COMPRAS \n");
		printf("\t\t\t\t"AZUL"0"RESET". Sair\n\n");												//Sair
		printf(AZUL"\t\tDigite sua opcao: "RESET);										
		scanf("%d", &op);
		fflush(stdin);//evitar repetições
		if(op<0 || op>8){													
			printf(RED"opção invalida, informe uma opção correspondente a tabela a cima....\n"RESET);
			sleep(2);
			LIMPA_TELA
			inicialLogo(0);
		}
	}while(op<0 || op>8);
	return op;
}
int retorno(void){																		//funcao para sair ou deslogar(voltar o menu(menu principal))
	int sair;
	do{
		printf("\n1-sair\n2-deslogar(voltando a tela de login)\n\nopção:");
		scanf("%i",&sair);
		fflush(stdin);
		if(sair!=1 && sair!=2)
			printf(RED"Informe corretamente a opção acima...\n"RESET);
	}while(sair!=1 && sair!=2);
	return sair;
}
void mostraSaldoRestaurante(void){													//SALDO DO RESTAURANTE
	int id;
	struct tRestaurante restaurante;
	FILE *arq = fopen("Restaurante.dat","rb");
	FILE *arqCliente= fopen("Idlogado.txt","r");									 //Abre para verificar qual login está usando
	if (arq == NULL) {
		error();
		return;
	}
	LIMPA_TELA
	inicialLogo(2);
	fscanf(arqCliente,"%i",&id);
	while(fread(&restaurante, sizeof(restaurante), 1, arq)){
		if(restaurante.idLogin==id){
			puts(restaurante.nome);
			printf("O seu saldo: %.2f\n",restaurante.saldo);
		}									
	}
	fclose(arq);
	fclose(arqCliente);
}
int main(void){
	int opcao,sair;
	setlocale(LC_ALL,"");
	LIMPA_TELA
	do{
		inicialLogo(2);
		opcao = menuRestaurante();
		switch(opcao){
			case 1:
				LIMPA_TELA
				inicialLogo(2);
				incluirPrato();														//Inclusão de comida
				break;	
			case 2:
				LIMPA_TELA
				inicialLogo(2);
				listagemCardapioRestaurante();												//Listagem de comida 
				system("PAUSE");
				LIMPA_TELA
				break;
			case 3:
				LIMPA_TELA
				inicialLogo(2);
				alteracaoCardapio();												//Alteração de comida
				break;
			case 4:
				LIMPA_TELA
				inicialLogo(2);
				exclusaoCardapio();													//Excluir comida
				break;
			case 5:
				LIMPA_TELA
				inicialLogo(2);
				alteracaoRestaurante();												//Altera o endereço do restaureante ou estabelecimento
				break;
			case 6:
				LIMPA_TELA
				inicialLogo(2);
				exclusaoRestaurante();												//excluir o do restaureante ou estabelecimento
				break;
			case 7:
				LIMPA_TELA
				inicialLogo(3);
				mostraSaldoRestaurante();
				system("pause");
				break;
			case 8:
				LIMPA_TELA
				inicialLogo(3);
				listarCompras();
				system("pause");
				break;
		}
		LIMPA_TELA
	}while (opcao != 0);
	LIMPA_TELA
	inicialLogo(2);
	sair=retorno();
	if(sair==1)														
		return 0;														//encerrar
	if(sair==2){														//voltar ao login
		system("start login"); 
		system("taskkill /im restaurante.exe"); 
	}
	return 0;
}
