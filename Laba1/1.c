#include <stdio.h>
#include <string.h>
#include <math.h>


typedef enum kOpts {
	OPT_H,
	OPT_P,
	OPT_S,
	OPT_E,
	OPT_A,
	OPT_F,
	OPT_INVALID
} kOpts;


int MyAtoi(char* str) {
	int res = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		res = 10 * res + str[i] - '0';
	}
	return res;
}


int GetOpts(int argc, char* argv[], kOpts* option, int* number) {
	if (argc != 3) {
		return 1;
	}

	if ((strcmp(argv[2], "-h") == 0) || (strcmp(argv[2], "/h") == 0)) {
		*option = OPT_H;
	}
	else if ((strcmp(argv[2], "-p") == 0) || (strcmp(argv[2], "/p") == 0)) {
		*option = OPT_P;
	}
	else if ((strcmp(argv[2], "-s") == 0) || (strcmp(argv[2], "/s") == 0)) {
		*option = OPT_S;
	}
	else if ((strcmp(argv[2], "-e") == 0) || (strcmp(argv[2], "/e") == 0)) {
		*option = OPT_E;
	}
	else if ((strcmp(argv[2], "-a") == 0) || (strcmp(argv[2], "/a") == 0)) {
		*option = OPT_A;
	}
	else if ((strcmp(argv[2], "-f") == 0) || (strcmp(argv[2], "/f") == 0)) {
		*option = OPT_F;
	}
	else {
		*option = OPT_INVALID;
		return 1;
	}

	*number = MyAtoi(argv[1]);
	return 0;
}


void HandlerOptH(int x) {
	printf("Натуральные числа в пределах 100, кратные %d: \n", x);
	char mult_bool = 0;
	for (int i = 1; i <= 100; i++) {
		if (i % x == 0) {
			printf("%d ", i);
			mult_bool = 1;
		}
	}
	if (!mult_bool) {
		printf("В пределах 100 чисел нет кратных числу %d.\n", x);
	}
	printf("\n");
}


void HandlerOptP(int x) {
	if (x < 2) {
		printf("Это число и не составное, и не простое.\n");
		return;
	}
	char prime_num = 1;
	for (int i = 2; i <= sqrt(x); i++) {
		if (x % i == 0) {
			printf("Это число составное.\n");
			prime_num = 0;
			break;
		}
	}
	if (prime_num) {
		printf("Это простое число.\n");
	}
}


void HandlerOptS(int x) {
	if (x == 0) {
		printf("0\n");
		return;
	}
	char hex[100];
	int ind = 0;
	while (x > 0) {
		int n = x % 16;
		hex[ind++] = (n < 10) ? (n + '0') : (n - 10 + 'A');
		x = x / 16;
	}

	for (int i = ind - 1; i >= 0; i--) {
		printf("%c ", hex[i]);
	}
	printf("\n");
}


void HandlerOptE(int x) {
	if (x > 10) {
		printf("Некорректный ввод. Введите число не больше 10.\n");
		return;
	}

	for (int i = 0; i < 11; i++) {
		for (int p = 1; p <= x; p++) {
			printf("%d^%d = %d\n", i, p, int(pow(i, p)));
		}
		printf("\n");
	}
}


void HandlerOptA(int x) {
	if (x < 1) {
		printf("Введите положительное число.\n");
		return;
	}
	int gauss_sum = (x + 1) * x / 2;
	printf("Сумма всех чисел от 1 до %d - это %d\n", x, gauss_sum);
}


void HandlerOptF(int x) {
	if (x < 0) {
		printf("Значение нельзя определить.\n");
		return;
	}
	long long fact = 1;
	for (int i = 1; i <= x; i++) {
		fact *= i;
	}
	printf("%d! = %lld\n", x, fact);
}


int main(int argc, char* argv[]) {
	kOpts opt;
	int procceed_number = 0;
	void (*handlers[6])(int) = {
		HandlerOptH,
		HandlerOptP,
		HandlerOptS,
		HandlerOptE,
		HandlerOptA,
		HandlerOptF
	};

	if (GetOpts(argc, argv, &opt, &procceed_number)) {
		printf("Ошибка: некорректный ввод.\n");
		return 1;
	}
	
	handlers[opt](procceed_number);
	return 0;
}
