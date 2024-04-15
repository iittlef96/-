#include <iostream>
//#include <windows.h>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <limits>
//Магазин косметики , Чикуля
// Размеры
int size = 10;
int receiptSize = 1;

// Глобальные массивы склада
int* idArr = new int[size];
std::string* nameArr = new std::string[size];
int* countArr = new int[size];
double* priceArr = new double[size];

// Глобальные массивы чека
std::string* nameReceiptArr = new std::string[receiptSize];
int* countReceiptArr = new int[receiptSize];
double* priceReceiptArr = new double[receiptSize];

// Объявление функций
void Start();
void CreateStorage();

template <typename ArrType>
void FillArray(ArrType staticArray[], ArrType dinArray[], int size);

void AddElementToReceipt(int& receiptSize, int id, int count);


void Shop();
void ShowStorage();
void Selling();
void PrintReceipt();
void ChangePrice();
void RemoveFromStorage();
void AddToStorage();
void ChangeStorage();
void ElementToEnd();
void DeleteElementByIndex();

// Тестовые функции

template <typename ArrType>
void PrintArray(ArrType arr[], int size);





int main()
{
	setlocale(LC_ALL, "ru");

	Start();

	delete[]idArr;
	delete[]nameArr;
	delete[]countArr;
	delete[]priceArr;
	delete[]nameReceiptArr;
	delete[]countReceiptArr;
	delete[]priceReceiptArr;
	system("pause");
	return 0;
}


void Start()
{
	std::string adminLogin = "admin";
	std::string adminPassword = "admin";
	std::string login, password;
	bool exit = false;
	int choose;
	std::cout << "\n\t\t\tДобро пожаловать в магазин Чикуля\n\n";
	do
	{
		std::cout << "Логин: ";
		std::getline(std::cin, login, '\n');
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Пароль: ";
		std::getline(std::cin, password, '\n');

		if (login!= adminLogin || password != adminPassword)
		{
			std::cerr << "Неверный логин и пароль\n\n";
			std::cout << "Попробовать еще раз? \n1- Да \n2 - Выход из программы";
			std::cin >> choose;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (choose == 2)
			{
				exit = true;
			}
		}
		else
		{
			exit = true;
			int chooseStorageType;
			do
			{
			std::cout << "Выберите формат склада: \n1 - Готовый склад\n2 - Создать склад вручную \n";
			std::cin >>chooseStorageType;

			} while (chooseStorageType < 1 || chooseStorageType > 2);
			if (chooseStorageType == 1)
			{
			CreateStorage();
			Shop();
			}
			else if (chooseStorageType == 2)
			{
				//В разработке    
			}
			else
			{
				std::cerr<<"Error chooseStorageType";
			}
		}

	} while (!exit);

}

void CreateStorage()
{
	const int staticSize = 10;
	int id[staticSize]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::string name[staticSize]{"Тушь  Dolce&Gabbana", "Помада Shanel", "Кисточка Vivien Sabo", 
		"Румяна Stellary", "Хайлайтер Pupa", "Бронзер Puse", "Пудра Nars", "Тени Tom Ford",
		"Гель для бровей Vivien Sabo", };
	int count[staticSize]{100, 80, 90, 120, 89, 100, 95, 80, 102, 150};
	double priceA[staticSize]{1020.9, 2490.9, 260.9, 659.0, 369.9, 599.0, 529.9, 1799.0, 260.9 };
	FillArray(id, idArr, staticSize);
	FillArray(name, nameArr, staticSize);
	FillArray(count, countArr, staticSize);
	FillArray(priceA, priceArr, staticSize);
}

template <typename ArrType>
void FillArray(ArrType staticArray[], ArrType dinArray[], int size)
{
	for (int i = 0; i < size; i++)
	{
		dinArray[i] = staticArray[i];
	}
}

template<typename ArrType>
void PrintArray(ArrType arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
}

void Shop()
{
	int choose;
	while (true)
	{
		do
		{
			std::cout << "\n1 - Показать склад \n2 - Начать продажу \n3 - Изменить цену \n4 - Списать товар \n5 - Пополнить товар \n6 - Изменение склада \n0 - Закончить смену";
			std::cin >> choose;
		} while (choose < 0 || choose > 6);
		if (choose ==1)
		{
			ShowStorage();
		}
		else if (choose == 2)
		{
			Selling();
		}
		else if (choose == 3)
		{
			ChangePrice();
		}
		else if (choose == 4)
		{
			RemoveFromStorage();
		}
		else if (choose == 5)
		{
			AddToStorage();
		}
		else if (choose == 6)
		{
			ChangeStorage();
		}
		else if (choose == 0)
		{
			break;
		}
		else
		{
			std::cerr << "Erorr";
		}


	}
}
void ShowStorage()
{
	std::cout << "id \t\t Название\t\t\t\t\tЦена\t Кол-во\n\n";
	for (int i = 0; i < size; i++)
	{
		std::cout << idArr[i] + 1 << "\t" << nameArr[i] << "\t\t" <<
			priceArr[i] << "\t" << countArr[i] << "\n";
	}
}

