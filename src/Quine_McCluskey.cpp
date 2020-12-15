#include<iostream>

using namespace std;

// 2^n
int dua_pangkat(int number){
    int hasil = 1;
    for(int i = 0; i < number; i++)
        hasil = hasil * 2 ;
    return hasil;
}

// 4, 5 => 0101
// Mencari input list dari minterm
string input_list(int jml_digit, int n) {
    int num = n;
    char result[jml_digit];
    int binaryNumber[100];
    int i = 0;

    // mengisi semua elemen dengan '0'
    for(int i = 0; i < jml_digit; i++)
        result[i] = '0';

    while (n > 0) {
        binaryNumber[i] = n % 2;
        n = n / 2;
        i++;
    }

    if(num > 0){
        int k = 0;
        for (int j = jml_digit - 1; j >= 0; j--){
            if(binaryNumber[j] != 0 && binaryNumber[j] != 1) 
                result[k] = '0';
            else
                result[k] = to_string(binaryNumber[j])[0];
            k++;
        }
    }

    result[jml_digit] = {};
    return result;
}

string to_variable(string s){
    char va = 'a';
    string result = "";
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '1')
            result += va;
        else if (s[i] == '0'){
            result += va;
            result += "'";
        }
        va++;
    }
    return result;
}

// Mencari minterm dalam string minterm
bool minterm_exists(string minterm_to_find, string minterm){
    minterm = "." + minterm + ".";
    minterm_to_find = "." + minterm_to_find + ".";
    if(minterm.find(minterm_to_find.c_str(), 0, minterm_to_find.size()) != string::npos) return true;
    return false;
}

int total_digit(int number){
    if(number == 0) return 1;
    int total = 0;
    while (number != 0){
		total++;
		number = number / 10;
	}
    return total;
}

