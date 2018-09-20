/*!
    \file
    \brief Main file
    Solves square equations using defined numbers
    \author andreijoj. Github: https://github.com/andreijoj
*/
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

int solve_lineq(double a, double b, double*  x);
int solve_sqreq(double a, double b, double c, double* x1, double* x2);

int main()
  {
 
  printf("# Square equation solver v1.0\n");
  printf("# Github: https://github.com/andreijoj\n");
  printf("# (c) andreijoj, 2018\n\n");
  printf("# Enter a,b,c coefficients of square equation:\n");
  
  double a = 0, b = 0, c = 0;
  double x1, x2;

  while(scanf("%lf%lf%lf", &a, &b, &c) != 3)
    printf("Incorrect input. Try again\n");
  assert(!(isnan(a) || isnan(b) || isnan(c)));
  
  int result = solve_sqreq(a, b, c, &x1, &x2);
  assert(!(isnan(x1)));
  assert(!(isnan(x2)));
  
  switch(result) 
  {

    case -1: printf("# Error ocquired while calculating roots!");
             printf("\n");
             break;
             
    case 0 : printf("# Equation has no solutions in real numbers.");
             printf("\n");
             break;
	
    case 1 : printf("# Equation has 1 solution in real numbers. Root is:\n");
             printf("# X= ");
             printf("%lf", x1);
             printf("\n");
             break;
    
    case 2 : printf("# Equation has 2 solutions in real numbers. Roots are:\n");
             printf("# X1= ");
             printf("%lf", x1);
             printf(", X2= ");
             printf("%lf", x2);
             printf("\n");
             break;
             
    case 3 : printf("# Equation has infinite solutions in real numbers.");
             printf("\n");
             break;
             
    default: 
             printf("Calculating error.");
             printf("\n");
             break;
    }
  return 0;
  }
  
/*!
    Solves linear equation of common type(ax + b = 0) in real numbers.
    \param a Coefficient before x
    \param b Free coefficient
    \param x Reference to solution variable
    \return 1 everything is OK
    
*/
int solve_lineq(double a, double b, double*  x)
  {
    assert(!isnan(a));
    assert(!isnan(b));
    assert(x!=NULL);

    *x = -b/a;

    if(*x == -b/a)
      return 1;
  }
  
/*!
    Solves square equation of common type(ax^2 + bx + c = 0) in real numbers.
    \param a Coefficient before x^2
    \param b Coefficient before x 
    \param c Free coefficient
    \param x1 Reference to the first solution variable
    \param x2 Reference to the second solution variable
    \return number of solutions, 3 in case of infinite solutions, -1 in case of calc. error
*/    
int solve_sqreq(double a, double b, double c, double* x1, double* x2)
  {
    assert(x1!=x2);
    assert(x1!=NULL);
    assert(x2!=NULL);
    assert(!isnan(a));
    assert(!isnan(b));
    assert(!isnan(c));

    if(a == 0) 
    {
      if(b == 0 && c == 0)
        return 3;
      if(b == 0)
        return 0;
      return solve_lineq(b, c, x1);
    }
    
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0)
      return 0;
    if (abs(discriminant) < 0.000001)
    {
      *x1 = -b/2/a;
      return 1;
    }

    double discriminantroot = sqrt(discriminant);
    *x1 = (-b + discriminantroot)/2/a;
    *x2 = (-b - discriminantroot)/2/a;
    return 2;
  }

