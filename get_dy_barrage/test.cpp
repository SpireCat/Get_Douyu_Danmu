
#include <iostream>
#include <string>
#include <ctime>


int main(){
  ctime t = ctime::getcurrenttime();

  int m = t.getmonth();

  cout << m << endl ;

  return 0;

}