#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
//-----------------
#define YELLOW "\x1b[0;33m" //AMARELO
#define GREEN "\x1b[1;32m"	//verde
#define RED "\x1b[1;31m" //VERMELHO
#define RESET "\x1b[0m" //Padrão
#define AZUL "\x1b[1;34m"	 //Blue
#define D1 "\x1b[1;32;32m"	//verde com borda
//-----------------
#define TAM_LOGIN 20
#define TAM_NOME 50
#define TAM_COMIDA 100
#define TAM_VEICULO 10
#define  LIMPA_TELA system("cls"); //FAZ A MESMA FUNÇÃO DO SYSTEM CLS, MAS É SÓ ESCREVER "LIMPAR"
void inicialLogo(int tipo){
	printf(D1"\t\t****************************************************************************\n"RESET);
	printf(D1"\t\t*"RESET""AZUL"  _____    ___  "RESET""YELLOW"  _____    ___    __  __  "RESET""AZUL" _____    ___    __  __   _____ "RESET""D1"*\n"RESET);
	printf(D1"\t\t*"RESET""AZUL" |_   _|  / _ \\"RESET""YELLOW"  /  ___|  / _ \\  |  \\/  |"RESET""AZUL" |  ___|  / _ \\  |  \\/  | | ____|"RESET""D1"*\n"RESET);
	printf(D1"\t\t*"RESET""AZUL"   | |   | | | |"RESET""YELLOW" | |     | | | | | |\\/| |"RESET""AZUL" | |_    | | | | | |\\/| | |  _|  "RESET""D1"*\n"RESET); 
	printf(D1"\t\t*"RESET""AZUL"   | |   | |_| |"RESET""YELLOW" | |___  | |_| | | |  | | "RESET""AZUL"|  _|   | |_| | | |  | | | |___ "RESET""D1"*\n"RESET); 
	printf(D1"\t\t*"RESET""AZUL"   |_|    \\___/"RESET""YELLOW"   \\____|  \\___/  |_|  |_|"RESET""AZUL" |_|      \\___/  |_|  |_| |_____|"RESET""D1"*\n"RESET);
	printf(D1"\t\t*"RESET""AZUL"                "RESET""YELLOW"                            "RESET""AZUL"                              "RESET""D1"*\n"RESET);
	printf(D1"\t\t****************************************************************************\n\n\n"RESET);				// mostra uma tela diferente para cada caso,
	if(tipo==1){																						//1-clientes
		printf(YELLOW"\t\t\t\t CLIENTE\n"RESET); 																
	}else if(tipo==2){																						
		printf(AZUL"\t\t\t\t\t RESTAURANTE\n"RESET);																		//2-restaurante
	}else if(tipo==3){																								//3-entregador
		printf(GREEN"\t\t\t\t ENTREGADOR\n"RESET);
	}else if(tipo==0){																								//0-login e registro
		printf(AZUL"\t\t\t\t\t REGISTER | LOGIN \n"RESET);
	}
}
struct tLogin{
	char login[TAM_LOGIN];
	char senha[TAM_LOGIN];
	char nome[TAM_NOME];		//o mesmo nome para todos os tipos
	int id;						//o mesmo id criado no login para para os demais programas
	int tipo; 					//1-cliente 2-restaurante 3-entregador
};
struct tEntregador{
	char nomeEntregador[TAM_NOME];//Nome do entregador para listar para o cliente
	char veiculo[TAM_VEICULO];	//armazena apenas o veiculo 
	char placa[TAM_VEICULO];	//armazena apenas o placa 
	int id;						//pega o idd base do login e armazena todos os dados nesse idd correspondente ao login
	int excluido;				//caso o usuario queria excluir, os dados **SÓ** do entregador será excluido
	float saldo;				//Saldo da sua conta
};
struct tRestaurante{
	char nome[TAM_NOME];		//o nome do restaureante ou estabelecimento
	char endereco[TAM_NOME];	//endereço do restaureante ou estabelecimento
	int idLogin;
	int idRestaurante;			//pega o id base do login e armazena todos os dados nesse idd correspondente ao login
	int excluido;				//caso o usuario queria excluir, os dados **SÓ** do Restaurante será excluido
	float saldo;				//Saldo da sua conta
};								
struct tComida{
	char nome[TAM_NOME];		//o nome da comida
	char ingredientes[TAM_NOME];//todos os ingredientes que foram ultilizados na receita da comida
	int idRestaurante;			//pega o id base do restaurante e armazena todos os dados nesse id correspondente ao restaurante
	int excluido;
	int qtdVendida;				//caso o usuario queria excluir, os dados **SÓ** do Cardapio será excluido
	float valor;
};
struct tCliente{
	char nome[TAM_NOME];		//NOME DO USUARIO
	float saldo;				//Saldo da sua conta
	int id;						//o mesmo id criado no login para para os demais programas
	int excluido;				//Caso o cliente queira escluir a conta 
};
struct tVenda{
	char comida[TAM_COMIDA];	//Nome da comida que está sendo vendido
	int idCliente;				//ID DO CLIENTE 
	char nomeEntregador[TAM_NOME];//NOME DO ENTREGADOR QUE FEZ A ENTREGA
	float valor;				//VALOR DA VENDA DESCONTADO NA CARTEIRA DO CLIENTE E ACRESCENTADO NA CARTEIRA DO RESTAURANTE E DO ENTREGADOR
	char data[TAM_LOGIN];		//DATA DA VENDA
};
//---------------------------------------------------	VALIDAÇÕES	---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void lehValidaPalavra(char *nome[]){												//lÊ E VALIDA A PALAVRA PASSANDO POR REFERENCIA(PONTEIRO)
	int limite;
	do{
		fflush(stdin);
		gets(nome);
		limite=strlen(nome);
		if(limite >TAM_NOME){
			printf(RED"\nExcedeu o limite de caracter! Tente novamente....\nInsira novamente:"RESET);
		}
		if(limite <1){
			printf(RED"\nVocê não digitou nada! Tente novamente...\nInsira novamente:"RESET);
		}
	}while(limite < 1 || limite >20);
}
void lehValidaCarro(char *veiculo,char *placa){										//LÊ O TIPO DO SEU VEICULO,ARMAZENA, LÊ A SUA PLACA E VALIDA, ARMAZENA E RETORNA O TIPO(VEICULO) E A PLACA
	int escolha=0,i,flag=0;
	char primeiraPlaca[3],segundaPlaca[4];
	do{
		printf("\nInforme o seu tipo de veiculo\n1-Bicicleta\n2-Carro\n3-Moto\nopção:");		//POSSUI 3 MEIOS DE TRANSPORTES;
		scanf("%i",&escolha);
		fflush(stdin);
		if(escolha<=0||escolha>=4)
			printf(RED"\n tipo invalido\nInsira novamente:"RESET);
	}while(escolha<=0||escolha>=4);
	if(escolha==1){
		strcpy(veiculo,"Bicicleta");	
		strcpy(segundaPlaca,"");
		return;												//CASO ELE TENHA UMA BICICLETA, N É NECESSARIO DE UMA PLACA 
	}else{																				//CASO ELE TENHA UM CARRO OU UMA MOTO, É NECESSARIO DE UMA PLACA 
		if(escolha==2){
			strcpy(veiculo,"Carro");
			printf("\t\tCarro\n");
		}else{
			strcpy(veiculo,"Moto");
			printf("\t\tMoto\n");
		}
		printf("\nexemplo: XXX-9999\n");												//LÊ E VALIDA A PARTE DE CARACTERES DA PLACA 
		printf("Informe a placa(Parte em XXX):");
		i=0;
		do{
			fflush(stdin);
			primeiraPlaca[i] = getch();
			printf("%c",primeiraPlaca[i]);
			if(isalpha(primeiraPlaca[i])){
				i++;	
			}else{
				printf(RED"\n Digito invalido \nInsira novamente:"RESET);
			}
		}while(i!=3);
		strcpy(placa,primeiraPlaca);													
		fflush(stdin);
		i=0;
		flag=0;
		printf("\nInforme a parte numerica da placa:");
		do{
			fflush(stdin);																//LÊ E VALIDA A PARTE NUMERICA DA PLACA 
			segundaPlaca[i] = getch();
			printf("%c",segundaPlaca[i]);
			if(isdigit(segundaPlaca[i])){
				i++;	
			}else{
				printf(RED"\n Digito invalido \nInsira novamente:"RESET);
			}
		}while(i!=4);	
		strcat(placa,segundaPlaca);														//CONCATENA AS DUAS PARTES EM UM VETOR
	}
}
void lehValidaLogin(char *login[]){													//LÊ O LOGIN,VALIDAR E COMPRAR SE EXISTE ALGUM IGUAL
	int flag;
	struct tLogin entrada;
	FILE *arq = fopen("login.dat","rb");
	if (arq == NULL) {
		error();
		return;
	}
	do{
		fseek(arq, 0, SEEK_SET);  												//Retorna o ponteiro para o inicio do arquivo 
		flag=0;
		printf("\nInforme o possivel login:\n");
		lehValidaPalavra(login);
		while(fread(&entrada, sizeof(entrada), 1, arq)){						//Faz a leitura dentro do arquivo e busca o login
			if(strcmp(entrada.login,login)==0){
				printf(RED"Login existente, informe outro...\n"RESET);
				flag = 1;
			}
		}
	}while(flag!=0);
	fclose(arq);
}
void lehValidaSenha(char *senha[]){													//LÊ E VALIDA DUAS SENHAS E CONFIRMA COM CONDIFÇÃO DE VALIDAÇÃO
	char senha1[TAM_LOGIN],senha2[TAM_LOGIN];
	int flag=0;
	do{
		printf("senha:");
		lehValidaPalavra(&senha1);
		printf("confirme a senha:");
		lehValidaPalavra(&senha2);
		if(strcmp(senha1,senha2)==0){
			strcpy(senha,senha1);
			flag=1;
		}else{
			printf(RED"senha invalida\n"RESET);
		}
	}while(flag!=1);
}
float lehValidaValor(void){															//LÊ E VALIDA UM VALOR
	float valor;
	do{
		scanf("%f",&valor);
		fflush(stdin);
		if(valor<0)
			printf(RED"\nvalor invalido..."RESET);
	}while(valor<0);
	return valor;
}
void lehHora(char *hora[]){															//LÊ O DIA E INFORMA QUANDO O USUARIO FIZER ALGUMA COMPRA
	char data1[10],data2[10],data3[9999];
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    itoa(tm.tm_mday,data1,10);
    itoa(tm.tm_mon + 1,data2,10);			//Copia um inteiro para string
    itoa(tm.tm_year + 1900,data3,10);		//(str,"%d",value) converts to decimal base. %x  converts to hexadecimal base. %o converts to octal base.
    strcpy(hora,data1);
    strcat(hora,"/");
    strcat(hora,data2);
    strcat(hora,"/");
    strcat(hora,data3);
}
//---------------------------------------------------	ENTREGADOR	---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void incluirEntregador(int idLogin,char *nome[]){									//INCLUSÃO DE ENTREGADORES
	struct tEntregador entregador;
	FILE *arq = fopen("Entregador.dat","ab");
	if (arq == NULL) {
		error();
		return;
	}
	strcpy(entregador.nomeEntregador,nome);
	lehValidaCarro(&entregador.veiculo,&entregador.placa);							//INCLUSÃO DO TIPO DE VEICULO, SE POSSUI PLACA OU NÃO
	entregador.excluido=0;
	entregador.id = idLogin;
	fwrite(&entregador, sizeof(entregador), 1, arq);
	fclose(arq);
	system("PAUSE");
}
void listagemEntregador(void){  													//INFORMAÇÕES DO USUARIO 
	int opcao,idd;
	struct tEntregador entregador;
	FILE *arq;
	FILE *arqTexto=fopen("Idlogado.txt","r");
	if (arqTexto == NULL) {
		error();
		return;
	}
	if (arq == NULL) {
		printf(RED"Você não possui cadastro como Entregador!\n"RESET);
		system("pause");
		LIMPA_TELA
		return;
	}
	do{
		opcao=0;
		LIMPA_TELA
		inicialLogo(3);
		printf("\t\t\t"GREEN"1"RESET"- Informações do seu veiculo\n");										//LISTAGEM DE TODOS OS  USUARIO 
		printf("\t\t\t"GREEN"2"RESET"- Alteração do seu veiculo\n");										//ALTERA INFORMAÇÕES DO USUARIO
		printf("\t\t\t"GREEN"0"RESET"- SAIR\n");
		printf(GREEN"\t\t\tOpção:"RESET);
		scanf("%i",&opcao);
		fflush(stdin);
		switch(opcao){
			case 1:
				LIMPA_TELA
				inicialLogo(3);
				fscanf(arqTexto,"%i",&idd);
				arq = fopen("Entregador.dat","rb");
				while(fread(&entregador, sizeof(entregador), 1, arq)){
					if(entregador.id==idd && entregador.excluido==0){			//LISTAGEM
						printf("\t\t\t\t");
						puts(entregador.veiculo);
						printf("\t\t\t\t");
						puts(entregador.placa);	
					}
				}
				fclose(arq);
				fclose(arqTexto);
				system("pause");
				break;
			case 2:
				LIMPA_TELA
				inicialLogo(3);
				alteracaoEntregador();											//ALTERAÇÃO
				break;
		}
	}while(opcao!=0);
	system("PAUSE");
	LIMPA_TELA
}
void alteracaoEntregador(void){  													//ALTERA INFORMAÇÕES DO USUARIO
	struct tEntregador entregador;
	int id;
	FILE *arq = fopen("Entregador.dat","r+b");
	FILE *arqTexto=fopen("Idlogado.txt","r");
	if (arqTexto == NULL) {
		error();
		return;
	}
	if (arq == NULL) {
		error();
		system("pause");
		LIMPA_TELA
		return;
	}
	fscanf(arqTexto,"%i",&id);
	fflush(stdin);
	while(fread(&entregador, sizeof(entregador), 1, arq)){
		if(entregador.id==id && entregador.excluido==0){					
			fflush(stdin);
			printf("\n!Informe os seus novos dados \n");
			lehValidaCarro(&entregador.veiculo,&entregador.placa);
			fseek(arq, -sizeof(entregador), SEEK_CUR);
			fwrite(&entregador, sizeof(entregador), 1, arq);
			fseek(arq, 0, SEEK_CUR);
			puts(entregador.veiculo);
			puts(entregador.placa);
		}
	}
	system("pause");
	LIMPA_TELA
	fclose(arq);
	fclose(arqTexto);
}
void exclusaoEntregador(void){														//EXCLUSÃO EXCLUSIVA DO ENTREGRADOR
	struct tEntregador entregador;
	int flag=0,id;
	FILE *arq = fopen("Entregador.dat","r+b");
	FILE *arqTexto=fopen("Idlogado.txt","r");
	if (arqTexto == NULL) {
		error();
		return;
	}
	if (arq == NULL) {
		printf(RED"Você não possui cadastro como Entregador!\n"RESET);
		system("pause");
		LIMPA_TELA
		return;
	}
	fscanf(arqTexto,"%i",&id);
	while(fread(&entregador, sizeof(entregador), 1, arq)){
		if(entregador.id==id){	
			entregador.excluido=1;
			fseek(arq, -sizeof(entregador), SEEK_CUR);
			fwrite(&entregador, sizeof(entregador), 1, arq);
			fseek(arq, 0, SEEK_CUR);
			flag=1;	
		}
	}
	if(flag==1){
		printf("\n\nExclusão bem sucedida\n");
	}else{
		printf(RED"\n\nExclusão mal sucedida\n"RESET);
	}
	fclose(arq);
	fclose(arqTexto);
	system("pause");
	LIMPA_TELA
}
//---------------------------------------------------	LOGIN		--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void login(void){																	//CHAMDO NO LOGIN PARA LOGAR EM CONTAS EXISTENTES, APÓS REGISTRO
	char login[TAM_LOGIN],senha[TAM_LOGIN];
	int flag=0,opcao;
	struct tLogin entrada;
	FILE *arq,*arqLogado;
	arqLogado = fopen("Idlogado.txt","w");
	if (arqLogado == NULL) {
		error();
		return;
	}
	if (arq == NULL) {
		error();
		return;
	}
	do{
		arq = fopen("login.dat","rb");
		fflush(stdin);
		printf("Digite # para sair\n");
	 	printf("\t\t\t\tLOGIN:");
		lehValidaPalavra(&login);
		if(strcmp(login,"#")==0){
			fclose(arqLogado);	
			fclose(arq);
			return;
		}
		fflush(stdin);
		printf("\t\t\t\tSENHA:");
		lehValidaPalavra(&senha);
		fflush(stdin);
		while(fread(&entrada, sizeof(entrada), 1, arq)){
			if(strcmp(entrada.login,login)==0){
				if(strcmp(entrada.senha,senha)==0){
					flag=1;
					do{
						LIMPA_TELA
						inicialLogo(0);
						printf("\t\t\t\t 1-Cliente\n\t\t\t\t 2-Restaurante\n\t\t\t\t 3-Entregador\n\t\t\t\t 0-Sair\n");	//como ele quer entrar
						printf("Digite sua opção:");
						scanf("%i",&opcao);
						fflush(stdin);
						if(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=0)
							printf("Opção inválida!\n");
					}while(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=0);
					switch(opcao){
						case 1:
							fprintf(arqLogado,"%i",entrada.id);
								//Verifica se o cliente não existe no banco
							FILE *arqCliente = fopen("Cliente.dat","rb");
							struct tCliente cliente;
							int clienteExistente = 0;
							while(fread(&cliente,sizeof(cliente),1,arqCliente)){
								if(cliente.id == entrada.id) //Verifica se o Login já possui perfil de cliente
									clienteExistente = 1;
							}	
							fclose(arqCliente);
							if(clienteExistente){
								fclose(arqLogado);	
								fclose(arq);	
								system("start cliente"); 														
								system("taskkill /im login.exe");
							}else{
								printf(RED"\nVOCÊ NÃO POSSUI UM PERFIL DE CLIENTE!\n"RESET);
								system("pause");
								LIMPA_TELA
							}
							break;
						case 2:
							fprintf(arqLogado,"%i",entrada.id);
							//Verifica se o Restaurante não existe no banco
							FILE *arqRestaurante = fopen("Restaurante.dat","rb");
							struct tRestaurante restaurante;
							int restauranteExistente = 0;
							while(fread(&restaurante,sizeof(restaurante),1,arqRestaurante)){
								if(restaurante.idLogin == entrada.id) //Verifica se o Login já possui perfil de restaurante
									restauranteExistente = 1;
							}	
							fclose(arqRestaurante);
							if(restauranteExistente){
								fclose(arqLogado);	
								fclose(arq);
								system("start restaurante");																
								system("taskkill /im login.exe");
						    }else{									
								printf(RED"\nVOCÊ NÃO POSSUI UM PERFIL DE RESTAURANTE!\n"RESET);
								system("pause");
								LIMPA_TELA
							}
							break;
						case 3:		
							fprintf(arqLogado,"%i",entrada.id);	
										//Verifica se o Restaurante não existe no banco
							FILE *arqEntregador = fopen("Entregador.dat","rb");
							struct tEntregador entregador;
							int entregadorExistente = 0;
							while(fread(&entregador,sizeof(entregador),1,arqEntregador)){
								if(entregador.id == entrada.id) //Verifica se o Login já possui perfil de restaurante
									entregadorExistente = 1;
							}	
							fclose(arqEntregador);
							if(restauranteExistente){
								fclose(arqLogado);	
								fclose(arq);
								system("start entregador");																
								system("taskkill /im login.exe");
						    }else{																	
								printf(RED"\nVOCÊ NÃO POSSUI UM PERFIL DE ENTREGADOR!\n"RESET);
								system("pause");
								LIMPA_TELA
							}
							break;	
						case 0:
							return;
							break;
					}
				}
			}
		}
		printf(RED"\nLogin ou senha incorreta, informe a senha correta...\n"RESET);
		fclose(arq);
	}while(flag==0);
}
void registro(void){																//CHAMDO NO LOGIN PARA REGISTRAR CONFORME A OPÇÃO DO USUARIO COMO CLIENTE,RESTAURANTE E ENTREGRADOR, DENTRO DE CADA FUNÇÃO TEM A INCLUSÃO DE CADA OPÇÃO DEIXANDO EXCLUSIVAMENTE OS PROFRAMAS PARA INFORMAS DE QUEM POSSUI REGISTRO
	char login[TAM_LOGIN],senha[TAM_LOGIN];
	int flag=0,opcao,menu=0,id,achei=0;
	struct tLogin entrada;
	FILE *arq = fopen("login.dat","ab");
	FILE *arqTexto=fopen("id.txt","r+");
	if(arqTexto == NULL){
		id = 1;
		arqTexto = fopen("id.txt","w");
		fclose(arqTexto);
		arqTexto = fopen("id.txt","r+");
		fprintf(arqTexto,"%i",id);
	}
	fscanf(arqTexto,"%i", &id);	
	do{
		LIMPA_TELA
		inicialLogo(34);
		printf(AZUL"\nEscolha o meteodo de registro!\n"RESET);
		printf(AZUL"1"RESET".Não possuo cadastro e gostaria só de me cadastrar\n");
		printf(AZUL"2"RESET".Não possuo cadastro e gostaria de me cadastrar como cliente,restaurante ou entregador\n");
		printf(AZUL"3"RESET".Possuo cadastro e gostaria só de me cadastrar como cliente,restaurante ou entregador\n");
		printf(AZUL"0"RESET".sair\n");
		printf(AZUL"Opção:"RESET);
		scanf("%i",&menu);
		fflush(stdin);
		if(menu!=1 && menu!=2 && menu!=3 && menu!=0)
			printf("Opção inválida!\n");
		if(menu==0){
			fclose(arqTexto);	
			fclose(arq);
			return;
		}
		switch(menu){
			case 1:
				printf("\n\t\t\t\t     ****REGISTRO**** \n");
				printf("NOME:");
				lehValidaPalavra(&entrada.nome);											//INCLUSÃO DO NOME	//INCLUSÃO DO DDD
		 		lehValidaLogin(&entrada.login);												//para todos os tipos e depois pergunto ao usuario como ele quer entrar assim possibilitando uma facil mobilidade 
				lehValidaSenha(&entrada.senha);
				entrada.id = id;
				flag=1;
				system("pause");
				fwrite(&entrada, sizeof(entrada), 1, arq);
				fclose(arqTexto);
				arqTexto = fopen("id.txt","w");
				id++;
				fprintf(arqTexto,"%i",id);
				fclose(arqTexto);
				fclose(arq);
				break;
			case 2:
				do{
					printf("\n\t\t\t\t     ****REGISTRO**** \n");
					printf("NOME:");
					lehValidaPalavra(&entrada.nome);											//INCLUSÃO DO NOME	//INCLUSÃO DO DDD
			 		lehValidaLogin(&entrada.login);												//para todos os tipos e depois pergunto ao usuario como ele quer entrar assim possibilitando uma facil mobilidade 
					lehValidaSenha(&entrada.senha);
					entrada.id = id;
					system("pause");
					do{
						LIMPA_TELA
						inicialLogo(0);
						printf("\t\t\t\t"AZUL"1"RESET"-Cliente\n\t\t\t\t"AZUL"2"RESET"-Restaurante\n\t\t\t\t"AZUL"3"RESET"-Entregador\n");	//como ele quer entrar
						printf(AZUL"Digite sua opção:"RESET);
						scanf("%i",&opcao);
						fflush(stdin);
						if(opcao!=1 && opcao!=2 && opcao!=3)
							printf(RED"Opção inválida!\n"RESET);
					}while(opcao!=1 && opcao!=2 && opcao!=3);
					switch(opcao){
						case 1:
							LIMPA_TELA																
							inicialLogo(1);	
							incluirCliente(entrada.id,&entrada.nome);										
							break;
						case 2:
							LIMPA_TELA																
							inicialLogo(2);											
							incluirRestaurante(entrada.id);
							break;
						case 3:														
							LIMPA_TELA																
							inicialLogo(3);											
							incluirEntregador(entrada.id,&entrada.nome);
							break;	
					}
				}while(opcao!=1 && opcao!=2 && opcao!=3);
				flag=1;
				fwrite(&entrada, sizeof(entrada), 1, arq);
				fclose(arqTexto);
				arqTexto = fopen("id.txt","w");
				id++;
				fprintf(arqTexto,"%i",id);
				fclose(arqTexto);
				fclose(arq);
				break;
			case 3:
				fclose(arq);
				arq = fopen("login.dat","rb");
				printf("\t\t\t\tLOGIN:");
				lehValidaPalavra(&login);
				fflush(stdin);
				printf("\t\t\t\tSENHA:");
				lehValidaPalavra(&senha);
				fflush(stdin);
				achei=0;
				fseek(arq, 0, SEEK_SET);  
				while(fread(&entrada, sizeof(entrada), 1, arq)){
					if(strcmp(entrada.login,login)==0)
						if(strcmp(entrada.senha,senha)==0)
							achei=1;
				}
				if(!achei){
					printf(RED"\nLOGIN OU SENHA ERRADO! TENTE NOVAMENTE...\n"RESET);
					system("pause");
				}
				if(achei){
					do{
						printf("\t\t\t\t"AZUL"1"RESET"-Cliente\n\t\t\t\t"AZUL"2"RESET"-Restaurante\n\t\t\t\t"AZUL"3"RESET"-Entregador\n");
						printf(AZUL"Digite sua opção:"RESET);
						scanf("%i",&opcao);
						fflush(stdin);
						if(opcao!=1 && opcao!=2 && opcao!=3)
							printf(RED"Opção inválida!\n"RESET);
					}while(opcao!=1 && opcao!=2 && opcao!=3);			
					switch(opcao){
						case 1:
							LIMPA_TELA	
							//Verifica se o cliente não existe no banco
							FILE *arqCliente = fopen("Cliente.dat","rb");
							struct tCliente cliente;
							int clienteExistente = 0;
							while(fread(&cliente,sizeof(cliente),1,arqCliente)){
								if(cliente.id == entrada.id) //Verifica se o Login já possui perfil de cliente
									clienteExistente = 1;
							}
							//	
							fclose(arqCliente);
							inicialLogo(1);	
							if(clienteExistente==1){
								printf(RED"\nJÁ EXISTE UM PERFIL REGISTRADO NESSE LOGIN!\n"RESET);
								system("pause");
						    }else											
								incluirCliente(entrada.id,entrada.nome);
							break;
						case 2:
							LIMPA_TELA	
								//Verifica se o Restaurante não existe no banco
							FILE *arqRestaurante = fopen("Restaurante.dat","rb");
							struct tRestaurante restaurante;
							int restauranteExistente = 0;
							while(fread(&restaurante,sizeof(restaurante),1,arqRestaurante)){
								if(restaurante.idLogin == entrada.id) //Verifica se o Login já possui perfil de restaurante
									restauranteExistente = 1;
							}	
								//
							fclose(arqRestaurante);
							inicialLogo(2);	
							if(restauranteExistente==1){
								printf(RED"\nJÁ EXISTE UM PERFIL REGISTRADO NESSE LOGIN!\n"RESET);
								system("pause");
						    }else																																				
								incluirRestaurante(entrada.id);
							break;
						case 3:														
							LIMPA_TELA
									//Verifica se o Restaurante não existe no banco
							FILE *arqEntregador = fopen("Entregador.dat","rb");
							struct tEntregador entregador;
							int entregadorExistente = 0;
							while(fread(&entregador,sizeof(entregador),1,arqEntregador)){
								if(entregador.id == entrada.id) //Verifica se o Login já possui perfil de restaurante
									entregadorExistente = 1;
							}
									//	
							fclose(arqEntregador);
							inicialLogo(3);	
							if(restauranteExistente==1){
								printf(RED"\nJÁ EXISTE UM PERFIL REGISTRADO NESSE LOGIN!\n"RESET);
								system("pause");
						    }else{														
								inicialLogo(3);											
								incluirEntregador(id,&entrada.nome);
							}
							break;	
					}
					flag=1;
				}
				fclose(arqTexto);
				fclose(arq);
				break;
		}
	}while(flag == 0);
//	fwrite(&entrada, sizeof(entrada), 1, arq);
//	fclose(arqTexto);
//	arqTexto = fopen("id.txt","w");
//	id++;
//	fprintf(arqTexto,"%i",id);
//	fclose(arqTexto);
//	fclose(arq);
}
//---------------------------------------------------	RESTAURANTE	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void incluirRestaurante(int idLogin){												//INCLUSÃO DE RESTAURANTES
	struct tRestaurante restaurante;
	int idRestaurante;
	FILE *arq = fopen("Restaurante.dat","ab");
	FILE *arqTexto=fopen("idRestaurante.txt","r+");	
	if(arqTexto == NULL){
		idRestaurante = 1;
		arqTexto = fopen("idRestaurante.txt","w");
		fclose(arqTexto);								//Caso n possua arquivo, ele cria 
		arqTexto = fopen("idRestaurante.txt","r+");
		fprintf(arqTexto,"%i",idRestaurante);
	}
	fscanf(arqTexto,"%i", &idRestaurante);	
	printf("Informe o nome do Restaurante:");										//Nome do restaurante												
	lehValidaPalavra(&restaurante.nome);
	printf("\nInforme o endereço do Restaurante:");									//Aonde ele se encontra
	lehValidaPalavra(&restaurante.endereco);
	restaurante.excluido=0;
	restaurante.idLogin = idLogin;
	restaurante.idRestaurante = idRestaurante;
	fwrite(&restaurante, sizeof(restaurante), 1, arq);
	//-------------------------------------------------
	fclose(arqTexto);
	arqTexto = fopen("idRestaurante.txt","w");
	idRestaurante++;
	fprintf(arqTexto,"%i",idRestaurante);
	fclose(arqTexto);
	fclose(arq);
	system("pause");
}
void alteracaoRestaurante(void){  													//ALTERA INFORMAÇÕES DO restaurante
	struct tRestaurante restaurante;
	int id;
	FILE *arq = fopen("Restaurante.dat","r+b");
	FILE *arqTexto=fopen("Idlogado.txt","r");
	if (arq == NULL) {
		error();
		return;
	}
	fscanf(arqTexto,"%i",&id);
	while(fread(&restaurante, sizeof(restaurante), 1, arq)){
		if(restaurante.idLogin==id && restaurante.excluido==0){					
			printf("\n!Informe o seu NOVO endereço!\n");
			lehValidaPalavra(&restaurante.endereco);
			fseek(arq, -sizeof(restaurante), SEEK_CUR);
			fwrite(&restaurante, sizeof(restaurante), 1, arq);
			fseek(arq, 0, SEEK_CUR);
		}
	}
	system("pause");
	LIMPA_TELA
	fclose(arqTexto);
	fclose(arq);
}
void exclusaoRestaurante(void){														//EXCLUSÃO EXCLUSIVA DO restaurante
	struct tRestaurante restaurante;
	int flag=0,id;
	FILE *arq = fopen("Restaurante.dat","r+b");
	FILE *arqTexto=fopen("Idlogado.txt","r");
	if (arq == NULL) {
		error();
		return;
	}
	fscanf(arqTexto,"%i",&id);
	while(fread(&restaurante, sizeof(restaurante), 1, arq)){
		if(restaurante.idLogin==id && restaurante.excluido==0){	
			restaurante.excluido=1;
			fseek(arq, -sizeof(restaurante), SEEK_CUR);
			fwrite(&restaurante, sizeof(restaurante), 1, arq);
			fseek(arq, 0, SEEK_CUR);
			flag=1;
		}
	}
	if(flag==1)
		printf("\n\nExclusão bem sucedida\n");			//TEMOS Q MOSTRAR AO USUARIO SE A OPERAÇÃO FOI BEM OU MAL SUCEDIDA 
	else
		printf(RED"\n\nExclusão mal sucedida\n"RESET);
	fclose(arqTexto);
	fclose(arq);
	system("pause");
	LIMPA_TELA
}
//---------------------------------------------------	CARDAPIO	------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void incluirPrato(void){															//INCLUSÃO DE CARDAPIO
	int	id;												
	struct tComida comida;
	struct tRestaurante restaurante;
	FILE *arq = fopen("Cardapio.dat","ab");
	FILE *arqIdLogado = fopen("Idlogado.txt","r"); //Abre para verificar qual login está usando
	FILE *arqRestaurante = fopen("Restaurante.dat","r"); //Abre para buscar a struct do restaurante correspondente ao login
	if (arq == NULL || arqIdLogado == NULL) {
		error();
		return;
	}
	fscanf(arqIdLogado,"%i",&id);                 // Pega o id do Login que está usando o programa
	while(fread(&restaurante,sizeof(restaurante),1,arqRestaurante)){   // compara o id do login com o id da struct do restaurante dentro do arquivo restaurante.dat
		if(restaurante.idLogin == id)
			id = restaurante.idRestaurante;  // Atribui o id do restaurante a variavel que será colocada no id da comida 
	}
	fclose(arqIdLogado);
	fclose(arqRestaurante);
	printf("Informe o nome do seu prato:");									//Nome do restaurante												
	lehValidaPalavra(&comida.nome);
	printf("\nInforme os ingredientes:");									//Aonde ele se encontra
	lehValidaPalavra(&comida.ingredientes);
	printf("\nInforme o valor do %s:",comida.nome);
	comida.valor=lehValidaValor();
	comida.excluido=0;
	comida.qtdVendida = 0;
	comida.idRestaurante = id;
	fwrite(&comida, sizeof(comida), 1, arq);
	fclose(arq);
	system("pause");
}
void listagemCardapio(void){  														//INFORMAÇÕES DO USUARIO 
	int id;
	struct tComida cardapio;
	struct tRestaurante restaurante;
	FILE *arq = fopen("Cardapio.dat","rb");
	FILE *arqRestaurante = fopen("Restaurante.dat","rb");
	if (arq == NULL) {
		error();
		return;
	}
	LIMPA_TELA
	inicialLogo(2);
	printf("\t\tRestaurante |\t\tNome da comida |\t\tIngredientes da comida|\t\tValor |\n");
	while(fread(&cardapio, sizeof(cardapio), 1, arq)){								//LISTAGEM
		if(cardapio.excluido==0){
			fseek(arqRestaurante, 0, SEEK_SET);  
			while(fread(&restaurante,sizeof(restaurante),1,arqRestaurante)){
				if(restaurante.idRestaurante==cardapio.idRestaurante)
					printf("|%s",restaurante.nome);
			}
			printf("\t\t|%s|\t\t%s|\t\t%.2f \n",cardapio.nome,cardapio.ingredientes,cardapio.valor);
		}
	}
	fclose(arq);
	fclose(arqRestaurante);
	
}

