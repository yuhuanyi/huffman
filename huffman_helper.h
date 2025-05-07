#pragma once
#ifndef __HUFFMAN_HELPER_
#define __HUFFMAN_HELPER_

#define EXAMPLE_MACRO_NAME

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdio>
#include <Windows.h>
#include <bitset>
#include"huffman_core.h"
#endif

using namespace std;

struct wordlist {
	char word;  // �ַ�
	int count;  // ����
	int side;	// ��
	int real;	// �Ƿ�Ϊ��ʵ�ڵ�
	wordlist* next; // ��һ��ָ��

	int label;			//������ ���
	wordlist* left;
	wordlist* right;
	wordlist* father;

};

//ȫ�ֱ���
int code[20];
int zero_count;
wordlist* wordlist_head;

//��ʼ������
void init()
{
	//��ʼ����������
	wordlist_head = (wordlist*)malloc(sizeof(wordlist));
	wordlist_head->word = '0';
	wordlist_head->count = 0;
	wordlist_head->side = 0;
	wordlist_head->next = NULL;

	//��ʼ������
	for (int i = 0; i < 20; i++)
	{
		code[i] = -1;
	}

	remove("code.txt");
	remove("bin.txt");
	remove("test2.txt");
}

//��������
int insert(char zifu)
{
	wordlist* p_seek;
	wordlist* p_new;

	p_seek = wordlist_head->next;
	while (p_seek != NULL)
	{
		if (p_seek->word == zifu)
		{
			p_seek->count++;
			return 1;
		}
		p_seek = p_seek->next;
	}

	//��ʼ��������½ڵ�
	p_new = (wordlist*)malloc(sizeof(wordlist));
	p_new->word = zifu;
	p_new->count = 1;
	p_new->side = 0;
	p_new->real = 1;
	p_new->label = 0;
	p_new->next = NULL;
	p_new->left = NULL;
	p_new->right = NULL;
	p_new->father = NULL;

	//����ڵ�
	p_seek = wordlist_head;
	while (p_seek->next != NULL)
	{
		p_seek = p_seek->next;
	}
	p_seek->next = p_new;
	return 1;
}

//��ȡ�ı�
int read_text(char filename[])
{
	char zifu;
	ifstream fin;//ʵ��������
	fin.open(filename);

	if (!fin.is_open())
	{
		cout << "�ı���ʧ��" << endl;
		return 0;
	}
	// ����ļ��Ƿ�Ϊ��
	if (fin.peek() == EOF) {
		cout << "�ı�Ϊ��" << endl;
		return 0;
	}
	while (fin.peek() != EOF)//����Ƿ�Ϊ�ļ�β
	{
		fin.get(zifu);
		cout << zifu;
		insert(zifu);
	}
}

//��ȡ������
int getlength()
{
	wordlist* p_seek;
	int length = 0;
	p_seek = wordlist_head->next;
	while (p_seek != NULL)
	{
		length++;
		p_seek = p_seek->next;
	}
	return length;
}

//��������
void sawp(wordlist* p_this, wordlist* p_next)
{
	char temp_word;
	int temp_count;
	int temp_side;

	temp_side = p_this->side;
	temp_word = p_this->word;
	temp_count = p_this->count;

	p_this->side = p_next->side;
	p_this->word = p_next->word;
	p_this->count = p_next->count;

	p_next->side = temp_side;
	p_next->word = temp_word;
	p_next->count = temp_count;
}

//��������ð������
int sort()
{
	int length = getlength();
	if (length <= 1)	return 2;

	wordlist* p_this, * p_next;
	for (int keep = length; keep > 1; keep--)
	{
		p_this = wordlist_head->next;
		p_next = p_this->next;

		for (int length = keep; length > 1; length--)
		{
			if (p_this->count > p_next->count)
				sawp(p_this, p_next);

			p_this = p_this->next;
			p_next = p_next->next;
		}
	}
	return 0;
}

//��ӡ����������е�Ԫ��
void display_wordlist()
{
	wordlist* p_this = wordlist_head->next;
	while (p_this != NULL)
	{
		if (p_this->word == '\n')
			cout << "���з�\t" << p_this->count << endl;
		else if (p_this->real == 0)
			cout << "��ڵ�\t" << p_this->count << endl;
		else
			cout << p_this->word << "\t" << p_this->count << endl;
		p_this = p_this->next;
	}
}

//ժ���������׽ڵ�
wordlist* removefirst()
{
	wordlist* black = wordlist_head->next;

	if (black == NULL)
		return black;
	else
	{
		wordlist_head->next = wordlist_head->next->next;
		return black;
	}
}

//��������
void addwordlist(wordlist* temp)
{
	wordlist* p_seek = wordlist_head;
	if (p_seek->next == NULL)
	{
		p_seek->next = temp;
		return;
	}
	else
	{
		//Ѱ�Ҳ���λ��
		while (p_seek->next != NULL && p_seek->next->count < temp->count)
		{
			p_seek = p_seek->next;
		}
		if (p_seek->next == NULL)
		{
			p_seek->next = temp;
			temp->next = NULL;
			return;
		}
		else
		{
			wordlist* p_keep = p_seek->next;
			p_seek->next = temp;
			temp->next = p_keep;
		}
	}
}

