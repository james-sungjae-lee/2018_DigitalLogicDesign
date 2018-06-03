#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
using namespace std;

int MIN_BITS;
vector<int> input_values;
bool show_mid = false;

class B_number{
public:
  int number;
  int dashes;
  bool used;
};
std::vector<std::vector<B_number> > table;
std::vector<std::vector<B_number> > p_group;
std::vector<std::vector<B_number> > final_group;
std::vector<B_number> printed_numbers;

int count_1s(int number);
void print_binary(int number);
void create_table();
void print_table();
void create_p_group();
void print_p_binary(int n, int d);
void create_final_group();
void print_final_group();
bool is_printed(B_number n);
void init();
void getinput();
int count_bits(int n);
B_number init_B_number(int n, int d, bool u);

int main(int argc, char const *argv[]) {
  getinput();
  init();
  return 0;
}

int count_1s(int number){
  int bit = 0;
  int count = 0;
  while (number > 0) {
    bit = number % 2;
    number >>= 1;
    if (bit) {
      count++;
    }
  }
  return count;
}

void print_binary(int number){
  int bits[MIN_BITS];
  int count = 0;
  while (number > 0 || count < MIN_BITS) {
    bits[count] = number % 2;
    number >>= 1;
    count ++;
  }
  for(int i=count-1;i>=0;i--){
		cout<<bits[i];
  }
}

void create_table(){
  int temp;
  B_number temp_num;
  for (size_t i = 0; i < input_values.size(); i++) {
    temp = count_1s(input_values[i]);
    if (temp + 1 > table.size()) {
      table.resize(temp + 1);
    }
    temp_num = init_B_number(input_values[i], 0, false);
    table[temp].push_back(temp_num);
  }
}

void print_table(){
  for (size_t i = 0; i < table.size(); i++) {
    cout << i;
    for (size_t j = 0; j < table[i].size(); j++) {
      std::cout << table[i][j].number << '\n';
      print_binary(table[i][j].number);
    }
  }
}

B_number init_B_number(int n, int d, bool u){
  B_number num;
  num.number = n;
  num.dashes = d;
  num.used = u;
  return num;
}

void create_p_group(){
  int temp;
  B_number temp_num;
  int temp_number, temp_dashes;
  for (size_t i = 0; i < table.size(); i++) {
    for (size_t j = 0; j < table[i].size(); j++) {
      for (size_t k = 0; k < table[i + 1].size(); k++) {
        temp_number = table[i][j].number & table[i+1][k].number;
        temp_dashes = table[i][j].number ^ table[i+1][k].number;

        if(count_1s(temp_dashes)==1) {
          table[i][j].used = true;
          table[i+1][k].used = true;


          temp = count_1s(temp_number);

          if(temp+1>p_group.size())
            p_group.resize(temp+1);

          temp_num = init_B_number(temp_number, temp_dashes, false);
          p_group[temp].push_back(temp_num);
      }
    }
  }
}
}

void print_p_group(){
  
}


















//
