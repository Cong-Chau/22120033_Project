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
	char id[max]; // ma lop
	char faculty[max]; // khoa cua lop truc thuoc
};

struct Node_Class {
	Class data;
	Node_Class* next;
};

struct Course {
	char id[max]; // ma mon hoc
	char name[max]; // ten khoa hoc
	char id_class; // lop hoc
	char teacher[max]; //ten giao vien
	char credit; // so tin chi
	int max_stu = 50; // sinh vien toi da
	char day[max]; // ngay hoc trong tuan
	char lesson[max]; // tiet hoc trong tuan
};

struct Node_Course {
	Course data;
	Node_Course* next;
};

struct NamHoc {
	int year;  //Nam hoc
	int solg;
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

// tao lop hoc cho sinh vien nam nhat
void Upper(char x[]);
Node_Class* makeNode_Class(Class x);
void addLast_Class(Node_Class*& cla, Class x);
int Count_file_class();
void input_Class(Class& x);
void Create_Class(Node_Class*& cla, int n);
void Connect_class(char x[], char file[]);
void Write_file_class(Class cla);
void Write_namefile_class(char x[]);
void Create_file_class(char file[]);
void Create_AllFile_Class(Node_Class* cla);

// them sinh vien nam nhat vao cac lop nam nhat
void List_Class(Node_Class* cla);
void Read_file_class(Node_Class*& cla, int n);
void Write_csv_class(Node_Stu* stu, int chon, int lim);
void Choose_Class(Node_Class* cla);

// doc file csv
int Change_char_int(char x[]);
Node_Stu* makeNode_student(Student x);
void addLast_stu(Node_Stu*& y, Student x);
int Count_file_csv(char file[]);
int Read_file_csv(Node_Stu*& stu, char file[]);


// tao hoc ki hien tai
int Count_file_year();
void Read_file_year(Node_year* year);
void Create_HK(int& namhoc, int& hk, char start[], char end[]);

