#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream inStream;

int MIN_BITS;

vector<int> input_values;

class B_number{
public:
  int number;
  int dashes;
  bool used;
  bool epi;
  vector<int> used_numbers;
};

std::vector<std::vector<B_number> > table;
std::vector<std::vector<B_number> > p_group;
std::vector<std::vector<B_number> > final_group;

std::vector<B_number> printed_numbers;
std::vector<B_number> used_checked_number;
int used_numbers_group[64] = {0};

int count_1s(int number);
void print_binary(int number);
string print_p_binary(int n, int d);

B_number init_B_number(int n, int d, bool u);

void create_table();
void create_p_group();
void create_final_group();

void create_used_num_group();
void check_epi();
vector<string> print_epi();
vector<string> print_nepi();

void print_final_group();
bool is_printed(B_number n);
bool used_checked(B_number n);

vector<string> init(vector<string> answer);
int count_bits(int n);

///////////////////////////////////////////////////////

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
  for(int i = count - 1; i >= 0; i--){
    std::cout << bits[i];
  }
}

void create_table() {
  int tmp;
  B_number temp_num;
  for (size_t i = 0; i < input_values.size(); i++) {
    tmp = count_1s(input_values[i]);
    if (tmp + 1 > table.size()) {
      table.resize(tmp + 1);
    }
    temp_num = init_B_number(input_values[i], 0, false);
    table[tmp].push_back(temp_num);
  }
}

B_number init_B_number(int n, int d, bool u){
  B_number num;
  num.number = n;
  num.dashes = d;
  num.used = u;
  return num;
}

void create_p_group() {
  int tmp;
  B_number temp_num;
  int temp_number, temp_dashes;
  for (size_t i = 0; i < table.size()-1; i++) {
    for (size_t j = 0; j < table[i].size(); j++) {
      for (size_t k = 0; k < table[i+1].size(); k++) {

        temp_number = table[i][j].number & table[i+1][k].number;
        temp_dashes = table[i][j].number ^ table[i+1][k].number;

        if (count_1s(temp_dashes) == 1) {
          table[i][j].used = true;
          table[i+1][k].used = true;

          tmp = count_1s(temp_number);
          if (tmp + 1 > p_group.size()) {
            p_group.resize(tmp + 1);
          }
          temp_num = init_B_number(temp_number, temp_dashes, false);
          temp_num.used_numbers.push_back(table[i][j].number);
          temp_num.used_numbers.push_back(table[i+1][k].number);
          p_group[tmp].push_back(temp_num);
        }
      }
    }
  }
}

string print_p_binary(int n, int d){
  int bits[MIN_BITS];
  int count = 0;
  string stringOfAnswer = "";

  while (n > 0 || count < MIN_BITS) {
    if (!(d%2)) {
      bits[count] = n%2;
    }else{
      bits[count] = 2;
    }
    n >>= 1;
    d >>= 1;
    count ++;
  }
  for(int i = count - 1; i >= 0; i--){
    if (bits[i] != 2) {
      stringOfAnswer.append(to_string(bits[i]));
    }else{
      stringOfAnswer.append("-");
    }
  }
  return stringOfAnswer;
}

void create_final_group() {
  short tmp;
  B_number temp_num;
  unsigned temp_number, temp_dashes;
  for (size_t i = 0; i < p_group.size() - 1; i++) {
    for (size_t j = 0; j < p_group[i].size(); j++) {
      for (size_t k = 0; k < p_group[i + 1].size(); k++) {
        if (p_group[i][j].dashes == p_group[i+1][k].dashes) {

          temp_number = p_group[i][j].number & p_group[i+1][k].number;
          temp_dashes = p_group[i][j].number ^ p_group[i+1][k].number;

          if (count_1s(temp_dashes) == 1) {
            temp_dashes ^= p_group[i][j].dashes;

            p_group[i][j].used = true;
            p_group[i + 1][k].used = true;

            tmp = count_1s(temp_number);

            if (tmp + 1> final_group.size()) {
              final_group.resize(tmp + 1);
            }
            temp_num = init_B_number(temp_number, temp_dashes, true);
            temp_num.used_numbers.push_back(p_group[i][j].used_numbers[0]);
            temp_num.used_numbers.push_back(p_group[i][j].used_numbers[1]);
            temp_num.used_numbers.push_back(p_group[i+1][k].used_numbers[0]);
            temp_num.used_numbers.push_back(p_group[i+1][k].used_numbers[1]);
            final_group[tmp].push_back(temp_num);
          }
        }
      }
    }
  }
}

void create_used_num_group() {
  for (size_t i = 0; i < final_group.size(); i++) {
    for (size_t j = 0; j < final_group[i].size(); j++) {
      if (!used_checked(final_group[i][j])) {
        for (size_t x = 0; x < final_group[i][j].used_numbers.size(); x++) {
          used_numbers_group[final_group[i][j].used_numbers[x]]++;
          used_checked_number.push_back(final_group[i][j]);
        }
      }
    }
  }
  for (size_t i = 0; i < p_group.size(); i++) {
    for (size_t j = 0; j < p_group[i].size(); j++) {
      if (!p_group[i][j].used) {
        for (size_t x = 0; x < p_group[i][j].used_numbers.size(); x++) {
          used_numbers_group[p_group[i][j].used_numbers[x]]++;
        }
      }
    }
  }
}

