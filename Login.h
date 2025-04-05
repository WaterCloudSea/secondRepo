#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h> // 用于反应意外情况
#include <Windows.h>

#define MAX_ID 11  //ID 的最大长度
#define MAX_PWD 20 //密码最大长度
#define MAX_NAME 15 // 名字最大长度
#define MAX_SEX 5 // 性别最大长度
#define MAX_PHONE 12 //电话最大长度

typedef struct Users {
	char id[MAX_ID]; //登录账号
	char pwd[MAX_PWD]; // 登录密码
	char name[MAX_NAME]; // 姓名
	char sex[MAX_SEX]; //性别
	char phone[MAX_PHONE]; //电话
}Users;

/************************声明函数***************************/

// 打印菜单
void menu();

// 用户注册
void Register();

//登录
void Login();

// 找回密码
void Reback();

// 定位光标
void gotoxy(int x,int y);

//获取x的位置
int posx();

// 获取y的位置
int posy();

// 密码输入（含掩盖功能）
void Getpwd(char* pwd);


