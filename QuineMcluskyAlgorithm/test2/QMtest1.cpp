// 2018년 5월 20일 1차 테스트
// QMalgo1.cpp 의 원본을 해석함

// 콘솔 입출력 / 벡터 자료구조 / 문자열 사용 / 스탠다드 라이브러리를 인클루드함.
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

// MIN_BITS 는 계산 / 출력되는 비트의 갯수이다.
// 가장 첫 번째 입력으로 MIN_BITS가 설정된다.
int MIN_BITS = 3;

// 입력된 값을 저장하는 곳이다. 두 번째 입력 개수에 따라 이 곳에 들어가는 값의 개수가 변화한다.
std::vector<unsigned> input_values;

// 중간 과정을 출력하기 위한 변수로 보인다. 정확한 사용은 아직 알 수 없다.
bool show_mid = false;

// B_number 라는 구조체를 정의한다. 하나의 숫자에 대한 여러 정보를 종합한다.
// 이 구조체는 실제 숫자, 대쉬(?), 숫자의 사용 여부를 담고 있다.
struct B_number{
  unsigned number;
  unsigned dashes;
  bool used;
  bool epi;
};

// 테이블이라는 이름의 벡터를 정의한다. 2차원 벡터로, 각 변수에 다른 벡터가 들어간다.
vector<vector<B_number> > table;

// p_group 이라는 이름의 2차원 벡터를 정의한다. 아마도 PI 들의 모임인 것 같다.
vector<vector<B_number> > p_group;

// final_group 이라는 이름의 2차원 벡터. 아마도 최종 결과일 것이다. 출력되는 부분.
vector<vector<B_number> > final_group;

// 한 번 출력된 결과를 다시 출력하지 않도록 체크해 두는 2차원 벡터이다.
vector<B_number> printed_numbers;

// 숫자를 받아와, 해당 숫자를 2진법으로 표현했을 때 1의 개수를 세는 함수이다.
unsigned count_1s(unsigned number);

// 10진 숫자를 2진법으로 출력하는 함수이다.
void print_binary(unsigned number);

// 테이블을 생성하는 함수이다. 여기서 숫자들이 1의 개수에 따라 정렬된다. (1이 0개, 1이 1개, 1이 2개 ...)
void create_table();

// 이렇게 만들어진 테이블을 출력하는 함수이다.
void print_table();

// B_number구조체를 생성하는 함수이다. n, d 는 각각 number, dashes에 들어가고, u는 used에 들어가는 듯 하다
B_number init_B_number(unsigned n, int d, bool u);

// 중간 과정을 생성한다고 한다. 아마도 PI 들을 생성하는 것 같다.
void create_p_group();

// 이렇게 생성된 중간 과정을 출력하는 듯 하다.
void print_p_group();

// 중간과정의 숫자를 이진 형태로 출력한다. 0 - 1 로 겹치는 것을 '-'로 변환하여 출력한다.
void print_p_binary(unsigned n, unsigned d);

// 최종 결과 테이블을 생성한다. 이 과정이 필요한 이유는 서로 다른 테이블들에서 PI들을 모아와야 하기 때문으로 보인다.
void create_final_group();

// 생성된 최종 결과 테이블을 출력한다.
void print_final_group();

// 이미 출력된 텀(B_number)를 출력하지 않도록 출력 여부를 체크하는 함수이다.
bool is_printed(B_number n);

// 테이블 생성과 출력을 진행하는 함수이다.
void init();

// 콘솔을 통해 입력을 받는 함수이다.
void getinput();

// 비트의 숫자를 센다? 숫자를 대신해 비트를 ? 잘 이해하지 못하겠다.
unsigned count_bits(unsigned n);

void check_epi(){};

void print_epi_nepi(){};

// 1. count 에 1의 개수가 들어가고, 반환되는 듯 하다.
// 2. bit 변수를 만들어, 입력받은 number를 2로 나눈 나머지를 임시로 저장한다.
// 3. 만약 나머지가 1이라면 count 증가시킴. 아니라면 그대로 진행한다.

unsigned count_1s(unsigned number){
  short bit = 0;
  int count = 0;
  while (number > 0) {
    bit = number % 2;
    number >>= 1; // right shift 연산자.입력받은 숫자를 2^1 만큼 나누어 저장.
    if (bit) {
      count++;
    }
  }
  return count;
}

// 단순하게 10진 숫자를 2진 형태로 변환한다. 배열을 사용한다.
// 1. bits 이름의 MIN_BITS 개수만큼을 가지는 배열을 생성한다.
// 2. number 가 0보다 크거나, count 횟수가 MIN_BITS 보다 작으면 반복한다.
// 3. 우선 bits의 count 위치에 number를 2로 나눈 나머지를 저장한다.
// 4. count를 증가시키고, bits의 다음 위치에 진행한다.
// 5. 위의 조건에 따라, number가 더이상 나눌 수 없게 되면 종료한다.
// 6. 위의 조건에 따라, count(bits의 저장 공간) 이 MIN_BITS 보다 크면 종료한다.
// 7. 만약 && 연산자였다면, 010 이 10 으로 표시된다. 즉, 이는 끝까지 표시하기 위함이다.

