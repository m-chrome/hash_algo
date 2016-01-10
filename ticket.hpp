#ifndef TICKET_HPP
#define TICKET_HPP

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

namespace ticket {

class Ticket
{
    private:

        string number;
        size_t cost;
        size_t date;
        size_t prize;
        long long thash;

    public:

        // Конструктор пустого билета
        Ticket();

        // Конструктор копирования в билет данных
        Ticket(string tnum, size_t tcost, size_t tdate, size_t tprize);

        Ticket(string tnum, size_t tcost, size_t tdate, size_t tprize, long long tthash);

        // Деструктор для билета
        ~Ticket();

        // Геттеры для данных
        string getKey() const;
        size_t getCost() const;
        size_t getDate() const;
        size_t getPrize() const;
        long long getHash() const;

        // Сеттер для хэша
        void fillHash(const long long &ticketHash);        
};

ostream& operator<<(ostream& item, const Ticket& data);

}
#endif // TICKET_HPP

