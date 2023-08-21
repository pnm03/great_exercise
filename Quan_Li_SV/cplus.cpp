#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <sstream>


double string_to_double (std::string a) {
     // a = "123.45678"
     bool tam = 0;  // kiểm tra nếu tới dấu '.' thì = 1 
     double num = 0;     // lấy số đằng trước dấu '.'   => {123}
     double num2 = 0;    // lấy số đằng sau dấu '.'     => {45678}
     int dem = 0;   // đếm tổng các số trước dấu '.' và cả dấu '.'   => {4}
     int dem1 = 0;  // là tổng các số đằng sau dấu '.'   => {5}
     int tp = 1;
     for (int i = 0; i < a.length(); i++) {
          if (a[i] == '.') {
               tam = 2;
               dem++;
               dem1 = dem+1;
               tam = 1;
               continue;
          }
          if (tam == 0) {
               num *= 10;
               num += a[i];
               num -= 48;
               dem++;
          }
          else if (tam == 1) {
               double a1 = 1.0/(pow(10,tp));      // chuyển số thành dạng số thập phân tương ứng
               int a2 = a[i]-48;     // chuyển mã char thành kí tự
               num2 = num2 + (a1 * a2);
               tp++;
          }
     }
     double kq = num+num2;
     // std::cout << "\n";
     std::cout << std::fixed << std::setprecision(a.length()-dem1+1);
     return kq;
}

struct sinh_vien {
	std::string name;
	int tuoi;
	float diem;
};

// Ham in ra so ki tu
void print_key (int a, int b) {
	// a la ki tu ascii can in
	// b la so lan in
	for (int i = 1; i <= b; i++) {
		std::cout << char(a);
	}
}

// In ra khung tren cua ham Print_all
void in_khung_tren ();
void in_khung_duoi ();

// Ham hien menu
void menu () {
	std::cout << "Danh sach thao tac:\n";
	std::cout << "1 - In danh sach SV\n";\
	std::cout << "2 - Them\n";
	std::cout << "3 - Sua\n";
	std::cout << "4 - Xoa\n";
	std::cout << "5 - Tim kiem\n";
	std::cout << "6 - Sap xep\n";
	std::cout << "7 - Thong ke\n";
	std::cout << "8 - Sao luu\n";
	std::cout << "9 - Thoat\n";
}

// Clear console
void clear_console () {
	std::string key;
	std::cout << "Press key to continue . . . ";
	std::cin.ignore();
	getline(std::cin, key);
	system("cls");
}

// Ham in thong tin
void print_all (std::string name_file);

// Ham lien ket sinh vien
sinh_vien lien_ket_sv (std::string line);

// Dem so thong tin trong file
int count_sv (std::string name_file) {
	std::ifstream input;
	input.open(name_file);
	std::string line;
	int count = 0;
	while (getline(input, line)) {
		count++;
	}
	return count;
}

// Them sinh vien
std::string add_sv (std::string file_name);

// Sua sinh vien
void edit_sv (int num_edit, int num_edit_pt, std::string name_file);

// Xoa sinh vien
void delete_sv (int num_delete, std::string name_file);

std::string get_name (std::string get_name);