// 두 번째 조건문 for는 만들어진 bits 배열을 출력하기 위함이다.count횟수만큼 출력한다.

void print_binary(unsigned number){
  unsigned bits[MIN_BITS];
  int count = 0;

  while (number > 0 || count < MIN_BITS) {
    bits[count] = number % 2;
    number >>= 1;
    count ++;
  }
  for(int i = count-1; i >= 0; i--){
    std::cout << bits[i];
  }
}


// 테이블 생성 함수이다.
// 1. input_values 배열에 저장된 숫자를 꺼내어 테이블로 생성하는 것 같다.
// 2. 그러므로 input_values 배열의 크기만큼 반복 시행한다.
// 3. 임시로 만들어둔 변수, tmp 에 배열의 숫자의 1개수를 꺼내와 저장한다.
// 4. 만약 1의 개수가 table의 사이즈보다 크다면, resize 한다. 참고로 테이블 사이즈는 초기화되지 않았으므로, 유동적이다.
// 5. B_number 구조체에 해당 숫자를 넣는다. 구체적인 구현 사항은 나중에 나온다.
// 6. table 2차원 벡터에서 1차원은 1의 개수에 대한 레이블로 채워진다.
// 7. 각각의 1의 개수에 따라 해당하는 B_number 구조체가 여러개 저장된다.

void create_table() {
  short tmp;
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

// 생성된 최초 테이블을 출력하는 함수이다.
// 1. 우선 테이블의 1차 사이즈만큼 반복하게 된다. (1의 개수의 종류만큼이다.)
// 2. 1의 개수를 출력하고, 해당 1의 개수에 위치한 2차 사이즈만큼 다시 반복한다.
// 3. 출력 결과로는 먼저 10진수로 나타낸 B_number 의 number를 출력하고,
//    다음으로 binary 형태의 number 를 출력한다. 이는 print_binary 함수로 해결한다.
// 4. 이것이 최초 테이블 계산 결과이다.

void print_table() {
  std::cout << endl << "테이블 계산 결과" << endl;
  for (size_t i = 0; i < table.size(); i++) {
    cout << i;
    for (size_t j = 0; j < table[i].size(); j++) {
      std::cout << "\tm" << table[i][j].number << '\t';
      print_binary(table[i][j].number);
      std::cout << '\n';
    }
    std::cout << "\n---------------------------------------" << '\n';
  }
}

// B_number 를 생성하는 함수이다.
// 1. 해당 10진 숫자 n, 대쉬 d, 사용여부 u를 받아와 각각에 저장한다.
// 2. 대쉬에는 기본값 0, used 에는 기본값 false가 들어간다.
// 3. 아직까지도 대쉬의 사용처를 모르겠다.

B_number init_B_number(unsigned n, int d, bool u){
  B_number num;
  num.number = n;
  num.dashes = d;
  num.used = u;
  return num;
}

// prime implicant 를 찾아내는 가장 중요한 함수이다.
// 1. 우선 3차 반복문을 사용한다. 가장 바깥은 테이블의 1차 size 만큼 반복하므로,
//    1의 갯수에 따라 반복한다 생각할 수 있겠다.
// 2. 다음으로는 마찬가지로 1의 개수에 따른 요소의 개수만큼 반복하게 된다.
// 3. 마지막으로 해당 1의 개수보다 하나 많은 요소의 개수만큼 반복한다.
// 예를 들어, 1의 개수가 0인 요소들과 1의 개수가 1인 요소를 모두 비교하면서 반복한다.

// 다음으로 해당 숫자들을 비교하여 대쉬 ( 0 / 1 로 겹치는 부분 )이 존재하는지 판별한다.
// 겹치는 부분에 대한 판별은 XOR 비트 연산자 ^ 로 시행한다. 이 결과값이 만약 1이라면
// Prime Implicant 라고 볼 수 있을 것이다.
// 새롭게 구성한 number 에 존재하는 1의 개수를 세어서, 이를 p_group에 넣는다.

// 결과적으로 p_group에는 1차적으로 거른 prime implicant가 남게 되었다.


void create_p_group() {
  short tmp;
  B_number temp_num;
  unsigned temp_number, temp_dashes;
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
          p_group[tmp].push_back(temp_num);
        }
      }
    }
  }
}

// 위에서 생성된 p_group을 출력하는 함수이다.
// 즉, 최초의 결과 이후에 생성된 테이블들, 중간 과정을 출력한다 말할 수 있겠다.
// 2중 반복문을 사용하여 p_group 의 1차 개수만큼, 그리고 다시 1차 각각의 요소 개수만큼 반복한다.
// print_p_binary 라는 함수를 이용하여 number 와 dashes를 통합해 출력하는 듯 하다.

void print_p_group() {
  cout << endl << "MID PROCESS COMPUTATION : " << endl;

  for (size_t i = 0; i < p_group.size(); i++) {
    cout << i;
    for (size_t j = 0; j < p_group[i].size(); j++) {
      cout << "\t\t";
      print_p_binary(p_group[i][j].number, p_group[i][j].dashes);
      cout << endl;
    }
    cout << " \n ---------------------------------------------------" << endl;
  }
}

