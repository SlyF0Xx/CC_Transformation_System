#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <Windows.h>
#include <regex>
#include <functional>
#include <conio.h>

using namespace std;

struct Str_Shift
{
	string str;
	int shift;
	Str_Shift(string str,int shift)
	{
		this->shift = shift;
		this->str = str;
	}
	Str_Shift()
	{
		this->str = string();
		this->shift = 0;
	}
};

struct Number
{
	string integer_part;
	string fraction_part;
	Number(string integer_part,string fraction_part)
	{
		this->integer_part = integer_part;
		this->fraction_part = fraction_part;
	}
	Number()
	{
		this->fraction_part = string();
		this->integer_part = string();
	}
};


//��������� ������� ����� ����� �� ���������� ������� ��������� � ����� ������. ���������. ���������� ������� � ����� �����
Str_Shift fraction_10_to(string A, int C)
{
	string temp1 = A;
	string temp2;
	int temp4(0);
	int count(0);
	Str_Shift output;
	while (!temp1.empty() && count<6)
	{
		for (auto i = temp1.rbegin(); i<temp1.rend(); i++)
		{
			temp2.push_back(((*i)*C + temp4) % 10);
			temp4 = ((*i)*C + temp4) / 10;
		}
		if (temp4)
		{
			temp2.push_back(temp4);
		}
		if (temp1.size() == temp2.size())
		{
			output.str.push_back(0);
			temp1 = temp2;
		}
		else
		{
			output.str.push_back(temp2.back());
			temp2.copy((char *)temp1.c_str(), temp1.size(), 0);
		}
		if (!temp1.front())
		{
			temp1.copy((char *)temp1.c_str(), temp1.size() - 1, 1);
			temp1.resize(temp1.size() - 1);
		}
		std::reverse(temp1.begin(), temp1.end());
		temp2.clear();
		temp4 = 0;
		count++;
	}


	bool shift(0);
	if (count == 6 && output.str.back() >= (C / 2.0))//����������
	{
		shift = 1; //�������
		int temp;
		for (int i(4); i >= 0; i--)
		{
			temp = (output.str[i] + shift) % C;
			shift = (output.str[i] + shift) / C;
			output.str[i] = temp;
			if (!shift)
			{
				break;
			}
		}
	}
	output.str.resize(5);
	if (shift)
	{
		output.shift = 1;
	}
	return output;
}


//��������� ����� ����� ����� �� ���������� ������� ��������� � ����� ������. ���������. ��������� ���������� � ������� �������� ��� ���������� ������� �����
string integer_10_to(Str_Shift A, int C)
{
	string temp1 = A.str;
	string temp2;
	string output;
	int temp4(0);
	while (!temp1.empty())
	{
		for (auto i = temp1.begin(); i< temp1.end(); i++)
		{
			temp2.push_back(((*i) + temp4 * 10) / C);
			temp4 = ((*i) + temp4 * 10) % C;
		}
		output.push_back(temp4);
		temp4 = 0;
		//temp1.clear();
		if (!temp2.front())
		{
			int null_index;
			for (null_index = 0; null_index < temp2.size(); null_index++)
			{
				if (temp2[null_index])
				{
					break;
				}
			}
			temp1.resize(temp2.size() - null_index);
			temp2.copy((char *)temp1.c_str(), temp2.size() - null_index, null_index);
		}
		else {
			temp1 = temp2;
		}
		temp2.clear();
	}
	std::reverse(output.begin(), output.end());

	if (A.shift)
	{
		int temp;
		for (int i(output.size() - 1); i >= 0; i--)
		{
			temp = (output[i] + A.shift) % C;
			A.shift = (output[i] + A.shift) / C;
			output[i] = temp;
			if (!A.shift)
			{
				break;
			}
		}
	}
	return output;
}


//��������� ������� ����� ����� �� ����� ������� ��������� � ���������� ������. ���������. ���������� ������� � ����� �����
Str_Shift fraction_to_10(string A, int B)
{
	Str_Shift output;
	string temp1 = A;
	double temp2(0);
	int count(-1);
	for (auto i : temp1)
	{
		temp2 += i*pow(B, count);
		count--;
	}

	temp2 = round(temp2 * 100000) / 100000;
	/*if((int)(temp2*1000000)%100000 >=5)	//�������� 6-��� ����� ����� �������
	{
		temp2 += 0.00001;
	}*/

	if (temp2 >= 1)
	{
		output.shift = 1;
	}

	for (int i(1); i <= 5; i++)
	{
		output.str.push_back((int)(temp2 * (int)pow(10, i)) % 10);
	}
	return output;
}


