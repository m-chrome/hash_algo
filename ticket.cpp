#include <iostream>
#include <cstdlib>
#include <string>

#include "ticket.hpp"

using namespace std;

namespace ticket {

    // Конструктор пустого билета
    Ticket::Ticket()
        :
            number(""),
            cost(0),
            date(0),
            prize(0),
            thash(0)
    {}

    // Конструктор копирования в билет данных
    Ticket::Ticket(string tnum, size_t tcost, size_t tdate, size_t tprize)
        :
            number(tnum),
            cost(tcost),
            date(tdate),
            prize(tprize)
    {}

    // Конструктор копирования в билет данных (c хэшем)
    Ticket::Ticket(string tnum, size_t tcost, size_t tdate, size_t tprize, long long tthash)
        :
            number(tnum),
            cost(tcost),
            date(tdate),
            prize(tprize),
            thash(tthash)
    {}

    // Деструктор для билета
    Ticket::~Ticket()
    {
        number.clear();
    }

    // Геттеры для полей билета
    string Ticket::getKey() const
    {
        return number;
    }

    size_t Ticket::getCost() const
    {
        return cost;
    }

    size_t Ticket::getDate() const
    {
        return date;
    }

    size_t Ticket::getPrize() const
    {
        return prize;
    }

    long long Ticket::getHash() const
    {
        return thash;
    }

    // Сеттер для хэша
    void Ticket::fillHash(const long long &ticketHash)
    {
        thash=ticketHash;
    }

    // Перегрузка оператора вывода для билета
    ostream& operator<<(ostream& item, const Ticket& data)
    {
        item << data.getKey() << ' ' << data.getCost() << ' '
                << data.getDate() << ' ' << data.getPrize();
        return item;
    }
}
