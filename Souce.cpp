#include "lab.h"
#include "baralho.h"
#include "jogador.h"

#define Lebre 0
#define Tartaruga 1
#define Lobo 2
#define Uivo 3
#define Raposa 4
#define Cordeiro 5

void espera() {
	gotoxy(0, 22);	system("pause");
}

void fazerContagem(baralho mesa, int contagem[])
{
	int i = 0;

	for (i = 0; i < 6; i++)
	{
		contagem[i] = 0;
	}

	i = 0;

	while (i < mesa.size)
	{
		switch (mesa.cartas[i])
		{
		case 'L':
			contagem[Lebre]++;
			break;
		case 'T':
			contagem[Tartaruga]++;
			break;
		case 'W':
			contagem[Lobo]++;
			break;
		case 'w':
			contagem[Uivo]++;
			break;
		case 'R':
			contagem[Raposa]++;
			break;
		case 'C':
			contagem[Cordeiro]++;
			break;

		default:
			printf("Deu asneira!!!!");
			break;
		}
		i++;
	}
}

void moverAnimais(baralho playDeck, int animais[], baralho trackDeck)
{
	int contagem[6] = { 0 };
	int i = 0;

	fazerContagem(playDeck, contagem);
	//for (i = 0; i < 5; i++)
	//{
	//	animais[i] += contagem[i];
	//}
	if (contagem[Uivo] != 0) 		//Lobo a uivar
	{
		animais[Lobo] += (contagem[Lobo] + contagem[Uivo]);

		return;
	}
	if (contagem[Lebre])
	{
		if (animais[Lebre] == 0) { animais[Lebre] += 2; }
		else {
			if (contagem[Lebre] != 4) { animais[Lebre] += 2; }
			else {
				if (animais[Lebre] < animais[Tartaruga]) { animais[Lebre] += 2; }
				else
					if (animais[Lebre] < animais[Lobo]) { animais[Lebre] += 2; }
					else
						if (animais[Lebre] < animais[Raposa]) { animais[Lebre] += 2; }
						else
							if (animais[Lebre] < animais[Cordeiro]) { animais[Lebre] += 2; }
			}
		}
		if (trackDeck.cartas[animais[Lebre]] >= trackDeck.cartas[animais[!Lebre]] && contagem[Lebre] == 4) {

			animais[Lebre] = 0;
		}// verificar se esta em primeiro (nao sei se está correto)!!!!!!!!!!!!!!!!!!
	}
	if (contagem[Tartaruga] != 4)
	{
		animais[Tartaruga] += 1;
	}
	else
	{
		animais[Tartaruga] += 2;
	}
	if (contagem[Lobo] == 1 || contagem[Lobo] == 2)
	{
		animais[Lobo] += 1;
	}
	if (contagem[Lobo] = 3)
	{
		animais[Lobo] += 2;
	}
	if (contagem[Lobo] = 4)
	{
		animais[Lobo] += 3;
	}
	if (contagem[Raposa])
	{
		animais[Raposa] += contagem[Raposa];
	}
	if (contagem[Cordeiro])
	{
		contagem[Cordeiro]++;
		do
		{
			animais[Cordeiro]++;
			contagem[Cordeiro]--;
		} while (trackDeck.cartas[animais[Cordeiro]] != 'R' && contagem[Cordeiro] != 0);

	}
}

