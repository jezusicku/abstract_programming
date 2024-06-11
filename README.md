Hotel Room Reservation System
Overview
This C++ program simulates a hotel room reservation system. It features different types of hotels and rooms, enabling the user to reserve rooms, find rooms with specific attributes, and calculate the total price of rooms in a luxury hotel.

File Description
This program contains the following key components:

Classes
Room: Abstract base class representing a generic hotel room.

Attributes:
m_factor: Multiplication factor for the room price.
m_price: Price of the room.
m_numbeds: Number of beds in the room.
Methods:
virtual bool m_reserve() = 0: Pure virtual function for reserving the room.
Getters and setters for m_factor, m_price, and m_numbeds.
StandardRoom: Derived class from Room representing a standard room.

Methods:
StandardRoom(): Constructor setting the number of beds to 2 and the factor to 2.
bool m_reserve() override: Overrides m_reserve to simulate reserving a standard room.
SuiteRoom: Derived class from Room representing a suite room.

Methods:
SuiteRoom(): Constructor setting the number of beds to 1 and the factor to 3.
bool m_reserve() override: Overrides m_reserve to simulate reserving a suite room.
Hotel: Abstract base class representing a generic hotel.

Attributes:
rooms: Vector storing pointers to rooms.
m_factor: Multiplication factor for room prices.
Methods:
virtual void addRoom(Room* p_room) = 0: Pure virtual function for adding a room.
Getter for rooms.
Getters and setters for m_factor.
LuxuryHotel: Derived class from Hotel representing a luxury hotel.

Methods:
LuxuryHotel(): Constructor setting the factor to 4.
void addRoom(Room* p_room) override: Overrides addRoom to add a room with calculated price.
BudgetHotel: Derived class from Hotel representing a budget hotel.

Methods:
BudgetHotel(): Constructor setting the factor to 2.
void addRoom(Room* p_room) override: Overrides addRoom to add a room with calculated price.
Functions and Templates
template <typename T> std::vector<T*> findRooms(std::vector<T*> rooms, int numBeds): Finds rooms with a specified number of beds.
Compare: Functor class to compare rooms based on their price.
bool operator()(Room* a, Room* b): Returns true if the price of a is less than the price of b.
