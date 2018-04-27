
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
double CalculateSmallestRange(pair<double, double>arr[], int n);
string split(string  s, int firstIndex, int secondIndex);
int CalculateK(double rang);
double BinaryConverter(string s);
bool NeedsRescale(double L, double U);
bool LowerBoundCheck(double L, double U);
bool UpperBoundCheck(double L, double U);
void decoding(char alphabet[], int sizeOfSet);
int ReturnIndex(char alpha[], int length, char ch);
void encoding(char alphabet[], int sizeOfSet);
char SearchForChar(int index, char arr[]);

string decodeMessege;
int tag_index;
int main()
{
	int  sizeOfset;
	int type;
	cout << "Arithmetic Coding With Scaling : " << endl;
	cout << "please enter the size of your set :  ";
	cin >> sizeOfset;
	char alphabet[sizeOfset];

	for (int i = 0; i<sizeOfset; i++) {
		cout << i + 1 << ":";
		cin >> alphabet[i];
	}

	cout << "for encoding type 1 , for decoding type 2 " << endl;
	cout << "******************************************************* " << endl;

	cin >> type;
	if (type == 1)encoding(alphabet, sizeOfset);
	else if (type == 2)decoding(alphabet, sizeOfset);



	system("pause");
	return 0;
}
double CalculateSmallestRange(pair<double, double>arr[], int n) { //get the min interval
	double Min = arr[0].second - arr[0].first;
	for (int i = 0; i<n; i++) {
		if (Min>(arr[i].second - arr[i].first)) {

			Min = arr[i].second - arr[i].first;
		}
	}

	return Min;
}
string split(string s, int firstIndex, int secondIndex) { //function return string from the firstindex to seconed
	string splited = "";
	s.erase(0, 1);

	s += decodeMessege[tag_index++];

	return s;

}
int CalculateK(double rang) { //calculate k
	int r;
	r = ceil(-log2(rang));
	return r;

}
double BinaryConverter(string s) { //convert the string tag into floating tag

	double value = 0.0;

	for (int i = 0; i<(int)s.size(); ++i) {
		if ((s[i] - '0') == 1)  value += pow(2, -1 * i - 1);
	}
	return value;
}
int ReturnIndex(char alpha[], int length, char ch) {
	int i = 0;
	while (ch != alpha[i]) {
		i++;
	}
	return i + 1;
}
bool NeedsRescale(double L, double U) { //return true if the function needs rescale return false if the function doesn't
	if (((L >= 0 && L<0.5) && (U >= 0 && U<0.5)) || ((L >= 0.5&&L <= 1.0) && (U >= 0.5&&U <= 1.0)))return 1;
	else return 0;
}
bool LowerBoundCheck(double L, double U) {
	if ((L >= 0 && L <= 0.5) && (U >= 0 && U <= 0.5)) return 1;
	else return 0;


}
bool UpperBoundCheck(double L, double U) {

	if (((L >= 0.5&&L <= 1.0) && (U >= 0.5&&U <= 1.0))) return 1;
	else return 0;



}
void decoding(char alphabet[], int sizeOfset) {

	string sTag;
	double Tag;
	int  sizeOfOutput;
	double input;

	pair<double, double>arr[sizeOfset];
	//pair<double, double>arr[3];
	arr[0].first = 0;

	for (int i = 0; i<sizeOfset; ++i) {
		cout << alphabet[i] << "------>";
		cin >> input;
		arr[i].second = input + arr[i].first;
		arr[i + 1].first = arr[i].second;

	}
	cout << "enter mess to be decoded" << endl;
	cin >> decodeMessege;
	tag_index = CalculateK(CalculateSmallestRange(arr, sizeOfset));
	sTag = decodeMessege.substr(0, 6);
	Tag = BinaryConverter(sTag);
	cout << "how many elements do you want to decode  " << endl;
	cin >> sizeOfOutput;


	double L = 0.0;
	double U = 1.0;
	double tempL;
	double tempU;


	while (sizeOfOutput) {
		tempL = L;
		tempU = U;
		for (int i = 0; i<sizeOfset; i++) {

			L = tempL + (tempU - tempL)*arr[i].first;
			U = tempL + (tempU - tempL)*arr[i].second;
			if (Tag >= L && Tag <= U) {
				cout << alphabet[i];
				break;
			}
		}
		while (NeedsRescale(L, U)) {
			sTag = split(sTag, 1, (int)sTag.size() - 1);
			Tag = BinaryConverter(sTag);
			if (LowerBoundCheck(L, U)) {
				L = 2 * (L);
				U = 2 * (U);
			}
			else if (UpperBoundCheck(L, U)) {
				L = 2 * (L - 0.5);
				U = 2 * (U - 0.5);
			}
		}
		sizeOfOutput--;


	}
}
void encoding(char alphabet[], int sizeOfset) {
	string encodedmess;
	string output = "";
	double input;
	cout << "enter the probability of each : " << endl;


	pair<double, double>arr[sizeOfset];
	arr[0].first = 0;

	for (int i = 0; i<sizeOfset; ++i) {
		cout << alphabet[i] << "------>";
		cin >> input;
		arr[i].second = input + arr[i].first;
		arr[i + 1].first = arr[i].second;
	}
	cout << "enter the mess" << endl;
	cin >> encodedmess;
	double L = 0.0;
	double U = 1.0;
	int n;
	double TempL;
	char c;
	for (int i = 0; i<(int)encodedmess.size(); i++) {
		c = encodedmess[i];
		n = ReturnIndex(alphabet, sizeOfset, c);
		TempL = L;
		L = L + (U - L)*arr[n - 1].first;
		U = TempL + (U - TempL)*arr[n - 1].second;

		while (NeedsRescale(L, U)) {
			if (LowerBoundCheck(L, U)) {
				L = 2 * (L);
				U = 2 * (U);
				output += "0";
			}
			else  if (UpperBoundCheck(L, U)) {
				L = 2 * (L - 0.5);
				U = 2 * (U - 0.5);
				output += "1";
			}
		}
	}
	output += '1';
	for (int i = output.size() + 1; i<32; i++)
	{
		output += '0';
	}
	cout << "binary value = " << output << endl;
	cout << "your Tag = " << BinaryConverter(output)<<endl;
}