void listagemCardapioRestaurante(){  														//INFORMAÇÕES DO USUARIO 
	struct tComida cardapio;
	struct tRestaurante restaurante;
	int idRestaurante;
	FILE *arq = fopen("Cardapio.dat","rb");
	FILE *arqIdLogado = fopen("Idlogado.txt","r");
	if (arq == NULL) {
		error();
		return;
	}
	fscanf(arqIdLogado,"%i",&idRestaurante);
	fclose(arqIdLogado);
	arqIdLogado = fopen("Restaurante.dat","rb");
	while(fread(&restaurante,sizeof(restaurante),1,arqIdLogado)){  //Procura o id logado na struct de restaurante e pega o id do restaurante e atribui a IdRestaurante
		if(restaurante.idLogin==idRestaurante)
			idRestaurante = restaurante.idRestaurante;
	}
	fclose(arqIdLogado);
	LIMPA_TELA
	inicialLogo(44);
	printf("\t\t|Nome da comida|\t\tIngredientes da comida|\t\tValor |\t\tVendida(s)|\n");
	while(fread(&cardapio, sizeof(cardapio), 1, arq)){								//LISTAGEM
		if(cardapio.excluido==0 && cardapio.idRestaurante == idRestaurante){
			printf("\t\t|%s|\t\t%s|\t\t%.2f|\t\t%i| \n",cardapio.nome,cardapio.ingredientes,cardapio.valor,cardapio.qtdVendida);
		}
	}
	fclose(arq);
}