int main () {
	std::string name_file = "data.txt";
	int count = count_sv(name_file); // So sinh vien co trong file
	std::vector<sinh_vien> arr_sv;
	// std::vector<sinh_vien> *point_arr_sv;
	sinh_vien point_arr_sv;
	std::string text;
	{
		std::ifstream input;
		input.open(name_file);
		while (getline(input, text)) {
			point_arr_sv = lien_ket_sv(text); // Lien ket cac sinh vien
			arr_sv.push_back(point_arr_sv);
		}
		input.close();
	}

	// Hien thi lenh
	int num_data; // Nhan lenh nguoi dung nhap tu ban phim
	do {
		// system("cls");
		menu();
		std::cout << "Nhap lenh: ";
		std::cin >> num_data;
		switch(num_data) {
			case 1:
				print_all(name_file);
				break;
			case 2:
				text = add_sv(name_file);
				point_arr_sv = lien_ket_sv(text); // Lien ket cac sinh vien
				arr_sv.push_back(point_arr_sv);
				{
					std::ifstream input;
					input.open(name_file);
					while (getline(input, text)) {
						point_arr_sv = lien_ket_sv(text); // Lien ket cac sinh vien
						arr_sv.push_back(point_arr_sv);
					}
					input.close();
				}
				break;
			case 3:
				std::cout << "[3] Chinh sua sinh vien\n";
				count = count_sv(name_file);
				int num_edit;
				do {
					std::cout << "(!) Nhap so thu tu sinh vien muon chinh sua: ";
					std::cin >> num_edit;
				} while (num_edit < 0 && num_edit > count);
				int num_edit_pt; // Phan tu can chinh sua
				std::cout << "\t1 - Ten\n";
				std::cout << "\t2 - Tuoi\n";
				std::cout << "\t3 - Diem so\n";
				std::cout << "\t(!) Nhap so phan tu muon chinh sua: ";
				std::cin >> num_edit_pt; // Vị tri can chinh sua
				edit_sv (num_edit, num_edit_pt, name_file);
				{
					std::ifstream input;
					input.open(name_file);
					while (getline(input, text)) {
						point_arr_sv = lien_ket_sv(text); // Lien ket cac sinh vien
						arr_sv.push_back(point_arr_sv);
					}
					input.close();
				}
				break;
			case 4: {
				int num_delete;
				std::cout << "[4] Xoa sinh vien\n";
				std::cout << "Nhap vi tri sinh vien can xoa: ";
				std::cin >> num_delete;
				delete_sv(num_delete, name_file);
				{
					std::ifstream input;
					input.open(name_file);
					while (getline(input, text)) {
						point_arr_sv = lien_ket_sv(text); // Lien ket cac sinh vien
						arr_sv.push_back(point_arr_sv);
					}
					input.close();
				}
				break;
			}
			case 5: {
				int num_delete_case5;
				std::string search_name;
				std::cout << "[5] Tim kiem sinh vien\n";
				std::cout << "\tNhap ten hoac ki tu can tim kiem: ";
				std::cin.ignore();
				getline(std::cin, search_name);
				{
					std::ifstream input;
					input.open(name_file);
					while (getline(input, text)) {
						point_arr_sv = lien_ket_sv(text); // Lien ket cac sinh vien
						arr_sv.push_back(point_arr_sv);
					}
					input.close();
				}
				in_khung_tren();
				count = count_sv(name_file);
				num_delete_case5 = 1;
				for (int i = 0; i < count; i++) {
					std::string name = arr_sv[i].name;
					if (name.find(search_name) != std::string::npos) {
						std::cout << std::setw(1) << "|" << std::setw(8) << num_delete_case5
						<< std::setw(1) << "|" << std::setw(20) << arr_sv[i].name;
						std::cout << std::setw(1) << "|" << std::setw(8) << arr_sv[i].tuoi;
						std::cout << std::setw(1) << "|" << std::setw(8) << arr_sv[i].diem << "|" << "\n";
						num_delete_case5++;
					}
				}
				in_khung_duoi();
				clear_console();
				break;
			}
			case 6: {
					arr_sv.clear();
					std::ifstream input;
					input.open(name_file);
					while (getline(input, text)) {
						point_arr_sv = lien_ket_sv(text); // Lien ket cac sinh vien
						arr_sv.push_back(point_arr_sv);
					}
					input.close();
					count = count_sv(name_file);
					std::cout << "[6] Sap xep du lieu sinh vien\n";
					std::cout << "\t1 - Sap xep theo ten theo ABC\n";
					std::cout << "\t2 - Sap xep theo diem tang dan\n";
					std::cout << "\t3 - Sap xep theo tuoi tang dan\n";
					int num_sx = 0;
					std::cout << "\tNhap kieu ban muon sap xep: ";
					std::cin >> num_sx;
					if (num_sx == 1) {
						for (int i = 0; i < count; i++) {
							std::string name_sx_1 = get_name(arr_sv[i].name);
							for (int j = 0; j < count; j++) {
								std::string name_sx_2 = get_name(arr_sv[j].name);
								if (name_sx_1[0] < name_sx_2[0]) {
									std::string name_sx_3 = arr_sv[i].name;
									int tuoi_sx_3 = arr_sv[i].tuoi;
									float diem_sx_3 = arr_sv[i].diem;
									arr_sv[i].name = arr_sv[j].name;
									arr_sv[i].tuoi = arr_sv[j].tuoi;
									arr_sv[i].diem = arr_sv[j].diem;
									arr_sv[j].name = name_sx_3;
									arr_sv[j].tuoi = tuoi_sx_3;
									arr_sv[j].diem = diem_sx_3;
								}
							}
						}
					}
					else if (num_sx == 2) {
						for (int i = 0; i < count; i++) {
							for (int j = 0; j < count; j++) {
								if (arr_sv[i].diem < arr_sv[j].diem) {
									std::string name_sx_4 = arr_sv[i].name;
									int tuoi_sx_4 = arr_sv[i].tuoi;
									float diem_sx_4 = arr_sv[i].diem;
									arr_sv[i].name = arr_sv[j].name;
									arr_sv[i].tuoi = arr_sv[j].tuoi;
									arr_sv[i].diem = arr_sv[j].diem;
									arr_sv[j].name = name_sx_4;
									arr_sv[j].tuoi = tuoi_sx_4;
									arr_sv[j].diem = diem_sx_4;
								}
							}
						}
					}	
					else if (num_sx == 3) {
						for (int i = 0; i < count; i++) {
							for (int j = 0; j < count; j++) {
								if (arr_sv[i].tuoi < arr_sv[j].tuoi) {
									std::string name_sx_5 = arr_sv[i].name;
									int tuoi_sx_5 = arr_sv[i].tuoi;
									float diem_sx_5 = arr_sv[i].diem;
									arr_sv[i].name = arr_sv[j].name;
									arr_sv[i].tuoi = arr_sv[j].tuoi;
									arr_sv[i].diem = arr_sv[j].diem;
									arr_sv[j].name = name_sx_5;
									arr_sv[j].tuoi = tuoi_sx_5;
									arr_sv[j].diem = diem_sx_5;
								}
							}
						}
					}
					in_khung_tren();
					for (int i = 0; i < count; i++) {
						std::cout << std::setw(1) << "|" << std::setw(8) << i+1
						<< std::setw(1) << "|" << std::setw(20) << arr_sv[i].name;
						std::cout << std::setw(1) << "|" << std::setw(8) << arr_sv[i].tuoi;
						std::cout << std::setw(1) << "|" << std::setw(8) << arr_sv[i].diem << "|" << "\n";
					}
					in_khung_duoi();
					std::cout << "\nDu lieu sap xep chua duoc luu vao Database. Neu muon luu ket qua sap xep nay vui long chon (8) sao luu.\n";
					std::cout << "Luu y: Phai thuc hien sao luu truoc khi su dung chuc nang khac hoac nhan (9) thoat chuong trinh.\n";
				}
				clear_console();
				break;
			case 7: {
				arr_sv.clear();
				{
					std::ifstream input;
					input.open(name_file);
					while (getline(input, text)) {
						point_arr_sv = lien_ket_sv(text); // Lien ket cac sinh vien
						arr_sv.push_back(point_arr_sv);
					}
					input.close();
				}
				std::cout << "[7] Thong ke so lieu sinh vien\n";
				count = count_sv(name_file);
				int diem_tbc = 0;
				float diem_max = 0;
				int hsg = 0; int hsk = 0; int hstb = 0;
				for (int i = 0; i < count; i++) {
					diem_tbc += arr_sv[i].diem;
					if (diem_max < arr_sv[i].diem) diem_max = arr_sv[i].diem;
					if (arr_sv[i].diem > 8) hsg++;
					else if (arr_sv[i].diem <= 8 && arr_sv[i].diem > 6) hsk++;
					else if (arr_sv[i].diem <= 6) hstb++;
				}
				diem_tbc /= count;
				std::cout << "\tSo diem trung binh ca lop la: " << diem_tbc << "\n";
				std::cout << "\tTi le hoc sinh gioi la: " << (hsg*100/count) << "%\n";
				std::cout << "\tTi le hoc sinh kha la: " << (hsk*100/count) << "%\n";
				std::cout << "\tTi le hoc sinh trung binh la: " << (hstb*100/count) << "%\n";
				std::cout << "\tSinh vien co diem cao nhat " << diem_max << " la:\n";
				for (int i = 0; i < count; i++) {
					if (arr_sv[i].diem == diem_max) std::cout << "\t- " << arr_sv[i].name << "\n";
				}
				clear_console();
				break;
			}
			case 8: {
				// Xoa file cu
				std::ofstream outputFile(name_file, std::ofstream::out | std::ofstream::trunc);

				std::ofstream output;
				output.open(name_file, std::ios::app);
				std::string name_reload, tuoi_reload, diem_reload;
				for (int i = 0; i < count; i++) {
					name_reload = arr_sv[i].name;
					std::stringstream ss;
    					ss << arr_sv[i].tuoi;
					tuoi_reload = 	ss.str();	
					std::stringstream ss1;
					ss1 << arr_sv[i].diem;
					if (i == count - 1) {
						diem_reload = ss1.str();
					}
					else {
						diem_reload = ss1.str() + "\n";
					}
					output << name_reload + ";" + tuoi_reload + ";" + diem_reload;
 				}
				for (int i = 1; i <= 10; i++) {
					std::cout << "| ";
					Sleep(50);
				}
				std::cout << "\nDa sao luu du lieu vao Database\n";
			}
			clear_console();
			break;
			case 9:
				clear_console();
				break;
			default:
				std::cout << "Lenh nhap khong dung. Vui long nhap lai\n";
				clear_console();
				break;
		}
	} while (num_data != 9);


	return 0;
}

