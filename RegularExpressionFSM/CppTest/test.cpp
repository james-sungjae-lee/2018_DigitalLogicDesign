#include <iostream>
#include <string>
using namespace std;

int index = 0;
char token;

bool solution(string regex){

  stateX:

  token = regex[index];
  index++;
  if (index == regex.length()) {
    return 0;
  }else if (token == 'x') {
    goto stateXY;
  }else{
    return 0;
  }

  stateXY:

  token = regex[index];
  index++;
  if (index == regex.length()) {
    return 0;
  }else if (token == 'y') {
    goto stateA;
  }else if (token == 'x') {
    goto stateXY;
  }else{
    return 0;
  }

  stateA:

  token = regex[index];
  index++;
  if (index == regex.length()) {
    return 0;
  }else if (token == 'a') {
    goto stateAB;
  }else{
    return 0;
  }

  stateAB:

  token = regex[index];
  index++;
  if (index == regex.length()) {
    return 0;
  }else if (token == 'b') {
    goto stateB;
  }else if (token == 'a') {
    goto stateAB;
  }else{
    return 0;
  }

  stateB:
  if (index < regex.length()){
    return 0;
  }else{
    return 1;
  }

}

int main(int argc, char const *argv[]) {
  bool a = solution("xyab");
  std::cout << a << '\n';
  return 0;
}
