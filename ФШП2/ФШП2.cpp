#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>
#include <string>
using namespace std;
// Структура для представления денежной суммы
struct Money {
	int pounds; // Фунты
	int shillings; // Шиллинги
	int pence; // Пенсы
};

// Функция для проверки корректности значения
bool isValidMoney(const Money& amount) {
	return (amount.pounds >= 0 && amount.shillings >= 0 && amount.pence >= 0
		&& amount.shillings < 20 && amount.pence < 12);
}

// Функция для увеличения суммы на заданное количество пенсов, шиллингов, фунтов
Money addMoney(const Money& original, int addedPence, int addedShillings, int addedPounds) {
	Money result = { original.pounds + addedPounds, original.shillings + addedShillings,
	original.pence + addedPence };

	// Приведение к максимально допустимым единицам
	while (result.pence >= 12) {
		result.shillings += 1;
		result.pence -= 12;
	}

	while (result.shillings >= 20) {
		result.pounds += 1;
		result.shillings -= 20;
	}

	return result;
}

Money TransferMoney(const Money& original) {
	Money result = { original.pounds,original.shillings,original.pence };
	while (result.pence >= 12) {
		result.shillings += 1;
		result.pence -= 12;
	}

	while (result.shillings >= 20) {
		result.pounds += 1;
		result.shillings -= 20;
	}

	return result;
}

// Функция для сложения двух денежных сумм
Money sumMoney(const Money& amount1, const Money& amount2) {
	return addMoney(amount1, amount2.pence, amount2.shillings, amount2.pounds);
}

// Функция для вычисления разности двух денежных сумм
Money subtractMoney(const Money& amount1, const Money& amount2) {
	return addMoney(amount1, -amount2.pence, -amount2.shillings, -amount2.pounds);
}

// Функция для перевода денежной суммы в пенсы
int moneyToPence(const Money& amount) {
	return amount.pounds * 240 + amount.shillings * 12 + amount.pence;
}

// Функция для вывода денежной суммы в формате »99–99–99»
void printMoney(const Money& amount) {
	std::cout « amount.pounds « "-" « amount.shillings « "-" « amount.pence;
}

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int count = 0;
	vector<Money> moneyList;
	while (true) {
		int pounds, shillings, pence;
		cout « "Введите сумму в фунтах, шерлингах и пенсах (например, 3 5 8): ";
		cin » pounds » shillings » pence;
		count = count + 1;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout « "Походу вы ввели не цифру ;(";
			cout « "Введите сумму еще раз: ";
			pounds = 0, shillings = 0, pence = 0;
			cin » pounds » shillings » pence;

		}
		Money money{ pounds, shillings, pence };
		if (isValidMoney(money)) {
			moneyList.push_back(money);
		}
		else {
			moneyList.push_back(TransferMoney(money));
		}
		cout « "Хотите продолжить вводить суммы? (да(+)/нет): ";
		string continueInput;
		cin » continueInput;

		if (continueInput != "+" && continueInput != "да") {
			break;
		}
	}

	for (const auto& money : moneyList) {
		cout « "Сумма: " « money.pounds « " фунтов, " « money.shillings « " шерлингов, " « money.pence « " пенсов" « std::endl;
	}
	while (true) {
		int c = 0, c1, c2;
		cout « "Хотите ли вы сложить две суммы? 1 - да, 0 - нет" « endl;
		cin » c;
		if (c == 1) {
			cout « "Введите номера сумм: "; cin » c1 » c2;
			printMoney(sumMoney(moneyList[c1 - 1], moneyList[c2 - 1]));
			cout « endl;
		}
		else { break; }
	}
	while (true) {
		int c = 0, c1, c2;
		cout « "Хотите ли вы вычесть две суммы? 1 - да, 0 - нет" « endl;
		cin » c;
		if (c == 1) {
			cout « "Введите номера сумм: "; cin » c1 » c2;
			Money difference = subtractMoney(moneyList[c1 - 1], moneyList[c2 - 1]);
			int differenceValue = std::abs(moneyToPence(difference));
			int f, sh;

			sh = differenceValue / 12;
			differenceValue = differenceValue % 12;
			f = sh / 20;
			cout « f « "-" « sh « "-" « differenceValue;

			//printMoney(subtractMoney(moneyList[c1 - 1], moneyList[c2 - 1]));
			cout « endl;
		}
		else { break; }
	}
	int n = moneyList.size();

	int ex
		= 0;

	Money sumTotal = { 0, 0, 0 };
	for (const auto& amount : moneyList) {
		sumTotal = sumMoney(sumTotal, amount);
	}
	Money average = { sumTotal.pounds / n, sumTotal.shillings / n, sumTotal.pence / n };


	Money closestPair1, closestPair2, farthestPair1, farthestPair2;
	int minDifference = INT_MAX;
	int maxDifference = INT_MIN;

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			Money difference = subtractMoney(moneyList[i], moneyList[j]);
			int differenceValue = std::abs(moneyToPence(difference));

			if (differenceValue < minDifference) {
				minDifference = differenceValue;
				closestPair1 = moneyList[i];
				closestPair2 = moneyList[j];
			}

			if (differenceValue > maxDifference) {
				maxDifference = differenceValue;
				farthestPair1 = moneyList[i];
				farthestPair2 = moneyList[j];
			}
		}
	}

	// Вывод результатов
	cout « "\n\nРезультаты:\n";
	cout « "Среднее значение: ";
	printMoney(average);
	cout « "\nБлижайщая пара: ";
	printMoney(closestPair1);
	cout « " и ";
	printMoney(closestPair2);
	cout « "\nДальняя пара: ";
	printMoney(farthestPair1);
	cout « " и ";
	printMoney(farthestPair2);



	return 0;

}