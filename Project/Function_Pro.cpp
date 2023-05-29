#include"Header_Pro.h"

char tail[] = { ".CSV" };

//--------------Dang nhap-------------//
//Mau chu
void textColor(int a) {
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, a);
}
//---------Phan header
void Display_Header() {
	textColor(243);
	cout << "====================================================================" << endl;
	cout << "=                                                                  =" << endl;
	cout << "=                        CHAO MUNG DEN VOI                         =" << endl;
	cout << "=               HE THONG QUAN LY THONG TIN SINH VIEN               =" << endl;
	cout << "=                                                                  =" << endl;
	cout << "====================================================================" << endl;
	textColor(7);
}
//-----Dem file
int Count_file(char file[]) {
	int dem = 0;
	ifstream read(file, ios::in);
	while (!read.eof()) {
		char x[max];
		read.getline(x, max);
		if (strlen(x) != 0)
			dem++;
	}
	read.close();
	return dem;
}

//-----------Dang nhap
int Login(Account* p, int n) {
	textColor(10);
	cout << "\n\t    ======= DANG NHAP TAI KHOAN =======" << endl;
	textColor(7);
	int mssv;
	cout << "\tTen tai khoan : "; cin >> mssv;
	int mk;
	cout << "\tMat khau      : "; cin >> mk;
	while ((checkMSSV_MSNV(p, n, mssv) == false) || (checkMK(p, n, mssv, mk) == false)) {
		textColor(12);
		cout << "\t*Ten tai khoan hoac mat khau khong chinh xac*" << endl;
		cout << "\t1. Thoat" << endl;
		cout << "\t2. Dang nhap lai" << endl;
		int x; cout << "\tChon: "; cin >> x;
		textColor(7);
		if (x == 1)
			return -1;
		system("cls");//Reset lai man hinh
		Display_Header();
		textColor(10);
		cout << "\n\t    ======= DANG NHAP TAI KHOAN =======" << endl;
		textColor(7);
		cout << "\tTen tai khoan : "; cin >> mssv;
		cout << "\tMat khau      : "; cin >> mk;
	}
	return mssv;
}

//----------Doi mat khau
void changeMK(Account*& p, int n, int y) {
	system("cls");
	Display_Header();
	textColor(10);
	cout << "\n\t      ===DOI MAT KHAU===" << endl;
	textColor(7);
	int  ms;
	cout << "     Ten tai khoan     : "; cin >> ms;
	int vitri = Find_Location(p, n, ms);

	while (vitri == -1) {
		textColor(12);
		cout << "  *Ten tai khoan vua nhap khong the tim thay*" << endl;
		textColor(7);
		cout << "  1. Thoat" << endl;
		cout << "  2. Nhap lai Ten tai khoan" << endl;
		int x; cout << "Chon: "; cin >> x;
		if (x == 1)
			return;
		system("cls");
		Display_Header();
		textColor(10);
		cout << "\n\t      ===DOI MAT KHAU===" << endl;
		textColor(7);
		cout << "     Ten tai khoan     : "; cin >> ms;
		vitri = Find_Location(p, n, ms);
	}
	int mkcu, mkmoi_1, mkmoi_2;
	cout << "     Mat khau cu       : "; cin >> mkcu;
	cout << "     Mat khau moi      : "; cin >> mkmoi_1;
	cout << "     Xac nhan mat khau : "; cin >> mkmoi_2;

	if (checkMK(p, n, ms, mkcu) == false) {
		textColor(12);
		cout << "  *Mat khau cu khong chinh xac*" << endl;
	}
	else {
		if (mkmoi_1 != mkmoi_2) {
			cout << "  *Xac nhan mat khau khong chinh xac*" << endl; textColor(10);
		}
		else
			textColor(10); cout << "  *Cap nhat mat khau thanh cong.*\n" << endl;
	}
	textColor(7);

	while ((checkMK(p, n, ms, mkcu) == false) || (mkmoi_1 != mkmoi_2)) {
		cout << "  1. Thoat" << endl;
		cout << "  2. Nhap lai" << endl;
		int x; cout << "  Chon: "; cin >> x;
		if (x == 1)
			return;
		system("cls");
		Display_Header();
		textColor(12);
		textColor(10);
		cout << "\n\t      ===DOI MAT KHAU===" << endl;
		textColor(7);
		textColor(7);
		cout << "     Ten tai khoan     : "; cin >> ms;
		cout << "     Mat khau cu       : "; cin >> mkcu;
		cout << "     Mat khau moi      : "; cin >> mkmoi_1;
		cout << "     Xac nhan mat khau : "; cin >> mkmoi_2;
		textColor(12);
		if (checkMK(p, n, ms, mkcu) == false)
			cout << "*Mat khau cu khong chinh xac*" << endl;
		else {
			if (mkmoi_1 != mkmoi_2) {
				cout << "*Xac nhan mat khau khong chinh xac*" << endl; textColor(10);
			}
			else
				textColor(10); cout << "*Cap nhat mat khau thanh cong.*\n" << endl;
		}
		textColor(7);
	}
	savePASS(p, n, ms, mkmoi_1, y);
}

//---------------------------------------------------------------//
//                     SINH VIEN
	//----------Luu mat khau moi-----------------//
void savePASS(Account*& p, int n, int mssv, int x, int y) {
	int vitri = Find_Location(p, n, mssv);
	p[vitri].password = x;
	if (y == 1) {
		ofstream write("accountSV.txt", ios::out);
		for (int i = 0; i < n; i++) {
			write << p[i].mssv_nv << endl;
			write << p[i].password << endl;
		}
		write.close();
	}
	if (y == 2) {
		ofstream write("accountNV.txt", ios::out);
		for (int i = 0; i < n; i++) {
			write << p[i].mssv_nv << endl;
			write << p[i].password << endl;
		}
		write.close();
	}

}

//---------------Xem file co bao nhieu phan tu
int DEM_sv() {
	ifstream read("accountSV.txt", ios::in);
	int n = 0;
	char tmp[100];
	while (!read.eof()) {
		read.getline(tmp, 100);
		if (strlen(tmp) == 0)
			n--;
		n++;
	}
	read.close();
	return n;
}
//--------------Doc du lieu tu file account v�o p
void Read_file_sv(Account*& p, int n) {
	ifstream read("accountSV.txt", ios::in);
	for (int i = 0; i < n; i++) {
		read >> p[i].mssv_nv;
		read >> p[i].password;
	}
	read.close();
}
//-------Tim vi tri cua mssv duoc nhap, tra ve -1 neu khong tim thay vi tri
int Find_Location(Account* p, int n, int x) {
	for (int i = 0; i < n; i++) {
		if (x == p[i].mssv_nv)
			return i;
	}
	return -1;
}
//------Kiem tra mssv co ton tai hay khong
bool checkMSSV_MSNV(Account* p, int n, int ms) {
	for (int i = 0; i < n; i++) {
		if (ms == p[i].mssv_nv)
			return true;
	}
	return false;
}
//------Kiem tra mat khau co chinh xac hay khong
bool checkMK(Account* p, int n, int ms, int pass) {
	int vitri = Find_Location(p, n, ms);
	if (vitri == -1)
		return false;
	if (pass == p[vitri].password)
		return true;
	return false;
}


//////////-------------FUNCTION--------------//////////////


//--------------------Giang vien---------------------//

int DEM_nv() {
	ifstream read("accountNV.txt", ios::in);
	int n = 0;
	char tmp[100];
	while (!read.eof()) {
		read.getline(tmp, 100);
		if (strlen(tmp) == 0)
			n--;
		n++;
	}
	read.close();
	return n;
}

void Read_file_nv(Account*& p, int n) {
	ifstream read("accountNV.txt", ios::in);
	for (int i = 0; i < n; i++) {
		read >> p[i].mssv_nv;
		read >> p[i].password;
	}
	read.close();
}

////---------------Chuc nang cho sinh vien

void Function_after_Login_SV(int id) {
	/*
	du lieu duoc khai bao sau
	*/
	while (1) {
		system("cls");
		Display_Header();
		cout << endl << "                    --SINH VIEN--                " << endl;
		cout << "   ===================================================" << endl;
		cout << "   =  0. Thoat" << endl;
		cout << "   =  1. Xem danh sach lop da duoc dang ky           =" << endl;
		cout << "   =  2. Xem bang diem tong ket                      =" << endl;
		cout << "   ===================================================" << endl;
		int chon; cout << "   Muc ban muon xem : "; cin >> chon;
		switch (chon) {
		case 0: {
			return;
		}
		case 1: {
			cout << "Chua duoc cap nhat\n";
			break;
		}
		case 2: {
			cout << "   Xem bang diem\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			if (n != 0) {
				Read_file_course(cou, n);
				//	Create_AllFile_Course(cou);
			//	List_Course(cou);
				Export_Score_Student(cou, id);
			}
			break;
		}
		}
		cout << "   Ban muon quay tro lai hay thoat?\n";
		cout << "     1. Tro lai     2. Thoat\n";
		int p; cout << "  Chon: "; cin >> p;
		if (p == 2) {
			return;
		}
	}
}

////---------------Chuc nang cho nhan vien

