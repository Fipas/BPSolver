#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {

	string nums[] = {"20", "40", "60", "100"};
	string cap[] = {"10", "30", "45", "1000"};
	string letters[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};

	string next = "";

	for (int ii = 0; ii < 4; ii++) {
		for (int jj = 0; jj < 4; jj++) {
			for (int kk = 0; kk < 10; kk++) {
				next = "n" + nums[ii] + "q" + cap[jj] + letters[kk] + ".tsp";
				cout << next << endl;

				stringstream ss;
				string line;
				ifstream file;
				ofstream out;
				string s;
				int n, d;
				int nodes;
				double x, y;
				file.open(next);
				out.open(next + ".tmp");

				getline(file, line);
				getline(file, line);
				getline(file, line);

				ss << line;
				ss >> s >> n;
				out << n << endl;
				nodes = n;

				getline(file, line);

				ss << line;
				ss >> s >> n;
				out << n << endl;

				getline(file, line);
				getline(file, line);

				for (int i = 0; i < nodes; i++) {
					getline(file, line);
					ss << line;
					ss >> n >> x >> y;
					out << fixed << setprecision(4) << x << " " << y << endl;
				}

				getline(file, line);
				for (int i = 0; i < nodes; i++) {
					getline(file, line);
					out << 20 << endl;
				}

				getline(file, line);
				for (int i = 0; i < nodes; i++) {
					getline(file, line);
					ss << line;
					ss >> n >> d;
					out << 10 << " " << (10 + d) << endl;
				}

				file.close();
				out.close();

				file.open(next + ".tmp");
				out.open(next);

				while (getline(file, line)) {
					out << line << endl;
				}

				file.close();
				out.close();
			}
		}
	}

	return 0;
}