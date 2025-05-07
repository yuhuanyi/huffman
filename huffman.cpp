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
	init();//初始化

	char filename[20];
	cout << "请输入需要压缩的文件名：";
	cin >> filename;
	read_text(filename);
	cout << endl;

	sort();//排序
	display_wordlist();//显示排序后的链表C

	build_huffmantree();//创建哈夫曼树

	display_huffmantree(wordlist_head->next);//编写并打印编码
	cout << endl;

	init_codetable();//初始化链表，清空之前的数据结构操作
	read_codetable();//读取编码文件code.txt
	display_codetable();//打印编码文件code.txt
	cout << endl;

	compress_code();//编码
	bin_to_txt("test.bin", "bin2.txt");
	decompress_code();//解码

	display_code_file("test2.txt");//打印test2.txt
    
}