//������������
void build_huffmantree()
{
	wordlist* left = removefirst();
	wordlist* right = removefirst();

	while (right != NULL)
	{
		wordlist* root;//Ҷ�ӽ��
		root = (wordlist*)malloc(sizeof(wordlist));

		root->count = (left->count + right->count);
		root->side = -1;//�����ɽڵ�
		//������Ϊ0��������Ϊ1
		left->side = 0;
		right->side = 1;

		//�������ڵ���Ϊ0
		left->label = 0;
		right->label = 0;
		root->label = 0;

		root->left = left;
		root->right = right;

		left->father = root;
		right->father = root;

		root->real = 0;
		root->word = '0';//�����һ��ֵ
		root->next = NULL;//��ʱΪ��

		addwordlist(root);

		display_wordlist();
		left = removefirst();
		right = removefirst();
		cout << endl;
	}
	left->father = NULL;//���һ���ڵ�����������
	addwordlist(left);
}

//����洢
void add_code(int j)
{
	int i = 0;
	while (code[i] != -1)
	{
		i++;
	}
	code[i] = j;
}

//��ӡ�ַ�����
void display_code()
{
	int i = 0;
	while (code[i] != -1)
	{
		cout << code[i];
		i++;
	}
}

//�ڱ���ĩβ���-1��ɾ������
void cancel_code_last()
{
	int i = 0;
	while (code[i] != -1)
	{
		i++;
	}
	i--;
	code[i] = -1;
}

//��code.txt�ļ���д�����������
void write_code(char zifu)
{
	ofstream fout;
	fout.open("code.txt", ios::app);
	int i = 0;
	fout << zifu;

	while (code[i] != -1)
	{
		fout << code[i];
		i++;
	}
	fout << endl;
	fout.close();
}

//�ݹ��д����ӡ����
void display_huffmantree(wordlist* p)
{
	//�ڵ㲻Ϊ����û�б�������
	if (p->left != NULL && p->left->label == 0)
	{
		add_code(0);
		display_huffmantree(p->left);
	}
	if (p->right != NULL && p->right->label == 0)
	{
		add_code(1);
		display_huffmantree(p->right);
	}
	else
	{
		if (p->real == 1)
		{
			if (p->word == '\n')
			{
				display_code();
				write_code(p->word);
				cout << "����" << endl;
			}
			else
			{
				display_code();
				write_code(p->word);
				cout << p->word << endl;
			}
		}
		p->label = 1;
		if (p->father != NULL)
		{
			cancel_code_last();
			display_huffmantree(p->father);
		}
	}
}


//ѹ���ɶ�����
void to_bin(const string& bin_str, const char* filename) {
	// ȷ���������ַ���������8�ı�����������ǣ���������
	size_t add_zero = (8 - bin_str.length() % 8) % 8;//���ġ�%8���Ǵ���8�ı���
	string add_bin_str = bin_str + string(add_zero, '0');
	zero_count = add_zero;

	ofstream outfile(filename, ios::binary);
	if (!outfile.is_open()) {
		cout << "�޷����ļ�����д��" << endl;
	}

	// ���������ַ���ÿ8���ַ���Ϊһ�飬������ת��Ϊ�ֽں�д���ļ�
	for (size_t i = 0; i < add_bin_str.length(); i += 8) {
		string er_jin_zhi_str = add_bin_str.substr(i, 8);//��i��ʼ��ȡ8����
		//����С�� 8,ʣ��λ������
		unsigned char er_jin_zhi_value = static_cast<unsigned char>(bitset<8>(er_jin_zhi_str).to_ulong());
		//reinterpret_cast ���� er_jin_zhi �ĵ�ַת��Ϊ char* ����
		outfile.write(reinterpret_cast<const char*>(&er_jin_zhi_value), 1);
	}

	outfile.close();
}

//ɾ���ļ�β�����0
void de_zero(const char* fileName, int zero_count) {
	ifstream infile(fileName);
	if (!infile.is_open()) {
		cout << "�޷����ļ�: " << fileName << endl;
		return;
	}

	//�ļ�infile�е��������ݶ�ȡ��һ��string����
	string content((istreambuf_iterator<char>(infile)),istreambuf_iterator<char>());
	infile.close();
	content = content.substr(0, content.length() - zero_count);

	ofstream outfile(fileName);
	outfile << content;
	outfile.close();
}

//�������ļ�ת�ı��ļ�
void bin_to_txt(const char* binfileName, const char* txtFileName) {
	ifstream binfile(binfileName, ios::binary);
	if (!binfile.is_open()) {
		cout << "�޷��򿪶������ļ�: " << binfileName << endl;
		return;
	}

	ofstream txtFile(txtFileName);
	if (!txtFile.is_open()) {
		cout << "�޷����ı��ļ�: " << txtFileName << endl;
		binfile.close();
		return;
	}

	unsigned char er_jin_zhi;

	while (binfile.read(reinterpret_cast<char*>(&er_jin_zhi), sizeof(er_jin_zhi))) {
		bitset<8> bits(er_jin_zhi); //��byte�е� 8 λ����ת��Ϊbitset�Ķ����Ʊ�ʾ��ʽ
		txtFile << bits.to_string();
	}

	binfile.close();
	txtFile.close();
	de_zero(txtFileName, zero_count);
}