void Function_after_Login_NV() {
	int year_now, hk;
	Node_year* year = NULL;

	while (1) {
		cout << endl << "                         --NHAN VIEN--                " << endl;
		cout << "   ==================================================================" << endl;
		cout << "   =  0. Thoat                                                      =" << endl;
		cout << "   =  1. Tao mot nam hoc moi                                        =" << endl;
		cout << "   =  2. Tao mot so lop cho sinh vien nam nhat                      =" << endl;
		cout << "   =  3. Them moi hoc sinh nam 1 vao cac lop nam 1                  =" << endl;
		cout << "   =  4. Tao 1 hoc ki moi                                           =" << endl;
		cout << "   =  5. Tao khoa hoc moi                                           =" << endl;
		cout << "   =  6. Tai tep CSV sinh vien da dang ky khoa hoc                  =" << endl;
		cout << "   =  7. Xem danh sach cac khoa hoc                                 =" << endl;
		cout << "   =  8. Cap nhat thong tin khoa hoc                                =" << endl;
		cout << "   =  9. Them 1 sinh vien vao khoa hoc                              =" << endl;
		cout << "   = 10. Xoa 1 sinh vien ra khoi khoa hoc                           =" << endl;
		cout << "   = 11. Xoa khoa hoc                                               =" << endl;
		cout << "   = 12. Xem danh sach cac lop                                      =" << endl;
		cout << "   = 13. Xem danh sach hoc sinh trong lop                           =" << endl;
		cout << "   = 14. Xem danh sach hoc sinh trong moi khoa hoc                  =" << endl;
		cout << "   = 15. Xuat danh sach sinh vien trong moi khoa hoc ra file CSV    =" << endl;
		cout << "   = 16. Nhap bang diem cua 1 khoa hoc                              =" << endl;
		cout << "   = 17. Xem bang diem cua 1 khoa hoc                               =" << endl;
		cout << "   = 18. Cap nhat ket qua cua hoc sinh                              =" << endl;
		cout << "   ==================================================================" << endl;
		int chon; cout << "    Chon muc ban muon xem : "; cin >> chon;
		system("cls");
		Display_Header();
		switch (chon) {
		case 0: {
			return;
		}
		case 1: {
			cout << "\n   Tao nam hoc moi\n";
			Create_1_year(year);
			break;
		}
		case 2: {
			cout << "\n   Tao mot so lop hoc moi cho sinh vien nam nhat\n";
			Node_Class* cla = NULL;
			int n;
			cout << "    So luong lop muon tao them: "; cin >> n;
			Create_Class(cla, n);
			Create_AllFile_Class(cla);
			textColor(10);
			cout << "  *Cac lop hoc da duoc tao thanh cong*\n\n";
			textColor(7);
			break;
		}
		case 3: {
			cout << "\n   Them sinh vien nam 1 vao lop nam 1\n";
			Node_Class* cla = NULL;
			char file[] = "class.txt";
			int n = Count_file(file) / 2;
			Read_file_class(cla, n);
			Create_AllFile_Class(cla);
			List_Class(cla);
			Choose_Class(cla);
			textColor(10);
			cout << "  *Da them sinh vien thanh cong*\n\n";
			textColor(7);
			break;
		}
		case 4: {
			cout << "\n   Tao hoc ki\n";
			char start[max], end[max];
			Create_HK(year_now, hk, start, end);
			break;
		}
		case 5: {
			cout << "\n   Tao khoa hoc moi\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			Create_AllFile_Course(cou);
			if (n != 0)
				Read_file_course(cou, n);
			Create_Course(cou);
			textColor(10);
			cout << "   *Khoa hoc da duoc tao thanh cong*\n\n";
			textColor(7);
			break;
		}
		case 6: {
			cout << "\n   Tai tep CSV sinh vien da dang ky khoa hoc\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			if (n != 0) {
				Read_file_course(cou, n);
//				Create_AllFile_Course(cou);
				List_Course(cou);
				Choose_Course(cou);
				textColor(10);
				cout << "   *Tai danh sach sinh vien thanh cong*\n\n";
				textColor(7);
			}
			else
				cout << "\n    Hien tai chua co bat ki khoa hoc nao!\n";
			break;
		}
		case 7: {
			cout << "\n   Danh sach cac khoa hoc\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			if (n != 0) {
				Read_file_course(cou, n);
				Display_Course(cou);
			}
			else
				cout << "\n    Hien tai chua co bat ki khoa hoc nao!\n";
		}
		case 8: {
			cout << "\n   Cap nhat thong tin khoa hoc\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			if (n != 0)
				Read_file_course(cou, n);
			List_Course(cou);
			Update_Course(cou);
			Re_Write_file_course(cou);
			Re_Write_namefile_course(cou);
			while (1) {
				cout << "\n   Muon tiep tuc cap nhat khoa hoc khac khong?\n";
				cout << "    1. Co     2. Khong\n";
				int a; cout << "   Chon: "; cin >> a;
				if (a == 2)
					break;
				system("cls");
				Display_Header();
				List_Course(cou);
				Update_Course(cou);
				Re_Write_file_course(cou);
				Re_Write_namefile_course(cou);
			}
			textColor(10);
			cout << "\n     *Thong tin khoa hoc da duoc cap nhat thanh cong*" << "\n\n";
			textColor(7);
			break;
		}
		case 9: {
			cout << "\n   Them 1 sinh vien vao khoa hoc\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			if (n != 0) {
				Read_file_course(cou, n);
			//	Create_AllFile_Course(cou);
				List_Course(cou);
				AddStudent_ofCourse(cou);
				textColor(10);
				cout << "   *Them sinh vien thanh cong*\n\n";
				textColor(7);
			}
			else
				cout << "\n    Hien tai chua co bat ki khoa hoc nao!\n";
			break;
		}
		case 10: {
			cout << "\n   Xoa 1 sinh vien vao khoa hoc\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			if (n != 0) {
				Read_file_course(cou, n);
				//	Create_AllFile_Course(cou);
				List_Course(cou);
				deleteStudent_ofCourse(cou);
			}
			else
				cout << "\n    Hien tai chua co bat ki khoa hoc nao!\n";
			break;
		}
		case 11: {
			cout << "\n   Xoa khoa hoc\n";
			Node_Namefile* nam = NULL;
			char file1[] = "name_file_course.txt";
			Read_Namefile(nam, file1);
			Node_Course* cou = NULL;
			char file2[] = "course.txt";
			int n = Count_file(file2) / 8;
			if (n != 0)
				Read_file_course(cou, n);
			List_Course(cou);
			Delete_Course(cou, n, nam);
			ReWrite_course(cou, nam, n);
			textColor(10); 
			cout << "\n  *Da xoa khoa hoc thanh cong*\n\n";
			textColor(7);
			break;
		}
		case 12: {
			cout << "\n   Danh sach cac lop hoc\n\n";
			Node_Class* cla = NULL;
			char file[] = "class.txt";
			int n = Count_file(file) / 2;
			Read_file_class(cla, n);
			Create_AllFile_Class(cla);
			List_Class(cla);
			break;
		}
		case 13: {
			cout << "\n   Danh sach cac lop hoc\n\n";
			Node_Class* cla = NULL;
			char file[] = "class.txt";
			int n = Count_file(file) / 2;
			Read_file_class(cla, n);
			List_Class(cla);
			Display_Student_ofClass(cla, n);
			break;
		}
		case 14: {
			cout << "\n   Xem danh sach sinh vien trong khoa hoc\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			if (n != 0) {
				Read_file_course(cou, n);
				//	Create_AllFile_Course(cou);
				List_Course(cou);
				Display_Student_ofCourse(cou);
			}
			else
				cout << "\n    Hien tai chua co bat ki khoa hoc nao!\n";
			break;
		}
		case 15: {
			cout << "\n   Xuat danh sach sinh vien 1 khoa hoc ra file CSV\n\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			if (n != 0) {
				Read_file_course(cou, n);
				//	Create_AllFile_Course(cou);
				List_Course(cou);
				Export_Course_File(cou);
			}
			break;
		}
		case 16: {
			cout << "\n   Nhap bang diem cua khoa hoc\n\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			if (n != 0) {
				Read_file_course(cou, n);
				//	Create_AllFile_Course(cou);
				List_Course(cou);
				Import_Score_Course(cou);
			}
			break;
		}
		case 17: {
			cout << "\n   Xem bang diem cua khoa hoc\n\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			if (n != 0) {
				Read_file_course(cou, n);
				//	Create_AllFile_Course(cou);
				List_Course(cou);
				View_Score_Course(cou);
			}
			break;
		}
		case 18: {
			cout << "\n   Cap nhat ket qua sinh vien\n\n";
			Node_Course* cou = NULL;
			char file[] = "course.txt";
			int n = Count_file(file) / 8;
			if (n != 0) {
				Read_file_course(cou, n);
				//	Create_AllFile_Course(cou);
				List_Course(cou);
				Update_Result_Student(cou);
			}
			break;
		}
		}
		cout << "\n   Ban muon thuc hien thao tac khac hay thoat?\n";
		cout << "     1. Tro lai     2. Thoat\n";
		int p; cout << "   Chon : "; cin >> p;
		if (p == 2) {
			return;
		}
		system("cls");
		Display_Header();
	}
}

