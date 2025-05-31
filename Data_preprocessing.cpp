#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <iomanip>
#include <limits>
#include <cmath>

struct Passenger {
    int PassengerId;
    int Survived;
    int Pclass;
    std::string Name;
    std::string Sex;
    double Age;
    int SibSp;
    int Parch;
    std::string Ticket;
    double Fare;
    std::string Cabin;
    std::string Embarked;
    std::string AgeCategory;
    std::string Surname;
};

double median(std::vector<double> v) {
    v.erase(std::remove_if(v.begin(), v.end(), [](double x){ return std::isnan(x); }), v.end());
    if (v.empty()) return std::numeric_limits<double>::quiet_NaN();
    std::sort(v.begin(), v.end());
    size_t mid = v.size() / 2;
    return (v.size() % 2) ? v[mid] : (v[mid-1] + v[mid]) / 2.0;
}

std::string mode(const std::vector<std::string>& v) {
    std::map<std::string, int> freq;
    for (auto& s : v) if (!s.empty()) freq[s]++;
    return std::max_element(freq.begin(), freq.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    })->first;
}

std::string categorize_age(double age) {
    if (age <= 12) return "Child";
    if (age <= 19) return "Teen";
    if (age <= 35) return "Adult";
    if (age <= 60) return "Middle-Aged";
    return "Senior";
}

int main() {
    using std::numeric_limits;
    const double NaN = numeric_limits<double>::quiet_NaN();

    std::vector<Passenger> data = {
        {21, 0, 2, "Ali, Mr. Ahmed",      "male",   54, 0, 0, "202000", 25.50, "C123",     "C"},
        {22, 1, 1, "Khan, Miss. Zainab",  "female", NaN, 0, 1, "203003", 75.25, "",         "S"},
        {23, 0, 3, "Rehman, Mr. Tariq",   "male",   36, 0, 0, "200010", 7.00,  "",         ""},
        {24, 1, 2, "Fatima, Mrs. Ayesha", "female", 28, 1, 2, "203999", 32.00, "D50",      "Q"},
        {25, 1, 3, "Javed, Miss. Noor",   "female", 17, 0, 0, "209111", 8.00,  "Unknown",  ""}
    };

    std::vector<std::string> embarkedList;
    for (auto& p : data) if (!p.Embarked.empty()) embarkedList.push_back(p.Embarked);
    std::string embarkedMode = mode(embarkedList);
    for (auto& p : data) if (p.Embarked.empty()) p.Embarked = embarkedMode;

    std::vector<double> ageList;
    for (auto& p : data) ageList.push_back(p.Age);
    double ageMedian = median(ageList);
    for (auto& p : data) if (std::isnan(p.Age)) p.Age = ageMedian;

    for (auto& p : data) if (p.Cabin.empty()) p.Cabin = "Not Assigned";

    for (auto& p : data) p.AgeCategory = categorize_age(p.Age);

    for (auto& p : data) p.Surname = p.Name.substr(0, p.Name.find(','));

    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(8)  << "Surv"
              << std::setw(6)  << "Age"
              << std::setw(13) << "AgeGroup"
              << std::setw(10) << "Embarked"
              << std::setw(15) << "Cabin"
              << std::setw(10) << "Surname" << '\n';

    std::cout << std::string(70, '-') << '\n';

    for (auto& p : data) {
        std::cout << std::setw(5)  << p.PassengerId
                  << std::setw(8)  << p.Survived
                  << std::setw(6)  << p.Age
                  << std::setw(13) << p.AgeCategory
                  << std::setw(10) << p.Embarked
                  << std::setw(15) << p.Cabin
                  << std::setw(10) << p.Surname << '\n';
    }
    return 0;
}
