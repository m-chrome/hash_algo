#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <set>
#include <unordered_map>

#include "ticket.hpp"

using namespace std;
using namespace ticket;

// Реализация "простой" (допускаются коллизии)
// хэш-функции получения хэша по номеру.
long long makeEasyHash(const string &key4hash)
{
    long long int easyHash=0;
    for(size_t i=0; i<key4hash.size(); i++)
    {
        easyHash += pow((key4hash[i] - '0' + 1),i);
    }
    return easyHash;
}

// Реализация "сложной" (минимизируются коллизии)
// хэш-функции получения хэша по номеру.
long long makeGoodHash(const string &key4hash)
{
    long long int goodHash=0;
    for(size_t i=0; i<key4hash.size(); i++)
    {
        goodHash += ((key4hash[i] - '0' + 1)*pow(i,i)+i);
    }
    return goodHash;
}

// Подсчёт коллизий в хэшированном контейнере
// Составляет set с "неуникальный хэш" и
// возвращает итоговое число коллизий.
long long calculateCollisions(unordered_multimap <long long, Ticket> list)
{
    long long collisions;
    set < long long > collHashes;
    for(auto &it: list)
    {
        if (list.count(it.first)>1)
        {
            collHashes.emplace(it.first);
        }
    }
    collisions=collHashes.size();
    collHashes.clear();
    return collisions;
}

// Хэш-поиск
// На вход подаём режим хэширования,
// контейнер с данными и ключ поиска
Ticket hashSearch(unordered_multimap <long long, Ticket> list, const string &key, const size_t &hashmode)
{
    long long keyHash;
    if (hashmode==1) keyHash=makeEasyHash(key);
    else if (hashmode==2) keyHash=makeGoodHash(key);
    if (list.count(keyHash)==0)
    {
        // Если билетов нет
        Ticket nullticket("",0,0,0,0);
        return nullticket;
    }
    for(auto &it: list)
    {
        if (keyHash==(it.second).getHash())
        {
            if (list.count(keyHash)>1)
            {
                // todo
                if (key==(it.second).getKey())
                    return it.second;
                else
                    continue;
            }
            else
                return it.second;
        }
    }
}

// Проверка найденного ключа на наличие
// или отсутствие в контейнере
void checkTicket(const Ticket &result)
{
    if (result.getKey()=="" &&
        result.getCost()== 0 &&
        result.getDate()== 0 &&
        result.getPrize()== 0 &&
        result.getHash()==0)
        cout << "These aren\'t tickets you are looking for." << endl;
    else
        cout << endl << result << endl;
}

int main()
{
    srand(time(0));

    // Открытие файла с данными по всем билетам
    ifstream data_list;
    data_list.open("ticket_list.txt");
    // Проверка на правильное открытие файла
    if (!data_list)
    {
        cout << "Can't open file!"<< endl;
        return 1;
    }

    // Шаблон для билета, более удобная форма
    struct ticketPattern {
        string number;
        size_t cost;
        size_t date;
        size_t prize;
    } form;

    cout << "Choose hash mode:" << endl;
    cout << "1) Print \'1\' for EasyHash" << endl;
    cout << "2) Print \'2\' for GoodHash" << endl;
    int hashMode;
    long long collisions;
    cin >> hashMode;
    if ((hashMode!=1) && (hashMode!=2))
    {
        cout << "Wrong mode!" << endl;
        return 1;
    }
    cout << "You chose " << hashMode << " mode." << endl << endl;
    unordered_multimap < long long, Ticket > ticketList;

    // Заполняем контейнер
    while(data_list >> form.number >> form.cost >> form.date >> form.prize)
    {
        Ticket item(form.number, form.cost, form.date, form.prize);
        if (hashMode==1) item.fillHash(makeEasyHash(form.number));
        else if (hashMode==2) item.fillHash(makeGoodHash(form.number));
        ticketList.emplace(item.getHash(), item);
    }
    /*cout << "Ticket list with hash:" << endl;
    for(auto &it: ticketList)
    {
        cout << it.second << endl;
    }*/
    cout << endl << "Some data we have: " << endl;
    cout << "Hash mode: " << hashMode << endl;
    cout << "Size: " << ticketList.size() << endl;
    collisions=calculateCollisions(ticketList);
    cout << "Collisions: " << collisions << endl << endl;
    cout << "Insert key (number of ticket): ";
    cin >> form.number;
    cout << "Result: ";
    double timer=(double)clock()/1000.0;
    checkTicket(hashSearch(ticketList, form.number, hashMode));
    timer = (double)clock()/1000.0 - timer;
    cout << "Runtime of hash search: " << timer << " msec." << endl;
    return 0;
}