void alteracaoCardapio(void){														//ALTERAR CARDAPIO
	char nome[TAM_NOME];											
	int flag=0,id;
	struct tComida cardapio;
	FILE *arqTexto=fopen("Idlogado.txt","r");
	FILE *arq = fopen("Cardapio.dat","r+b");
	if (arq == NULL) {
		error();
		return;
	}
	listagemCardapio();
	printf("\nInforme o nome da comida que deseja alterar:");
	lehValidaPalavra(&nome);
	fflush(stdin);
	fscanf(arqTexto,"%i",&id);
	while(fread(&cardapio, sizeof(cardapio), 1, arq)){
		if(cardapio.idRestaurante==id && cardapio.excluido==0){	
			if(strcmp(cardapio.nome,nome)==0){				
				fflush(stdin);
				printf("Informe o NOVO nome do seu prato:");									//Nome do restaurante												
				lehValidaPalavra(&cardapio.nome);
				printf("\nInforme os NOVOS ingredientes:");									//Aonde ele se encontra
				lehValidaPalavra(&cardapio.ingredientes);
				fseek(arq, -sizeof(cardapio), SEEK_CUR);
				fwrite(&cardapio, sizeof(cardapio), 1, arq);
				fseek(arq, 0, SEEK_CUR);
				flag=1;
			}
		}
	}
	if(flag==1)
		printf("\n\nAlteração bem sucedida\n");			//TEMOS Q MOSTRAR AO USUARIO SE A OPERAÇÃO FOI BEM OU MAL SUCEDIDA 
	else
		printf(RED"\n\nAlteração mal sucedida, tente novamente...\n"RESET);
	system("pause");
	LIMPA_TELA
	fclose(arq);
	fclose(arqTexto);
}
void exclusaoCardapio(void){														//EXCLUSÃO EXCLUSIVA DO restaurante
	char nome[TAM_NOME];														
	struct tComida cardapio;
	struct tRestaurante restaurante;
	int flag=0,id;
	FILE *arqTexto=fopen("Idlogado.txt","r");
	FILE *arq = fopen("Cardapio.dat","r+b");
	if (arq == NULL) {
		error();
		return;
	}
	listagemCardapioRestaurante();
	fscanf(arqTexto,"%i",&id);
	fclose(arqTexto);
	arqTexto = fopen("Restaurante.dat","rb");
	while(fread(&restaurante,sizeof(restaurante),1,arqTexto)){  //Procura o id logado na struct de restaurante e pega o id do restaurante e atribui a IdRestaurante
		if(restaurante.idLogin==id)
			id = restaurante.idRestaurante;
	}
	fclose(arqTexto);
	printf("\nInforme o nome da comida que deseja excluir:");
	lehValidaPalavra(&nome);
	while(fread(&cardapio, sizeof(cardapio), 1, arq)){
		if(cardapio.idRestaurante==id && cardapio.excluido==0 && strcmp(cardapio.nome,nome)==0){	
			cardapio.excluido=1;
			fseek(arq, -sizeof(cardapio), SEEK_CUR);
			fwrite(&cardapio, sizeof(cardapio), 1, arq);
			fseek(arq, 0, SEEK_CUR);
			flag=1;
		}
	}
	if(flag==1)
		printf("\n\nAlteração bem sucedida\n");			//TEMOS Q MOSTRAR AO USUARIO SE A OPERAÇÃO FOI BEM OU MAL SUCEDIDA 
	else
		printf(RED"\n\nAlteração mal sucedida, tente novamente...\n"RESET);
	fclose(arq);
	fclose(arqTexto);
	system("pause");
	LIMPA_TELA
}
void listaEcompra(char *comida[],float *valor,char *entrega[]){						//LISTAR O CARDAPIO E INFORMAR O QUE ELE QUER COMPRAR
	int achei=0,opcao,id,flag=0,idEntregador,id_Restaurante,idAleatorio,entregadorSelect=0,gerado=0;
	float valorCliente=0,valorComida=0,valorInicial=0,valorFinal=0,valorEntregador=0,valorRestaurante=0;
	char comidaComprada[TAM_NOME];
	struct tComida cardapio;
	struct tCliente cliente;
	struct tRestaurante restaurante;
	struct tEntregador entregador;
	FILE *arqEntregador;
	FILE *arqRestaurante;
	FILE *arqCliente = fopen("Cliente.dat","rb");
	FILE *arqLogado= fopen("Idlogado.txt","r");
	FILE *arqTexto = fopen("id.txt","r");
	FILE *arqCardapio;
	if ( arqLogado == NULL || arqCliente == NULL) {
		error();
		return;
	}
	fscanf(arqLogado,"%i",&id);
	fclose(arqLogado);
	fscanf(arqTexto,"%i",&idAleatorio);
	fclose(arqTexto);
	while(fread(&cliente, sizeof(cliente), 1, arqCliente)){
		if(cliente.id==id){		//Pega o saldo do cliente
			valorCliente=cliente.saldo;
		}									
	}
	fclose(arqCliente);
	srand(time(NULL));
	do{
		do{
			idEntregador = rand() % idAleatorio;
			if(idEntregador!=id){
				gerado = 1;
			}
		}while(gerado==0);
		arqEntregador = fopen("Entregador.dat","rb");
		if(arqEntregador==NULL){
			error();
			printf("Não se possuem entregador cadastrado!\n");
			return;
		}
		while(fread(&entregador, sizeof(entregador), 1, arqEntregador)){
			if(entregador.excluido==0 && entregador.id==idEntregador){										//Pega o id do primeiro motoboy e diferente do cliente caso o cliente tbm seja entregador
				strcpy(entrega,entregador.nomeEntregador); 
				entregadorSelect = 1;
			}
		}
		fclose(arqEntregador);
	}while(entregadorSelect==0);
	
	valorInicial=valorCliente;								//pega o inicial e com base no inicial e no quando ele restou, consegue-se calcular o valor que ele gastou 
	do{
		listagemCardapio();									//Lista as comidas
		arqCardapio = fopen("Cardapio.dat","rb");
		if(arqCardapio==NULL){
			error();
			return;
		}
		printf("O seu saldo: %.2f",valorCliente);			//SALDO ATUAL DO CLIENTE
		do{
			achei=0;
			printf("\nDigite # para sair( voltar )");
			printf("\n Informe a comida que deseja comprar:");
			lehValidaPalavra(comidaComprada);
			if(strcmp(comidaComprada,"#")==0){// condição de saida
				fclose(arqEntregador);
				fclose(arqRestaurante);
				fclose(arqCliente);									//Confirmar que n deixou nenhum arquivo aberto
				fclose(arqLogado);
				fclose(arqCardapio);
				return;
			}
			while(fread(&cardapio, sizeof(cardapio), 1, arqCardapio)){								//LISTAGEM
				if(strcmp(cardapio.nome,comidaComprada)==0){
					achei=1;
					valorComida=cardapio.valor;
					id_Restaurante=cardapio.idRestaurante;
					
				}
			}
			if(valorCliente>=valorComida && achei==1){
				printf("\nCompra bem-sucedida");
				fclose(arqCardapio);
				arqCardapio = fopen("Cardapio.dat","r+b");
				while(fread(&cardapio, sizeof(cardapio), 1, arqCardapio)){			//Alterar o saldo do restaurante
					if(strcmp(cardapio.nome,comidaComprada)==0){				
						cardapio.qtdVendida++;
						fseek(arqCardapio, -sizeof(cardapio), SEEK_CUR);
						fwrite(&cardapio, sizeof(cardapio), 1, arqCardapio);
						fseek(arqCardapio, 0, SEEK_CUR);
					}
				fclose(arqCardapio);
				}
			}else if(valorCliente<valorComida && achei==1){
				printf(RED"\nSaldo indisponível!Você só possui:%.2f",valorCliente);
				printf(RESET);
			}
		if(achei==0)
			printf(RED"\nNão achamos a sua comida, por favor insisra novamente\n"RESET);
		}while(achei==0);
		valorCliente=valorCliente-valorComida;//Desconta da carteira do cliente
		valorRestaurante=valorComida-9;		//Restaurante ganha o valor da comida e é tirado 9 reais para o entregador 
		arqRestaurante = fopen("Restaurante.dat","r+b"); //abre o arquivo para ler e armazenar o novo valor 
		while(fread(&restaurante, sizeof(restaurante), 1, arqRestaurante)){			//Alterar o saldo do restaurante
			if(id_Restaurante==restaurante.idRestaurante && restaurante.excluido==0){				
				restaurante.saldo=valorRestaurante;
				fseek(arqRestaurante, -sizeof(restaurante), SEEK_CUR);
				fwrite(&restaurante, sizeof(restaurante), 1, arqRestaurante);
				fseek(arqRestaurante, 0, SEEK_CUR);
			}
		}
		fclose(arqRestaurante);			
		if(flag==0){														//POR MAIS DE UM NOME
			strcpy(comida,comidaComprada);									
		}else{
			strcat(comida,"|");
			strcat(comida,comidaComprada);
		}
		flag++;
		do{																			//REPETIÇÃO
			printf("\nDeseja comprar novamente?\n "YELLOW"1"RESET"-sim \n "YELLOW"2"RESET"-não \n opção:");		
			scanf("%i",&opcao);
			fflush(stdin);
			if(opcao!=1 && opcao!=2)
				printf(RED"\n Opção invalida, por favor insisra novamente\n"RESET);
		}while(opcao!=1 && opcao!=2);
	}while(opcao==1);
	valorEntregador=9;
	valorFinal=valorInicial-valorCliente;		//VALOR FINAL PARA TVENDAS
	*valor=valorFinal;
	fclose(arqCardapio);
	arqEntregador = fopen("Entregador.dat","r+b");//abre o arquivo para ler e armazenar o novo valor 
	while(fread(&entregador, sizeof(entregador), 1, arqEntregador)){				//ATUALIZANDO O SALDO DO ENTREGADOR SABENDO Q ELE SEMPRE GANHA 9 POR ENTREGA 
		if(entregador.id==idEntregador){
			entregador.saldo=valorEntregador;											
			fseek(arqEntregador, -sizeof(entregador), SEEK_CUR);
			fwrite(&entregador, sizeof(entregador), 1, arqEntregador);
			fseek(arqEntregador, 0, SEEK_CUR);
		}
	}
	fclose(arqEntregador);
	//MUDA O VALOR DA CARTEIRA DO CLIENTE
	arqCliente = fopen("Cliente.dat","r+b");
	while(fread(&cliente, sizeof(cliente), 1, arqCliente)){				//ATUALIZANDO O SALDO
		if(cliente.id==id){												
			cliente.saldo=valorCliente;
			fseek(arqCliente, -sizeof(cliente), SEEK_CUR);
			fwrite(&cliente, sizeof(cliente), 1, arqCliente);
			fseek(arqCliente, 0, SEEK_CUR);
			
		}
	}
	fclose(arqCliente);
}
//---------------------------------------------------	CLIENTE 	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void incluirCliente(int idLogin,char nome[]){										//INCLUSÃO DE ENTREGADORES
	struct tCliente cliente;
	FILE *arq = fopen("Cliente.dat","ab");
	if (arq == NULL) {
		error();
		return;
	}
	strcpy(cliente.nome,nome);
	printf("Digite o valor que deseja depositar no aplicativo:");
	cliente.saldo=lehValidaValor();
	cliente.excluido=0;
	cliente.id= idLogin;
	fwrite(&cliente, sizeof(cliente), 1, arq);
	fclose(arq);
	system("PAUSE");
}
void comprarComida(void){															//REGISTRO DE COMPRAS 													
	int	idLogado;
	struct tVenda vendas;
	FILE *arqVendas=fopen("Vendas.dat","ab");
	FILE *arqLogado=fopen("Idlogado.txt","r"); //Abre para verificar qual login está usando
	if(arqLogado == NULL){
		error();
		return;
	}
	//----------------------------------------------------------------------------------------------------------------------------------------------------	
	fscanf(arqLogado,"%i",&idLogado);
	fclose(arqLogado);
	//----------------------------------------------------------------------------------------------------------------------------------------------------
	vendas.idCliente=idLogado;
	listaEcompra(&vendas.comida,&vendas.valor,&vendas.nomeEntregador);
	//--------------------------------------------	PEGAR A HORA E DATA	----------------------------------------------------------------------------------//ultilizando a biblioteca #include <time.h>
	lehHora(&vendas.data);
	//----------------------------------------------------------------------------------------------------------------------------------------------------
	fwrite(&vendas, sizeof(vendas), 1, arqVendas);
	fclose(arqVendas);
}
void listarCompras(void){															//ULTIMAS COMPRAS
	int id;
	struct tVenda vendas;
	FILE *arq = fopen("Vendas.dat","rb");
	FILE *arqCliente= fopen("Idlogado.txt","r"); //Abre para verificar qual login está usando
	if (arq == NULL) {
		error();
		return;
	}
	LIMPA_TELA
	inicialLogo(1);
	fscanf(arqCliente,"%i",&id);
	printf("\t\t\tComidas\t  \tValor\tEntregador\t\tData\n\n");
	while(fread(&vendas, sizeof(vendas), 1, arq)){								//LISTAGEM
		if(vendas.idCliente==id)
			printf("%30s          %5.2f %10s     %20s \n",vendas.comida,vendas.valor,vendas.nomeEntregador,vendas.data);
	}
	fclose(arq);
	fclose(arqCliente);
}
//---------------------------------------------------	RETURN 0 	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void error(){
	printf(RED"Error!\n"RESET);
}