// - Tao nam hoc moi
Node_year* makeNode_year(NamHoc x) {
	Node_year* tmp = new Node_year;
	tmp->data = x;
	tmp->next = NULL;
	return tmp;
}

void addLast_year(Node_year*& y, NamHoc x) {
	Node_year* tmp = makeNode_year(x);
	if (y == NULL)
		y = tmp;
	else {
		Node_year* last = y;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = tmp;
	}
}
// nhap 1 nam
void input_Year(NamHoc& x) {
	cout << "  Nam hoc         : "; cin >> x.year;
	cout << "  So luong lop mo : "; cin >> x.solg;
}
// ghi them nam vao file year.txt
void write_File_year(Node_year* year) {
	ofstream write("namhoc.txt", ios::out);

	while (year != NULL) {
		write << year->data.year << endl;
		write << year->data.solg << endl;
		year = year->next;
	}
	write.close();
}
// tao nam hoc moi
void Create_1_year(Node_year*& year) {
	NamHoc x;
	input_Year(x);
	addLast_year(year, x);
	write_File_year(year);
}

/////----------- tao lop hoc cho sinh vien nam nhat------------////
void Upper_First(char x[]) {
	int lenght = strlen(x);
	for (int i = 0; i < lenght; i++) {
		if (x[i] >= 'A' && x[i] <= 'Z') {
			x[i] += 32;
		}
	}
	x[0] -= 32;
	for (int i = 1; i < lenght; i++) {
		if (x[i] == ' ')
			x[i + 1] -= 32;
	}
}
void Upper(char x[]) {
	for (int i = 0; i < strlen(x); i++) {
		if (x[i] >= 'a' && x[i] <= 'z')
			x[i] -= 32;
	}
}

Node_Class* makeNode_Class(Class x) {
	Node_Class* tmp = new Node_Class;
	tmp->data = x;
	tmp->next = NULL;
	return tmp;
}

void addLast_Class(Node_Class*& cla, Class x) {
	Node_Class* tmp = makeNode_Class(x);
	if (cla == NULL)
		cla = tmp;
	else {
		Node_Class* last = cla;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = tmp;
	}
}
// doc file class.txt
void Read_file_class(Node_Class*& cla, int n) {
	ifstream read("class.txt", ios::in);
	for (int i = 0; i < n; i++) {
		Class x;
		read.getline(x.id, max);
		read.getline(x.faculty, max);
		addLast_Class(cla, x);
	}
	read.close();
}

void input_Class(Class& x) {
	cout << "  Ma lop : "; cin.getline(x.id, max);
	cout << "  Khoa   : "; cin.getline(x.faculty, max);
	Upper(x.id);
	Upper(x.faculty);
}
// tao class moi
void Create_Class(Node_Class*& cla, int n) {
	cin.ignore();
	for (int i = 0; i < n; i++) {
		Class x;
		input_Class(x);
		addLast_Class(cla, x);
		Write_file_class(x);
	}
}
// noi chuoi tu ma lop voi duoi .CSV de tao file
void Connect_class(char x[], char file[]) {
	int dem = 0;
	for (int i = 0; i < strlen(x); i++) {
		file[dem] = x[i];
		dem++;
	}
	int lim = strlen(x) + strlen(tail);
	for (int i = 0; i < strlen(tail); i++) {
		file[dem] = tail[i];
		dem++;
	}
	file[lim] = '\0';
}
// ghi thong tin class vao file class.txt
void Write_file_class(Class cla) {
	ofstream write("class.txt", ios::app);
	write << cla.id << endl;
	write << cla.faculty << endl;
	write.close();
}
// ghi ten file moi class vao file name_file_class.txt
void Write_namefile_class(char x[]) {
	ofstream write("name_file_class.txt", ios::app);
	write << x << endl;
	write.close();
}
// tao 1 file moi
void Create_file(char file[]) {
	ofstream write(file, ios::out);
	write.close();
}
// kiem tra xem lop da ton tai hay chua
bool Check_namefile_exist(Node_Class* cla, int local, char file[]) {
	for (int i = 0; i < local; i++, cla = cla->next) {
		char tmp[max];
		Connect_class(cla->data.id, tmp);
		if (strcmp(file, tmp) == 0)
			return false;
	}
	return true;
}
// mo hoac tao tat cac file class
void Create_AllFile_Class(Node_Class* cla) {
	char x[] = "class.txt";
	int i = Count_file(x) / 2;
	while (cla != NULL) {
		char file[max];
		Connect_class(cla->data.id, file);
		if (Check_namefile_exist(cla, i, file)) {
			Write_namefile_class(file);
		}
		Create_file(file);
		cla = cla->next;
	}
}

//------------------them hoc sinh nam 1 vao cac lop nam 1----------------//

    // - doc file CSV
int Change_char_int(char x[]) {// change char to int
	int rec = 0;
	for (int i = 0; i < strlen(x); i++) {
		rec = rec * 10 + (x[i] - '0');
	}
	return rec;
}

Node_Stu* makeNode_student(Student x) {
	Node_Stu* tmp = new Node_Stu;
	tmp->data = x;
	tmp->next = NULL;
	return tmp;
}

void addLast_stu(Node_Stu*& y, Student x) {
	Node_Stu* tmp = makeNode_student(x);
	if (y == NULL)
		y = tmp;
	else {
		Node_Stu* last = y;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = tmp;
	}
}
// dem file csv thong tin sinh vien
int Count_file_csv(char file[]) {
	int dem = 0;
	ifstream read(file, ios::in);
	while (!read.eof()) {
		char x[max];
		read.getline(x, max);
		if (strlen(x) != 0)
			dem++;
	}
	read.close();
	if (dem == 0)
		return dem;
	return dem - 1;
}
//doc file csv thong tin sinh vien
int Read_file_csv(Node_Stu*& stu, char file[]) {
	ifstream read(file, ios::in);
	if (read.is_open()) {
		char tmp[max];
		read.getline(tmp, max);
		for (int i = 0; i < Count_file_csv(file); i++) {
			Student x;
			char No[max];
			read.getline(No, max, ',');//
			char tmp_id[max];
			read.getline(tmp_id, max, ',');//
			x.ID = Change_char_int(tmp_id);
			read.getline(x.name, max, ',');//
			read.getline(x.ho, max, ',');//
			read.getline(x.sex, max, ',');//
			read.getline(x.birth, max, ','); //
			char tmp_cccd[max];
			read.getline(tmp_cccd, max); //
			x.cccd = Change_char_int(tmp_cccd);
			addLast_stu(stu, x);
		}
		cout << endl;
		read.close();
		Arrange_Stu(stu);
		return 1;
	}
	else {
		cout << "  Link file gap su co!!" << endl;
		return 0;
	}
}

// ---- danh sach cac lop da duoc tao
void List_Class(Node_Class* cla) {
	for (int i = 1; cla != NULL; i++) {
		if (i < 10)
			cout << "    " << i << ". ";
		if (i > 9)
			cout << "   " << i << ". ";
		cout << cla->data.id << endl;
		cla = cla->next;
	}
	cout << endl;
}
// kiem tra xem lop duoc chon co ton tai hay khong
bool check_File_Class(char x[]) {
	Node_Class* cla = NULL;
	char xx[] = "class.txt";
	Read_file_class(cla, Count_file(xx) / 2);
	while (cla != NULL) {
		if (strcmp(x, cla->data.id) == 0)
			return true;
		cla = cla->next;
	}
	return false;
}

//------ghi danh sach sinh vien vao file class
void Write_csv_class(Node_Stu* stu, int chon, int lim) {
	Node_Class* cla = NULL;
	char x[] = "class.txt";
	int n = Count_file(x) / 2;
	Read_file_class(cla, n);
	for (int i = 1; i < chon; i++) {
		cla = cla->next;
	}
	char file[max];
	Connect_class(cla->data.id, file);
	ofstream write(file, ios::out);
	write << "No" << ",";
	write << "MSSV" << ",";
	write << "Ten" << ",";
	write << "Ho" << ",";
	write << "Gioi tinh" << ",";
	write << "Ngay sinh" << ",";
	write << "CMND/CCCD" << endl;
	if (write.is_open()) {
		for (int i = 0; i < lim; i++) {
			write << i + 1 << ",";
			write << stu->data.ID << ",";
			write << stu->data.name << ",";
			write << stu->data.ho << ",";
			write << stu->data.sex << ",";
			write << stu->data.birth << ",";
			write << stu->data.cccd << endl;
			stu = stu->next;
		}
		textColor(10);
		cout << "\n      *DA THEM DANH SACH VAO FILE : " << file << " *" << "\n\n";
		textColor(7);
		write.close();
	}
}
//------ chuc nang them hoc sinh nam 1 vao cac lop nam 1
void Choose_Class(Node_Class* cla) {
	int chon;
	cout << "  Lop ban muon them danh sach: ";
	cin >> chon;
	char xx[] = "class.txt";
	while (chon < 1 || chon > Count_file(xx) / 2) {
		cout << "  Lop duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay dung thao tac? \n";
		cout << "   1. Nhap lai    2. Dung\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;

		system("cls");
		Display_Header();
		List_Class(cla);
		if (c == 1) {
			cout << "\n  Lop ban muon them danh sach : ";
			cin >> chon;
		}
	}
	char link[50];
	cout << "  Link file sinh vien        : ";
	cin.ignore();
	cin.getline(link, max);
	Node_Stu* stu = NULL;
	int x = Read_file_csv(stu, link);
	int lim = Count_file_csv(link);
	if (x == 0) {
		cout << "  Khong the xem duoc danh sach do su co mo file!!\n";
	}
	if (x == 1) {
		cout << "  Danh sach sinh vien \n";
		Node_Stu* tmp = stu;
		int i = 1;
		while (tmp != NULL) {
			cout << "\t ";
			cout << i << ",";
			cout << tmp->data.ID << ",";
			cout << tmp->data.name << ",";
			cout << tmp->data.ho << ",";
			cout << tmp->data.sex << ",";
			cout << tmp->data.birth << ",";
			cout << tmp->data.cccd << endl;
			tmp = tmp->next;
			i++;
		}
		Write_csv_class(stu, chon, lim);
	}
	// update account
	Update_Account(stu);
	//
}