int initBetBaralho(baralho* myB) {
	if (myB->cartas == NULL) {
		createBaralho(myB, 5);
		if (myB->cartas == NULL) {
			return ALLOCATION_ERROR;
		}
	}
	if (myB->size != 0) { return DECKNOTEMPTY; }

	int i = 0;
	myB->cartas[myB->size] = 'L'; myB->size++;
	myB->cartas[myB->size] = 'T'; myB->size++;
	myB->cartas[myB->size] = 'W'; myB->size++;
	myB->cartas[myB->size] = 'R'; myB->size++;
	myB->cartas[myB->size] = 'C'; myB->size++;

	return NOERROR;
}
int initBaralhoPrincipal(baralho* myB) {
	if (myB->cartas == NULL) {
		createBaralho(myB, 81);
		if (myB->cartas == NULL) {
			return ALLOCATION_ERROR;
		}
	}
	if (myB->size != 0) { return DECKNOTEMPTY; }

	int i = 0;
	//L, T, W, w, R, C
	for (i = 0; i < myB->maxSize; i++) {
		if (i < 18) { myB->cartas[i] = 'L'; }
		if (i >= 18 && i < 35) { myB->cartas[i] = 'T'; }
		if (i >= 35 && i < 48) { myB->cartas[i] = 'W'; }
		if (i >= 48 && i < 51) { myB->cartas[i] = 'w'; }
		if (i >= 51 && i < 66) { myB->cartas[i] = 'R'; }
		if (i >= 66) { myB->cartas[i] = 'C'; }
	}
	myB->size = myB->maxSize;
	return NOERROR;
}
BOOL check4ofSame(baralho playDeck) {

	int i = 0;
	int contagem[6] = { 0 };

	for (i = 0; i < 6; i++) {
		fazerContagem(playDeck, contagem);
		i++;
	}
	if (contagem[Lebre] >= 4) { return false; }
	if (contagem[Tartaruga] >= 4) { return false; }
	if (contagem[Cordeiro] >= 4) { return false; }
	if (contagem[Raposa] >= 4) { return false; }
	if (contagem[Lobo] + contagem[Uivo] >= 4) { return false; }

	/////////NAO SEI SE ESTÁ CERTO!!!!!!!!!!!!!!!!!!!!!!!!!
	//fazer contagem !!!!!!!!!!!!!!FALTA FAZER!!!!!!!!!!!!!!!!!!!!
	//verificar se alguem tem 4 !!!!!!!!!!!!!!FALTA FAZER!!!!!!!!!!!!!!!!!!!!
}
void jogoNovo() {
	system("cls");

	//Inicialização
	baralho mainDeck, betDeck, discardDeck, playDeck, trackDeck;

	createBaralho(&trackDeck, 13);
	//funçaõ inittrackDeck !!!!!!!!!!!!!!FALTA FAZER!!!!!!!!!!!!!!!!!!!!

	createBaralho(&mainDeck, 81);
	initBaralhoPrincipal(&mainDeck);	//inicializar o baralho de 81 cartas
	shuffleBaralho(&mainDeck);
	createBaralho(&betDeck, 5);
	initBetBaralho(&betDeck);			//inicializar o baralho de 5 cartas
	createBaralho(&discardDeck, 81);	//não precisa de 81...
	createBaralho(&playDeck, 8);		//baralho de mesa; para jogar as cartas

	jogador players[2];
	int i = 0;
	for (i = 0; i < 2; i++) {
		createJogador(&players[i]);
		initJogador(&players[i], &mainDeck, &betDeck); // inicializa a mão e as apostas
	}

	//jogo :D
	//RONDA
	int firstPlayer = rand() % 2;
	int activePlayer = firstPlayer;

	int animais[6] = { 0 }; // L,T,W,w,R,C
	int contagem[6] = { 0 };

	//REPOR CARTA
	while (playDeck.size < playDeck.maxSize && !check4ofSame(playDeck))
	{
		moveCarta(&playDeck, &(players[activePlayer].mao));
		if (mainDeck.size) {
			moveCarta(&(players[activePlayer].mao), &mainDeck);
		}
		else {
			moveCarta(&mainDeck, &discardDeck);
			moveCarta(&(players[activePlayer].mao), &mainDeck);
			////////!!!!!!!!!!!!!!FALTA FAZER!!!!!!!!!!!!!!!!!!!!   ||||||||FEITO MAS NAO SEI SE ESTÁ CORRETO|||||||
		}

		activePlayer = !activePlayer;
	}
	// fase de movimento
	moverAnimais(playDeck, animais, trackDeck);



	//fase de descarte
	while (playDeck.size != 0)
	{
		moveCarta(&discardDeck, &playDeck);
	}



	// salva tudo
	FILE* fp = NULL;
	fopen_s(&fp, "game000.txt", "w");
	if (fp) {
		fprintf(fp, "mainDeck:");
		saveBaralho(fp, mainDeck);
		fprintf(fp, "\nbetDeck:");
		saveBaralho(fp, betDeck);
		fprintf(fp, "\ndiscardDeck:");
		saveBaralho(fp, discardDeck);
		fprintf(fp, "\nplayDeck:");
		saveBaralho(fp, playDeck);
		for (i = 0; i < 2; i++) {
			fprintf(fp, "\nplayer%d:", i);
			saveJogador(fp, players[i]);
		}
		fprintf(fp, "\nanimais:(");
		for (i = 0; i < 6; i++)
		{
			fprintf(fp, "%d,", animais[i]);
		}
		fprintf(fp, "\n)");
		fclose(fp);
	}

	//free all allocated memory
	freeBaralho(&mainDeck);
	freeBaralho(&betDeck);
	freeBaralho(&discardDeck);
	freeBaralho(&playDeck);
	for (i = 0; i < 2; i++) {
		freeJogador(&players[i]);
	}
	freeBaralho(&trackDeck);
}
void carregarJogo() {

	char aux[20] = { '\0' };
	int i = 0;
	//Inicialização
	baralho mainDeck, betDeck, discardDeck, playDeck;
	createBaralho(&mainDeck, 1);
	createBaralho(&betDeck, 1);
	createBaralho(&discardDeck, 1);
	createBaralho(&playDeck, 1);

	jogador players[2];
	for (i = 0; i < 2; i++) {
		createJogador(&players[i]);
	}

	// leitura de ficheiro
	FILE* fp = NULL;
	fopen_s(&fp, "game000.txt", "r");
	if (fp) {
		fscanf_s(fp, " %[^:]:", aux, sizeof(aux) - 1); //lê "mainDeck:"
		readBaralho(fp, &mainDeck);
		fscanf_s(fp, " %[^:]:", aux, sizeof(aux) - 1); //lê "betDeck:"
		readBaralho(fp, &betDeck);
		fscanf_s(fp, " %[^:]:", aux, sizeof(aux) - 1); //lê "discardDeck:"
		readBaralho(fp, &discardDeck);
		fscanf_s(fp, " %[^:]:", aux, sizeof(aux) - 1); //lê "playDeck:"
		readBaralho(fp, &playDeck);
		for (i = 0; i < 2; i++) {
			fscanf_s(fp, " %[^:]:", aux, sizeof(aux) - 1); //lê "player#:"
			readJogador(fp, &players[i]);
		}
		fclose(fp);
	}

	//jogo :D


	//print all:  just to check
	system("cls");
	gotoxy(2, 3);
	printf("mainDeck:");
	printBaralho(mainDeck);
	printf("\nbetDeck:");
	printBaralho(betDeck);
	printf("\ndiscardDeck:");
	printBaralho(discardDeck);
	printf("\nplayDeck:");
	printBaralho(playDeck);
	for (i = 0; i < 2; i++) {
		printf("\nplayer%d:", i);
		printJogador(players[i]);
	}

	//free all allocated memory
	freeBaralho(&mainDeck);
	freeBaralho(&betDeck);
	freeBaralho(&discardDeck);
	freeBaralho(&playDeck);
	for (i = 0; i < 2; i++) {
		freeJogador(&players[i]);
	}
}
char menu() {
	setlocale(LC_ALL, ""); //Escrever carateres especiais
	char opt = '0';
	do {
		system("cls");		//limpa o ecrã
		showRectAt(7, 6, 34, 11);
		gotoxy(10, 8);	printf("Menu");

		gotoxy(10, 10);	printf("A - Jogar uma Partida nova");
		gotoxy(10, 11);	printf("B - Jogar uma Partida gravada");
		gotoxy(10, 12);	printf("C - Regras do jogo");
		gotoxy(10, 13);	printf("D - Sair");

		gotoxy(10, 15);	printf("Escolha uma opção: ");
		(void)scanf("%c", &opt);
		opt = toupper(opt);
	} while (opt != 'A' && opt != 'B' && opt != 'C' && opt != 'D');
	setlocale(LC_ALL, "C");		// retorna ao modo de consola
	return opt;
}
void paginainicial() {
	system("cls");
	setlocale(LC_ALL, "");
	gotoxy(10, 10);	printf("A Lebre e a Tartaruga");
	gotoxy(10, 12);	printf("by Luís Nunes");
	espera();
}
int main() {

	initRandom();
	setFullScreen(true);
	setColor(MY_COLOR_BLACK, MY_COLOR_GRAY);

	paginainicial();

	char opt = '0';

	do {
		opt = menu();
		switch (opt) {
		case 'A':
			jogoNovo();
			break;
		case 'B':
			printf("\tAqui vou carregar o jogo");
			carregarJogo();
			break;
		case 'C':
			setlocale(LC_ALL, "pt_PT.UTF-8");
			system("cls");
			FILE* fp;
			char content[1000];
			fp = fopen("Regras.txt", "r");

			if (fp == NULL) {
				printf("Erro a abrir!!");
			}
			else {
				while ((fgets(content, sizeof(content), fp) != NULL)){
					printf("%s", content);
				}
			}
			break;
		case 'D':
			printf("\tSair");
			break;
		default:
			printf("\tERRO");
			break;
		}
		espera();
	} while (opt != 'D');


	//Libertar memória

	return 0; // no error
}