// B_number 구조체에서 number 와 dashes 를 받아와 종합적으로 출력한다.
// 기존의 binary 출력과 마찬가지로 n 이 0보다 크고, count 가 MIN_BITS보다 작으면 진행한다.
// 만약 dash를 2로 나눈 결과값이 0이라면, 즉, dash의 끝값이 0이라면 bits라는 배열에
// n 을 2로 나눈 나머지값을 저장한다. 한마디로 dash가 0일때는 n을 그대로 저장하고,
// dash가 1일때는 2를 저장한다는 것이다.

// while문이 끝나고 나면, bits 배열에는 dash 와 number를 섞은 값이 거꾸로 입력되어 있다.
// dash가 섞인 부분에는 2가 입력되어 있으므로, 만약 bits[i]가 2라면 "-" 를 출력한다.

void print_p_binary(unsigned n, unsigned d){
  unsigned bits[MIN_BITS];
  int count = 0;

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
      cout << bits[i];
    }else{
      cout << "-";
    }
  }
}

// 최종 결과를 final_group 벡터에 저장하는 함수. 매우 중요!!

// p_group의 생성 과정과 흡사하게 진행된다.
// 1. temp_dashes 로 XOR연산을 통해 새로운 dash 하나 더 찾기
// 2. bit AND 연산으로 새로운 number 찾기
// 3. 만약 새로운 dash가 존재하는 값이라면, 즉 count_1s(temp_dashes) == 1이면
//    대쉬가 하나 더 늘어나야 하므로, 현재의 dash를 temp_dashes에 추가해 준다!
// 4. final_group의 사이즈를 조정해주며, 결과로 나온 temp_num 을 추가해주면 끝이다.

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
            final_group[tmp].push_back(temp_num);
          }
        }
      }
    }
  }
}

// 위에서 생성된 final_group을 출력하는 함수이다.
// 1. 순차적으로 출력한다.
// 2. 가장 먼저 final_group의 요소들이 출력된 상태인지 확인하고 출력한다. 출력한 것은 printed_numbers에 넣는다.
// 3. 다음으로는 p_group의 요소들이 used 된 요소인지 확인하고, 아니라면 출력한다.
// 4. 마지막으로 table의 요소들 중 used된 요소인지 확인하고, 아니라면 출력한다.
// 5. 이 방법의 문제점은, table - p_group - final_group 의 3단계로만 이루어졌다는 점이며
//    3단계 이상의 상황에 대처할 수 없다는 점이다. 이를 해결하기 위한 방안을 고안해야 한다.

void print_final_group() {
  cout << endl << "Final : \n -----------------------" << endl;
  for (size_t i = 0; i < final_group.size(); i++) {
    for (size_t j = 0; j < final_group[i].size(); j++) {
      if (!is_printed(final_group[i][j])) {
        print_p_binary(final_group[i][j].number, final_group[i][j].dashes);
        cout << endl;
        printed_numbers.push_back(final_group[i][j]);
      }
    }
  }
  for (size_t i = 0; i < p_group.size(); i++) {
    for (size_t j = 0; j < p_group[i].size(); j++) {
      if (!p_group[i][j].used) {
        print_p_binary(p_group[i][j].number, p_group[i][j].dashes);
        cout << endl;
      }
    }
  }
  for (size_t i = 0; i < table.size(); i++) {
    for (size_t j = 0; j < table[i].size(); j++) {
      if (!table[i][j].used) {
        print_p_binary(table[i][j].number, table[i][j].dashes);
        cout << endl;
      }
    }
  }
  cout << "---------------------------------" << endl;
}

bool is_printed(B_number n){
  for (size_t i = 0; i < printed_numbers.size(); i++) {
    if (n.number == printed_numbers[i].number && n.dashes == printed_numbers[i].dashes) {
      return true;
    }
  }
  return false;
}

void init() {
  table.resize(1);
  p_group.resize(1);
  final_group.resize(1);

  create_table();
  print_table();
  create_p_group();
  print_p_group();
  create_final_group();
  print_final_group();
  check_epi();
  print_epi_nepi();
}

void getinput() {
  unsigned in;
  int num_bits = 0;
  std::cout << "\nInput value " << '\n' << "> ";
  while (cin >> in) {
    input_values.push_back(in);
    num_bits = count_bits(in);
    if (num_bits > MIN_BITS) {
      MIN_BITS = num_bits;
    }
    cout << "> ";
  }
}

unsigned count_bits(unsigned n){
  short bit = 0;
  int count = 0;
  while (n > 0) {
    bit = n % 2;
    n >>= 1;
    count ++;
  }
  return count;
}

int main(int argc, char const *argv[]) {
  // 일단 argc / argv 활용 부분은 건드리지 않는다. 이해하기 너무 복잡하다.

  std::cout << "\nQuine McCluskey Algorithm" << '\n';
  // 입력을 받고, 간소화 한다. 메인 함수에서는 이게 끝이다.
  std::cin >> MIN_BITS;
  getinput();
  init();
  return 0;
}














//
