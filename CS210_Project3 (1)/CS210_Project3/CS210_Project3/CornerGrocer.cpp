// File Header
// Name: Luis Tomassini
// Project: Corner Grocer Item Tracker
// Description: Program to track item purchases, display frequency data, and generate a histogram.

#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <limits>
using namespace std;

class GroceryTracker {
private:
    map<string, int> m_itemFrequency;

    void loadDataFromFile(const string& filename) {
        ifstream inFile(filename);
        string item;
        if (!inFile) {
            cerr << "Error: Unable to open file." << endl;
            return;
        }
        while (inFile >> item) {
            m_itemFrequency[item]++;
        }
        inFile.close();
    }

    void saveFrequencyToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error: Unable to open output file." << endl;
            return;
        }
        for (const auto& pair : m_itemFrequency) {
            outFile << pair.first << " " << pair.second << endl;
        }
        outFile.close();
    }

public:
    GroceryTracker(const string& inputFile) {
        loadDataFromFile(inputFile);
        saveFrequencyToFile("frequency.dat");
    }

    void searchItemFrequency() {
        string item;
        cout << "Enter the item name to search: ";
        cin >> item;
        auto it = m_itemFrequency.find(item);
        if (it != m_itemFrequency.end()) {
            cout << "Frequency of " << item << ": " << it->second << endl;
        }
        else {
            cout << "Item not found." << endl;
        }
    }

    void displayAllItems() {
        if (m_itemFrequency.empty()) {
            cout << "No items found in data file." << endl;
            return;
        }
        cout << "\nItem Frequency List:\n";
        for (const auto& pair : m_itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    void displayHistogram() {
        if (m_itemFrequency.empty()) {
            cout << "No items found in data file." << endl;
            return;
        }
        cout << "\nItem Purchase Histogram:\n";
        for (const auto& pair : m_itemFrequency) {
            cout << setw(15) << left << pair.first << " ";
            cout << string(pair.second, '*') << endl;
        }
    }
};

int main() {
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt");
    int choice;
    do {
        cout << "\nMenu Options:\n";
        cout << "1 - Search Item Frequency\n";
        cout << "2 - Display All Item Frequencies\n";
        cout << "3 - Display Histogram\n";
        cout << "4 - Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 4: ";
        }

        switch (choice) {
        case 1:
            tracker.searchItemFrequency();
            break;
        case 2:
            tracker.displayAllItems();
            break;
        case 3:
            tracker.displayHistogram();
            break;
        case 4:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