///-----------tao mot ki hoc moi-------------///
int Count_file_year() {
	int dem = 0;
	ifstream read("namhoc.txt", ios::in);
	while (!read.eof()) {
		char x[max];
		read.getline(x, max);
		if (strlen(x) != 0)
			dem++;
	}
	read.close();
	return dem;
}
// doc file year.txt
void Read_file_year(Node_year* year) {
	int n = Count_file_year();
	ifstream read("namhoc.txt", ios::in);
	for (int i = 0; i < n; i++) {
		NamHoc x;
		read >> x.year;
		read >> x.solg;
		addLast_year(year, x);
	}
	read.close();
}
//  toa hoc ky moi 
void Create_HK(int& namhoc, int& hk, char start[], char end[]) {
	cout << "  Nam hoc cua hoc ki nay    : "; cin >> namhoc;
	Node_year* year = NULL;
	cout << "  Day la hoc ki(1,2,3)      : "; cin >> hk;
	cin.ignore();
	cout << "  Ngay bat dau(DD/MM/YYYY)  : "; cin.getline(start, max);
	cout << "  Ngay ket thuc(DD/MM/YYYY) : "; cin.getline(end, max);
	textColor(10); cout << "  *DA XAC NHAN HOC KI HIEN TAI*\n\n"; textColor(7);
}


///---------Tao 1 khoa hoc va tai tep csv sinh vien da dang ky khoa hoc-----///

// - tao 1 khoa hoc
Node_Course* makeNode_Course(Course x) {
	Node_Course* tmp = new Node_Course;
	tmp->data = x;
	tmp->next = NULL;
	return tmp;
}

void addLast_Course(Node_Course*& cou, Course x) {
	Node_Course* tmp = makeNode_Course(x);
	if (cou == NULL)
		cou = tmp;
	else {
		Node_Course* last = cou;
		while (last->next != NULL)
			last = last->next;
		last->next = tmp;
	}
}
// tao file 1 khoa hoc bang cach ghep ma lop_ma mom.CSV
void Connect_Course(char x[], char y[], char file[]) {
	int dem = 0;
	for (int i = 0; i < strlen(x); i++) {
		file[dem] = x[i];
		dem++;
	}
	file[dem] = '_';
	dem++;
	for (int i = 0; i < strlen(y); i++) {
		file[dem] = y[i];
		dem++;
	}
	int lim = strlen(x) + strlen(y) + strlen(tail);
	for (int i = 0; i < strlen(tail); i++) {
		file[dem] = tail[i];
		dem++;
	}
	file[lim + 1] = '\0';
}
// nhap thong tin 1 khoa hoc
void input_Course(Course& x) {
	cout << "\n  Ma mon     : "; cin.getline(x.id, max); Upper(x.id);
	cout << "  Ten mon hoc  : "; cin.getline(x.name, max); Upper(x.name);
	cout << "  Lop hoc      : "; cin.getline(x.id_class, max); Upper(x.id_class);
	cout << "  Giao vien    : "; cin.getline(x.teacher, max); Upper(x.teacher);
	cout << "  Tin chi      : "; cin.getline(x.credit, 2);
	cout << "  Buoi hoc     : "; cin.getline(x.day, max); Upper(x.day);
	cout << "  Tiet hoc     : "; cin.getline(x.lesson, max); Upper(x.lesson);
	cout << endl;
}
// ghi  thong tin 1 khoa hoc vao file course.txt
void Write_file_course(Course x) {
	ofstream write("course.txt", ios::app);
	write << x.id << endl;
	write << x.name << endl;
	write << x.id_class << endl;
	write << x.teacher << endl;
	write << x.credit << endl;
	write << x.max_stu << endl;
	write << x.day << endl;
	write << x.lesson << endl;
	write.close();
}
// Tao Khoa hoc moi
void Create_Course(Node_Course*& cou) {
	Course x;
	cin.ignore();
	input_Course(x);
	addLast_Course(cou, x);
	char file[max];
	Connect_Course(x.id_class, x.id, file);
	Write_namefile_course(file);
	Create_file(file);
	Write_file_course(x);
}
// doc file course.txt de lay thong tin tat ca khoa hoc
void Read_file_course(Node_Course*& cou, int n) {
	ifstream read("course.txt", ios::in);
	for (int i = 0; i < n; i++) {
		Course x;
		read.getline(x.id, max); Upper(x.id);
		read.getline(x.name, max); Upper(x.name);
		read.getline(x.id_class, max); Upper(x.id_class);
		read.getline(x.teacher, max); Upper(x.teacher);
		read.getline(x.credit, 2);
		char tmp[max];
		read.getline(tmp, max);
		read.getline(x.day, max); Upper(x.day);
		read.getline(x.lesson, max); Upper(x.lesson);
		addLast_Course(cou, x);
	}
	read.close();
}
//  kiem tra xem khoa hoc dc tao ton tai chua
bool check_File_Course(char x[], char  y[]) {
	Node_Course* cou = NULL;
	char xx[] = "course.txt";
	Read_file_course(cou, Count_file(xx) / 8);
	while (cou != NULL) {
		if (strcmp(x, cou->data.id) == 0) 
			if (strcmp(y, cou->data.id_class) == 0)
				return true;
		cou = cou->next;
	}
	return false;
}
// ghi ten file khoa hoc da duoc tao vai file name_file_course.txt
void Write_namefile_course(char x[]) {
	ofstream write("name_file_course.txt", ios::app);
	write << x << endl;
	write.close();
}
// mo hoac tao tat ca khoa hoc
void Create_AllFile_Course(Node_Course* cou) {
	while (cou != NULL) {
		char file[max];
		Connect_Course(cou->data.id_class, cou->data.id, file);
		if (!check_File_Course(cou->data.id, cou->data.id_class))
			Write_namefile_course(file);
		Create_file(file);
		cou = cou->next;
	}
}

// - Tai tep csv sinh vien da dang ky khoa hoc
void List_Course(Node_Course* cou) {
	cout << "\n   Danh sach cac lop:\n";
	for (int i = 1; cou != NULL; i++) {
		if (i < 10)
			cout << "    " << i << ". ";
		if (i > 9)
			cout << "   " << i << ". ";
		cout << cou->data.id_class;
		cout << "   " << cou->data.id;
		cou = cou->next;
		cout << endl;
	}
	cout << endl;
}

//--- Tai tep csv sinh vien da dang ky khoa hoc
Node_Score* makeNode_Score(Score x) {
	Node_Score* tmp = new Node_Score;
	tmp->data = x;
	tmp->next = NULL;
	return tmp;
}
void addLast_Score(Node_Score*& sco, Score x) {
	Node_Score* tmp = makeNode_Score(x);
	if (sco == NULL)
		sco = tmp;
	else {
		Node_Score* last = sco;
		while (last->next != NULL)
			last = last->next;
		last->next = tmp;
	}
}

int Read_input_course(Node_Score*& sco, char file[]) {
	int n = Count_file_csv(file);
	ifstream read(file, ios::in);
	if (read.is_open()) {
		char tmp[max];
		read.getline(tmp, max);
		for (int i = 0; i < n; i++) {
			Score x;
			char no[max];
			read.getline(no, max, ',');
			char tmp_id[max];
			read.getline(tmp_id, max, ',');
			x.ID = Change_char_int(tmp_id);
			read.getline(x.name, max);
			x.score_mid = 0;
			x.score_fin = 0;
			x.score_total = 0;
			char tmp_mark[] = "Khong";
			strcpy_s(x.other_mark, strlen(tmp_mark) + 1, tmp_mark);
			addLast_Score(sco, x);
		}
		Arrange_StuScore(sco);
		return 1;
	}
	else 
		return 0;
}

int Read_Stu_Sco_Course(Node_Score*& sco, int n, char file[]) {
	ifstream read(file, ios::in);
	if (read.is_open()) {
		char tmp[max];
		read.getline(tmp, max);
		for (int i = 0; i < n; i++) {
			Score x;
			char No[max];
			read.getline(No, max, ',');//

			char tmp_id[max];
			read.getline(tmp_id, max, ',');//
			x.ID = Change_char_int(tmp_id);

			read.getline(x.name, max, ',');//

			char tmp_mid[max];
			read.getline(tmp_mid, max, ',');//
			x.score_mid = atof(tmp_mid);

			char tmp_fin[max];
			read.getline(tmp_fin, max, ',');//
			x.score_fin = atof(tmp_fin);

			char tmp_total[max];
			read.getline(tmp_total, max, ',');//
			x.score_total = atof(tmp_total);
			read.getline(x.other_mark, max);
			addLast_Score(sco, x);
		}
		cout << endl;
		read.close();
		Arrange_StuScore(sco);
		return 1;
	}
	else {
		cout << "  Link file gap su co!!" << endl;
		return 0;
	}
}

