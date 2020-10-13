//INTERFACE ENTRAGADOR
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
		printf("\n1-sair\n2-deslogar(voltando a tela de login)\n\nopção:");
		scanf("%i",&sair);
		fflush(stdin);
		if(sair!=1 && sair!=2)
			printf(RED"Informe corretamente a opção acima...\n"RESET);
	}while(sair!=1 && sair!=2);
	return sair;
}
int menuEntregador(void) { 																	//MENU CRUD
	int op;
	do{
		printf("\t\t\t\t"GREEN"1"RESET". INFORMAÇÕES\n");
		printf("\t\t\t\t"GREEN"2"RESET". EXCLUIR CONTA\n");
		printf("\t\t\t\t"GREEN"3"RESET". SALDO \n");
		printf("\t\t\t\t"GREEN"0"RESET". Sair\n\n");
		printf(GREEN"\t\tDigite sua opcao: "RESET);											//VALIDAÇÃO CRUD
		scanf("%i", &op);
		fflush(stdin);
		if(op<0 || op>3){													
			printf(RED"opção invalida, informe uma opção correspondente a tabela a cima....\n"RESET);
			sleep(2);
			LIMPA_TELA
			inicialLogo(3);
		}
	}while(op<0 || op>3);
	return op;
}
void mostraSaldoEntregador(void){													//SALDO DO Entregador
	int id;
	struct tEntregador entregador;
	FILE *arq = fopen("Entregador.dat","rb");
	FILE *arqCliente= fopen("Idlogado.txt","r");									 //Abre para verificar qual login está usando
	if (arq == NULL) {
		printf("Error!");
		return;
	}
	LIMPA_TELA
	inicialLogo(3);
	fscanf(arqCliente,"%i",&id);
	while(fread(&entregador, sizeof(entregador), 1, arq)){
		if(entregador.id==id){
			puts(entregador.nomeEntregador);
			printf("O seu saldo: %.2f\n",entregador.saldo);
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
		inicialLogo(3);
		opcao = menuEntregador();
		switch(opcao){
			case 1:
				LIMPA_TELA
				inicialLogo(3);
				listagemEntregador(); //listagem e alteração
				break;
			case 2:
				LIMPA_TELA
				inicialLogo(3);
				exclusaoEntregador(); //exclusão
				break;
			case 3:
				LIMPA_TELA
				inicialLogo(3);
				mostraSaldoEntregador();
				system("pause");
				break;
		}
		LIMPA_TELA
	}while (opcao != 0);
	LIMPA_TELA
	inicialLogo(3);
	sair=retorno();
	if(sair==1)														
		return 0;														//encerrar
	if(sair==2){														//voltar ao login
		system("start login"); 
		system("taskkill /im entregador.exe"); 
	}
	return 0;
}


