#include <iostream>
#include <string>
using namespace std;

char token;

int solution(string regex){

  token = regex[0];
  regex.erase(regex.begin());
  if (token == 'x') {
    goto stateXY;
  }else{
    return 0;
  }

  stateXY:

  token = regex[0];
  regex.erase(regex.begin());
  if (token == 'x') {
    goto stateXY;
  }else if (token == 'y') {
    goto stateA;
  }else{
    return 0;
  }

  stateA:

  token = regex[0];
  regex.erase(regex.begin());
  if (token == 'a') {
    goto stateAB;
  }else{
    return 0;
  }

  stateAB:

  token = regex[0];
  regex.erase(regex.begin());
  if (token == 'a') {
    goto stateAB;
  }else if (token == 'b') {
    goto stateB;
  }else{
    return 0;
  }

  stateB:
  if (regex.empty()) {
    return 1;
  }else{
    return 0;
  }
}

int main(int argc, char const *argv[]) {
  std::cout << solution("xyab") << '\n';
  return 0;
}
