#include <bits/stdc++.h>    
#include "TextTable.h"                                         
using namespace std;

int main() {
  srand(time(NULL));
  vector<int> x1, x2, x3, y;
  vector<double> xn1, xn2, xn3;
  int n = 8;
  for (int i = 0; i < n; i++) {
    x1.push_back(rand() % 21);
    x2.push_back(rand() % 21);
    x3.push_back(rand() % 21);
  }

  int a0 = rand() % 21;
  int a1 = rand() % 21;
  int a2 = rand() % 21;
  int a3 = rand() % 21;

  cout << "a0 = " << a0 << "; a1 = " << a1 << "; a2 = " << a2 << "; a3 = " << a3 << ";\n";

  int minimum_x1 = *min_element(x1.begin(),x1.end());
  int maximum_x1  = *max_element(x1.begin(),x1.end());
  int minimum_x2 = *min_element(x2.begin(),x2.end());
  int maximum_x2  = *max_element(x2.begin(),x2.end());
  int minimum_x3 = *min_element(x3.begin(),x3.end());
  int maximum_x3  = *max_element(x3.begin(),x3.end());

  double x10 = (double)(minimum_x1 + maximum_x1) / 2;
  double x20 = (double)(minimum_x2 + maximum_x2) / 2;
  double x30 = (double)(minimum_x3 + maximum_x3) / 2;
                                
  double dx1 = maximum_x1 - x10;
  double dx2 = maximum_x2 - x20; 
  double dx3 = maximum_x3 - x30;

  for (int i = 0; i < n; i++) {
    xn1.push_back((double)(x1[i] - x10) / dx1);
    xn2.push_back((double)(x2[i] - x20) / dx2);
    xn3.push_back((double)(x3[i] - x30) / dx3);
  }

  for (int i = 0; i < n; i++) {
    y.push_back((double)a0 + a1 * x1[i] + a2 * x2[i] + a3 * x3[i]);
  }

  int sum_y = 0;
  for (int i = 0; i < n; i++) {
    sum_y += y[i];  
  }

  double average_y = (double) sum_y / n;
  double left_closest;

  vector<int> y_sorted(y.size());
  partial_sort_copy(begin(y), end(y), begin(y_sorted), end(y_sorted));
  for (int i = 0; i < n; i++) {
    if (y_sorted[i] <= average_y) {
      left_closest = y_sorted[i];
    }  
  }
  
  auto it = find(y.begin(), y.end(), left_closest);
  int result_index = it - y.begin();

  double Yet = a0 + a1 * x10 + a2 * x20 + a3 * x30; 
 
  TextTable t( '-', '|', '+' );

  t.add("#");
  t.add("X1");
  t.add("X2");
  t.add("X3");
  t.add("Y");
  t.add("   ");
  t.add("XN1");
  t.add("XN2");
  t.add("XN3");
  t.endOfRow();

  for (int i = 0; i < 8; i++) {
    t.add(to_string(i+1));
    t.add(to_string(x1[i]));
    t.add(to_string(x2[i]));
    t.add(to_string(x3[i]));
    t.add(to_string(y[i]));
    t.add("   ");
    t.add(to_string(xn1[i]));
    t.add(to_string(xn2[i]));
    t.add(to_string(xn3[i]));
    t.endOfRow();
  }

  t.add("x0");
  t.add(to_string(x10));
  t.add(to_string(x20));
  t.add(to_string(x30));
  t.add(to_string(Yet));
  t.add("   ");
  t.add("   ");
  t.add("   ");
  t.add("   ");
  t.endOfRow();

  t.add("dx");
  t.add(to_string(dx1));
  t.add(to_string(dx2));
  t.add(to_string(dx3));
  t.add("   ");
  t.add("   ");
  t.add("   ");
  t.add("   ");
  t.add("   ");
  t.endOfRow();

  cout << t;
  cout << "A plan point that satisfies a given optimality criterion: (" << x1[result_index] << "; " << x2[result_index] << "; " << x3[result_index] << ")\n";                                                  
  cout << "average_y = " << average_y << "; left_closest = " << left_closest << ";\n\n";
  cout << "Result: " << a0 << " + " << a1  << " * " << x1[result_index] << " + " << a2 << " * " << x2[result_index];
  cout << " + " << a3 << " * " << x3[result_index] << " = " << y[result_index] << ";\n";
}