// sap xep tang dan theo mssv
void Arrange_Stu(Node_Stu*& stu) {
	for (Node_Stu* i = stu; i->next != NULL; i = i->next) {
		for (Node_Stu* j = i->next; j != NULL; j = j->next) {
			if (i->data.ID > j->data.ID) {
				Student tmp = i->data;
				i->data = j->data;
				j->data = tmp;
			}
		}
	}
}
void Arrange_StuScore(Node_Score*& sco) {
	for (Node_Score* i = sco; i->next != NULL; i = i->next) {
		for (Node_Score* j = i->next; j != NULL; j = j->next) {
			if (i->data.ID > j->data.ID) {
				Score tmp = i->data;
				i->data = j->data;
				j->data = tmp;
			}
		}
	}
}

void Write_Stu_Sco_Course(Node_Score* sco, char file[]) {
	ofstream write(file, ios::out);
	write << "No,MSSV,Ho va ten,Giua ky,Cuoi ky,Tong ket,Danh dau khac\n";
	write << setprecision(1) ;
	for (int i = 1; sco != NULL; i++, sco = sco->next) {
		write << i << ',';
		write << sco->data.ID << ',';
		write << sco->data.name << ',';
		write << fixed << sco->data.score_mid << ',';
		write << fixed << sco->data.score_fin << ',';
		write << fixed << sco->data.score_total << ',';
		write << sco->data.other_mark << endl;
	}
	write.close();
}

void Choose_Course(Node_Course* cou) {
	int chon;
	cout << "\n  Khoa hoc can tai danh sach: ";
	cin >> chon;
	char xx[] = "course.txt";
	int n = Count_file(xx) / 8;
	while (chon < 1 || chon > n) {
		cout << "  Khoa hoc duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay quay lai menu? \n";
		cout << "   1. Nhap lai    2. Quay lai\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		List_Course(cou);
		if (c == 1) {
			cout << "\n  Khoa hoc can tai danh sach: ";
			cin >> chon;
		}
	}
	Node_Course* tmp = cou;
	for (int i = 1; i < chon; i++) {
		tmp = tmp->next;
	}
	char file[max];
	Connect_Course(tmp->data.id_class, tmp->data.id, file);
	char link[50];
	cout << "  File CSV co dang: No, ma so sinh vien, ho va ten\n";
	cout << "  Link file sinh vien : ";
	cin.ignore();
	cin.getline(link, max);
	Node_Score* sco = NULL;
	int x = Read_input_course(sco, link);
	if (x == 0) {
		textColor(10);
		cout << "   *Tai danh sach sinh vien that bai*\n\n";
		textColor(7);
	}
	else {
		Node_Score* tmp = sco;
		cout << "  Danh sach sinh vien:\n";
		for (int i = 1; tmp != NULL; i++, tmp = tmp->next) {
			cout << "   " << i << ". " << tmp->data.ID;
			cout << "   " << tmp->data.name << endl;
		}
	}
	Write_Stu_Sco_Course(sco, file);
}

//-----Xem danh sach cac khoa hoc
void Display_Course(Node_Course* cou) {
	for (int i = 1; cou != NULL; i++, cou = cou->next) {
		if (i < 10)
			cout << "    " << i << ". ";
		else
			cout << "   " << i << ". ";
		cout << cou->data.id;
		cout << "\n       " << cou->data.name;
		cout << "\n       " << cou->data.id_class;
		cout << "\n       " << cou->data.teacher;
		cout << "\n       " << cou->data.credit;
		cout << "\n       " << cou->data.max_stu;
		cout << "\n       " << cou->data.day;
		cout << "\n       " << cou->data.lesson << endl;
	}
	cout << endl;
}

// - cap nhat tai khoan moi
Node_Account* makeNode_Account(Account x) {
	Node_Account* tmp = new Node_Account;
	tmp->data = x;
	tmp->next = NULL;
	return tmp;
}

void addLast_Account(Node_Account*& acc, Account x) {
	Node_Account* tmp = makeNode_Account(x);
	if (acc == NULL)
		acc = tmp;
	else {
		Node_Account* last = acc;
		while (last->next != NULL)
			last = last->next;
		last->next = tmp;
	}
}
// kiem tra mssv da ton tai hay chua
bool Check_Account(int mssv) {
	char file[] = "accountSV.txt";
	Node_Account* acc = NULL;
	int n = Count_file(file) / 2;
	ifstream read(file, ios::in);
	for (int i = 0; i < n; i++) {
		Account x;
		read >> x.mssv_nv;
		read >> x.password;
		addLast_Account(acc, x);
	}
	read.close();
	for (int i = 0; i < n; i++) {
		if (mssv == acc->data.mssv_nv)
			return false;
	}
	return true;
}
// cap nhat tai khoan chua ton tai
void Update_Account(Node_Stu* stu) {
	ofstream write("accountSV.txt", ios::app);
	while (stu != NULL) {
		if (Check_Account(stu->data.ID)) {
			write << stu->data.ID << endl;
			write << stu->data.cccd << endl;
		}
		stu = stu->next;
	}
	write.close();
}

//-----Cap nhat thong tin khoa hoc
void Update_Course(Node_Course*& cou) {
	int chon;
	cout << "\n  Khoa hoc can cap nhat thong tin: ";
	cin >> chon;
	char xx[] = "course.txt";
	int n = Count_file(xx) / 8;
	while (chon < 1 || chon > n) {
		cout << "  Khoa hoc duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay quay lai menu? \n";
		cout << "   1. Nhap lai    2. Quay lai\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		List_Course(cou);
		if (c == 1) {
			cout << "\n  Khoa hoc can cap nhat thong tin: ";
			cin >> chon;
		}
	}
	Node_Course* tmp = cou;
	for (int i = 1; i < chon; i++) {
		tmp = tmp->next;
	}
	char file_1[max];
	Connect_Course(tmp->data.id_class, tmp->data.id, file_1);
	Node_Score* sco = NULL;
	int lim = Count_file_csv(file_1);
	if (lim != 0)
		Read_Stu_Sco_Course(sco, lim, file_1);
	while (1) {
		cout << "\n  1. Ma mon hoc       : " << tmp->data.id;
		cout << "\n  2. Ten mon hoc      : " << tmp->data.name;
		cout << "\n  3. Lop hoc/Ma lop   : " << tmp->data.id_class;
		cout << "\n  4. Giao vien        : " << tmp->data.teacher;
		cout << "\n  5. Tin chi          : " << tmp->data.credit;
		cout << "\n  6. Sinh vien toi da : " << tmp->data.max_stu;
		cout << "\n  7. Ngay hoc         : " << tmp->data.day;
		cout << "\n  8. Tiet hoc         : " << tmp->data.lesson << endl << endl;
		int a; // thong tin can thay doi
		cout << "   Thong tin can thay doi: ";
		cin >> a;
		while (a == 1 || a == 2 || a == 6) {
			cout << "   Thong tin nay la co dinh khong the thay doi!\n";
			cout << "   Vui long chon thong tin khac hoac thoat\n";
			cout << "      1. Chon lai      2. Thoat\n";
			cout << "   Chon: "; int b; cin >> b;
			if (b == 2)
				return;
			system("cls");
			Display_Header();
			cout << "\n   Cap nhat thong tin khoa hoc\n";
			List_Course(cou);
			cout << "\n  1. Ma mon hoc       : " << tmp->data.id;
			cout << "\n  2. Ten mon hoc      : " << tmp->data.name;
			cout << "\n  3. Lop hoc/Ma lop   : " << tmp->data.id_class;
			cout << "\n  4. Giao vien        : " << tmp->data.teacher;
			cout << "\n  5. Tin chi          : " << tmp->data.credit;
			cout << "\n  6. Sinh vien toi da : " << tmp->data.max_stu;
			cout << "\n  7. Ngay hoc         : " << tmp->data.day;
			cout << "\n  8. Tiet hoc         : " << tmp->data.lesson << endl << endl;
			cout << "   Thong tin can thay doi: ";
			cin >> a;
		}
		cin.ignore();
		switch (a) {
		case 3: {
			cout << "\n   Lop hoc/Ma lop moi : ";
			cin.getline(tmp->data.id_class, max);
			Upper(tmp->data.id_class);
			break;
		}
		case 4: {
			cout << "\n   Giao vien moi : ";
			cin.getline(tmp->data.teacher, max);
			Upper(tmp->data.teacher);
			break;
		}
		case 5: {
			cout << "\n   Tin chi moi : ";
			cin.getline(tmp->data.credit, 2);
			Upper(tmp->data.credit);
			break;
		}
		case 7: {
			cout << "\n   Ngay hoc moi : ";
			cin.getline(tmp->data.day, max);
			Upper(tmp->data.day);
			break;
		}
		case 8: {
			cout << "\n   Tiet hoc moi : ";
			cin.getline(tmp->data.lesson, max);
			Upper(tmp->data.lesson);
			break;
		}
		}
		remove(file_1); // xoa khoa hoc cu
		char file_2[max];
		Connect_Course(tmp->data.id_class, tmp->data.id, file_2);
		Write_Stu_Sco_Course(sco, file_2);
		cout << "   Ban muon tiep tuc cap nhat khoa hoc nay khong?\n";
		cout << "    1. Co       2. Khong\n";
		int c; cout << "   Chon: "; cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		cout << "\n   Cap nhat thong tin khoa hoc\n";
	}
}
// ghi lai thong tin cac khoa hoc
void Re_Write_file_course(Node_Course* cou) {
	ofstream write("course.txt", ios::out);
	while (cou != NULL) {
		write << cou->data.id << endl;
		write << cou->data.name << endl;
		write << cou->data.id_class << endl;
		write << cou->data.teacher << endl;
		write << cou->data.credit << endl;
		write << cou->data.max_stu << endl;
		write << cou->data.day << endl;
		write << cou->data.lesson << endl;
		cou = cou->next;
	}
	write.close();
}
// ghi lai ten file cac khoa hoc
void Re_Write_namefile_course(Node_Course* cou) {
	ofstream write("name_file_course.txt", ios::out);
	while (cou != NULL) {
		char file[max];
		Connect_Course(cou->data.id_class, cou->data.id, file);
		write << file << endl;
		cou = cou->next;
	}
	write.close();
}