void in_khung_tren () {
	std::cout << std::left;
	std::cout << char(43);
	print_key(45, 8);
	std::cout << char(43);
	print_key(45, 20);
	std::cout << char(43);
	print_key(45, 8);
	std::cout << char(43);
	print_key(45, 8);
	std::cout << char(43) << "\n";
	std::cout	<< std::setw(1) << char(179) << std::setw(8) << "STT" 
			<< std::setw(1) << char(179)
			<< std::setw(20) << "Ho Ten" << std::setw(1) << char(179)
			<< std::setw(8) << "Tuoi" << std::setw(1) << char(179)
			<< std::setw(8) << "Diem" << std::setw(1) << char(179) << "\n";
	std::cout << char(43);
	print_key(45, 8);
	std::cout << char(43);
	print_key(45, 20);
	std::cout << char(43);
	print_key(45, 8);
	std::cout << char(43);
	print_key(45, 8);
	std::cout << char(43) << "\n";
}
void in_khung_duoi () {
	std::cout <<char(43);
	print_key(45, 8);
	std::cout << char(43);
	print_key(45, 20);
	std::cout << char(43);
	print_key(45, 8);
	std::cout << char(43);
	print_key(45, 8);
	std::cout << char(43) << "\n";
}

sinh_vien lien_ket_sv (std::string line) {
	sinh_vien p;
	std::string check_str = ";";
	int check_i = line.find(check_str); // Lay vi tri chua dau ";" dau tien

	// In ra ten
	std::string name = line.substr(0, check_i);
	p.name = name;
	// In ra tuoi
	line = line.substr(check_i+1, line.size()-1);
	check_i = line.find(check_str);
	std::string tuoi = line.substr(0, check_i);
	int tuoi_i = string_to_double(tuoi);
	p.tuoi = tuoi_i;

	// In ra diem
	line = line.substr(check_i+1, line.size()-1);
	std::string diem = line;
	float diem_i = string_to_double(diem);
	p.diem = diem_i;
	return p;
}

