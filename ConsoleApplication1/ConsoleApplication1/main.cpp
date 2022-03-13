#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

string	perevod(char c)
{
	// Перевод из буквы в двоичный код
	string	word = "00000000";
	int		nb = c;
	int		i = 7;

	if (nb < 0)
	{
		nb *= -1;
		word[0] = '1';
	}
	while (nb > 1)
	{
		word[i] = (nb % 2) + 48;
		i--;
		nb /= 2;
	}
	word[i] = (nb % 2) + 48;
	return (word);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	ifstream fd_container("texts\\container.txt"); //Контейнер
	if (!fd_container.is_open()) // если файл не открыт
	{
		cout << "Ошибка при открытии контейнера\n";
		return 1;
	}
	string container = "", message = "", s1;
	while (getline(fd_container, s1))
	{
		container += s1;
		container += "\n";
	}
	fd_container.close(); // закрываем файл
	int space_nb = 0;
	for (int i = 0; i != container.length(); i++)
	{
		if (container[i] == 32 || container[i] == '\n')
			space_nb++;
	}
	//cout << container << endl;
	cout << "Количество свободных бит для скрытия в конетейнере = " << space_nb << endl;

	ifstream fd_message("texts\\message.txt"); //Сообщение
	if (!fd_message.is_open()) // если файл не открыт
	{
		cout << "Ошибка при открытии сообшения\n";
		return 2;
	}
	while (getline(fd_message, s1))
	{
		message += s1;
		message += "\n";
	}
	fd_message.close(); // закрываем файл
	//cout << message << endl;
	cout << "Количество бит нужных для скрытия = " << (message.length() * 8) << endl;

	//Если не хватает бит
	if (space_nb < (message.length() * 8))
	{
		cout << " Не хватает бит для стенографирования в количестве = "
				<< (space_nb - (message.length() * 8)) << endl;
		return (0);
	}
	
	string	binary = ""; //Перевод сообщения в бинарный код
	for (int i = 0; i != message.length(); i++)
	{
		binary += perevod(message[i]);
		//binary += " ";
	}
	//cout << binary << endl;

	char	*mod_container = new char[container.length() + binary.length() + 5000];
	int		j = 0;
	int		binary_count = 0;

	for (int i = 0; i != container.length(); i++)
	{
		mod_container[j] = container[i];
		if ((mod_container[j] == ' ' || mod_container[j] == '\n') && binary_count < binary.length())
		{
			if (binary[binary_count] == '1')
				mod_container[++j] = ' ';
			binary_count++;
		}
		j++;
	}
	mod_container[j] = '\0';

	//Запись стенографии в файл
	ofstream fout("texts\\sten_container.txt");
	if (!fout.is_open())
	{
		cout << "Файл sten_container.txt не может быть открыт!\n";
		return 3;
	}
	fout << mod_container; // запись строки в файл
	fout.close();

	
	cout << "Если хотите рассшифровать нажмите 1  " << endl;
	int pp = 0;
	cin >> pp;
	if (pp != 1)
		return 0;

	//Перевод стенографиия в сообщение
	string		desten_message = "", s2 = "+";
	int			ans = 0;
	int			word = 0;
	char		cr;
	int			minus = 1;

	j = -1;
	while (mod_container[++j])
	{
		if (mod_container[j] == ' ' || mod_container[j] == '\n')
		{
			if (word == 0 && mod_container[j + 1] == ' ')
			{
				minus = -1;
				j++;
			}
			if (mod_container[j + 1] == ' ' && word != 0)
			{
				ans = ans + pow(2, (7 - word));
				j++;
			}
			word++;
		}
		if (word == 8)
		{
			if (ans == 0)
				break;
			cr = ans * minus;
			s2[0] = cr;
			ans = 0;
			word = 0;
			minus = 1;
			desten_message += s2;
		}
	}
	//cout << desten_message << endl;

	ofstream de_sten_message("texts\\de_sten_message.txt");
	if (!de_sten_message.is_open())
	{
		cout << "Файл de_sten_message.txt не может быть открыт!\n";
		return 4;
	}
	de_sten_message << desten_message; // запись строки в файл
	de_sten_message.close();

	delete [] mod_container;
	system("pause");
	return 0;
}

