#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class Ticket {
private:
    std::string passengerName;
    bool isBooked;

public:
    Ticket() : passengerName(""), isBooked(false) {}

    void BookTicket(const std::string& name) {
        if (!isBooked) {
            passengerName = name;
            isBooked = true;
            std::cout << "Ticket booked for " << passengerName << std::endl;
        } else {
            std::cout << "This seat is already booked by " << passengerName << std::endl;
        }
    }

    void DisplayTicket(int seatNumber) const {
        if (isBooked) {
            std::cout << "Seat " << seatNumber << ": Passenger: " << passengerName << std::endl;
        } else {
            std::cout << "Seat " << seatNumber << ": This seat is not booked." << std::endl;
        }
    }

    bool IsBooked() const {
        return isBooked;
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

        tickets[seatNumber].BookTicket(passengerName);
    }

    void DisplayTickets() const {
        std::cout << "Tickets for " << routeName << " train (From: " << from << " To: " << to << " Departure: " << departureTime << "):" << std::endl;
        for (int i = 0; i < totalSeats; ++i) {
            std::cout << "Seat " << i << ": ";
            tickets[i].DisplayTicket(i);
        }
    }

    void DisplayBookedTickets() const {
        PrintBox("Booked Tickets");
        for (int i = 0; i < totalSeats; ++i) {
            tickets[i].DisplayTicket(i);
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

    int GetTotalSeats() const {
        return totalSeats;
    }

    bool IsSeatBooked(int seatNumber) const {
        if (seatNumber < 0 || seatNumber >= totalSeats) {
            return true; // Invalid seat number is considered booked
        }
        return tickets[seatNumber].IsBooked();
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
        std::cout << "3. View booked tickets" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            PrintBox("Available Trains");
            std::cout << std::left << std::setw(4) << "No." << std::setw(20) << "Route" << std::setw(20) << "From" << std::setw(20) << "To" << std::setw(15) << "Departure" << std::setw(15) << "Seats" << std::endl;
            for (size_t i = 0; i < trains.size(); ++i) {
                std::cout << std::setw(4) << i + 1 << std::setw(20) << trains[i].GetRouteName() << std::setw(20) << trains[i].GetFrom() << std::setw(20) << trains[i].GetTo() << std::setw(15) << trains[i].GetDepartureTime() << std::setw(15) << trains[i].GetTotalSeats() << std::endl;
            }
            std::cout << std::endl;
        } else if (choice == 2) {
            int trainIndex, numSeats, seatNumber;
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

            std::cout << "Enter number of seats to book: ";
            std::cin >> numSeats;

            if (numSeats <= 0 || numSeats > trains[trainIndex].GetTotalSeats()) {
                std::cout << "Invalid number of seats." << std::endl;
                continue;
            }

            for (int i = 0; i < numSeats; ++i) {
                std::cout << "Enter seat number " << i + 1 << " (0-" << trains[trainIndex].GetTotalSeats() - 1 << "): ";
                std::cin >> seatNumber;

                if (seatNumber < 0 || seatNumber >= trains[trainIndex].GetTotalSeats()) {
                    std::cout << "Invalid seat number." << std::endl;
                    continue;
                }

                if (trains[trainIndex].IsSeatBooked(seatNumber)) {
                    std::cout << "Seat " << seatNumber << " is already booked." << std::endl;
                } else {
                    std::cout << "Enter passenger name for seat " << seatNumber << ": ";
                    std::cin.ignore();
                    std::getline(std::cin, passengerName);
                    trains[trainIndex].BookTicket(passengerName, seatNumber);
                }
            }
        } else if (choice == 3) {
            int trainIndex;

            std::cout << "Select a train (1-" << trains.size() << "): ";
            std::cin >> trainIndex;
            trainIndex--;

            if (trainIndex < 0 || trainIndex >= trains.size()) {
                std::cout << "Invalid train selection." << std::endl;
                continue;
            }

            trains[trainIndex].DisplayBookedTickets();
        } else if (choice == 4) {
            std::cout << "Exiting. Thank you!" << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