void print_all (std::string name_file) {
	std::ifstream input;
	input.open(name_file);
	std::string line;
	std::cout << "[1] In danh sach sinh vien:\n";
	in_khung_tren();
	int count = 1;
	while (getline(input, line)) {
		std::string check_str = ";";
		int check_i = line.find(check_str); // Lay vi tri chua dau ";" dau tien

		// In ra ten
		std::string name = line.substr(0, check_i);
		std::cout << std::setw(1) << "|" << std::setw(8) << count
				<< std::setw(1) << "|" << std::setw(20) << name;
		
		// In ra tuoi
		line = line.substr(check_i+1, line.size()-1);
		check_i = line.find(check_str);
		std::string tuoi = line.substr(0, check_i);
		int tuoi_i = string_to_double(tuoi);  // Chuyen string -> double
		std::cout << std::setw(1) << "|" << std::setw(8) << tuoi_i;

		// In ra diem
		line = line.substr(check_i+1, line.size()-1);
		// check_i = line.find(check_str);
		std::string diem = line;
		double diem_i = string_to_double(diem);
		std::cout << std::setw(1) << "|" << std::setw(8) << diem_i << "|" << "\n";

		count++;
	}
	in_khung_duoi();
	clear_console();
}

std::string add_sv (std::string file_name) {
	std::ofstream output;
	output.open(file_name, std::ios::app);
	std::string name, tuoi, diem;
	std::cout << "[2] Them sinh vien:\n";
	std::cin.ignore();
	std::cout << "Nhap ten: ";
	getline(std::cin, name);
	std::cout << "Nhap tuoi: ";
	getline(std::cin, tuoi);
	std::cout << "Nhap diem: ";
	getline(std::cin, diem);
	output << "\n" + name + ";" + tuoi + ";" + diem;
	// std::cout << "\n";
	for (int i = 1; i <= 10; i++) {
		std::cout << "| ";
		Sleep(70);
	}
	std::cout << "\nDa them sinh vien " << name << "\n";
	output.close();
	clear_console();
	return name + ";" + tuoi + ";" + diem;
}

