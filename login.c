//LOGIN
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include "function.c"
void sobreOAplicativo(void){
	printf(D1"O que � o TOCOMFOME?\n"RESET);
	printf("O TOCOMFOME � uma plataforma de entrega de pedidos. Divulgamos o seu card�pio atrav�s do app. Ao receber um pedido, voc� o prepara normalmente e n�s enviamos um entregador para retir�-lo e lev�-lo at� o cliente.\n\n\n");
	printf(D1"Como funciona?\n"RESET);
	printf(""AZUL"1"RESET".Um cliente abre o app TOCOMFOME, escolhe um ou mais itens do seu card�pio e faz um pedido.\n");
	printf(""AZUL"2"RESET".Voc� aceita o pedido\n");
	printf(""AZUL"3"RESET".Voc� prepara o pedido e o entrega a um dos nossos entregadores parceiros.\n");
	printf(""AZUL"4"RESET".O parceiro entrega o seu pedido ao cliente\n\n\n");
	printf(D1"Quem realiza as entregas?\n"RESET);
	printf("Nossa ampla rede de entregadores parceiros ajuda a garantir que os seus pratos sejam levados at� o cliente o mais r�pido poss�vel.\n\n");
	system("pause");
}
int menuLogin(void){																//MENU PRINCIPAL(LOGIN E REGISTRO)
	int op;
	do{
		printf("\t\t\t\t"AZUL"1"RESET". LOGIN\n");
		printf("\t\t\t\t"AZUL"2"RESET". REGISTER\n");
		printf("\t\t\t\t"AZUL"3"RESET". Sobre o aplicativo(perguntas frequentes)\n");
		printf("\t\t\t\t"AZUL"0"RESET". Sair\n\n");
		printf(AZUL"\t\tDigite sua opcao: "RESET);
		scanf("%d", &op);
		fflush(stdin);//evitar repeti��es															//VALIDA��O MENU PRINCIPA
		if(op<0 || op>3){													
			printf(RED"op��o invalida, informe uma op��o correspondente a tabela a cima....\n"RESET);
			sleep(2);
			LIMPA_TELA
			inicialLogo(3);
		}
	}while(op<0 || op>3);
	return op;
}
int main(void){
	int opcao;
	setlocale(LC_ALL,"");
	LIMPA_TELA
	do{
		inicialLogo(0);
		opcao = menuLogin();
		switch(opcao){
			case 1:
				LIMPA_TELA
				inicialLogo(0);
				login();
				break;
			case 2:
				LIMPA_TELA
				inicialLogo(0);
				registro();
				break;
			case 3:
				LIMPA_TELA
				inicialLogo(4); //apenas a logo
				sobreOAplicativo();
				break;
		}
		LIMPA_TELA
	}while (opcao != 0);
	return 0;
}
