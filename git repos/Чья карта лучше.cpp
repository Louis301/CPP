//Программа, определяющая игрока, у которого лучшая комбинация карт (Покер)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void shuffle(int [][13], int [][5], int [][5]);
int dp_para(int [][5]);
int kare(int [][5]);
int troyka(int [][5]);
int flesh(int [][5]);
int strit(int [][5]);

void str_komb(int);

main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	
	char *suit[4] = {"червей", "пик", "треф", "бубней"};
	char *face[13]={"Двойка", "Тройка", "Четвёрка", "Пятёрка", "Шестёрка", "Семёрка", "Восьмёрка", "Девятка", "Десятка", "Валет", "Дама", "Король", "Туз"};
	int deck[4][13] = {0}, i, j, a = 1, b = 5, gamer[2][5] = {2, 2, 3, 3, 7, 0, 0, 0, 2, 0}, gamer2[2][5] = {7, 4, 4, 3, 7, 0, 2, 3, 0, 0}, n_komb = 0, n2_komb = 0;	
	
	shuffle(deck, gamer, gamer2);
	
	for(i = 0; i <= 3; i++) {
		for(j = 0; j <= 12; j++) {
			printf("%4d", deck[i][j]);
		}
		puts("");
	} puts("\n");

//===========================================================================gamer 1		
	for(i = 0; i <= 1; i++) {
		for(j = 0; j <= 4; j++) {
			printf("%4d", gamer[i][j]);
		}
		puts("");
	} puts("--------------------------");
	
	for(i = 0; i <= 1; i++) {
	    if(strit(gamer) != 0) {n_komb = strit(gamer); break;}
	    if(flesh(gamer) != 0) {n_komb = flesh(gamer); break;}
	    if(kare(gamer) != 0) {n_komb = kare(gamer); break;}
	    if(troyka(gamer) != 0) {n_komb = troyka(gamer); break;}
	    if(dp_para(gamer) != 0) {n_komb = dp_para(gamer); break;}
	} str_komb(n_komb); puts("\n");

//===========================================================================gamer 2	
	for(i = 0; i <= 1; i++) {
		for(j = 0; j <= 4; j++) {
			printf("%4d", gamer2[i][j]);
		}
		puts("");
	} puts("--------------------------");
	
	for(i = 0; i <= 1; i++) {
	    if(strit(gamer2) != 0) {n2_komb = strit(gamer2); break;}
	    if(flesh(gamer2) != 0) {n2_komb = flesh(gamer2); break;}
	    if(kare(gamer2) != 0) {n2_komb = kare(gamer2); break;}
	    if(troyka(gamer2) != 0) {n2_komb = troyka(gamer2); break;}
	    if(dp_para(gamer2) != 0) {n2_komb = dp_para(gamer2); break;}
	} str_komb(n2_komb); puts("\n");
	
	
	if(n_komb > n2_komb) puts("Карта первого игрока лучше");
	if(n_komb < n2_komb) puts("Карта второго игрока лучше");
	if(n_komb == n2_komb) puts("Карты равны");
	
	return 0;         
}

void shuffle(int wDeck[][13], int g[][5], int g2[][5]) 
{
	int card, row, column;
	
	for(card = 1; card <= 52; card++) {
		row = rand() % 4;
		column = rand() % 13;
	    while(wDeck[row][column] != 0) {
		    row = rand() % 4;
		    column = rand() % 13;
	    }
		wDeck[row][column] = card;	
		
		if(card >= 1 && card <= 5) {
			g[0][card - 1] = column;
			g[1][card - 1] = row;
		}
		if(card >= 6 && card <= 10) {
			g2[0][card - 6] = column;
			g2[1][card - 6] = row;
		}
    }
    
}

int dp_para(int g[][5])
{
	int k = 0, k1 = -1, i, j, p = 1, komb = 0;
	for(i = 0; i <= 3; i++) {
		for(j = p; j <= 4; j++) {
			if(g[0][i] == g[0][j]) {k++; k1 = g[0][i]; if(k == 2) {komb = 2; break;}}
			if(g[0][i] != k1 && g[0][i] == g[0][j]) k++;
		}
		p++; if(k == 2) break;
	}
	if(k == 1) komb = 1;
	return komb;
}

int kare(int g[][5])
{
	int k = 0, j, m = 0, komb = 0;
	for(j = 1; j <= 4; j++) {
		if(g[0][0] == g[0][j]) k++;	
	}  
	for(j = 2; j <= 4; j++) {
		if(g[0][1] == g[0][j]) m++;	
	}  
	if(m == 3 || k == 3) komb = 4;
	return komb;
}

int strit(int g[][5])
{
	int k = 0, i, m = 0, komb = 0; 
    for(i = 0; i <= 3; i++) {
		if(g[0][i + 1] > g[0][i]) k++;
		if(g[0][i + 1] < g[0][i]) m++;
	}
	if(k == 4 || m == 4) komb = 6;
	return komb;
}

int flesh(int g[][5])
{
	int k = 0, i, komb = 0; 
	for(i = 0; i <= 3; i++) {
		if(g[1][i + 1] == g[1][i]) k++;
	}
	if(k == 4) komb = 5;
	return komb;
}

int troyka(int g[][5])
{
	int k = 0, j, m = 0, p = 0, komb = 0;
	for(j = 1; j <= 4; j++) {
		if(g[0][0] == g[0][j]) k++;	
	}  
	for(j = 2; j <= 4; j++) {
		if(g[0][1] == g[0][j]) m++;	
	}
	for(j = 3; j <= 4; j++) {
		if(g[0][2] == g[0][j]) p++;	
	}   
    if(m == 2 || k == 2 || p == 2) komb = 3;
    return komb;
}

void str_komb(int n_k) 
{
	if(n_k == 0) puts("так себе...");
	if(n_k == 1) puts("пара");
	if(n_k == 2) puts("две пары");
	if(n_k == 3) puts("тройка");
	if(n_k == 4) puts("каре");
	if(n_k == 5) puts("флэш");
	if(n_k == 6) puts("стрит");
}


