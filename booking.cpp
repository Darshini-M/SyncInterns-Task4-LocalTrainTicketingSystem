#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class Ticket {
private:
    std::string passengerName;
    int seatNumber;
    bool isBooked;

public:
    Ticket() : passengerName(""), seatNumber(-1), isBooked(false) {}

    void BookTicket(const std::string& name, int seat) {
        if (!isBooked) {
            passengerName = name;
            seatNumber = seat;
            isBooked = true;
            std::cout << "Ticket booked for " << passengerName << " at seat " << seatNumber << std::endl;
        } else {
            std::cout << "Seat " << seatNumber << " is already booked by " << passengerName << std::endl;
        }
    }

    void DisplayTicket() const {
        if (isBooked) {
            std::cout << "Passenger: " << passengerName << " | Seat: " << seatNumber << std::endl;
        } else {
            std::cout << "This ticket is not booked." << std::endl;
        }
    }
};

class Train {
private:
    std::string routeName;
    std::string from;
    std::string to;
    std::string departureTime;
    int totalSeats;
    std::vector<Ticket> tickets;

public:
    Train(const std::string& route, const std::string& fromStation, const std::string& toStation, const std::string& departTime, int seats)
        : routeName(route), from(fromStation), to(toStation), departureTime(departTime), totalSeats(seats) {
        for (int i = 0; i < totalSeats; ++i) {
            tickets.push_back(Ticket());
        }
    }

    void BookTicket(const std::string& passengerName, int seatNumber) {
        if (seatNumber < 0 || seatNumber >= totalSeats) {
            std::cout << "Invalid seat number." << std::endl;
            return;
        }

        tickets[seatNumber].BookTicket(passengerName, seatNumber);
    }

    void DisplayTickets() const {
        std::cout << "Tickets for " << routeName << " train (From: " << from << " To: " << to << " Departure: " << departureTime << "):" << std::endl;
        for (int i = 0; i < totalSeats; ++i) {
            std::cout << "Seat " << i << ": ";
            tickets[i].DisplayTicket();
        }
    }

    std::string GetRouteName() const {
        return routeName;
    }

    std::string GetFrom() const {
        return from;
    }

    std::string GetTo() const {
        return to;
    }

    std::string GetDepartureTime() const {
        return departureTime;
    }
};

void PrintBox(const std::string& text) {
    int width = text.length() + 4;
    std::string line(width, '*');

    std::cout << line << std::endl;
    std::cout << "* " << text << " *" << std::endl;
    std::cout << line << std::endl;
}

int main() {
    std::vector<Train> trains;
    trains.emplace_back("City Express", "Station A", "Station B", "08:00 AM", 10);
    trains.emplace_back("Suburban Shuttle", "Station C", "Station D", "09:30 AM", 8);
    trains.emplace_back("Rapid Rail", "Station E", "Station F", "10:45 AM", 12);

    int choice;

    while (true) {
        std::cout << "Select an option:" << std::endl;
        std::cout << "1. Display available trains" << std::endl;
        std::cout << "2. Book a ticket" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            PrintBox("Available Trains");
            std::cout << std::left << std::setw(4) << "No." << std::setw(20) << "Route" << std::setw(20) << "From" << std::setw(20) << "To" << std::setw(15) << "Departure" << std::endl;
            for (size_t i = 0; i < trains.size(); ++i) {
                std::cout << std::setw(4) << i + 1 << std::setw(20) << trains[i].GetRouteName() << std::setw(20) << trains[i].GetFrom() << std::setw(20) << trains[i].GetTo() << std::setw(15) << trains[i].GetDepartureTime() << std::endl;
            }
            std::cout << std::endl;
        } else if (choice == 2) {
             int trainIndex, seatNumber;
            std::string passengerName;

            std::cout << "Select a train (1-" << trains.size() << "): ";
            std::cin >> trainIndex;
            trainIndex--;

            if (trainIndex < 0 || trainIndex >= trains.size()) {
                std::cout << "Invalid train selection." << std::endl;
                continue;
            }

            std::cout << "Enter passenger name: ";
            std::cin.ignore();
            std::getline(std::cin, passengerName);

            std::cout << "Enter seat number: ";
            std::cin >> seatNumber;

            trains[trainIndex].BookTicket(passengerName, seatNumber);
        } else if (choice == 3) {
            std::cout << "Exiting. Thank you!" << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
