#include <bits/stdc++.h>

using namespace std;

int main() {
  srand(time(NULL));
  int x1min = 10, x1max = 50, x2min = -20, x2max = 60, ymin = -950, n = 5, p1sum = 0, p2sum = 0, p3sum = 0, Rkr = 2;
  double p1avg, p2avg, p3avg, m = 5, x1sum = 0, x2sum = 0;
  vector<int> p1, p2, p3, x1 = {-1, 1, -1}, x2 = {-1, -1, 1};
  double p1dispersion, p2dispersion, p3dispersion;
  for (int i = 0; i < n; i++) {
    p1.push_back((rand() % 101) + ymin);
    p1sum += p1[i];
    p2.push_back((rand() % 101) + ymin);
    p2sum += p2[i];
    p3.push_back((rand() % 101) + ymin);
    p3sum += p3[i];
  }
  p1avg = (double)p1sum / n;
  p2avg = (double)p2sum / n;
  p3avg = (double)p3sum / n;
  p1sum = 0, p2sum = 0, p3sum = 0;
  for (int i = 0; i < n; i++) {
    p1sum += (p1[i]-p1avg) * (p1[i]-p1avg); 
    p2sum += (p2[i]-p2avg) * (p2[i]-p2avg);
    p3sum += (p3[i]-p3avg) * (p3[i]-p3avg);  
  }
  p1dispersion = (double) p1sum / n;
  p2dispersion = (double) p2sum / n;
  p3dispersion = (double) p3sum / n;
  
  double romanovskyi_deviation = 1.79;
  double Fuv1 = p1dispersion / p2dispersion;
  double Fuv2 = p3dispersion / p1dispersion;  
  double Fuv3 = p3dispersion / p2dispersion;
  double Tuv1 = ((m-2)/m)*Fuv1;
  double Tuv2 = ((m-2)/m)*Fuv2;
  double Tuv3 = ((m-2)/m)*Fuv3; 
  double Ruv1 = abs(Tuv1-1) / romanovskyi_deviation;
  double Ruv2 = abs(Tuv2-1) / romanovskyi_deviation;
  double Ruv3 = abs(Tuv3-1) / romanovskyi_deviation;

  if (Ruv1 < Rkr && Ruv2 < Rkr && Ruv3 < Rkr) {
    cout << "The dispersion is homogeneous\n";
    double a1, a2, a3, a11, a22, an0, an1, an2;
    for (int i = 0; i < 3; i++) {
      x1sum += x1[i];
      x2sum += x2[i];
    }
    double mx1 = x1sum/x1.size();
    double mx2 = x2sum/x2.size();
    double pavg = (p1avg + p2avg + p3avg) / 3;

    a1 = (double)(x1[0] * x1[0] + x1[1] * x1[1] + x1[2] * x1[2]) / 3;
    a2 = (double)(x1[0] * x2[0] + x1[1] * x2[1] + x1[2] * x2[2]) / 3;
    a3 = (double)(x2[0] * x2[0] + x2[1] * x2[1] + x2[2] * x2[2]) / 3;
    a11 = (double)(x1[0]*p1avg + x1[1]*p2avg + x1[2]*p3avg)/3;
    a22 = (double)(x2[0]*p1avg + x2[1]*p2avg + x2[2]*p3avg)/3; 

    double d1 = (double)pavg*(a1*a3-a2*a2)-mx1*(a11*a3-a2*a22)+mx2*(a11*a2-a1*a22); 
    double d2 = (double)1*(a11*a3-a2*a22)-pavg*(mx1*a3-a2*mx2)+mx2*(mx1*a22-a11*mx2);
    double d3 = (double)1*(a1*a22-a11*a2)-mx1*(mx1*a22-a11*mx2)+pavg*(mx1*a2-a1*mx2);
    double d = (double)1*(a1*a3-a2*a2)-mx1*(mx1*a3-a2*mx2)+mx2*(mx1*a2-a1*mx2);

    double b0 = d1/d;
    double b1 = d2/d;
    double b2 = d3/d;
    
    double test1 = b0 + b1*x1[0] + b2*x2[0];
    double test2 = b0 + b1*x1[1] + b2*x2[1];
    double test3 = b0 + b1*x1[2] + b2*x2[2];
    
    double dx1 = (double)abs(x1max-x1min)/2;
    double dx2 = (double)abs(x2max-x2min)/2;
    double x10 = (double)(x1max+x1min)/2;
    double x20 = (double)(x2max+x2min)/2;

    an0 = b0 - b1*(x10/dx1) - b2*(x20/dx2);
    an1 = b1/dx1;
    an2 = b2/dx2;
    
    double test11 = an0 + an1*x1min + an2*x2min;
    double test22 = an0 + an1*x1max + an2*x2min;
    double test33 = an0 + an1*x1min + an2*x2max;
   
    cout << "Experiment planning matrix:\n";
    cout << "x1   x2   y1   y2   y3   y4   y5\n";
    cout <<  x1min << " " << x2min << " " << p1[0] << " " << p1[1] << " " << p1[2] << " " << p1[3] << " " << p1[4] << "\n";
    cout <<  x1max << " " << x2min << " " << p2[0] << " " << p2[1] << " " << p2[2] << " " << p2[3] << " " << p2[4] <<  "\n";
    cout <<  x1min << "  " << x2max << " " << p3[0] << " " << p3[1] << " " << p3[2] << " " << p3[3] << " " << p3[4] << "\n";
    cout << "Normalized matrix of experiment planning:\n";
    cout << "x1   x2\n";
    cout <<  x1[0] << " " << x2[0] << "\n";
    cout << " " <<  x1[1] << " " << x2[1] << "\n";
    cout <<  x1[2] << "  " << x2[2] << "\n\n";
    cout << "Y average values: " << p1avg << ", " << p2avg << ", " << p3avg << "\n\n";
    cout << "Normalized regression equation:\n";
    cout << "y = " << b0 << " + " << b1 << " * x1 + " << b2 << " * x2\n"; 
    cout << "Let's check:\n";
    cout << b0 << " + " << b1 << " * " << x1[0] << " + " << b2 << " * " << x2[0] << " = " << test1 << "\n";
    cout << b0 << " + " << b1 << " * " << x1[1] << " + " << b2 << " * " << x2[1] << " = " << test2 << "\n";
    cout << b0 << " + " << b1 << " * " << x1[2] << " + " << b2 << " * " << x2[2] << " = " << test3 << "\n\n";
    cout << "Naturalized regression equation:\n";
    cout << "y = " << an0 << " + " << an1 << " * x1 + " << an2 << " * x2\n";
    cout << "Let's check:\n";
    cout << an0 << " + " << an1 << " * " << x1min << " + " << an2 << " * " << x2min << " = " << test11 << "\n";
    cout << an0 << " + " << an1 << " * " << x1max << " + " << an2 << " * " << x2min << " = " << test22 << "\n";
    cout << an0 << " + " << an1 << " * " << x1min << " + " << an2 << " * " << x2max << " = " << test33 << "\n\n"; 
    cout << "Therefore, the coefficients of equations are correct.\n";
  } else {
    cout << "The dispersion is inhomogeneous";
  }
}

