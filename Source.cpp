#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
constexpr int g_price = 200;

class Room {
public:
    virtual bool m_reserve() = 0;
    int getNumBeds()
    {
        return m_numbeds;
    }
    void setNumBeds(int val)
    {
        this->m_numbeds = val;
        return;
    }
    int getPrice()
    {
        return m_price;
    }
    void setPrice(int val)
    {
        this->m_price = val;
        return;
    }
    double getFactor()
    {
        return m_factor;
    }
    void setFactor(double val)
    {
        this->m_factor = val;
    }
private:
    double m_factor = 0.;
    int m_price = 0;
    int m_numbeds = 0;
};

class StandardRoom : public Room {
public:
    StandardRoom()
    {
        setNumBeds(2);
        setFactor(2);
    }
    bool m_reserve() {
        std::cout << "Rezerwacja standardowego pokoju zakończona sukcesem!" << std::endl;
        return true;
    }
};

class SuiteRoom : public Room {
public:
    bool m_reserve() {
        std::cout << "Rezerwacja apartamentu zakończona sukcesem!" << std::endl;
        return true;
    }
    SuiteRoom()
    {
        setNumBeds(1);
        setFactor(3);
    }
};

class Hotel {
public:
    virtual void addRoom(Room* p_room) = 0;
    auto getRooms()
    {
        return rooms;
    }
protected:
    double getFactor()
    {
        return m_factor;
    }
    void setFactor(double val)
    {
        this->m_factor = val;
    }

    std::vector<Room*> rooms;
private:
    double m_factor = 0.;
};

class LuxuryHotel : public Hotel
{
public:
    LuxuryHotel()
    {
        setFactor(4);
    }
    void addRoom(Room* p_room) override
    {
        p_room->setPrice(g_price * this->getFactor() * p_room->getFactor());
        this->rooms.push_back(p_room);
    }
};

class BudgetHotel : public Hotel
{
public:
    BudgetHotel()
    {
        setFactor(2);
    }
    void addRoom(Room* p_room) override
    {
        p_room->setPrice(g_price * this->getFactor() * p_room->getFactor());
        this->rooms.push_back(p_room);
    }
};

template <typename T>
std::vector<T*> findRooms(std::vector<T*> rooms, int numBeds) {
    std::vector<T*> foundRooms;
    for (auto room : rooms) {
        if (room->getNumBeds() == numBeds) {
            foundRooms.push_back(room);
        }
    }
    return foundRooms;
}
class Compare
{
public:
    bool operator()(Room* a, Room* b)
    {
        return a->getPrice() < b->getPrice();
    }

};

int main() {

    std::vector<Hotel*> l_hotels;
    l_hotels.reserve(2);
    l_hotels.push_back(new LuxuryHotel());
    l_hotels.push_back(new BudgetHotel());
    l_hotels[0]->addRoom(new SuiteRoom());
    l_hotels[1]->addRoom(new StandardRoom());
    l_hotels[1]->addRoom(new SuiteRoom());
    l_hotels[0]->addRoom(new StandardRoom());
    l_hotels[0]->addRoom(new SuiteRoom());
    std::vector<Room*> foundRooms(findRooms(l_hotels[0]->getRooms(), 2));
    std::vector<Room*> foundRoomsinSecondHotel = findRooms(l_hotels[1]->getRooms(), 2);
    foundRooms.insert(std::end(foundRooms), std::begin(foundRoomsinSecondHotel), std::end(foundRoomsinSecondHotel));
    std::cout << "Znaleziono " << foundRooms.size() << " pokoje z 2 łóżkami:" << std::endl;
    std::sort(foundRooms.begin(), foundRooms.end(), Compare());
    for (std::vector<Room*>::iterator it = foundRooms.begin();it != foundRooms.end();it++)
    {
        std::cout << "Cena: " << (*it)->getPrice() << std::endl;
    }
    auto l_roomsInLuxuryHotel = l_hotels[0]->getRooms();
    int l_sum = std::accumulate(std::begin(l_roomsInLuxuryHotel), std::end(l_roomsInLuxuryHotel), 0,
        [](int x, Room* p_room)
        {
            return x + p_room->getPrice();
        });
    std::cout << "Suma cen pokojów w luksusowym hotelu " << l_sum << std::endl;
 
}