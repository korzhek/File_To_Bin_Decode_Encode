#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <bitset>
#include <string>


//test

using namespace std;

int get_size(int *size) {
	struct stat results;
	if (stat("in.jpg", &results) == 0) {
		*size = results.st_size;
		cout << "[+] Определен размер файла: " << *size << " байт" << endl;
	} else {
		cout << "[-] Ошибка чтения файла!" << endl;
		system("pause");
		return -1;
	}
	return *size;
}

void read(char *buffer, int size) {
	fstream myFile;
	myFile.open("in.jpg", ios::in | ios::binary);
	myFile.read(buffer, size);
	myFile.close();
	cout << "[+] Файл успешно прочитан." << endl;
}


void encode(char* buffer, int size, char* bits) {
	string byte;
	int count = 0;
	cout << "[*] Кодирование " << size << " байт в " << size * 8 << " бит." << endl;
	for (int i = 0; i < size; i++)
	{
		byte = bitset<8>(buffer[i]).to_string();
		for (int j = 0; j < 8; j++)
		{
			bits[count] = byte[j];
			//cout << bits[count];
			count++;
		}
	}
	//cout << endl;
}


void decode(char* buffer, int size, char* bits) {
	int count = 0;
	cout << "[*] Декодирование " << size * 8 << " бит в " << size << " байт." << endl;
	for (int i = 0; i < size; i++)
	{
		string byte;
		for (int j = 0; j < 8; j++)
		{
			byte += bits[count];
			count++;
		}
		buffer[i] = bitset<8>(byte).to_ulong();
		//cout << buffer[i];
	}
	
	//cout << endl;
}


void print(char* buffer, int size) {
	cout << "[!] Содержание буфера: ";
	for (int i = 0; i < size; i++)
	{
		cout << buffer[i];
	}
	cout << endl;
}

void write(char* buffer, int size) {
	fstream myFile;
	myFile.open("out.jpg", ios::out | ios::binary);
	myFile.write(buffer, size);
	myFile.close();
	cout << "[+] Файл успешно записан." << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	int size = get_size(&size);
	char *buffer = new char[size];
	char *bits = new char[size * 8];
	
	read(buffer, size);
	//print(buffer, size);
	encode(buffer, size, bits);
	decode(buffer, size, bits);
	write(buffer, size);

	delete[] buffer;
	delete[] bits;
	system("pause");
	return 0;
}
