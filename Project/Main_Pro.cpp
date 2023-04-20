#include"Header_Pro.h"



int main() {
	Display_Header();
	int n = DEM_sv() / 2;//So sinh vien trong  file accountSV.txt
	Account* sv, * gv;
	sv = new Account[n];
	int m = DEM_gv() / 2;//So giang vien trong  file accountGV.txt
	gv = new Account[m];
	NamHoc year;//khai bao mot nam hoc

	//----- Doc file vao bien ----//
	Read_file_sv(sv, n);//Thong tin tron file accountSV.txt
	Read_file_gv(gv, m);//Thong tin tron file accountGV.txt


	cout << endl << "                    BAN LA AI?                    " << endl;
	cout << "     =============================================" << endl;
	cout << "     =  1. Sinh vien                             =" << endl;
	cout << "     =  2. Giang vien                            =" << endl;
	cout << "     =============================================" << endl;
	int x; cout << "      Chon: "; cin >> x;
	system("cls");
	Display_Header();
	switch (x) {
	case 1: {
		cout << endl << "                    --SINH VIEN--                " << endl;
		cout << "   ===================================================" << endl;
		cout << "   =  1. Dang nhap                                   =" << endl;
		cout << "   =  2. Doi mat khau                                =" << endl;
		cout << "   ===================================================" << endl;
		int x1; cout << "      Chon: "; cin >> x1;
		switch (x1) {
		case 1: {
			system("cls");
			Display_Header();
			int mssv = Login(sv, n);
			if (mssv == -1)
				return 0;
			system("cls");
			Display_Header();
			Function_after_Login_SV(mssv);
			break;
		}
		case 2: {
			changeMK(sv, n, x);
			cout << "Ban co muon quay lai trang dang nhap?\n";
			cout << "\t1.Co\t2.Khong\n";
			int c; cin >> c;
			if (c == 1) {
				system("cls");
				Display_Header();
				Login(sv, n);

			}
			if (c == 2)
				return 0;
			break;
		}
		}
		break;
	}
	case 2: {
		cout << endl << "                    --GIANG VIEN--                " << endl;
		cout << "   ===================================================" << endl;
		cout << "   =  1. Dang nhap                                   =" << endl;
		cout << "   =  2. Doi mat khau                                =" << endl;
		cout << "   ===================================================" << endl;
		int x1; cout << "      Chon: "; cin >> x1;
		switch (x1) {
		case 1: {
			system("cls");
			Display_Header();
			int msgv = Login(gv, n);
			if (msgv == -1)
				return 0;
			Function_after_Login_NV();
			break;
		}
		case 2: {
			changeMK(gv, n, x);
			cout << "Ban co muon quay lai trang dang nhap?\n";
			cout << "\t1.Co\t2.Khong\n";
			int c; cin >> c;
			if (c == 1) {
				system("cls");
				Display_Header();
				Login(sv, n);

			}
			if (c == 2)
				return 0;
			break;
		}
		}
		break;
	}
	}
	delete[]sv;
	delete[]gv;
	cout << endl;
	system("pause");
	return 0;
}

