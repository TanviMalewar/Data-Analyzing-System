#include <bits/stdc++.h>
using namespace std;

class Sensor {
private:
    vector<double> readings;
public:
    void inputData(int n) {
        double value;
        cout << "Enter " << n << " sensor readings:"<<endl;
        for (int i = 0; i < n; i++) {
            cin >> value;
            readings.push_back(value);
        }
    }
    vector<double> getReadings() {
        return readings;
    }
};

class DataAnalyzer {
private:
    vector<double> data;
public:
    DataAnalyzer(vector<double> readings) {
        data = readings;
    }
    double getAverage() {
        double sum = 0;
        for (double val : data) sum += val;
        return sum / data.size();
    }
    double getMin() {
        return *min_element(data.begin(), data.end());
    }
    double getMax() {
        return *max_element(data.begin(), data.end());
    }
    void displayStats() {
        cout << "Statistics of Sensor"<<endl;
        cout << "Average: " << getAverage() << endl;
        cout << "Minimum: " << getMin() << endl;
        cout << "Maximum: " << getMax() << endl;
    }
};

class FaultDetector {
private:
    vector<double> data;
    double lowerLimit, upperLimit;

public:
    FaultDetector(vector<double> readings, double low, double high) {
        data = readings;
        lowerLimit = low;
        upperLimit = high;
    }

    void detectOutOfRange() {
        cout<<endl;
        cout << "Out of range values"<<endl;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] < lowerLimit || data[i] > upperLimit) {
                cout << "Reading " << i << " = " << data[i] << " is OUT OF RANGE"<<endl;
            }
            else{
                cout<<"No value is out of range"<<endl;
            }
        }
    }

    void detectSpikes() {
        cout<<endl;
        cout << "Sudden Spikes"<<endl;
        for (int i = 1; i < data.size(); i++) {
            if (abs(data[i] - data[i - 1]) > 20) { 
                cout << "Spike between index " << i - 1 << " and " << i
                     << " (" << data[i - 1] << " -> " << data[i] << ")\n";
            }
        }
    }
};

int main() {
    int n;
    cout << "Enter number of readings: ";
    cin >> n;

    Sensor s1;
    s1.inputData(n);

    vector<double> readings = s1.getReadings();

    DataAnalyzer analyzer(readings);
    analyzer.displayStats();

    double low, high;
    cout<<endl;
    cout << "Enter acceptable range (low and high): ";
    cin >> low >> high;

    FaultDetector detector(readings, low, high);
    detector.detectOutOfRange();
    detector.detectSpikes();

    return 0;
}