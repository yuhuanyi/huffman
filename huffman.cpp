#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdio>
#include<Windows.h>

#include"huffman_core.h"
#include"huffman_helper.h"

using namespace std;

int main()
{
	init();//��ʼ��

	char filename[20];
	cout << "��������Ҫѹ�����ļ�����";
	cin >> filename;
	read_text(filename);
	cout << endl;

	sort();//����
	display_wordlist();//��ʾ����������C

	build_huffmantree();//������������

	display_huffmantree(wordlist_head->next);//��д����ӡ����
	cout << endl;

	init_codetable();//��ʼ���������֮ǰ�����ݽṹ����
	read_codetable();//��ȡ�����ļ�code.txt
	display_codetable();//��ӡ�����ļ�code.txt
	cout << endl;

	compress_code();//����
	bin_to_txt("test.bin", "bin2.txt");
	decompress_code();//����

	display_code_file("test2.txt");//��ӡtest2.txt
    
}