//-- Them 1 sinh vien vao khoa hoc
void Input_Stu_Course(Score& sco) {
	cout << "\n  Thong tin sinh vien:\n";
	cout << "   MSSV                          :";
	cin >> sco.ID;
	cin.ignore();
	cout << "   Ho va ten                     :";
	cin.getline(sco.name, max); Upper_First(sco.name);
	cout << "   Giua ky(chua co nhap 0)       :";
	cin >> sco.score_mid;
	cout << "   Cuoi ky(chua co nhap 0)       :";
	cin >> sco.score_fin;
	cout << "   Tong ket(chua co nhap 0)      :";
	cin >> sco.score_total;cin.ignore();
	cout << "   Ghi chu(khong co nhap 'Khong'):";
	cin.getline(sco.other_mark, max); Upper_First(sco.other_mark);
}

void AddStudent_ofCourse(Node_Course* cou) {
	int chon;
	cout << "\n  Khoa hoc can them sinh vien: ";
	cin >> chon;
	char xx[] = "course.txt";
	int n = Count_file(xx) / 8;
	while (chon < 1 || chon > n) {
		cout << "  Khoa hoc duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay quay lai menu? \n";
		cout << "   1. Nhap lai    2. Quay lai\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		List_Course(cou);
		if (c == 1) {
			cout << "\n  Khoa hoc can them sinh vien: ";
			cin >> chon;
		}
	}
	Node_Course* tmp = cou;
	for (int i = 1; i < chon; i++) {
		tmp = tmp->next;
	}
	char file[max];
	Connect_Course(tmp->data.id_class, tmp->data.id, file);
	Node_Score* sco = NULL;
	int lim = Count_file(file) - 1;
	if (lim != 0) {
		Read_Stu_Sco_Course(sco, lim, file);
		Node_Score* display = sco;
		int i = 1;
		while (display != NULL) {
			if (i < 10)
				cout << "   " << i << ". ";
			if (i > 9)
				cout << "  " << i << ". ";
			cout << "MSSV      : " << display->data.ID << endl;
			cout << "      Ho va ten : " << display->data.name << endl;
			display = display->next;
			i++;
		}
	}
	Score x;
	Input_Stu_Course(x);
	addLast_Score(sco, x);
	Arrange_StuScore(sco);
	Write_Stu_Sco_Course(sco, file);
}

//------Xoa 1 sinh vien trong khoa hoc
int findLocal(Node_Score* sco, int id) {
	for (int i = 1; sco != NULL; i++, sco = sco->next) {
		if (id == sco->data.ID)
			return i;
	}
	return -1;
}

void delete_Student(Node_Score*& sco, int local, int lim) {
	if (local == 1) {
		sco = sco->next;
	}
	else if (local == lim) {
		Node_Score* tmp = sco;
		for (int i = 1; i < lim - 1; i++) {
			tmp = tmp->next;
		}
		tmp->next = NULL;
	}
	else {
		Node_Score* tmp = sco;
		for (int i = 1; i < local - 1; i++) {
			tmp = tmp->next;
		}
		tmp->next = tmp->next->next;
	}
}

void reWrite_Stu_Sco_Course(Node_Score* sco, char file[]) {
	ofstream write(file, ios::out);
	write.clear();
	write << "No,MSSV,Ho va ten,Giua ky,Cuoi ky,Tong ket,Danh dau khac\n";
	for (int i = 1; sco != NULL; i++, sco = sco->next) {
		write << i << ',';
		write << sco->data.ID << ',';
		write << sco->data.name << ',';
		write << sco->data.score_mid << ',';
		write << sco->data.score_fin << ',';
		write << sco->data.score_total << ',';
		write << sco->data.other_mark << endl;
	}
	write.close();
}

void deleteStudent_ofCourse(Node_Course* cou) {
	int chon;
	cout << "\n  Khoa hoc can xoa sinh vien: ";
	cin >> chon;
	char xx[] = "course.txt";
	int n = Count_file(xx) / 8;
	while (chon < 1 || chon > n) {
		cout << "  Khoa hoc duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay quay lai menu? \n";
		cout << "   1. Nhap lai    2. Quay lai\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		List_Course(cou);
		if (c == 1) {
			cout << "\n  Khoa hoc can xoa sinh vien: ";
			cin >> chon;
		}
	}
	system("cls");
	Display_Header();
	cout << "\n   Danh sach sinh vien:";
	Node_Course* tmp = cou;
	for (int i = 1; i < chon; i++) {
		tmp = tmp->next;
	}
	char file[max];
	Connect_Course(tmp->data.id_class, tmp->data.id, file);
	Node_Score* sco = NULL;
	int lim = Count_file(file) - 1;
	if (lim != 0) {
		Read_Stu_Sco_Course(sco, lim, file);
		Node_Score* display = sco;
		int i = 1;
		while (display != NULL) {
			if (i < 10)
				cout << "   " << i << ". ";
			if (i > 9)
				cout << "  " << i << ". ";
			cout << "MSSV      : " << display->data.ID << endl;
			cout << "      Ho va ten : " << display->data.name << endl;
			display = display->next;
			i++;
		}
	}
	int id;
	cout << "\n   MSSV cua sinh vien can xoa: "; cin >> id;
	int local = findLocal(sco, id);
	while (local == -1) {
		cout << "\n   Sinh vien co ma so " << id << " khong ton tai!\n";
		cout << "   Ban muon nhap lai khong?\n";
		cout << "     1. Co   2. Khong\n";
		int a;
		cout << "   Chon: "; cin >> a;
		if (a == 2) {
			textColor(10);
			cout << "\n  *Khong co sinh vien bi xoa*\n\n";
			textColor(7);
			return;
		}
		system("cls");
		Display_Header();
		cout << "\n   Danh sach sinh vien:\n";
		Node_Score* display = sco;
		int i = 1;
		while (display != NULL) {
			if (i < 10)
				cout << "   " << i << ". ";
			if (i > 9)
				cout << "  " << i << ". ";
			cout << "MSSV      : " << display->data.ID << endl;
			cout << "      Ho va ten : " << display->data.name << endl;
			display = display->next;
			i++;
		}
		cout << "\n   MSSV cua sinh vien can xoa: "; cin >> id;
		local = findLocal(sco, id);
	}
	delete_Student(sco, local, lim);
	system("cls");
	Display_Header();
	cout << "\n   Danh sach sinh vien sau khi xoa:\n";
	Node_Score* display = sco;
	int i = 1;
	while (display != NULL) {
		if (i < 10)
			cout << "   " << i << ". ";
		if (i > 9)
			cout << "  " << i << ". ";
		cout << "MSSV      : " << display->data.ID << endl;
		cout << "      Ho va ten : " << display->data.name << endl;
		display = display->next;
		i++;
	}
	reWrite_Stu_Sco_Course(sco, file);
	textColor(10);
	cout << "   *Them sinh vien thanh cong*\n\n";
	textColor(7);
}



//danh sach sinh vien trong lop hoc
void Display_Student(Node_Stu* stu) {
	int i = 1;
	while (stu != NULL) {
		if (i < 10)
			cout << "   " << i << ". ";
		if (i > 9)
			cout << "  " << i << ". ";
		cout << "MSSV : " << stu->data.ID << endl;
		cout << "      Ten : " << stu->data.name << endl;
		cout << "      Ho : " << stu->data.ho << endl;
		cout << "      Gioi tinh : " << stu->data.sex << endl;
		cout << "      Ngay sinh : " << stu->data.birth << endl;
		cout << "      CCCD/CMND : " << stu->data.cccd << endl;
		stu = stu->next; i++;
	}
}


