#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
using namespace std;

class Record 
{
private:
	int key;
	char option;
	SYSTEMTIME systime;
public:
	Record()
	{
		key = rand()%20 + 1;
		char transAction[3] = {'I', 'D', 'M'};
		option = transAction[rand()%3];
		GetLocalTime(&systime);
	}
	int getKey() { return key; }
	char getOption() { return option; }
	WORD getYear() { return systime.wYear; }
	WORD getMonth() { return systime.wMonth; }
	WORD getDay() { return systime.wDay; }
	WORD getHour() { return systime.wHour; }
	WORD getMinute() { return systime.wMinute; }
	WORD getSecond() { return systime.wSecond; }
	WORD getMilliseconds() { return systime.wMilliseconds; }
	void setOption(char ch) { option = ch; }
};

int main()
{
	ofstream fout;
	
	fout.open("transactionFile.txt");

	srand(time(NULL));

	int count=0;
	Record *record[60];

	fout << "<트랜잭션 로그의 상태변화 출력>" << endl;

	for(int i=0; i<60; i++) {
		record[i] = new Record();
		fout << record[i]->getKey() << " / " ;
		fout << record[i]->getYear() << "-" << record[i]->getMonth() << "-" << record[i]->getDay() << " " << record[i]->getHour() << ":" ;
		fout << record[i]->getMinute() << ":" << record[i]->getSecond() << ":" << record[i]->getMilliseconds() << "(" << record[i]->getOption() << ")" << endl;
	}

	fout << endl << endl;
	
	for(int i=1; i< 60; i++)
		for(int j=0; j<i; j++) {
			if(record[i]->getKey() < record[j]->getKey()) {
				Record *r = record[i];
				record[i] = record[j];
				record[j] = r;
			}
			else if(record[i]->getKey() == record[j]->getKey()) {
				if(record[i]->getYear() < record[j]->getYear()) {
					Record *r = record[i];
					record[i] = record[j];
					record[j] = r;
				}
				else if(record[i]->getYear() == record[j]->getYear()) {
					if(record[i]->getMonth() < record[j]->getMonth()) {
						Record *r = record[i];
						record[i] = record[j];
						record[j] = r;
					}
					else if(record[i]->getMonth() == record[j]->getMonth()) {
						if(record[i]->getDay() < record[j]->getDay()) {
							Record *r = record[i];
							record[i] = record[j];
							record[j] = r;
						}
						else if(record[i]->getDay() == record[j]->getDay()) {
							if(record[i]->getHour() < record[j]->getHour()) {
								Record *r = record[i];
								record[i] = record[j];
								record[j] = r;
							}
							else if(record[i]->getHour() == record[j]->getHour()) {
								if(record[i]->getMinute() < record[j]->getMinute()) {
									Record *r = record[i];
									record[i] = record[j];
									record[j] = r;
								}
								else if(record[i]->getMinute() == record[j]->getMinute()) {
									if(record[i]->getSecond() < record[j]->getSecond()) {
										Record *r = record[i];
										record[i] = record[j];
										record[j] = r;
									}
									else if(record[i]->getSecond() == record[j]->getSecond()) {
										if(record[i]->getMilliseconds() < record[j]->getMilliseconds()) {
											Record *r = record[i];
											record[i] = record[j];
											record[j] = r;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	
	fout << "<정렬된 로그 파일>" << endl;

	for(int i=0; i<60; i++) {
		fout << record[i]->getKey() << " / " ;
		fout << record[i]->getYear() << "-" << record[i]->getMonth() << "-" << record[i]->getDay() << " " << record[i]->getHour() << ":" ;
		fout << record[i]->getMinute() << ":" << record[i]->getSecond() << ":" << record[i]->getMilliseconds() << "(" << record[i]->getOption() << ")" << endl;
	}

	fout.close();

	int fileArr[21] = {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
	int newFileArr[21] = {0};
	int filePtr = 1;
	int logPtr = 0;

	while(1)
	{
		if(logPtr >= 60)
		{
			if(filePtr > 20)
				break;
			else 
			{
				while(filePtr <= 20)
				{
					if(fileArr[filePtr])
						newFileArr[filePtr] = 1;
					filePtr++;
				}
			}
		}
		else
		{
			if(filePtr > 20)
			{
				if(record[logPtr-1]->getKey() == record[logPtr]->getKey())
				{
					if(record[logPtr-1]->getOption() == 'I')
					{
						if(record[logPtr]->getOption() == 'I')
							record[logPtr]->setOption('I');
						else if(record[logPtr]->getOption() == 'M')
							record[logPtr]->setOption('I');
						else
							record[logPtr]->setOption('D');
					}
					else if(record[logPtr-1]->getOption() == 'M')
					{
						if(record[logPtr]->getOption() == 'I')
							record[logPtr]->setOption('I');
						else if(record[logPtr]->getOption() == 'M')
							record[logPtr]->setOption('D');
						else
							record[logPtr]->setOption('D');
					}
					else
					{
						if(record[logPtr]->getOption() == 'I')
							record[logPtr]->setOption('I');
						else if(record[logPtr]->getOption() == 'M')
							record[logPtr]->setOption('D');
						else
							record[logPtr]->setOption('D');
					}
					logPtr++;
				}
				else
				{
					if(record[logPtr-1]->getOption() == 'I')
						newFileArr[logPtr-1] = 1;
					else if(record[logPtr-1]->getOption() == 'M')
					{
						cout << record[logPtr-1]->getKey() << " / " ;
						cout << record[logPtr-1]->getYear() << "-" << record[logPtr-1]->getMonth() << "-" << record[logPtr-1]->getDay() << " ";
						cout << record[logPtr-1]->getHour() << " " << record[logPtr-1]->getMinute() << ":" << record[logPtr-1]->getSecond() << ":";
						cout << record[logPtr-1]->getMilliseconds() << "(" << record[logPtr-1]->getOption() << ") 수정 실패" << endl;
					}
					else
					{
						cout << record[logPtr-1]->getKey() << " / " ;
						cout << record[logPtr-1]->getYear() << "-" << record[logPtr-1]->getMonth() << "-" << record[logPtr-1]->getDay() << " ";
						cout << record[logPtr-1]->getHour() << " " << record[logPtr-1]->getMinute() << ":" << record[logPtr-1]->getSecond() << ":";
						cout << record[logPtr-1]->getMilliseconds() << "(" << record[logPtr-1]->getOption() << ") 삭제 실패" << endl;
					}
					logPtr++;
					filePtr++;
				}
			}
			else
			{
				if(record[logPtr]->getKey() < filePtr)
				{
					if(record[logPtr-1]->getKey() == record[logPtr]->getKey())
					{
						if(record[logPtr-1]->getOption() == 'I')
						{
							if(record[logPtr]->getOption() == 'I')
								record[logPtr]->setOption('I');
							else if(record[logPtr]->getOption() == 'M')
								record[logPtr]->setOption('I');
							else
								record[logPtr]->setOption('D');
						}
						else if(record[logPtr-1]->getOption() == 'M')
						{
							if(record[logPtr]->getOption() == 'I')
								record[logPtr]->setOption('I');
							else if(record[logPtr]->getOption() == 'M')
								record[logPtr]->setOption('D');
							else
								record[logPtr]->setOption('D');
						}
						else
						{
							if(record[logPtr]->getOption() == 'I')
								record[logPtr]->setOption('I');
							else if(record[logPtr]->getOption() == 'M')
								record[logPtr]->setOption('D');
							else
								record[logPtr]->setOption('D');
						}
						logPtr++;
					}
					else
					{
						if(record[logPtr-1]->getOption() == 'I')
							newFileArr[logPtr-1] = 1;
						else if(record[logPtr-1]->getOption() == 'M')
						{
							cout << record[logPtr-1]->getKey() << " / " ;
							cout << record[logPtr-1]->getYear() << "-" << record[logPtr-1]->getMonth() << "-" << record[logPtr-1]->getDay() << " ";
							cout << record[logPtr-1]->getHour() << " " << record[logPtr-1]->getMinute() << ":" << record[logPtr-1]->getSecond() << ":";
							cout << record[logPtr-1]->getMilliseconds() << "(" << record[logPtr-1]->getOption() << ") 수정 실패" << endl;
						}
						else
						{
							cout << record[logPtr-1]->getKey() << " / " ;
							cout << record[logPtr-1]->getYear() << "-" << record[logPtr-1]->getMonth() << "-" << record[logPtr-1]->getDay() << " ";
							cout << record[logPtr-1]->getHour() << " " << record[logPtr-1]->getMinute() << ":" << record[logPtr-1]->getSecond() << ":";
							cout << record[logPtr-1]->getMilliseconds() << "(" << record[logPtr-1]->getOption() << ") 삭제 실패" << endl;
						}
						logPtr++;
						filePtr++;
					}
				}
				else if(record[logPtr]->getKey() == filePtr)
				{
					if(logPtr == 0)
					{
						if(record[logPtr]->getOption() == 'I')
							record[logPtr]->setOption('I');
						else if(record[logPtr]->getOption() == 'M')
							record[logPtr]->setOption('D');
						else
							record[logPtr]->setOption('D');
						logPtr++;
					}
					else if(record[logPtr-1]->getKey() == record[logPtr]->getKey())
					{
						if(record[logPtr-1]->getOption() == 'I')
						{
							if(record[logPtr]->getOption() == 'I')
								record[logPtr]->setOption('I');
							else if(record[logPtr]->getOption() == 'M')
								record[logPtr]->setOption('I');
							else
								record[logPtr]->setOption('D');
						}
						else if(record[logPtr-1]->getOption() == 'M')
						{
							if(record[logPtr]->getOption() == 'I')
								record[logPtr]->setOption('I');
							else if(record[logPtr]->getOption() == 'M')
								record[logPtr]->setOption('I');
							else
								record[logPtr]->setOption('D');
						}
						else
						{
							if(record[logPtr]->getOption() == 'I')
								record[logPtr]->setOption('I');
							else if(record[logPtr]->getOption() == 'M')
								record[logPtr]->setOption('D');
							else
								record[logPtr]->setOption('D');
						}
						logPtr++;
					}
					else
					{
						if(record[logPtr-1]->getOption() == 'I')
						{
							cout << record[logPtr-1]->getKey() << " / " ;
							cout << record[logPtr-1]->getYear() << "-" << record[logPtr-1]->getMonth() << "-" << record[logPtr-1]->getDay() << " ";
							cout << record[logPtr-1]->getHour() << " " << record[logPtr-1]->getMinute() << ":" << record[logPtr-1]->getSecond() << ":";
							cout << record[logPtr-1]->getMilliseconds() << "(" << record[logPtr-1]->getOption() << ") 삽입 실패" << endl;
						}
						else if(record[logPtr-1]->getOption() == 'M')
							newFileArr[logPtr-1] = 1;
						else
						{
							cout << record[logPtr-1]->getKey() << " / " ;
							cout << record[logPtr-1]->getYear() << "-" << record[logPtr-1]->getMonth() << "-" << record[logPtr-1]->getDay() << " ";
							cout << record[logPtr-1]->getHour() << " " << record[logPtr-1]->getMinute() << ":" << record[logPtr-1]->getSecond() << ":";
							cout << record[logPtr-1]->getMilliseconds() << "(" << record[logPtr-1]->getOption() << ") 삭제 실패" << endl;
						}
						logPtr++;
						filePtr++;
					}
				}
				else 
				{
					newFileArr[filePtr]=1;
					filePtr++;
				}
			}
		}
	}

	fout.open("masterFile.txt");
	for(int i=1; i<=20; i++)
		if(newFileArr[i])
			fout << i << " ";
	fout << endl;

	fout.close();
	return 0;
}