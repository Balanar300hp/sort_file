#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <iterator>
#include <algorithm>

using namespace std;

class B {
public:
	B(string name_main_file);
	auto division()->void;
	auto file_size(string name_file)->size_t;
	auto make_file(string name_file)->void;
	auto file_sort()->void;
	auto write_to_out(string line)->void;
private:
	fstream file;
	size_t buffer, count_of_files, closed_files;
	bool out;
	vector<string> lines;
	vector<string> file_names;
};

B::B(string name_main_file) :file(name_main_file), buffer(100), count_of_files(0), closed_files(0) {//TESTED
	if (file.is_open()) {
		out=true;
		division();
	}
};

auto B::make_file(string name_file)->void {//TESTED
	file_names.push_back(name_file);
	std::sort(lines.begin(), lines.end());
	ofstream temp(name_file);
	for (auto i : lines)
	{
		temp << i;
		if (i != *(--lines.end())) temp << endl;
	}
	temp.close();
	lines.clear();
}//TESTED

auto B::file_size(string name_file)->size_t { // TESTED
	long fsize;
	ifstream temp(name_file);
	temp.seekg(0, ios::end);
	fsize = temp.tellg();
	temp.close();
	return fsize;

}

auto B::write_to_out(string line)->void {//TESTED
	ofstream file("out.txt", ios::app);
	file << line << endl;
	file.close();

}

bool ya(string* p, int k)
{
	for (int i = 0; i < k; ++i){
		
		if (p[i] != "яяя") {
		return false;
	}
}
	return true;
}


auto B::file_sort()->void {

	ifstream *files_streams = new ifstream[count_of_files];
	for (int i = 0; i < count_of_files; ++i) {
		files_streams[i].open(file_names[i]);
	}

	string *top_line = new string[count_of_files];
	for (int i = 0; i < count_of_files; ++i)
	{
		getline(files_streams[i], top_line[i]);
	}

	while (out) {
		string temp_min_line = top_line[0];
		int num_min_line = 0;

		for (int i = 0; i < count_of_files; ++i)
		{
			if (top_line[i] < temp_min_line)
			{
				temp_min_line = top_line[i];
				num_min_line = i;
			}
		}
		
		write_to_out(temp_min_line);

		if (!files_streams[num_min_line].eof())
		{
			getline(files_streams[num_min_line], top_line[num_min_line]);
		}
		else {
			files_streams[num_min_line].close();
			closed_files++;
			if (closed_files == count_of_files) { out = false; };
		}

	}
}


auto B::division()->void {//TESTED
	string line_of_file;
	size_t temp_size_files = 0;
	while (!file.eof()) {
		getline(file, line_of_file);
		temp_size_files += line_of_file.size();


		if (temp_size_files <= buffer) {
			lines.push_back(line_of_file);
		}
		else {
			count_of_files++;

			make_file(to_string(count_of_files) + ".txt");
			lines.push_back(line_of_file);
			temp_size_files = line_of_file.size();
		}
	}
	file.close();

	if (lines.size()) {
		count_of_files++;
		make_file(to_string(count_of_files) + ".txt");
	}


	file_sort();
};


int main()
{
	setlocale(LC_ALL, "Russian");
	B obj("names.txt");

	


	system("pause");
	return 0;
}


