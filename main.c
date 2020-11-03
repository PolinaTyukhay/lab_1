#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#define SIZE 80
#define MAX 2147483647
#define NAME 256


// из буквы в цифру 
int c_to_n(char c) {
	int n = 0;
	if ((c >= '0') && (c <= '9')) {

		n = c - '0';
	}
	else if ((c >= 'A') && (c <= 'Z')) {
		n = c - 'A' + 10;
	}
	else if ((c >= 'a') && (c <= 'z')) {
		n = c - 'a' + 36;
	}
	else {
		printf("\nнекорекный ввод: символ не представлен в системе :%d , %c", c, c);
		exit(0);
	}
	return(n);

}
// из строки в число 
int my_atoi(const char* str, int p) {
	long long n = 0;
	for (int i = 0; str[i] != '\0'; i++) {

		n = n * p + c_to_n(str[i]);
		if (n > MAX) { // чтобы не привышал инт 
			printf("Число не попадает в диапоазон допустимых значений для int ");
			exit(0);
		}
	}
	return(n);
}
// функция меняет строку на месте 
void reverse(char* s) {
	int i, j;
	char c;
	// strlen() возвращает длину строки, оканчивающейся нулевым символом
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
//из цифры в букву 
char n_to_c(int a) {
	char c = 0;
	if ((a >= 0) && (a <= 9)) {
		c = a + '0';
	}
	else if (((a >= 10) && (a <= 35))) {
		c = a + 55;
	}
	else if (((a >= 36) && (a <= 61))) {
		c = a + 61;
	}
	return(c);
}
//из цифры  в строку
char* my_itoa(char* buf, int a, int p, int znak) {

	int i = 0;
	//printf("\n metka %d\n", a);
	do {

		buf[i++] = n_to_c(a % p);


	} while ((a /= p) > 0);
	if (znak == -1) {
		buf[i++] = '-';
	}
	buf[i] = '\0';
	reverse(buf);// функция меняет строку на месте 
	printf("строка\n");
	printf("%s", buf);// обратный порядок 
	return(buf);

}
// нахождение максимального символа в строке 
int max_sist(char* str, char p) {
	char max_c = str[0];
	//printf("\nmax_sist %s", str);
	for (int i = 1; i < p; i++) {
		//printf("\n%d\t%c\n", str[i], str[i]);
		if (str[i] > max_c) {
			max_c = str[i];
		}
	}
	int  max_n = 0;
	max_n = c_to_n(max_c);
	//printf("\nMaxC=%c\n", max_c);
	//printf("\nMaxD=%d\n", max_n);
	return(max_n);
}
//чтобы символы продходили в систему 
int check(char* str, int p) {
	for (int i = 0; str[i] != '\0'; i++) {
		int n = 0;
		n = c_to_n(str[i]);
		if (n > p) {
			return(0);
		}
	}
	return(1);
}
//непечатные символы 
char echo(unsigned char sim) {
	unsigned char c = '?';
	if ((sim >= 32) && (sim != 127)&&(sim < 254)) {
		c=sim; 
	}
	/*else
	{
		printf("%d %c",sim, sim  );
	}*/
	return(c);
}
int main()
{
	setlocale(LC_ALL, "Rus");
	printf("If ATOI-1, if ITOA - 2,if file - 3\n");
	int des;
	scanf_s("%d", &des);
	if (des == 1) {      // если надо из строки в число 
		printf("введиде систему счисления\n");
		int sist;
		scanf_s("%d", &sist);
		if ((sist > 62) || (sist < 2)) {
			printf("\nнекорекный ввод: система выходит за ограничения (2 <= p <= 62)");
			exit(0);
		}
		printf("введите строку\n");
		char StrSim[SIZE];
		int i = 0;
		char c;
		int znak = 1;
		//функция getche считывает символ с консоли , но не выводит на экран , а записывает на i-тое место в , и выводит на экран 
		while ((c = getche()) != '\r') {

			if ((c == '+') && (i == 0)) { 
				znak = 1;
			}
			else if ((c == '-') && (i == 0)) {
				znak = -1;
			}
			else
			{
				if (c == 8) { // удаление того что написано неправильно 
					if (i > 0) {
						i--;
						StrSim[i] = '\0';
					}
				}
				else {
					StrSim[i] = c;
					i++;
				}
			}

		}
		StrSim[i] = '\0'; // конец обрабатываемой строки 
		if (sist == 0) {
			sist = max_sist(StrSim, i) + 1;// система на 1 больше максимального числа в строке
			printf("\nсистема\n%d\n", sist);
		}
		int ch = 1;
		ch = check(StrSim, sist);// на случай если числа в системе ее превышают 
		if (ch == 0) {
			printf("\nчисло вне заданной системы");
			exit(0);
		}
		printf("\nстрока \n");
		printf("%s\n", StrSim);
		signed int chislo = 0; // чтобы точно была знаковым
		chislo = my_atoi(StrSim, sist);
		printf("получилось число  \n%d", chislo * znak);
	}
	else if (des == 2) { // если из числа в строку 
		printf("введиде систему счисления\n");
		int sist;
		scanf_s("%d", &sist);
		printf("введите число \n");
		int i = 0;
		int znak = 1; 
		int chislo = 0;
		int c;
		long long n = 0;// заведомо больше инта 
		while ((c = getche()) != '\r') {
			if ((c == '+') && (i == 0)) {
				znak = 1;
				i++;
			}
			else if ((c == '-') && (i == 0)) {
				znak = -1;
				i++;
			}
			else
			{
				if (((c - '0') >= 0) && ((c - '0') <= 9)) {
					n = n * 10 + (c - '0');
					if (n > MAX) { // чтобы в инт хватило 
						printf("\nЧисло не попадает в диапоазон допустимых значений для int\n ");
						exit(0);
					}
				}
				else {
					printf("\nлишние знаки\n ");
					exit(0);
				}
			}
		}
		chislo = n;
		int prov = 0;
		prov = chislo;
		printf("\nполучилось число  \n%d\n", chislo * znak);
		int rasm=0;// для определения количества ячеек 
		do {
			rasm ++;
			//printf("\nppp\n%d\t %d\n", prov, rasm  );
		} while (( prov  /= sist ) > 0);
		char* NewStr;
		rasm++; // для '0'
	    if (znak == -1) {
		    rasm++; // для '-'
	    }
		//printf("\nproverka %d\n",  rasm);
	    NewStr = (char*)malloc(rasm * sizeof(char));
	    my_itoa(NewStr, chislo, sist, znak);
	    free(NewStr);
	}
	else if (des == 3) {
	    printf("пока все \n");
	    char name[NAME];
        printf("Ведите имя файла: ");
		fseek(stdin, 0,SEEK_SET);
		gets_s(name, 255);
	    FILE* f;
	    fopen_s(&f, name, "rb");
	    /* if (!f)
		    printf("Error!");
	    else
		    printf("Good!");*/
	    unsigned char* str;
	    long long nLen = 0;
	    fseek(f, 0, SEEK_END);
	    nLen = ftell(f);
	    str = (char*)malloc(nLen + 1);
	    fseek(f, 0, SEEK_SET);
	    fread(str, 1, nLen, f);
	    str[nLen] = '\0';//массив 
	    fclose(f);
	    int out = 0;
	     printf("\nрезультат\n");
	    for (int i = 0; i < nLen; i++) {
			if (out == 16) {
				printf("|| ");
				for (int j = i - 16; j < i; j++) {
					printf("%c", echo(str[j]));
				}
				printf("\n");
				out = 0;
			}
			out++;
		    printf("%02X  ", str[i]);
	    }
		int razn = 0 , new=out;

		for (int i = out ; i < 16; i++) {
			printf("    ");
		}
	    printf("|| ");
        for (int j = nLen - out; j <nLen; j++) {
		    printf("%c", echo(str[j]));
	    }
	    printf("\n");
	    	
    }
}