void edit_sv (int num_edit, int num_edit_pt, std::string name_file) {
	int count = 1;
	std::ifstream input;
	input.open(name_file);
	std::string line;
	std::string text_file;
	
	while (getline(input, line)) {
		if (count == num_edit) {

			std::string check_str = ";";
			int check_i = line.find(check_str); // Lay vi tri chua dau ";" dau tien

			// Lay ra ten
			std::string name = line.substr(0, check_i);

			// Lay ra tuoi
			line = line.substr(check_i+1, line.size()-1);
			check_i = line.find(check_str);
			std::string tuoi = line.substr(0, check_i);

			// Lay ra diem
			line = line.substr(check_i+1, line.size()-1);
			std::string diem = line;

			if (num_edit_pt == 1) {
				std::string name_edit;
				std::cout << "\tNhap ten can chinh sua: ";
				std::cin.ignore();
				getline(std::cin, name_edit);
				if (count == 1) {
					text_file = name_edit + ";" + tuoi + ";" + diem;
				}
				else {
					text_file = text_file + "\n" + name_edit + ";" + tuoi + ";" + diem;
				}
			}
			else if (num_edit_pt == 2) {
				std::string tuoi_edit;
				std::cout << "\tNhap tuoi can chinh sua: ";
				std::cin.ignore();
				getline(std::cin, tuoi_edit);
				if (count == 1) {
					text_file = name + ";" + tuoi_edit + ";" + diem;
				}
				else {
					text_file = text_file + "\n" + name + ";" + tuoi_edit + ";" + diem;
				}
			}
			else if (num_edit_pt == 3) {
				std::string diem_edit;
				std::cout << "\tNhap diem can chinh sua: ";
				std::cin.ignore();
				getline(std::cin, diem_edit);
				if (count == 1) {
					text_file = name + ";" + tuoi + ";" + diem_edit;
				}
				else {
					text_file = text_file + "\n" + name + ";" + tuoi + ";" + diem_edit;
				}
			}
		}
		else {
			if (count == 1) {
				text_file = line;
			}
			else {
				text_file = text_file + "\n" + line;
			}
		}
		count++;
	}
	input.close();

	std::ofstream output;
	output.open(name_file);
	output << text_file;
	output.close();
	for (int i = 1; i <= 10; i++) {
		std::cout << "| ";
		Sleep(50);
	}
	std::cout << "\nDa chinh sua va cap nhat vao database\n";
	clear_console();
}

void delete_sv (int num_delete, std::string name_file) {
	int count = 1;
	std::ifstream input;
	input.open(name_file);
	std::string line;
	std::string text_file;
	while (getline(input, line)) {
		if (count != num_delete) {
			if (count == 1) {
				text_file = line;
			}
			else {
				text_file = text_file + "\n" + line;
			}
		}
		count++;
	}
	input.close();

	std::ofstream output;
	output.open(name_file);
	output << text_file;
	output.close();
	for (int i = 1; i <= 10; i++) {
		std::cout << "| ";
		Sleep(50);
	}
	std::cout << "\nDa thuc hien xoa va cap nhat vao database\n";
	clear_console();
}

std::string get_name (std::string get_name) {
	std::string space = " ";
	int num = 0;
	while (get_name.find(space) != -1) {
		num = get_name.find(space);
		get_name = get_name.substr(num+1, get_name.length()-1);
	}
	return get_name;
}