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
	char word;  // 字符
	int count;  // 计数
	int side;	// 边
	int real;	// 是否为真实节点
	wordlist* next; // 下一个指针

	int label;			//树遍历 标记
	wordlist* left;
	wordlist* right;
	wordlist* father;

};

//全局变量
int code[20];
int zero_count;
wordlist* wordlist_head;

//初始化函数
void init()
{
	//初始化单词链表
	wordlist_head = (wordlist*)malloc(sizeof(wordlist));
	wordlist_head->word = '0';
	wordlist_head->count = 0;
	wordlist_head->side = 0;
	wordlist_head->next = NULL;

	//初始化编码
	for (int i = 0; i < 20; i++)
	{
		code[i] = -1;
	}

	remove("code.txt");
	remove("bin.txt");
	remove("test2.txt");
}

//创建链表
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

	//初始化插入的新节点
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

	//插入节点
	p_seek = wordlist_head;
	while (p_seek->next != NULL)
	{
		p_seek = p_seek->next;
	}
	p_seek->next = p_new;
	return 1;
}

//读取文本
int read_text(char filename[])
{
	char zifu;
	ifstream fin;//实例化对象
	fin.open(filename);

	if (!fin.is_open())
	{
		cout << "文本打开失败" << endl;
		return 0;
	}
	// 检查文件是否为空
	if (fin.peek() == EOF) {
		cout << "文本为空" << endl;
		return 0;
	}
	while (fin.peek() != EOF)//检查是否为文件尾
	{
		fin.get(zifu);
		cout << zifu;
		insert(zifu);
	}
}

//获取链表长度
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

//交换函数
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

//链表排序（冒泡排序）
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

//打印升序的链表中的元素
void display_wordlist()
{
	wordlist* p_this = wordlist_head->next;
	while (p_this != NULL)
	{
		if (p_this->word == '\n')
			cout << "换行符\t" << p_this->count << endl;
		else if (p_this->real == 0)
			cout << "虚节点\t" << p_this->count << endl;
		else
			cout << p_this->word << "\t" << p_this->count << endl;
		p_this = p_this->next;
	}
}

//摘除并返回首节点
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

//插入链表
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
		//寻找插入位置
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

//构建哈夫曼树
void build_huffmantree()
{
	wordlist* left = removefirst();
	wordlist* right = removefirst();

	while (right != NULL)
	{
		wordlist* root;//叶子结点
		root = (wordlist*)malloc(sizeof(wordlist));

		root->count = (left->count + right->count);
		root->side = -1;//新生成节点
		//左子树为0，右子树为1
		left->side = 0;
		right->side = 1;

		//遍历过节点标记为0
		left->label = 0;
		right->label = 0;
		root->label = 0;

		root->left = left;
		root->right = right;

		left->father = root;
		right->father = root;

		root->real = 0;
		root->word = '0';//随机赋一个值
		root->next = NULL;//暂时为空

		addwordlist(root);

		display_wordlist();
		left = removefirst();
		right = removefirst();
		cout << endl;
	}
	left->father = NULL;//最后一个节点在左子树上
	addwordlist(left);
}

//编码存储
void add_code(int j)
{
	int i = 0;
	while (code[i] != -1)
	{
		i++;
	}
	code[i] = j;
}

//打印字符编码
void display_code()
{
	int i = 0;
	while (code[i] != -1)
	{
		cout << code[i];
		i++;
	}
}

//在编码末尾添加-1，删除编码
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

//向code.txt文件中写入哈夫曼编码
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

//递归编写并打印编码
void display_huffmantree(wordlist* p)
{
	//节点不为空且没有被遍历过
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
				cout << "换行" << endl;
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


//压缩成二进制
void to_bin(const string& bin_str, const char* filename) {
	// 确保二进制字符串长度是8的倍数，如果不是，则进行填充
	size_t add_zero = (8 - bin_str.length() % 8) % 8;//最后的“%8”是处理8的倍数
	string add_bin_str = bin_str + string(add_zero, '0');
	zero_count = add_zero;

	ofstream outfile(filename, ios::binary);
	if (!outfile.is_open()) {
		cout << "无法打开文件进行写入" << endl;
	}

	// 将二进制字符串每8个字符分为一组，并将其转换为字节后写入文件
	for (size_t i = 0; i < add_bin_str.length(); i += 8) {
		string er_jin_zhi_str = add_bin_str.substr(i, 8);//从i开始提取8个数
		//长度小于 8,剩余位置置零
		unsigned char er_jin_zhi_value = static_cast<unsigned char>(bitset<8>(er_jin_zhi_str).to_ulong());
		//reinterpret_cast 来将 er_jin_zhi 的地址转换为 char* 类型
		outfile.write(reinterpret_cast<const char*>(&er_jin_zhi_value), 1);
	}

	outfile.close();
}

//删除文件尾多余的0
void de_zero(const char* fileName, int zero_count) {
	ifstream infile(fileName);
	if (!infile.is_open()) {
		cout << "无法打开文件: " << fileName << endl;
		return;
	}

	//文件infile中的所有内容读取到一个string对象
	string content((istreambuf_iterator<char>(infile)),istreambuf_iterator<char>());
	infile.close();
	content = content.substr(0, content.length() - zero_count);

	ofstream outfile(fileName);
	outfile << content;
	outfile.close();
}

//二进制文件转文本文件
void bin_to_txt(const char* binfileName, const char* txtFileName) {
	ifstream binfile(binfileName, ios::binary);
	if (!binfile.is_open()) {
		cout << "无法打开二进制文件: " << binfileName << endl;
		return;
	}

	ofstream txtFile(txtFileName);
	if (!txtFile.is_open()) {
		cout << "无法打开文本文件: " << txtFileName << endl;
		binfile.close();
		return;
	}

	unsigned char er_jin_zhi;

	while (binfile.read(reinterpret_cast<char*>(&er_jin_zhi), sizeof(er_jin_zhi))) {
		bitset<8> bits(er_jin_zhi); //将byte中的 8 位数据转换为bitset的二进制表示形式
		txtFile << bits.to_string();
	}

	binfile.close();
	txtFile.close();
	de_zero(txtFileName, zero_count);
}