//-----Xoa 1 khoa hoc
Node_Namefile* makeNode_Namefile(char x[]) {
	Node_Namefile* tmp = new Node_Namefile;
	strcpy_s(tmp->data, strlen(x) + 1, x);
	tmp->next = NULL;
	return tmp;
}

void addLast_Namefile(Node_Namefile*& nam, char x[]) {
	Node_Namefile* tmp = makeNode_Namefile(x);
	if (nam == NULL)
		nam = tmp;
	else {
		Node_Namefile* last = nam;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = tmp;
	}
}

void Read_Namefile(Node_Namefile*& nam, char file[]) {
	int n = Count_file(file);
	ifstream read(file, ios::in);
	for (int i = 0; i < n; i++) {
		char x[max];
		read.getline(x, max);
		addLast_Namefile(nam, x);
	}
	read.close();
}

void Delete_Course(Node_Course*& cou, int& n,Node_Namefile*& nam) {
	cout << "\n   Khoa hoc ban muon xoa: ";
	int local;
	cin >> local;
	char xx[] = "course.txt";
	while (local < 1 || local > n) {
		cout << "  Khoa hoc duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay quay lai menu? \n";
		cout << "   1. Nhap lai    2. Quay lai\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		List_Course(cou);
		if (c == 1) {
			cout << "\n   Khoa hoc ban muon xoa: ";
			cin >> local;
		}
	}

	if (local == 1) {
		cou = cou->next;
		nam = nam->next;
	}
	else if (local == n) {
		Node_Course* tmp = cou;// xoa course
		while (tmp->next->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = NULL;
		Node_Namefile* tmp1 = nam;// xoa ten file course
		while (tmp1->next->next != NULL) {
			tmp1 = tmp1->next;
		}
		tmp1->next = NULL;
	}
	else {
		Node_Course* tmp = cou;
		for (int i = 1; i < local; i++) {
			tmp = tmp->next;
		}
		tmp->next = tmp->next->next;
		Node_Namefile* tmp1 = nam;
		for (int i = 1; i < local; i++) {
			tmp1 = tmp1->next;
		}
		tmp->next = tmp->next->next;
	}
	n--;
}

// ghi lai file course
void ReWrite_course(Node_Course* cou, Node_Namefile* nam, int n) {
	ofstream write1("course.txt", ios::out);
	write1.clear();
	write1.close();
	Re_Write_file_course(cou);
	ofstream write2("name_file_course.txt", ios::out);
	write2.clear();
	write1.close();
	Re_Write_namefile_course(cou);
}

//----Xem danh sach sinh vien cua lop hoc
void Display_Student_ofClass(Node_Class* cla, int n) {
	cout << "\n   Lop hoc ban muon xem danh sach sinh vien: ";
	int local;
	cin >> local;
	char xx[] = "class.txt";
	while (local < 1 || local > n) {
		cout << "  Lop hoc duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay quay lai menu? \n";
		cout << "   1. Nhap lai    2. Quay lai\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		List_Class(cla);
		if (c == 1) {
			cout << "\n   Lop hoc ban muon xem danh sach sinh vien: ";
			cin >> local;
		}
	}
	Node_Class* tmp = cla;
	for (int i = 1; i < local; i++) {
		tmp = tmp->next;
	}
	char file[max];
	Connect_class(tmp->data.id, file);
	int lim = Count_file_csv(file);
	if (lim == 0) {
		cout << "   Khoa hoc khong co sinh vien, khong the xuat danh sach\n\n";
		return;
	}
	Node_Stu* stu = NULL;
	Read_file_csv(stu, file);
	Display_Student(stu);
}

//----Xem danh sach sinh vien cua khoa hoc
void Display_Student_ofCourse(Node_Course* cou) {
	int chon;
	cout << "\n  Khoa hoc can xem sinh vien: ";
	cin >> chon;
	char xx[] = "course.txt";
	int n = Count_file(xx) / 8;
	while (chon < 1 || chon > n) {
		cout << "  Khoa hoc duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay quay lai menu? \n";
		cout << "   1. Nhap lai    2. Quay lai\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		List_Course(cou);
		if (c == 1) {
			cout << "\n  Khoa hoc can xem sinh vien: ";
			cin >> chon;
		}
	}
	system("cls");
	Display_Header();
	cout << "\n   Danh sach sinh vien:";
	Node_Course* tmp = cou;
	for (int i = 1; i < chon; i++) {
		tmp = tmp->next;
	}
	char file[max];
	Connect_Course(tmp->data.id_class, tmp->data.id, file);
	Node_Score* sco = NULL;
	int lim = Count_file(file) - 1;
	if (lim != 0) {
		Read_Stu_Sco_Course(sco, lim, file);
		int i = 1;
		while (sco != NULL) {
			if (i < 10)
				cout << "   " << i << ". ";
			if (i > 9)
				cout << "  " << i << ". ";
			cout << "MSSV          : " << sco->data.ID << endl;
			cout << "      Ho va ten     : " << sco->data.name << endl;
			cout << "      Danh dau khac : " << sco->data.other_mark << endl;
			sco = sco->next;
			i++;
		}
	}
	else {
		cout << "\n   Khoa hoc hien tai khong co sinh vien\n\n";
	}
	
}

//--- Xuat danh sach sinh vien trong khoa hoc ra file CSV
void Connect_File(char x[max], char y[max]) {
	int lenght = strlen(x) + strlen(y) + 1;
	int i = strlen(x);
	int j = 0;
	x[i] = 92;
	i++;
	for (i; i < lenght; i++) {
		x[i] = y[j];
		j++;
	}
	x[lenght] = '\0';
}

void Export_Course_File(Node_Course* cou) {
	int chon;
	cout << "\n  Khoa hoc can xuat danh sach sinh vien: ";
	cin >> chon;
	char xx[] = "course.txt";
	int n = Count_file(xx) / 8;
	while (chon < 1 || chon > n) {
		cout << "  Khoa hoc duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay quay lai menu? \n";
		cout << "   1. Nhap lai    2. Quay lai\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		List_Course(cou);
		if (c == 1) {
			cout << "\n  Khoa hoc can xuat danh sach sinh vien: ";
			cin >> chon;
		}
	}
	system("cls");
	Display_Header();
	cout << "\n   Danh sach sinh vien:";
	Node_Course* tmp = cou;
	for (int i = 1; i < chon; i++) {
		tmp = tmp->next;
	}
	char file[max];
	Connect_Course(tmp->data.id_class, tmp->data.id, file);
	Node_Score* sco = NULL;
	int lim = Count_file(file) - 1;
	if (lim != 0) {
		Read_Stu_Sco_Course(sco, lim, file);
		Node_Score* display = sco;
		int i = 1;
		while (display != NULL) {
			if (i < 10)
				cout << "   " << i << ". ";
			if (i > 9)
				cout << "  " << i << ". ";
			cout << "MSSV          : " << display->data.ID << endl;
			cout << "      Ho va ten     : " << display->data.name << endl;
			cout << "      Giua ky       : " << display->data.score_mid << endl;
			cout << "      Cuoi ky       : " << display->data.score_fin << endl;
			cout << "      Tong ket      : " << display->data.score_total << endl;
			cout << "      Danh dau khac : " << display->data.other_mark << endl;
			display = display->next;
			i++;
		}
		char output_file[max];
		cin.ignore();
		cout << "\n   Dia chi xuat file: ";
		cin.getline(output_file, max);
		Connect_File(output_file, file);
		Write_Stu_Sco_Course(sco, output_file);
	}
	else {
		cout << "\n   Khoa hoc hien tai khong co sinh vien\n\n";
	}
}

//--- Nhap diem vao khoa hoc
bool Check_ID_import(Node_Score* sco, Node_Score* _import) {
	while (sco != NULL) {
		if (sco->data.ID != _import->data.ID) {
			return false;
		}
		sco = sco->next;
		_import = _import->next;
	}
	return true;
}
void Re_Assign(Node_Score*& sco, Node_Score* _import) {
	Node_Score* tmp = sco;
	while (tmp != NULL) {
		tmp->data.score_mid = _import->data.score_mid * 1.0;
		tmp->data.score_fin = _import->data.score_fin * 1.0;
		tmp->data.score_total = _import->data.score_total * 1.0;
		strcpy_s(tmp->data.other_mark, strlen(_import->data.other_mark) + 1, _import->data.other_mark);
		tmp = tmp->next;
		_import = _import->next;
	}
}
void Import_Score_Course(Node_Course* cou) {
	int chon;
	cout << "\n  Khoa hoc can nhap bang diem: ";
	cin >> chon;
	char xx[] = "course.txt";
	int n = Count_file(xx) / 8;
	while (chon < 1 || chon > n) {
		cout << "  Khoa hoc duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay quay lai menu? \n";
		cout << "   1. Nhap lai    2. Quay lai\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		List_Course(cou);
		if (c == 1) {
			cout << "\n  Khoa hoc can nhap bang diem: ";
			cin >> chon;
		}
	}
	Node_Course* tmp = cou;
	for (int i = 1; i < chon; i++) {
		tmp = tmp->next;
	}
	char file[max];
	Connect_Course(tmp->data.id_class, tmp->data.id, file);
	Node_Score* sco = NULL;
	int lim = Count_file(file) - 1;
	if (lim != 0) {
		Read_Stu_Sco_Course(sco, lim, file);
		Arrange_StuScore(sco);
		char import_file[max];
		cin.ignore();
		cout << "  File diem : ";
		cin.getline(import_file, max);
		int size_import = Count_file(import_file) - 1;
		if (lim != size_import) {
			cout << "\n   Thong tin sinh vien khong trung khop!\n\n";
			return;
		}
		Node_Score* _import = NULL;
		Read_Stu_Sco_Course(_import, size_import, import_file);
		Arrange_StuScore(_import);
		if (!Check_ID_import(sco, _import)) {
			cout << "\n   Thong tin sinh vien khong trung khop!\n\n";
			return;
		}
		Re_Assign(sco, _import);
		Node_Score* display = sco;
		int i = 1;
		cout << setprecision(1);
		while (display != NULL) {
			if (i < 10)
				cout << "   " << i << ". ";
			if (i > 9)
				cout << "  " << i << ". ";
			
			cout << "MSSV          : " << display->data.ID << endl;
			cout << "      Ho va ten     : " << display->data.name << endl;
			cout << fixed << "      Giua ky       : " << display->data.score_mid << endl;
			cout << fixed << "      Cuoi ky       : " << display->data.score_fin << endl;
			cout << fixed << "      Tong ket      : " << display->data.score_total << endl;
			cout << "      Danh dau khac : " << display->data.other_mark << endl;
			display = display->next;
			i++;
		}
		Write_Stu_Sco_Course(sco, file);
		textColor(10);
		cout << "\n  *Da nhap bang diem thanh cong*\n\n";
		textColor(7);
	}
	else {
		textColor(10);
		cout << "\n  *Khoa hoc hien tai khong co sinh vien de nhap diem*\n\n";
		textColor(7);
	}
}

//--- Xem bang diem 1 khoa hoc
void View_Score_Course(Node_Course* cou) {
	int chon;
	cout << "\n  Khoa hoc can xem bang diem: ";
	cin >> chon;
	char xx[] = "course.txt";
	int n = Count_file(xx) / 8;
	while (chon < 1 || chon > n) {
		cout << "  Khoa hoc duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay quay lai menu? \n";
		cout << "   1. Nhap lai    2. Quay lai\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		List_Course(cou);
		if (c == 1) {
			cout << "\n  Khoa hoc can xem bang diem: ";
			cin >> chon;
		}
	}
	Node_Course* tmp = cou;
	for (int i = 1; i < chon; i++) {
		tmp = tmp->next;
	}
	char file[max];
	Connect_Course(tmp->data.id_class, tmp->data.id, file);
	Node_Score* sco = NULL;
	int lim = Count_file(file) - 1;
	if (lim != 0) {
		system("cls");
		Display_Header();
		cout << "\n   Xem bang diem khoa hoc:\n";
		cout << "   Tu  file: '" << file << "'\n";
		Read_Stu_Sco_Course(sco, lim, file);
		Node_Score* display = sco;
		int i = 1;
		cout << setprecision(1);

		while (display != NULL) {
			if (i < 10)
				cout << "   " << i << ". ";
			if (i > 9)
				cout << "  " << i << ". ";
			cout << "MSSV          : " << display->data.ID << endl;
			cout << "      Ho va ten     : " << display->data.name << endl;
			cout << fixed << "      Giua ky       : " << display->data.score_mid << endl;
			cout << fixed << "      Cuoi ky       : " << display->data.score_fin << endl;
			cout << fixed << "      Tong ket      : " << display->data.score_total << endl;
			cout << "      Danh dau khac : " << display->data.other_mark << endl;
			display = display->next;
			i++;
		}
		Write_Stu_Sco_Course(sco, file);
		textColor(10);
		cout << "\n  *Da nhap bang diem thanh cong*\n\n";
		textColor(7);
	}
	else {
		textColor(10);
		cout << "\n  *Khoa hoc hien tai khong co sinh vien de nhap diem*\n\n";
		textColor(7);
	}
}

//---- Cap nhat ket qua sinh vien
void Update_Result_Student(Node_Course* cou) {
	int chon;
	cout << "\n  Khoa hoc can cap nhat ket qua: ";
	cin >> chon;
	char xx[] = "course.txt";
	int n = Count_file(xx) / 8;
	while (chon < 1 || chon > n) {
		cout << "  Khoa hoc duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay quay lai menu? \n";
		cout << "   1. Nhap lai    2. Quay lai\n";
		int c;
		cout << "   Chon: ";
		cin >> c;
		if (c == 2)
			return;
		system("cls");
		Display_Header();
		List_Course(cou);
		if (c == 1) {
			cout << "\n  Khoa hoc can cap nhat ket qua: ";
			cin >> chon;
		}
	}
	Node_Course* tmp = cou;
	for (int i = 1; i < chon; i++) {
		tmp = tmp->next;
	}
	char file[max];
	Connect_Course(tmp->data.id_class, tmp->data.id, file);
	Node_Score* sco = NULL;
	int lim = Count_file(file) - 1;
	if (lim != 0) {
		system("cls");
		Display_Header();
		cout << "\n   Bang diem khoa hoc:\n";
		cout << "   Tu  file: '" << file << "'\n";
		Read_Stu_Sco_Course(sco, lim, file);
		Node_Score* display = sco;
		int i = 1;
		cout << setprecision(1);
		while (display != NULL) {
			if (i < 10)
				cout << "   " << i << ". ";
			if (i > 9)
				cout << "  " << i << ". ";
			cout << "MSSV          : " << display->data.ID << endl;
			cout << "      Ho va ten     : " << display->data.name << endl;
			display = display->next;
			i++;
		}
		int id;
		cout << "\n  MSSV cua sinh vien can cap nhat ket qua: ";
		cin >> id;
		Node_Score* find = sco;
		int local = findLocal(sco, id);
		while (local == -1) {
			cout << "\n\n  Khong the tim thay sinh vien!\n";
			cout << "\n  Nhap lai mssv(nhap 0 neu muon tro lai): ";
			cin >> id;
			if (id == 0) {
				textColor(4);
				cout << "\n  *Cap nhat ket qua that bai*\n\n";
				textColor(7);
				return;
			}
			local = findLocal(sco, id);
		}
		for (int i = 1; i < local; i++) {
			find = find->next;
		}
		system("cls");
		Display_Header();
		cout << "\n   Cap nhat ket qua sinh vien\n\n";
		cout << endl;
		cout << "    " << find->data.ID;
		cout << "    " << find->data.name << endl;
		cout << fixed << "     1. Giua ky       : " << find->data.score_mid << endl;
		cout << fixed << "     2. Cuoi ky       : " << find->data.score_fin << endl;
		cout << fixed << "     3. Tong ket      : " << find->data.score_total << endl;
		cout << "     4. Danh dau khac : " << find->data.other_mark << endl << endl;
		cout << "    Ket qua can cap nhat: ";
		int result;
		cin >> result;
		switch (result) {
		case 1: {
			cout << "     Cap nhat diem giua ky: ";
			cin >> find->data.score_mid;
			break;
		}
		case 2: {
			cout << "     Cap nhat diem cuoi ky: ";
			cin >> find->data.score_fin;
			break;
		}
		case 3: {
			cout << "     Cap nhat diem tong ket: ";
			cin >> find->data.score_total;
			break;
		}
		case 4: {
			cin.ignore();
			cout << "     Danh dau khac: ";
			cin.getline(find->data.other_mark, max);
			break;
		}
		}

		Write_Stu_Sco_Course(sco, file);
		textColor(10);
		cout << "\n  *Cap nhat bang diem thanh cong*\n\n";
		textColor(7);
	}
	else {
		textColor(4);
		cout << "\n  *Khoa hoc hien tai khong co sinh vien de cap nhat*\n\n";
		textColor(7);
	}
}



//--- Xuat bang diem sinh vien
int Take_Score(Node_Score* sco, int id, float& mid, float& fin, float& total) {
	while (sco != NULL) {
		if (id == sco->data.ID) {
			mid = sco->data.score_mid;
			fin = sco->data.score_fin;
			total = sco->data.score_total;
			return 1;
		}
		sco = sco->next;
	}
	return 0;
}
void Export_Score_Student(Node_Course* cou, int id) {
	Node_Course* tmp = cou;
	int sumcredit = 0;
	float score = 0;
	for (; tmp != NULL; tmp = tmp->next) {
		char file[max];
		float mid, fin, total;
		Connect_Course(tmp->data.id_class, tmp->data.id, file);
		Node_Score* sco = NULL;
		int lim = Count_file(file) - 1;
		if (lim > 0) {
			Read_Stu_Sco_Course(sco, lim, file);
			int take = Take_Score(sco, id, mid, fin, total);
			if (take == 1) {
				cout << "   " << tmp->data.id_class << "  " << tmp->data.name << ":\n";
				cout << "     Giua ky  : " << mid << endl;
				cout << "     Cuoi ky  : " << fin << endl;
				cout << "     Tong ket : " << total << endl;
				int credit = atof(tmp->data.credit);
				sumcredit += credit;
				score += total * credit;
			}
		}
	}
	float avg = score / sumcredit;
	cout << "\n   Diem trung binh: " << avg << endl << endl;
}