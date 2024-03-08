#include <algorithm>
#include <iostream>
#include <vector>

void printArr(std::vector<int> arr);
void countingSort(std::vector<int> &arr);
void remove_duplic(std::vector<int> &arr);
void fill_vector(std::vector<int> &arr, char name);
char u_have_choise(void);
void u_have_answer(char name, std::vector<int> arr1, std::vector<int> arr2);

void unification(std::vector<int> arr1, std::vector<int> arr2);
void intersection(std::vector<int> arr1, std::vector<int> arr2);
void difference(std::vector<int> arr1, std::vector<int> arr2);
void entry_A_B(std::vector<int> arr1, std::vector<int> arr2);
void entry_B_A(std::vector<int> arr1, std::vector<int> arr2);

int main(void) {

  size_t size1;

  size_t size2;

  std::cout << "Введите количество элементов для множества A и множества B "
               "через пробел."
            << std::endl;

  std::cin >> size1 >> size2;

  std::vector<int> first_vector(size1);

  std::vector<int> second_vector(size2);

  fill_vector(first_vector, 'A');

  fill_vector(second_vector, 'B');

  countingSort(first_vector);

  char answer = 's';

  while (answer != 'q') {
    answer = u_have_choise();
    u_have_answer(answer, first_vector, second_vector);
  }
}

void printArr(std::vector<int> arr) {
  std::cout << "\n..." << std::endl;
  for (int i = 0; i < arr.size(); i++) {
    std::cout << i + 1 << ": " << arr[i] << '\n';
  }
}

void countingSort(std::vector<int> &arr) {
  int max = arr[0];
  size_t n = arr.size();
  for (int i = 1; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  int *count = new int[max + 1]();

  for (int i = 0; i < n; i++) {
    count[arr[i]]++;
  }

  int index = 0;
  for (int i = 0; i <= max; i++) {
    while (count[i] > 0) {
      arr[index++] = i;
      count[i]--;
    }
  }

  delete[] count;

  remove_duplic(arr);
}

void remove_duplic(std::vector<int> &arr) {
  int n = arr.size();
  std::vector<int> unique;

  for (int i = 0; i < n; i++) {
    if (std::find(unique.begin(), unique.end(), arr[i]) == unique.end()) {
      unique.push_back(arr[i]);
    }
  }

  arr = unique;
}

void fill_vector(std::vector<int> &arr, char name) {
  std::cout << "Заполните множество " << name << " элементами." << std::endl;
  for (int i = 0; i < arr.size(); i++) {
    std::cout << i + 1 << ": ";
    std::cin >> arr[i];
  }
  std::cout << "\nМножество " << name << " успешно заполнено!\n" << std::endl;
}

char u_have_choise(void) {
  std::cout << "\nВыберите одно из действий или введите 'q' для выхода из "
               "программы:\n1. Найти объединение множеств.\n2. Найти "
               "пересечение множеств.\n3. Найти разность множеств.\n4. "
               "Проверить вхождение множества A в множество B.\n5. Проверить "
               "вхождение множества B в множество A.\n6. Вывести множество. "
            << '\n';
  char c;
  std::cin >> c;
  return c;
}

void u_have_answer(char name, std::vector<int> arr1, std::vector<int> arr2) {
  switch (name) {
  case '1':
    unification(arr1, arr2);
    break;
  case '2':
    intersection(arr1, arr2);
    break;
  case '3':
    difference(arr1, arr2);
    break;
  case '4':
    entry_A_B(arr1, arr2);
    break;
  case '5':
    entry_B_A(arr1, arr2);
    break;
  case '6':
    std::cout << "\nКакое множество вы хотите вывести, A или B?" << std::endl;
    char ch;
    std::cin >> ch;
    if (ch == 'A' || ch == 'a') {
      printArr(arr1);
    } else {
      printArr(arr2);
    }
    break;
  case 'q':
    exit(1);
    break;
  default:
    std::cout << "\nТакого варианта выбора не существует, попробуйте выбрать "
                 "другой.\n"
              << std::endl;
    break;
  }
}

void unification(std::vector<int> arr1, std::vector<int> arr2) {
  size_t size = arr1.size() + arr2.size();
  std::vector<int> un(size);
  for (int i = 0; i < arr1.size(); i++) {
    un[i] = arr1[i];
  }
  int arr2_count = 0;
  for (int i = arr1.size(); i < size; i++) {
    un[i] = arr2[arr2_count];
    arr2_count++;
  }
  arr2_count = 0;
  countingSort(un);
  remove_duplic(un);
  std::cout << "\nРезультат объединения двух множеств..." << std::endl;
  printArr(un);
}

void intersection(std::vector<int> arr1, std::vector<int> arr2) {
  size_t max = arr1[0];
  for (int i = 1; i < arr1.size(); i++) {
    if (arr1[i] > max) {
      max = arr1[i];
    }
  }

  for (int i = 1; i < arr2.size(); i++) {
    if (arr2[i] > max) {
      max = arr2[i];
    }
  }
  std::vector<int> count(max + 1);

  for (int i = 0; i < arr1.size(); i++) {
    count[arr1[i]]++;
  }

  for (int i = 0; i < arr2.size(); i++) {
    count[arr2[i]]++;
  }

  std::vector<int> result(arr1.size() + arr2.size());

  int index = 0;

  for (int i = 0; i < max + 1; i++) {
    if (count[i] == 2) {
      result[index++] = i;
    }
  }

  result.erase(std::remove(result.begin(), result.end(), 0), result.end());
  std::cout << "\nРезультат пересечения двух множеств..." << std::endl;
  printArr(result);
}

void difference(std::vector<int> arr1, std::vector<int> arr2) {
  size_t max = arr1[0];
  for (int i = 1; i < arr1.size(); i++) {
    if (arr1[i] > max) {
      max = arr1[i];
    }
  }

  for (int i = 1; i < arr2.size(); i++) {
    if (arr2[i] > max) {
      max = arr2[i];
    }
  }
  std::vector<int> count(max + 1);

  for (int i = 0; i < arr1.size(); i++) {
    count[arr1[i]]++;
  }

  for (int i = 0; i < arr2.size(); i++) {
    count[arr2[i]]++;
  }
  int index = 0;
  std::vector<int> result(arr1.size() + 1);
  for (int i = 0; i < arr1.size(); i++) {
    for (int j = 0; j < max; j++) {
      if (count[j] == 1 and j == arr1[i]) {
        result[index++] = j;
      }
    }
  }
  result.erase(std::remove(result.begin(), result.end(), 0), result.end());
  std::cout << "\nРезультат разницы двух множеств..." << std::endl;
  printArr(result);
}

void entry_A_B(std::vector<int> arr1, std::vector<int> arr2) {
  size_t count = 0;
  for (int i = 0; i < arr1.size(); i++) {
    for (int j = 0; j < arr2.size(); j++) {
      if (arr1[i] == arr2[j]) {
        count++;
      }
    }
  }
  if (count == arr1.size()) {
    std::cout << "\nМножество А входит в множество B\n" << std::endl;
  } else {
    std::cout << "\nМножество A не входит в множество B\n" << std::endl;
  }
}

void entry_B_A(std::vector<int> arr1, std::vector<int> arr2) {
  size_t count = 0;
  for (int i = 0; i < arr2.size(); i++) {
    for (int j = 0; j < arr1.size(); j++) {
      if (arr2[i] == arr1[j]) {
        count++;
      }
    }
  }
  if (count == arr2.size()) {
    std::cout << "\nМножество А входит в множество B\n" << std::endl;
  } else {
    std::cout << "\nМножество A не входит в множество B\n" << std::endl;
  }
}