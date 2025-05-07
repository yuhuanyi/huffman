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
	char code[20]; // 哈弗曼编码
	char word;  //编码字符
	codetable* next;
};

codetable* codetable_head;

//编码链表初始化
void init_codetable()
{
	codetable_head = (codetable*)malloc(sizeof(codetable));
	codetable_head->word = '0';
	codetable_head->code[0] = '\0';
	codetable_head->next = NULL;
}

//添加节点到链表末尾
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

//读取编码文件并创建存储链表
void read_codetable()
{
	ifstream fin;
	fin.open("code.txt");

	while (fin.peek() != EOF)
	{
		codetable* temp;
		temp = (codetable*)malloc(sizeof(codetable));
		temp->word = fin.get();//先读取字符

		char code_part;
		int i = 0;
		code_part = fin.get();

		while (code_part != '\n')//读取编码
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

//打印读取编码表
void display_codetable()
{
	cout << "哈夫曼对应的编码表" << endl;
	codetable* p_seek;
	p_seek = codetable_head->next;
	while (p_seek != NULL)
	{
		if (p_seek->word == '\n')
			cout << "换行符\t" << p_seek->code << endl;
		else
			cout << p_seek->word << "\t" << p_seek->code << endl;
		p_seek = p_seek->next;
	}
	cout << "显示完毕" << endl;
}

//压缩
void compress_code() {
	char zifu;
	ifstream fin;
	fin.open("test.txt");
	if (!fin.is_open()) {
		cout << "未打开文件" << endl;
		return;
	}
	ofstream fout;
	fout.open("bin.txt", ios::app);
	stringstream bin_code;  // 用于收集二进制编码的字符串流

	while (fin.peek() != EOF) {
		fin.get(zifu);
		codetable* p_seek;
		p_seek = codetable_head->next;
		while (zifu != p_seek->word) {
			p_seek = p_seek->next;
		}
		fout << p_seek->code;  // 向bin.txt文件写入编码
		bin_code << p_seek->code;  // 将编码添加到字符串流中
	}
	fin.close();
	fout.close();

	// 将字符串流中的内容转换为字符串并写入test.bin文件
	string binary_str = bin_code.str();
	to_bin(binary_str, "test.bin");
}

//解压缩
void decompress_code()
{
	char code[20];
	code[0] = '\0';
	int i = 0;
	ifstream fin;
	fin.open("bin.txt");

	if (!fin.is_open())
	{
		cout << "未打开文件" << endl;
		return;
	}

	while (fin.peek() != EOF)
	{
		ofstream fout;
		fout.open("test2.txt", ios::app);

		codetable* p_seek;
		p_seek = codetable_head->next;

		while (strcmp(code, p_seek->code) != 0)//比较匹配字符
		{
			fin.get(code[i]);
			code[i + 1] = '\0';
			if (strcmp(code, p_seek->code) == 0)
				break;

			while (p_seek != NULL && strcmp(code, p_seek->code) != 0)
			{
				//寻找匹配的字符
				p_seek = p_seek->next;
			}
			if (p_seek != NULL && strcmp(code, p_seek->code) == 0)
			{
				//成功匹配到字符
				i = 0;
				break;
			}
			i++;
			p_seek = codetable_head->next;
		}
		fout << p_seek->word;
		fout.close();
		cout << "匹配成功" << "  " << code << p_seek->code << endl;
		i = 0;
		code[0] = 5;
	}
	fin.close();
}

//打印编码和译码
void display_code_file(const char* filename)
{
	ifstream fin;
	fin.open(filename);
	char output;
	cout << "编码文件如下：" << endl;

	while (fin.peek() != EOF)
	{
		fin.get(output);
		cout << output;
	}
	cout << "\n输出结束" << endl;
	fin.close();
}
