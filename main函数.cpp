#include "module1.h"
#include <cstdlib>
#include "tinyxml2.h"
#include "xmlserialize.cpp"

using namespace tinyxml2;


#define EXIT_ABNOEMAL(msg) {printf("%s\n", msg); return -1;}

int serializeToXML(Serialization* serialization, const string& filePath) {
	tinyxml2::XMLDocument doc;
	//use serializetion's serialize function
	int ret = serialization->serializeXML(doc, filePath);
	return ret;
}



int main() {
	cout << "Please choose the module you want to implement" << endl;
	cout << "If you want to implement a module to support binary serialization/deserialization" << endl;
	cout << "Please  input 1" << endl;
	cout << "If you want to implement a a wrapper module of tinyxml2 to support XML serialization" << endl;
	cout << "Please  input 2" << endl;
	cout << "Please input your choice:" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		Diary a, b;//create two obeject a,b
		cout << "Enter the Date: " << endl;
		cin>>a.date;//input a.date;
		cout << "Enter the Content:" << endl;
		string line;
		getline(cin, line);
		while (line != ".") {//input a.content until meeting "."
			a.AddContent(line);
			getline(cin, line);
			a.num_lines++;//the number of lines increase
		}
		Diary n0, n1;//create two obeject n0,n1
		n0 = serialize(a, "n.data");//put the result of serialize into n0
		n1 = deserialize(b, "n.data");//put the result of deserialize into n1

		if (n0 == n1) {   //test whether the result is right;
			cout << "right" << endl;
		}
		system("pause");
		return 0;
	}

	if (choice == 2) {
		const string fileName = "pair.xml";
		string fir;
		string sec;
		cout << "Please enter data of first" << endl;
		cin >> fir;
		cout << "Please enter data of second" << endl;
		cin >> sec;
		std::pair<string, string>pair1(fir, sec);
		string pair0;//serialize object to xml
		auto serialization0 = new Serialization(pair0);
		Std_pair first(fir);
		Std_pair second(sec);
		serialization0->vStd_pairs.push_back(first);
		serialization0->vStd_pairs.push_back(second);
		int ret;
		ret = serializeToXML(serialization0, fileName);//create xml file
		if (ret)
		{
			EXIT_ABNOEMAL("convert to xml error!");
		}
		SAFE_DELETE(serialization0);
		system("pause");
		return 0;
	}
	
}