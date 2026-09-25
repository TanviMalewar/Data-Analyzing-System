#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

// Sensor Class
class Sensor {
private:
    vector<double> readings;

public:
    void inputData(int n) {
        readings.clear();
        readings.reserve(n);

        cout << "\nEnter " << n << " sensor readings:\n";

        for (int i = 0; i < n; i++) {
            double value;

            while (true) {
                cout << "Reading " << i + 1 << ": ";

                if (cin >> value) {
                    readings.push_back(value);
                    break;
                }

                cout << "Invalid input. Please enter a numeric value.\n";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    const vector<double>& getReadings() const {
        return readings;
    }
};

// Data Analyzer Class
class DataAnalyzer {
private:
    const vector<double>& data;

public:
    DataAnalyzer(const vector<double>& readings)
        : data(readings) {}

    double getAverage() const {
        if (data.empty()) {
            return 0.0;
        }

        double sum = 0.0;

        for (double value : data) {
            sum += value;
        }

        return sum / data.size();
    }

    double getMin() const {
        if (data.empty()) {
            return 0.0;
        }

        return *min_element(data.begin(), data.end());
    }

    double getMax() const {
        if (data.empty()) {
            return 0.0;
        }

        return *max_element(data.begin(), data.end());
    }

    void displayStats() const {
        if (data.empty()) {
            cout << "\nNo data available for analysis.\n";
            return;
        }
        cout << "SENSOR DATA ANALYSIS\n";

        cout << "Number of readings : " << data.size() << '\n';
        cout << "Average            : " << getAverage() << '\n';
        cout << "Minimum            : " << getMin() << '\n';
        cout << "Maximum            : " << getMax() << '\n';
    }
};

// Fault Detector Class
class FaultDetector {
private:
    const vector<double>& data;

    double lowerLimit;
    double upperLimit;
    double spikeThreshold;

public:
    FaultDetector(
        const vector<double>& readings,
        double low,
        double high,
        double threshold
    )
        : data(readings),
          lowerLimit(low),
          upperLimit(high),
          spikeThreshold(threshold) {}

    void detectOutOfRange() const {
        if (data.empty()) {
            cout << "\nNo data available for fault detection.\n";
            return;
        }

        cout << "OUT-OF-RANGE CHECK\n";

        bool found = false;

        for (size_t i = 0; i < data.size(); i++) {

            if (data[i] < lowerLimit || data[i] > upperLimit) {

                cout << "Reading " << i + 1
                     << " = " << data[i]
                     << " is OUT OF RANGE";

                if (data[i] < lowerLimit) {
                    cout << " (Below lower limit)";
                } else {
                    cout << " (Above upper limit)";
                }

                cout << '\n';

                found = true;
            }
        }

        if (!found) {
            cout << "No value is out of range.\n";
        }
    }


    void detectSpikes() const {
        if (data.size() < 2) {
            cout << "\nNot enough readings to detect spikes.\n";
            return;
        }

        cout << "SPIKE DETECTION\n";

        bool found = false;

        for (size_t i = 1; i < data.size(); i++) {

            double difference = abs(data[i] - data[i - 1]);

            if (difference > spikeThreshold) {

                cout << "Spike detected between reading "
                     << i << " and " << i + 1
                     << " | Difference = "
                     << difference << '\n';

                found = true;
            }
        }

        if (!found) {
            cout << "No sudden spikes detected.\n";
        }
    }
};


int main() {
    cout << "SENSOR DATA ANALYZING SYSTEM\n";

    int n;
    // Input number of readings
    while (true) {

        cout << "\nEnter number of sensor readings: ";

        if (cin >> n && n > 0) {
            break;
        }

        cout << "Invalid input. Number of readings "
             << "must be greater than 0.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Collect sensor readings
    Sensor sensor;

    sensor.inputData(n);

    const vector<double>& readings = sensor.getReadings();

    // Analyze data
    DataAnalyzer analyzer(readings);

    analyzer.displayStats();
    // Input acceptable range
    double lowerLimit;
    double upperLimit;

    while (true) {

        cout << "\nEnter acceptable lower limit: ";

        if (!(cin >> lowerLimit)) {
            cout << "Invalid input. Please enter a number.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            continue;
        }

        cout << "Enter acceptable upper limit: ";

        if (!(cin >> upperLimit)) {
            cout << "Invalid input. Please enter a number.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            continue;
        }

        if (lowerLimit >= upperLimit) {
            cout << "Lower limit must be less than "
                 << "upper limit.\n";
            continue;
        }

        break;
    }

    // Input spike threshold
    double spikeThreshold;

    while (true) {

        cout << "\nEnter spike detection threshold: ";

        if (cin >> spikeThreshold && spikeThreshold > 0) {
            break;
        }

        cout << "Threshold must be a positive number.\n";

        cin.clear();
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }

    // Fault Detection
    FaultDetector detector(
        readings,
        lowerLimit,
        upperLimit,
        spikeThreshold
    );

    detector.detectOutOfRange();

    detector.detectSpikes();

    // Program Complete
    cout << "ANALYSIS COMPLETE\n";

    return 0;
}
