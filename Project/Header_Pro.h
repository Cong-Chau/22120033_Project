#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include<conio.h>
#include<stdlib.h>
#include<iomanip>
#define max 500
using namespace std;

struct Account {
	int mssv_nv;
	int password;
};

struct Node_Account {
	Account data;
	Node_Account* next;
};

struct Student {
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
	char id_class[max]; // lop hoc
	char teacher[max]; //ten giao vien
	char credit[2]; // so tin chi
	int max_stu = 50; // sinh vien toi da
	char day[max]; // ngay hoc trong tuan
	char lesson[max]; // tiet hoc trong tuan
};

struct Node_Course {
	Course data;
	Node_Course* next;
};

struct Year {
	int year;  //Nam hoc
	int solg;
};

struct Node_year {
	Year data;
	Node_year* next;
};

struct Score {
	int ID;
	char name[max];
	float score_mid; // diem giua ki
	float score_fin; // diem cuoi ki
	float score_total; // diem tong	
	char other_mark[max]; // danh dau khac
};

struct Node_Score {
	Score data;
	Node_Score* next;
};

// Chuc nang dang nhap cung mot so chuc nang khac
void Display_Header();
void textColor(int a);
int Count_file(char file[]);
int Find_Location(Account* p, int n, int x);
bool checkMSSV_MSNV(Account* p, int n, int ms);
bool checkMK(Account* p, int n, int ms, int pass);
int Login(Account* p, int n);
void changeMK(Account*& p, int n, int y);
void savePASS(Account*& p, int n, int ms, int x, int y);

/// --------SINH VIEN ----------//
int DEM_sv();
void Read_file_sv(Account*& p, int n);

// xem dach sach cac mon phai hoc trong ky nay
void View_Course_ofStudent(Node_Course* cou, int id);

// xuat bang diem sinh vien
void Create_namefileStudent(int id, char file[]);
int Take_Score(Node_Score* sco, int id, float& mid, float& fin, float& total);
void Export_Score_Student(Node_Course* cou, int id);

/// --------NHAN VIEN ----------//
int DEM_nv();
void Read_file_nv(Account*& p, int n);
void Function_after_Login_SV(int mssv);
void Function_after_Login_NV();

//  tao 1 nam hoc
Node_year* makeNode_year(Year x);
void addLast_year(Node_year*& y, Year x);
void input_Year(Year& x);
void write_File_year(Node_year* year);
void Create_1_year(Node_year*& year);

// tao lop hoc cho sinh vien nam nhat
void Upper_First(char x[]);
void Upper(char x[]);
Node_Class* makeNode_Class(Class x);
void addLast_Class(Node_Class*& cla, Class x);
void input_Class(Class& x);
void Create_Class(Node_Class*& cla, int n);
void Connect_class(char x[], char file[]);
void Write_file_class(Class cla);
void Create_file(char file[]);
bool Check_namefile_exist(Node_Class* cla, int local, char file[]);

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
Node_Account* makeNode_Account(Account x);
void addLast_Account(Node_Account*& acc, Account x);
bool Check_Account(int mssv);
void Update_Account(Node_Stu* stu);

// tao hoc ki hien tai
int Count_file_year();
void Read_file_year(Node_year* year);
void Create_HK(int& namhoc, int& hk, char start[], char end[]);

// tao khoa hoc
Node_Course* makeNode_Course(Course x);
void addLast_Course(Node_Course*& cou, Course x);
void Connect_Course(char x[], char y[], char file[]);
void input_Course(Course& x);
void Write_file_course(Course x);
void Create_Course(Node_Course*& cou);
void Read_file_course(Node_Course*& cou, int n);
bool check_File_Course(char x[], char  y[]);
void List_Course(Node_Course* cou);
void Choose_Course(Node_Course* cou);

// tai tep csv sinh vien dang ky khoa hoc
Node_Score* makeNode_Score(Score x);
void addLast_Score(Node_Score*& sco, Score x);
int Read_input_course(Node_Score*& sco, char file[]);
void Choose_Course(Node_Course* cou);
void Arrange_StuScore(Node_Score*& sco);
void Write_Stu_Sco_Course(Node_Score* sco, char file[]);
int Read_Stu_Sco_Course(Node_Score*& sco, int n, char file[]);

// xem danh sach khoa hoc
void Display_Course(Node_Course* cou);

// cap nhat thong tin khoa hoc
void Update_Course(Node_Course*& cou);
void Re_Write_file_course(Node_Course* cou);

// them 1 sinh vien vao khoa hoc
void Input_Stu_Course(Score& sco);
void AddStudent_ofCourse(Node_Course* cou);

// xoa 1 sinh vien ra khoi khoa hoc
int findLocal(Node_Score* sco, int id);
void delete_Student(Node_Score*& sco, int local, int lim);
void reWrite_Stu_Sco_Course(Node_Score* sco, char file[]);
void deleteStudent_ofCourse(Node_Course* cou);

// xoa 1 khoa hoc
void Delete_Course(Node_Course*& cou, int& n);
void ReWrite_course(Node_Course* cou, int n);


// xem danh sach sinh vien trong moi lop
void Display_Student_ofClass(Node_Class* cla, int n);

// xem danh sach sinh vien trong khoa hoc
void Display_Student_ofCourse(Node_Course* cou);

// xuat danh sach sinh vien 1 khoa hoc ra file CSV
void Connect_File(char x[max], char y[max]);
void Export_Course_File(Node_Course* cou);

// nhap diem 1 khoa hoc
void Arrange_Stu(Node_Stu*& stu);
bool Check_ID_import(Node_Score* sco, Node_Score* _import);
void Re_Assign(Node_Score*& sco, Node_Score* _import);
void Import_Score_Course(Node_Course* cou);

// xem bang diem 1 khoa hoc
void View_Score_Course(Node_Course* cou);

// cap nhat ket qua sinh vien
void Update_Result_Student(Node_Course* cou);