bool is_printed(B_number n){
  for (size_t i = 0; i < printed_numbers.size(); i++) {
    if (n.number == printed_numbers[i].number && n.dashes == printed_numbers[i].dashes) {
      return true;
    }
  }
  return false;
}

bool used_checked(B_number n){
  for (size_t i = 0; i < used_checked_number.size(); i++) {
    if (n.number == used_checked_number[i].number && n.dashes == used_checked_number[i].dashes) {
      return true;
    }
  }
  return false;
}

void check_epi(){
  for (size_t i = 0; i < final_group.size(); i++) {
    for (size_t j = 0; j < final_group[i].size(); j++) {
      for (size_t k = 0; k < final_group[i][j].used_numbers.size(); k++) {
        for (size_t x = 0; x < 64; x++) {
          if (used_numbers_group[x] == 1) {
            if (x == final_group[i][j].used_numbers[k]) {
              final_group[i][j].epi = true;
            }
          }
        }
      }
    }
  }
  for (size_t i = 0; i < p_group.size(); i++) {
    for (size_t j = 0; j < p_group[i].size(); j++) {
      for (size_t k = 0; k < p_group[i][j].used_numbers.size(); k++) {
        for (size_t x = 0; x < 64; x++) {
          if (used_numbers_group[x] == 1) {
            if (x == p_group[i][j].used_numbers[k]) {
              p_group[i][j].epi = true;
            }
          }
        }
      }
    }
  }
  for (size_t i = 0; i < table.size(); i++) {
    for (size_t j = 0; j < table[i].size(); j++) {
      for (size_t k = 0; k < table[i][j].used_numbers.size(); k++) {
        for (size_t x = 0; x < 64; x++) {
          if (used_numbers_group[x] == 1) {
            if (x == table[i][j].used_numbers[k]) {
              table[i][j].epi = true;
            }
          }
        }
      }
    }
  }
}

vector<string> print_epi(vector<string> answer) {
  answer.push_back("EPI");
  for (size_t i = 0; i < final_group.size(); i++) {
    for (size_t j = 0; j < final_group[i].size(); j++) {
      if (!is_printed(final_group[i][j]) && final_group[i][j].epi == true) {
        answer.push_back(print_p_binary(final_group[i][j].number, final_group[i][j].dashes));
        printed_numbers.push_back(final_group[i][j]);
      }
    }
  }
  for (size_t i = 0; i < p_group.size(); i++) {
    for (size_t j = 0; j < p_group[i].size(); j++) {
      if (!p_group[i][j].used && p_group[i][j].epi == true) {
        answer.push_back(print_p_binary(p_group[i][j].number, p_group[i][j].dashes));
      }
    }
  }
  for (size_t i = 0; i < table.size(); i++) {
    for (size_t j = 0; j < table[i].size(); j++) {
      if (!table[i][j].used && table[i][j].epi == true) {
        answer.push_back(print_p_binary(table[i][j].number, table[i][j].dashes));
      }
    }
  }
  return answer;
}

vector<string> print_nepi(vector<string> answer) {
  answer.push_back("NEPI");
  for (size_t i = 0; i < final_group.size(); i++) {
    for (size_t j = 0; j < final_group[i].size(); j++) {
      if (!is_printed(final_group[i][j]) && final_group[i][j].epi == false) {
        answer.push_back(print_p_binary(final_group[i][j].number, final_group[i][j].dashes));
        printed_numbers.push_back(final_group[i][j]);
      }
    }
  }
  for (size_t i = 0; i < p_group.size(); i++) {
    for (size_t j = 0; j < p_group[i].size(); j++) {
      if (!p_group[i][j].used && p_group[i][j].epi == false ) {
        answer.push_back(print_p_binary(p_group[i][j].number, p_group[i][j].dashes));
      }
    }
  }
  for (size_t i = 0; i < table.size(); i++) {
    for (size_t j = 0; j < table[i].size(); j++) {
      if (!table[i][j].used  && table[i][j].epi == false) {
        answer.push_back(print_p_binary(table[i][j].number, table[i][j].dashes));
      }
    }
  }
  return answer;
}

vector<string> init(vector<string> answer){
  table.resize(1);
  p_group.resize(1);
  final_group.resize(1);

  create_table();
  create_p_group();
  create_final_group();

  create_used_num_group();
  check_epi();

  answer = print_epi(answer);
  answer = print_nepi(answer);
  return answer;
}

int count_bits(int n){
  int bit = 0;
  int count = 0;
  while (n > 0) {
    bit = n % 2;
    n >>= 1;
    count ++;
  }
  return count;
}

vector<string> solution(vector<int> input){
  vector<string> answer;
  MIN_BITS = input[0];
  int inNum = input[1];
  for (size_t i = 0; i < inNum; i++) {
    input_values.push_back(input[i+2]);
  }
  answer = init(answer);
  table.clear();
  p_group.clear();
  final_group.clear();
  printed_numbers.clear();
  used_checked_number.clear();
  input_values.clear();
  for (size_t i = 0; i < 64; i++) {
    used_numbers_group[i] = 0;
  }
  int i = 0;
  while (answer[i] != "NEPI") {
    i++;
  }
  sort(answer.begin() + 1, answer.begin() + i);
  sort(answer.begin() + i + 1, answer.end());
  return answer;
}

int main(int argc, char const *argv[]) {
  vector<int> input = {3, 6, 0, 1, 2, 5, 6, 7};
  vector<string> a;
  a = solution(input);
  for (size_t i = 0; i < a.size(); i++) {
    std::cout << a[i] << ' ';
  }
  return 0;
}