//��������� ����� ����� ����� �� ����� ������� ��������� � ���������� ������. ���������. ��������� ���������� � ������� �������� ��� ���������� ������� �����
string integer_to_10(Str_Shift A, int B)
{
	string output;
	string temp1 = A.str;
	double temp2(0);
	int count(temp1.size() - 1);
	for (auto i : temp1)
	{
		temp2 += i*pow(B, count);
		count--;
	}

	if (A.shift)
	{
		temp2++;
	}
	
	for (int i(log10(temp2)); i >= 0; i--)
	{
		output.push_back(((int)temp2 % (int)pow(10, i + 1)) / (int)pow(10, i));
	}
	return output;
}

bool chek(Number input, Number answer)
{
	if((input.integer_part==answer.integer_part || ((input.integer_part == "0") && answer.integer_part.empty()))
		&& (input.fraction_part==answer.fraction_part || input.fraction_part+"00000"==answer.fraction_part))
	//if (input == answer || input+','+"00000" == answer)
	{
		cout << "OK" << endl;
		return true;
	}
	else
	{
		cout << "Wrong answer" << endl;
		return false;
	}
}

int main()
{
	SetConsoleOutputCP(1251);											//����� ������� ��������

	const string salt = "P3111";										//��������� ����. ��������� ������� � ����������� ���������
	const int hash_number_const = 127;									//������� �����������. ��������� ������� ����� � ����� ������������ ��������

	regex ex_surname(".*");												//�������� ����� �������
	const regex ex_year("[1-2]{1}[0-9]{3}");							//�������� ����� ����
	const regex ex_variant("[0-9]{1,}");								//�������� ����� ��������
	const regex ex_input_format("[0-9A-F]{1,}([.,]{0,1}[0-9A-Z]{1,5})?");	//�������� ����� ������
	const regex ex_dot("\\.");											//���� ������� .


	const char* Input_Surname = "������� ���� ������� / Input your surname";
	const char* Input_Year = "������� ������� ��� � ������� dddd /Input currunt year in format dddd";
	const char* Input_Variant = "������� ��� �������/Input your variant";
	const char* Input_Answer = "������� ��� ����� /Input your anwer ";

	const char* Task = "Your task will be transfer number A in B CC into C CC \n Please press any key to continue";

	const char* Err_Uncorrect_Surname = "Uncorrected input. \n Please try again";
	const char* Err_Uncorrect_Year = "Uncorrected input.Your answer may contain simbols[0 - 9]. \n Note, that current year must be introduced in  format dddd \n Please try again";
	const char* Err_Uncorrect_Variant = "Uncorrected input.Your answer may contain simbols[0 - 9]. \n Please try again";
	const char* Err_Uncorrect_Answer = "Uncorrected input.Your answer may contain simbols[0 - 9][A - F][., ]. \n Note that your answer must contain a maximum of 5 characters after the decimal point. \n Please, try again";


	cout << Input_Surname << endl;
	string surname;
	cin >> surname;														//�������� ����� � ������� ����������� ���������
	while (!regex_match(surname, ex_surname))	//
	{
		cout << endl<< Err_Uncorrect_Surname <<endl;
		cin >> surname;
	}


	cout << Input_Year << endl;
	string year;
	cin >> year;														//�������� ����� � ������� ����������� ���������
	while (!regex_match(year, ex_year))
	{
		cout <<endl<< Err_Uncorrect_Year <<endl;
		cin >> year;
	}
	

	cout << Input_Variant << endl;
	string variant;
	cin >> variant;														//�������� ����� � ������� ����������� ���������
	while (!regex_match(variant, ex_variant))
	{
		cout <<endl<< Err_Uncorrect_Variant <<endl;
		cin >> variant;
	}

	std::hash<std::string> student_str_hash;
	unsigned int student_hash = student_str_hash(surname+ year+variant+salt);

	cout <<endl<< "��� ID = " << student_hash<<endl;

	srand(student_hash);


	cout<<endl << Task <<endl;

	_getch();
	cout << endl;


	Number A;
	int B, C;
	vector<Number>answers;
	vector<Number>input;

	string temp;

	for (int i(0); i < 9; i++)
	{
		switch (i) //��������� ���������
		{
		case 0:
			A.integer_part.push_back((rand() % 9) + 1);
			for (int i(0); i < 4; i++)
			{
				A.integer_part.push_back(rand() % 10);
			}
			B = 10;
			C = (rand() % 6) * 2 + 5;
			break;
		case 1:
			B = (rand() % 6) * 2 + 5;
			A.integer_part.push_back((rand() % (B - 1)) + 1);
			for (int i(0); i < 4; i++)
			{
				A.integer_part.push_back(rand() % B);
			}
			C = 10;
			break;
		case 2:
			B = (rand() % 6) * 2 + 5;
			A.integer_part.push_back((rand() % (B - 1)) + 1);
			for (int i(0); i < 4; i++)
			{
				A.integer_part.push_back(rand() % B);
			}
			C = (rand() % 6) * 2 + 5;
			break;
		case 3:
			A.integer_part.push_back((rand() % 9) + 1);
			A.integer_part.push_back(rand() % 10);
			A.fraction_part.push_back(rand() % 10);
			A.fraction_part.push_back((rand() % 9)+1);
			B = 10;
			C = 2;
			break;
		case 4:
			A.integer_part.push_back((rand() % 15) + 1);
			A.integer_part.push_back(rand() % 16);
			A.fraction_part.push_back(rand() % 16);
			A.fraction_part.push_back((rand() % 15)+1);
			B = 16;
			C = 2;
			break;
		case 5:
			A.integer_part.push_back((rand() % 7) + 1);
			A.integer_part.push_back((rand() % 7) + 1);
			A.fraction_part.push_back(rand() % 8);
			A.fraction_part.push_back((rand() % 7)+1);
			B = 8;
			C = 2;
			break;
		case 6:
			for (int i(0); i < 5; i++)
			{
				A.fraction_part.push_back(rand() % 2);
			}
			A.fraction_part.push_back(1);
			B = 2;
			C = 16;
			break;
		case 7:
			for (int i(0); i <5; i++)
			{
				A.fraction_part.push_back(rand() % 2);
			}
			A.fraction_part.push_back(rand() % 2);
			B = 2;
			C = 10;
			break;
		case 8:
			A.integer_part.push_back((rand() % 15) + 1);
			A.integer_part.push_back(rand() % 16);
			for (int i(1); i < 4; i++)
			{
				A.fraction_part.push_back(rand() % 16);
			}
			A.fraction_part.push_back((rand() % 15)+1);
			B = 16;
			C = 10;
			break;
		}

		//��������� ����������� ������
		if (A.integer_part.empty()) { A.integer_part.push_back (0); }
		Str_Shift temp1;
		string temp2;
		if (B != 10)	//���������� �����������
		{
			if (C != 10)
			{
					temp1 = fraction_to_10(A.fraction_part, B);
					temp2 = integer_to_10(Str_Shift(A.integer_part, temp1.shift), B);
					temp1 = fraction_10_to(temp1.str, C);
					temp2 = integer_10_to(Str_Shift(temp2,temp1.shift), C);
			}
			else
			{
				temp1 = fraction_to_10(A.fraction_part, B);
				temp2 = integer_to_10(Str_Shift(A.integer_part, temp1.shift), B);
			}
		}
		else
		{
			temp1 = fraction_10_to(A.fraction_part, C);
			temp2 = integer_10_to(Str_Shift(A.integer_part, temp1.shift), C);
		}
		answers.push_back(Number(temp2, temp1.str));

		for (auto &i : answers.back().fraction_part) //�������������� ������ � "���������" ����
		{
			if (i > 9)
			{
				i = 'A' + i - 10;
			}
			else
			{
				i = i + '0';
			}
		}

		for (auto &i : answers.back().integer_part) //�������������� ������ � "���������" ����
		{
			if (i > 9)
			{
				i = 'A' + i - 10;
			}
			else
			{
				i = i + '0';
			}
		}

		for (auto &i : A.fraction_part) //�������������� ���������� ����� � "���������" ����
		{
			if (i > 9)
			{
				i = 'A' + i - 10;
			}
			else
			{
				i = i + '0';
			}
		}

		for (auto &i : A.integer_part) //�������������� ���������� ����� � "���������" ����
		{
			if (i > 9)
			{
				i = 'A' + i - 10;
			}
			else
			{
				i = i + '0';
			}
		}

		cout << endl << "����� A/Number A = ";
		if (A.fraction_part.empty())
		{
			cout<<A.integer_part;
		}
		else
		{
			cout<<A.integer_part + ',' + A.fraction_part;
		}
		cout << endl;
		cout << "����� B/Number B = " << B << endl;
		cout << "����� C/Number C = " << C << endl;

		cout << Input_Answer << endl;
		cin >> temp;										//�������� ����� � ������� ����������� ���������
		while (!regex_match(temp, ex_input_format))
		{
			cout << endl << Err_Uncorrect_Answer << endl;
			cin >> temp;
		}

		temp = regex_replace(temp, ex_dot, ",$1");			//���� ������� .		//�� �������� � �� ,
	
		string int_part;
		string fract_part;

		smatch s;
		regex_search(temp, s, regex(","));
		if (!s.empty())
		{
			for (auto i : s)
			{
				int_part = s.prefix();
				fract_part = s.suffix();
			}
		}
		else
		{
			int_part = temp;
			fract_part.clear();
		}

		input.push_back(Number(int_part,fract_part));
		A.fraction_part.clear();
		A.integer_part.clear();
	}

	cout << endl << "Your results:" << endl;
	int result(0);
	for (int i(0); i < 9; i++)
	{
		cout << "Task �" << i+1<<" - ";
		if (input[i].fraction_part.size() < 5)
		{
			for (int j(input[i].fraction_part.size()); j < 5; j++)
			{
				input[i].fraction_part += '0';
			}
			result += chek(input[i], answers[i]);
		}
		else
		{
			result += chek(input[i], answers[i]);
		}
	}

	cout << "Your score is "<< result;

	_getch();
	return 0;
}