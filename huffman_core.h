#pragma once
#ifndef __HUFFMAN_CORE_
#define __HUFFMAN_CORE_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdio>
#include <Windows.h>
#include <sstream>
#include"huffman_helper.h"

#endif
using namespace std;

struct codetable {
	char code[20]; // ����������
	char word;  //�����ַ�
	codetable* next;
};

codetable* codetable_head;

//���������ʼ��
void init_codetable()
{
	codetable_head = (codetable*)malloc(sizeof(codetable));
	codetable_head->word = '0';
	codetable_head->code[0] = '\0';
	codetable_head->next = NULL;
}

//��ӽڵ㵽����ĩβ
void add_codetable(codetable* temp)
{
	codetable* p_seek;
	p_seek = codetable_head;
	while (p_seek->next != NULL)
	{
		p_seek = p_seek->next;
	}
	p_seek->next = temp;
}

//��ȡ�����ļ��������洢����
void read_codetable()
{
	ifstream fin;
	fin.open("code.txt");

	while (fin.peek() != EOF)
	{
		codetable* temp;
		temp = (codetable*)malloc(sizeof(codetable));
		temp->word = fin.get();//�ȶ�ȡ�ַ�

		char code_part;
		int i = 0;
		code_part = fin.get();

		while (code_part != '\n')//��ȡ����
		{
			temp->code[i] = code_part;
			i++;
			code_part = fin.get();
		}

		temp->code[i] = '\0';
		temp->next = NULL;

		add_codetable(temp);
	}
	fin.close();
}

//��ӡ��ȡ�����
void display_codetable()
{
	cout << "��������Ӧ�ı����" << endl;
	codetable* p_seek;
	p_seek = codetable_head->next;
	while (p_seek != NULL)
	{
		if (p_seek->word == '\n')
			cout << "���з�\t" << p_seek->code << endl;
		else
			cout << p_seek->word << "\t" << p_seek->code << endl;
		p_seek = p_seek->next;
	}
	cout << "��ʾ���" << endl;
}

//ѹ��
void compress_code() {
	char zifu;
	ifstream fin;
	fin.open("test.txt");
	if (!fin.is_open()) {
		cout << "δ���ļ�" << endl;
		return;
	}
	ofstream fout;
	fout.open("bin.txt", ios::app);
	stringstream bin_code;  // �����ռ������Ʊ�����ַ�����

	while (fin.peek() != EOF) {
		fin.get(zifu);
		codetable* p_seek;
		p_seek = codetable_head->next;
		while (zifu != p_seek->word) {
			p_seek = p_seek->next;
		}
		fout << p_seek->code;  // ��bin.txt�ļ�д�����
		bin_code << p_seek->code;  // ��������ӵ��ַ�������
	}
	fin.close();
	fout.close();

	// ���ַ������е�����ת��Ϊ�ַ�����д��test.bin�ļ�
	string binary_str = bin_code.str();
	to_bin(binary_str, "test.bin");
}

//��ѹ��
void decompress_code()
{
	char code[20];
	code[0] = '\0';
	int i = 0;
	ifstream fin;
	fin.open("bin.txt");

	if (!fin.is_open())
	{
		cout << "δ���ļ�" << endl;
		return;
	}

	while (fin.peek() != EOF)
	{
		ofstream fout;
		fout.open("test2.txt", ios::app);

		codetable* p_seek;
		p_seek = codetable_head->next;

		while (strcmp(code, p_seek->code) != 0)//�Ƚ�ƥ���ַ�
		{
			fin.get(code[i]);
			code[i + 1] = '\0';
			if (strcmp(code, p_seek->code) == 0)
				break;

			while (p_seek != NULL && strcmp(code, p_seek->code) != 0)
			{
				//Ѱ��ƥ����ַ�
				p_seek = p_seek->next;
			}
			if (p_seek != NULL && strcmp(code, p_seek->code) == 0)
			{
				//�ɹ�ƥ�䵽�ַ�
				i = 0;
				break;
			}
			i++;
			p_seek = codetable_head->next;
		}
		fout << p_seek->word;
		fout.close();
		cout << "ƥ��ɹ�" << "  " << code << p_seek->code << endl;
		i = 0;
		code[0] = 5;
	}
	fin.close();
}

//��ӡ���������
void display_code_file(const char* filename)
{
	ifstream fin;
	fin.open(filename);
	char output;
	cout << "�����ļ����£�" << endl;

	while (fin.peek() != EOF)
	{
		fin.get(output);
		cout << output;
	}
	cout << "\n�������" << endl;
	fin.close();
}