void Selling()
{

	int chooseId = 0, chooseCount = 0, confirm = 0;
	double totalSum = 0;
	bool isFirst = true;
	while (true)
	{
		totalSum = 0;
		do
		{
			std::cout << "Введите id товара для покупки: ";
			std::cin >> chooseId;
			if (chooseId < 1 || chooseId > size)
			{
				std::cerr << "Нет такого Id\n";
				continue;
			}

			if (countArr[chooseId - 1] > 0)
			{
				while (true)
				{
					std::cout << "\nВы выбрали: " << nameArr[chooseId - 1] << "\n";
					std::cout << "Кол-во товара на складе: " << countArr[chooseId - 1] << "\n";
					std::cout << "Выберите кол-во товара для покупки: ";
					std::cin >> chooseCount;
					if (chooseCount < 1 || chooseCount > countArr[chooseId - 1])
					{
						std::cerr << "Товара не хватает\n";
						continue;
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				std::cerr << "Этого товара нет на складе\n";
				continue;
			}




			std::cout << "\nВы выбрали: " << nameArr[chooseId - 1] << "\n";
			std::cout << "В кол-ве " << chooseCount << "\n";
			std::cout << "Подтвердите выбор: \n1 - подтвердить\n2 - отмена\n";
			std::cin >> confirm;

			if (confirm == 1)
			{
				if (isFirst)
				{
					isFirst = false;
					nameReceiptArr[receiptSize - 1] = nameArr[chooseId - 1];
					countReceiptArr[receiptSize - 1] = chooseCount;
					priceReceiptArr[receiptSize - 1] = priceArr[chooseId - 1] * chooseCount;
					countArr[chooseId - 1] -= chooseCount;
				}
				else if (!isFirst)
				{
					AddElementToReceipt(receiptSize, chooseId, chooseCount);
				}

			}
			else
			{
				continue;
			}

			std::cout << "Купить ещё 1 товар? ";
			std::cout << "\n1 - Да\n2 - Нет\nВаш выбор: ";
			std::cin >> confirm;

			if (confirm == 1)
			{
				continue;
			}
			break;
		} while (true);

		PrintReceipt();

		// Сделать скидки
		// Вывести итого с учётом скидок


		// totalSum;


	}



}

void PrintReceipt()
{

	std::cout << "Название\t\t\t\t\tКол-во\tЦена\n\n";
	for (int i = 0; i < receiptSize; i++)
	{
		std::cout << nameReceiptArr[i] << "\t\t\t" << countReceiptArr[i] <<
			priceReceiptArr[i] << "\t" << "\n";
	}


}

void ChangePrice()
{
	int id;
	double newPrice = 0;

	do
	{
		std::cout << "Введите id товара: ";
		std::cin >> id;
	} while (id < 1 || id > idArr[size - 1]);

	std::cout << "\n\nТекущая цена продукта: " << nameArr[id - 1] << " = " << priceArr[id - 1];
	do
	{
		std::cout << "Введите новую цену товара: ";
		std::cin >> newPrice;
	} while (newPrice < 0.01 || newPrice > 100000.03);
	priceArr[id - 1] = newPrice;
	std::cout << "Изменение цены произошло успешно\n";
}

void RemoveFromStorage()
{
	int id;
	int goodCout = 0;

	do
	{
		std::cout << "Введите id товара: ";
		std::cin >> id;
	} while (id < 1 || id > idArr[size - 1]);

	std::cout << "\n\nТекущее кол-во товара: " << nameArr[id - 1] << " = " << countArr[id - 1];
	do
	{
		std::cout << "\nСколько списать товара со склада: ";
		std::cin >> goodCout;
	} while (goodCout < countArr[id - 1]);
	countArr[id - 1] = goodCout;
	std::cout << "Списание товара произошло успешно\n";
}

void AddToStorage()
{
	int id;
	int goodCout = 0;

	do
	{
		std::cout << "Введите id товара: ";
		std::cin >> id;
	} while (id < 1 || id > idArr[size - 1]);

	std::cout << "\n\nТекущее кол-во товара: " << nameArr[id - 1] << " = " << countArr[id - 1];
	do
	{
		std::cout << "\nСколько lдобавить товара: ";
		std::cin >> goodCout;
	} while (goodCout < 0);
	countArr[id - 1] += goodCout;
	std::cout << "Добавление товара произошло успешно\n";
}

void AddElementToReceipt(int& receiptSize, int id, int count)
{

	std::string* nameReceiptArrTemp = new std::string[receiptSize];
	int* countReceiptArrTemp = new int[receiptSize];
	double* priceReceiptArrTemp = new double[receiptSize];

	for (int i = 0; i < receiptSize; i++)
	{
		nameReceiptArrTemp[i] = nameReceiptArr[i];
		countReceiptArrTemp[i] = countReceiptArr[i];
		priceReceiptArrTemp[i] = priceReceiptArr[i];
	}
	delete[]nameReceiptArr;
	delete[]countReceiptArr;
	delete[]priceReceiptArr;

	receiptSize++;
	nameReceiptArr = new std::string[receiptSize];
	countReceiptArr = new int[receiptSize];
	priceReceiptArr = new double[receiptSize];

	for (int i = 0; i < receiptSize - 1; i++)
	{
		nameReceiptArr[i] = nameReceiptArrTemp[i];
		countReceiptArr[i] = countReceiptArrTemp[i];
		priceReceiptArr[i] = priceReceiptArrTemp[i];
	}
	nameReceiptArr[receiptSize - 1] = nameArr[id - 1];
	countReceiptArr[receiptSize - 1] = count;
	priceReceiptArr[receiptSize - 1] = priceArr[id - 1] * count;
	countArr[id - 1] -= count;
	delete[]nameReceiptArrTemp;
	delete[]countReceiptArrTemp;
	delete[]priceReceiptArrTemp;

}

void ChangeStorage()
{
	int choose;
	do
	{

	std::cout << "Изменение склада. \n1 - добавить новый товар \n2 - удалить товар\n 3 - выйти\n";
	std::cin >> choose;

	} while (choose < 1 || choose > 3);
	if (choose == 1)
	{
		ElementToEnd();
	}
	else if (choose == 2)
	{
		DeleteElementByIndex();
	}
	else if (choose == 3)
	{
		std::cout << "Выход";
	}


}

void ElementToEnd()
{
	int* idArrTemp = new int[size];
	std::string* nameArrTemp = new std::string[size];
	int* countArrTemp = new int[size];
	double* priceArrTemp = new double[size];

	for (int i = 0; i < size; i++)
	{
		idArrTemp[i] = idArr[i];
		nameArrTemp[i] = nameArr[i];
		countArrTemp[i] = countArr[i];
		priceArrTemp[i] = priceArr[i];
	}
	delete[]idArr;
	delete[]nameArr;
	delete[]countArr;
	delete[]priceArr;

	size++;
	idArr = new int[size];
	nameArr = new std::string[size];
	countArr = new int[size];
	priceArr = new double[size];
	for (int i = 0; i < size - 1; i++)
	{
		idArr[i] = idArrTemp[i];
		nameArr[i] = nameArrTemp[i];
		countArr[i] = countArrTemp[i];
		priceArr[i] = priceArrTemp[i];

	}
	idArr[size - 1] = size - 1;
	std::cout << "\nВВедите имя нового товара";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, nameArr[size - 1]);
	std::cout << "\nВВедите количество нового товара";
	std::cin >> countArr[size - 1];
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "\nВведите цену нового товара";
	std::cin >> priceArr[size - 1];
	std::cout << "\nТовар успешно добавлен\n";

	delete[]idArrTemp;
	delete[]nameArrTemp;
	delete[]countArrTemp;
	delete[]priceArrTemp;
}

void DeleteElementByIndex()
{

	int* idArrTemp = new int[size];
	std::string* nameArrTemp = new std::string[size];
	int* countArrTemp = new int[size];
	double* priceArrTemp = new double[size];

	for (int i = 0; i < size; i++)
	{
		idArrTemp[i] = idArr[i];
		nameArrTemp[i] = nameArr[i];
		countArrTemp[i] = countArr[i];
		priceArrTemp[i] = priceArr[i];
	}
	delete[]idArr;
	delete[]nameArr;
	delete[]countArr;
	delete[]priceArr;

	size--;
	idArr = new int[size];
	nameArr = new std::string[size];
	countArr = new int[size];
	priceArr = new double[size];

	int index = 0;
	std::cout << "Какой товар удалить? id\n";
	std::cin >> index;

	for (int i = 0, j = 0; i < size, j < size; i++, j++)
	{
		if (i == index - 1)
		{
			i++;
			idArr[j] = idArrTemp[j];
			nameArr[j] = nameArrTemp[i];
			countArr[j] = countArrTemp[i];
			priceArr[j] = priceArrTemp[i];
		}
		else
		{
			idArr[j] = idArrTemp[j];
			nameArr[j] = nameArrTemp[i];
			countArr[j] = countArrTemp[i];
			priceArr[j] = priceArrTemp[i];
		}
	}
	std::cout << "Удаление товара завершено\n";
	delete[]idArrTemp;
	delete[]nameArrTemp;
	delete[]countArrTemp;
	delete[]priceArrTemp;
}
