#include <iostream>

class Time {
private:
    int hours, minutes, seconds;

    int toTotalSeconds() const {
        return hours * 3600 + minutes * 60 + seconds;
    }

    void setFromSeconds(int totalSeconds) {
        totalSeconds %= 86400;
        if (totalSeconds < 0) totalSeconds += 86400;

        hours = totalSeconds / 3600;
        minutes = (totalSeconds % 3600) / 60;
        seconds = totalSeconds % 60;
    }

public:
    Time() {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }

    Time(int h, int m, int s) {
        if (h >= 0 && h < 24) hours = h; else hours = 0;
        if (m >= 0 && m < 60) minutes = m; else minutes = 0;
        if (s >= 0 && s < 60) seconds = s; else seconds = 0;
    }

    Time timeToMidnight() const {
        int total = toTotalSeconds();
        int remaining = 0;
        if (total != 0) {
            remaining = 86400 - total;
        }

        Time result;
        result.setFromSeconds(remaining);
        return result;
    }

    void tick() {
        seconds++;
        if (seconds >= 60) {
            seconds = 0;
            minutes++;
            if (minutes >= 60) {
                minutes = 0;
                hours++;
                if (hours >= 24) hours = 0;
            }
        }
    }

    bool isDinnerTime() const {
        int total = toTotalSeconds();
        return (total >= 73800 && total <= 79200);
    }

    bool isPartyTime() const {
        return (hours >= 23 || hours < 6);
    }

    Time difference(const Time& other) const {
        int diff = toTotalSeconds() - other.toTotalSeconds();
        if (diff < 0) diff = -diff;

        Time result;
        result.setFromSeconds(diff);
        return result;
    }

    int compare(const Time& other) const {
        int t1 = this->toTotalSeconds();
        int t2 = other.toTotalSeconds();
        if (t1 > t2) return 1;
        if (t1 < t2) return -1;
        return 0;
    }

    void print() const {
        if (hours < 10) std::cout << "0";
        std::cout << hours << ":";
        if (minutes < 10) std::cout << "0";
        std::cout << minutes << ":";
        if (seconds < 10) std::cout << "0";
        std::cout << seconds << std::endl;
    }
};

void bubbleSort(Time arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].compare(arr[j + 1]) == 1) {
                Time temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    Time t1(21, 15, 30);
    Time t2(23, 45, 0);
    Time t3;

    std::cout << "Printing t1 and t2:" << std::endl;
    std::cout << "Time 1: "; t1.print();
    std::cout << "Time 2: "; t2.print();

    Time toMidnight = t1.timeToMidnight();
    std::cout << "Remaining time to midnight based on time 1: "; toMidnight.print();

    std::cout << "Time 1 before tick: "; t1.print();
    t1.tick();
    std::cout << "Time 1 after tick:  "; t1.print();

    std::cout << "Is time 1 time for dinner? " << (t1.isDinnerTime() ? "Yes" : "No") << std::endl;
    std::cout << "Is time 2 party time?   " << (t2.isPartyTime() ? "YES" : "NO") << std::endl;

    Time diff = t1.difference(t2);
    std::cout << "The difference between time 1 and time 2 is: "; diff.print();

    int cmp = t1.compare(t2);
    if (cmp == -1) std::cout << "Time 1 is earlier than time 2" << std::endl;
    else if (cmp == 1) std::cout << "Time 1 is later than time 2" << std::endl;

    std::cout << "\nSorting an arrey:" << std::endl;
    Time schedule[10] = {
        Time(15, 0, 0), Time(8, 20, 0), Time(21, 30, 0),
        Time(23, 59, 59), Time(0, 0, 5), Time(12, 0, 0),
        Time(18, 45, 0), Time(5, 10, 0), Time(20, 15, 0),
        Time(2, 30, 0)
    };

    bubbleSort(schedule, 10);
    for (int i = 0; i < 10; i++) schedule[i].print();

    return 0;
}