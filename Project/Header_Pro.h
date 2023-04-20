#include<iostream>
#include<fstream>
#include<windows.h>
#define max 100
using namespace std;


struct Account {
	int mssv_gv;
	int password;
};

struct Student {
	//int No;
	int ID; //mssv
	char name[max]; //Ten
	char ho[max]; //Ho va ten dem
	char sex[max]; //Gioi tinh
	char birth[max]; //Ngay sinh
	int cccd; //So cccd hoac cmnd
};

struct Node_Stu {
	Student data;
	Node_Stu* next;
};

struct Class {
	char idclass[max]; //Ma lop hoc
	char nameclass[max]; //ten khoa hoc
	int amount = 50; //So luong sinh vien toi da trong lop 
	Node_Stu* stu; //Danh sach sinh vien trong lop
};

struct Node_class {
	Class data;
	Node_class* next;
};

struct NamHoc {
	int year;  //Nam hoc
	int solg;
	Node_class* cla; // Danh sach lop mo
};

struct Node_year {
	NamHoc data;
	Node_year* next;
};





void Display_Header();
void textColor(int a);
int Find_Location(Account* p, int n, int x);
bool checkMSSV_MSGV(Account* p, int n, int ms);
bool checkMK(Account* p, int n, int ms, int pass);
int Login(Account* p, int n);
void changeMK(Account*& p, int n, int y);
void savePASS(Account*& p, int n, int ms, int x, int y);

//sinh vien
int DEM_sv();
void Read_file_sv(Account*& p, int n);


//giao vien
int DEM_gv();
void Read_file_gv(Account*& p, int n);

void Function_after_Login_SV(int mssv);
void Function_after_Login_NV();
//  tao 1 nam hoc
Node_year* makeNode_year(NamHoc x);
void addLast_year(Node_year*& y, NamHoc x);
void input_Year(NamHoc& x);
void write_File_year(Node_year* year);
void Create_1_year(Node_year*& year);

// tao 1 lop hoc
void upper_Class(char x[]);
Node_class* makeNode_Class(Class x);
void addLast_Class(Node_class*& clss, Class x);
void input_Class(Class& x);
void write_File_class(Node_class* clss);
void create_NewClass(Node_class*& clss);

// tao hoc ki hien tai
int Count_file_year();
void Read_file_year(Node_year* year);
void Create_HK(int& namhoc, int& hk, char start[], char end[]);

// them hoc sinh nam 1 vao lop nam 1
Node_Stu* makeNode_student(Student x);
void addLast_stu(Node_Stu*& y, Student x);
int Count_file_class();
void Read_file_class(Node_class*& clss, int n);
bool check_File_Class(char x[]);
void List_class(Node_class* clss);
void Connect_Char(char x[], char y[], char file[]);
void Create_file_clss(Class x);
void Create_ALL_clss(Node_class* clss);
void Choose_Class(Node_class* clss);
void Write_csv_class(Node_Stu* stu, int chon, int lim);