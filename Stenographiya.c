
#include <stdio.h>
#include <windows.h>
#include <stdlib.h> // для функции system

int main(int ac, char **av)
{
	system("chcp 65001"); // смена кодировки, если файл в кодировке utf-8	

	int	a = 'А';
	int	b = 'Я';
	int	c = 'а';
	int	d = 'Ё';

	char сh = 53392;
	printf("Приве\n%i\n%i\n%i\n%i\n%c\n", a, b, c, d, сh);
	return 0;
}