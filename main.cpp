#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Содержание каждого задания
struct Task {
    string name;    // Название 
    int start;      // Время начала 
    int duration;   // Продолжительность 
    int end;        // Время окончания 
    int points;     // Баллы 
};

// Сравнение для сортировки заданий
bool compareTasks(Task a, Task b) {
    if (a.end != b.end) {
        return a.end < b.end; 
    }
    return a.start < b.start; 
}

int main() {
    // Ввод данных
    int n;
    cin >> n;
    vector<Task> tasks(n);
    for (int i = 0; i < n; i++) {
        cin >> tasks[i].name >> tasks[i].start >> tasks[i].duration >> tasks[i].points;
        tasks[i].end = tasks[i].start + tasks[i].duration; // Вычисляем время окончания
    }

    // Сортировка заданий по времени окончания, а при равенстве по времени начала
    sort(tasks.begin(), tasks.end(), compareTasks);

    // Для каждого задания находим последнее задание, которое можно выполнить до него
    vector<int> comp(n, -1); // Индекс совместимого задания или -1 если такого нет
    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (tasks[j].end <= tasks[i].start) {
                comp[i] = j;
                break;
            }
        }
    }

    // Вычисляем максимальное количество баллов, которое можно получить
    vector<long> maxP(n, 0); // maxPoints[i] - максимальные баллы для первых заданий
    maxP[0] = tasks[0].points; // Только первое задание

    for (int i = 1; i < n; i++) {
        // Баллы, если включаем текущее задание
        long pointsWithCurrent = tasks[i].points;
        if (comp[i] != -1) {
            pointsWithCurrent += maxP[comp[i]];
        }

        // Выбираем максимум между включением и исключением текущего задания
        maxP[i] = max(pointsWithCurrent, maxP[i - 1]);
    }

    cout << maxP[n - 1] << endl; // Выводим максимальное количество баллов

    // Восстанавливаем выбранные задания
    vector<string> sel;
    int curr = n - 1;
    while (curr >= 0) {
        if (curr == 0) {
            if (maxP[0] > 0) {
                sel.push_back(tasks[0].name);
            }
            break;
        }
        if (maxP[curr] == maxP[curr - 1]) {
            curr--; // Текущее задание не было выбрано
        }
        else {
            sel.push_back(tasks[curr].name); 
            curr = comp[curr]; // Переходим к предыдущему совместимому заданию
        }
    }

    // Выводим имена заданий в правильном порядке
    reverse(sel.begin(), sel.end());
    for (int i = 0; i < sel.size(); i++) {
        if (i > 0) cout << " ";
        cout << sel[i];
    }
    cout << endl;

    return 0;
}
