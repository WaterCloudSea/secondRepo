#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h> // ���ڷ�Ӧ�������
#include <Windows.h>

#define MAX_ID 11  //ID ����󳤶�
#define MAX_PWD 20 //������󳤶�
#define MAX_NAME 15 // ������󳤶�
#define MAX_SEX 5 // �Ա���󳤶�
#define MAX_PHONE 12 //�绰��󳤶�

typedef struct Users {
	char id[MAX_ID]; //��¼�˺�
	char pwd[MAX_PWD]; // ��¼����
	char name[MAX_NAME]; // ����
	char sex[MAX_SEX]; //�Ա�
	char phone[MAX_PHONE]; //�绰
}Users;

/************************��������***************************/

// ��ӡ�˵�
void menu();

// �û�ע��
void Register();

//��¼
void Login();

// �һ�����
void Reback();

// ��λ���
void gotoxy(int x,int y);

//��ȡx��λ��
int posx();

// ��ȡy��λ��
int posy();

// �������루���ڸǹ��ܣ�
void Getpwd(char* pwd);