int main(){
    // ================ Persiapan ================
    // Memasukkan inputan yang akan di proses

    int jml_input;

    cout << "======================\n";
    cout << "LANGKAH PERSIAPAN\n";
    cout << "======================\n";
    cout << "Masukkan jumlah input : ";
    cin >> jml_input;
    cin.ignore();

    cout << "======================\n";

    int loop;
    loop = dua_pangkat(jml_input);
    int minterm[loop];
    for(int i = 0; i < loop; i++){
        cout << "Masukkan (m" << i << ") : ";
        cin >> minterm[i];
        cin.ignore();
    }

    cout << "\nMohon tunggu...\n";

    // Keluarkan inputan
    for(int i = 0; i < loop; i++){
        if(minterm[i] == 1)
            cout << "(m" << i << ") = " << input_list(jml_input, i) << "\n";
    }

    cout << "Langkah persiapan selesai :) . \n";
    system("pause");
    cout << "\n=================\n";
    cout << "LANGKAH PERTAMA\n";
    cout << "=================\n";

    // ================ Langkah 1 ================
    // Pengelompokan input berdasarkan jumlah digit '1'

    string group[loop][loop][3];

    string input;
    int count;
    int count_g_member[loop] = {0};

    cout << "Mohon tunggu...\n";

    // hitung jumlah digit '1'
    for(int i = 0; i < loop; i++){
        if(minterm[i] != 1) continue;
        count = 0;
        string input = input_list(jml_input, i);
        for(int j = 0; j < jml_input; j++){
            if(input[j] == '1')
                count++;
        }

        group[ count ][ count_g_member[count] ][ 0 ] = to_string(i);
        group[ count ][ count_g_member[count] ][ 1 ] = input;
        group[ count ][ count_g_member[count] ][ 2 ] = "check";
        count_g_member[count]++;
    }
    cout << "\n";

    for(int i = 0; i <= jml_input; i++){
        for(int j = 0; j < count_g_member[i]; j++)
            cout << group[i][j][0] << " | " << group[i][j][1] << " | " << group[i][j][2] << "\n" ;
        cout << "-----------------------------------\n";
    }

    cout << "Langkah pertama selesai :) . \n";
    system("pause");
    cout << "\n================\n";
    cout << "LANGKAH KEDUA\n";
    cout << "================\n";

    // ================ Langkah 2 ================
    // Menghilangkah 'check'

    string t_group[loop][loop][3];
    string f_group[loop][3];
    int t_count_g_member[loop] = {0};
    int f_count_g_member = 0;
    int change  = 0, row_change = 0, group_change = 0, table_change = 0;
    int nth_table = 0;
    int i_last;

    cout << "Mohon tunggu...\n";

    while(true){
        nth_table++;
        cout << "=================\n";
        cout << "Tabel ke-" << nth_table;
        cout << "\n=================\n";

        table_change = 0;
        for(int i = 0; i <= jml_input - nth_table; i++)
        {
            group_change = 0;
            for(int j = 0; j < count_g_member[i]; j++)
            {
                row_change = 0;
                for(int k = 0; k < count_g_member[i+1]; k++)
                {
                    next_row:
                    if(!(k < count_g_member[i+1])) break;

                    input = group[i][j][1];
                    change = 0; // untuk hitung berapa perubahan

                    for(int l = 0; l < jml_input; l++)
                    {
                        if((group[i][j][1][l] == '-') ^ (group[i+1][k][1][l] == '-')){
                            k++;
                            goto next_row;
                        }
                        if(group[i][j][1][l] != group[i+1][k][1][l]){
                            change++;
                            input[l] = '-';
                        }
                    }
                    if(change == 1){
                        t_group[i][ t_count_g_member[i] ][0] = group[i][j][0] + "." +group[i+1][k][0];
                        t_group[i][ t_count_g_member[i] ][1] = input;
                        t_group[i][ t_count_g_member[i] ][2] = "check";
                        t_count_g_member[i]++;
                        row_change++;
                    };
                }
                group_change += row_change;
            }
            if(group_change < 1){
                for(int j = 0; j < count_g_member[i]; j++){
                    f_group[ f_count_g_member ][0] = group[i][j][0];
                    f_group[ f_count_g_member ][1] = group[i][j][1];
                    f_group[ f_count_g_member ][2] = to_variable(group[i][j][1]);
                    f_count_g_member++;
                }
            }
            table_change += group_change;
            i_last = i;
        }

        // Tabel terakhir
        if(table_change < 1){
            for(int j = 0; j < count_g_member[i_last+1]; j++){
                f_group[ f_count_g_member ][0] = group[i_last+1][j][0];
                f_group[ f_count_g_member ][1] = group[i_last+1][j][1];
                f_group[ f_count_g_member ][2] = to_variable(group[i_last+1][j][1]);
                f_count_g_member++;
            }
            break;
        }

        // Pindahkan value dari temp ke real
        for(int i = 0; i < loop; i++){
            for(int j = 0; j < loop; j++){
                group[i][j][0] = t_group[i][j][0];
                group[i][j][1] = t_group[i][j][1];
                group[i][j][2] = t_group[i][j][2];
            }
            count_g_member[i] = t_count_g_member[i];
        }

        // Bersihkan template
        for(int i = 0; i < loop; i++){
            for(int j = 0; j < loop; j++){
                t_group[i][j][0] = "";
                t_group[i][j][1] = "";
                t_group[i][j][2] = "";
            }
            t_count_g_member[i] = 0;
        }

        for(int i = 0; i < jml_input; i++){
            for(int j = 0; j < count_g_member[i]; j++)
                cout << group[i][j][0] << " | " << group[i][j][1] << " | " << group[i][j][2] << "\n" ;
            cout << "-----------------------------------\n";
        }
        system("pause");
    }

    system("Pause");
    cout << "\n==============================\n";
    cout << "HASIL AKHIR DARI LANGKAH 2\n";
    cout << "==============================\n";

    // Menghapus yang duplikat
    for(int i = 1; i < f_count_g_member; i++)
        if(f_group[i - 1][1] == f_group[i][1]){
            for(int j = i; j < f_count_g_member; j++){
				f_group[j][0] = f_group[j+1][0];
				f_group[j][1] = f_group[j+1][1];
				f_group[j][2] = f_group[j+1][2];
            }
            f_group[f_count_g_member-1][0]={};
            f_group[f_count_g_member-1][1]={};
            f_group[f_count_g_member-1][2]={};
			f_count_g_member--;
        }

    for(int i = 0; i < f_count_g_member; i++)
        cout << f_group[i][0] << " | " << f_group[i][1] << " | " << f_group[i][2] << "\n" ;
    cout << "-----------------------------------\n";

    cout << "Langkah kedua selesai :) . \n";
    system("pause");
    cout << "\n================\n";
    cout << "LANGKAH KETIGA\n";
    cout << "================\n";

    cout << "\n==============================\n";
    cout << "HASIL AKHIR DARI LANGKAH 3\n";
    cout << "==============================\n";

    int col1_len = f_group[0][2].size();
    int col2_len = f_group[0][0].size();
    for(int i = 1; i < f_count_g_member; i++){
        if(col1_len <  f_group[i][2].size()) col1_len =  f_group[i][2].size();
        if(col2_len <  f_group[i][0].size()) col2_len =  f_group[i][0].size();
    }

    cout << "|PI";
    for(int i = 0; i < col1_len - 2; i++) cout << " ";
    cout << "|Minterm";
    for(int i = 0; i < col2_len - 7; i++) cout << " ";
    cout << "|";
    for(int i = 0; i < loop;i++)
        if(minterm[i] == 1){
            cout << i;
            for(int j = 0; j < total_digit(loop) - total_digit(i); j++) cout << " ";
            cout  << "|";
        }
    cout << "\n";

    for(int i = 0; i < f_count_g_member; i++){
        cout << "|" << f_group[i][2];
        for(int j = 0; j < col1_len - f_group[i][2].size(); j++) cout << " ";
        cout << "|";
        cout << f_group[i][0];
        for(int k = 0; k < col2_len - f_group[i][0].size(); k++) cout << " ";
        cout << "|" ;
        for(int j = 0; j < loop; j++){
            if(minterm[j] != 1) continue;
            cout << ((minterm_exists(to_string(j), f_group[i][0])) ? "x" : " ");
            for(int k = 0; k < total_digit(loop) - 1; k++) cout << " ";
            cout  << "|";
        }
        cout << "\n";
    }
    cout << "-----------------------------------\n";
    return 0;
}
