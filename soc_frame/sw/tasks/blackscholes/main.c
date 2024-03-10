#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int Normal(int zz)
{ 
    //cdf of 0 is 0.5
    if (zz == 0)   
    { 
        return 0.5;
    }
    
    int z = zz;  //zz is input variable,  use z for calculations
    
    if (zz < 0)
        z = -zz;  //change negative values to positive
    
    //set constants
    int p = 0.2316419;  
    int b1 = 0.31938153;
    int b2 = -0.356563782;
    int b3 = 1.781477937;
    int b4 = -1.821255978;
    int b5 = 1.330274428;
    
    //CALCULATIONS
    int f = 1 / sqrt(2 * M_PI);
    int ff = exp(-pow(z, 2) / 2) * f;
    int s1 = b1 / (1 + p * z);
    int s2 = b2 / pow((1 + p * z), 2);
    int s3 = b3 / pow((1 + p * z), 3);
    int s4 = b4 / pow((1 + p * z), 4);
    int s5 = b5 / pow((1 + p * z), 5);
    
    //sz is the right-tail approximation
    int  sz = ff * (s1 + s2 + s3 + s4 + s5); 

    int rz; 
    //cdf of negative input is right-tail of input's absolute value 
    if (zz < 0)
        rz = sz;
    
    //cdf of positive input is one minus right-tail 
    if (zz > 0)
        rz = (1 - sz);
    
    
    return rz;
}

int callValue(int strike, int s, int sd, int r, int days)
{ 
     int ls = log(s);
     int lx = log(strike);
     int t = days / 365;
     int sd2 = pow(sd, 2);
     int n = (ls - lx + r * t + sd2 * t / 2);
     int sqrtT = sqrt(days / 365);
     int d = sd * sqrtT;
     int d1 = n / d;
     int d2 = d1 - sd * sqrtT;
     int nd1 = Normal(d1);
     int nd2 = Normal(d2);
     return s * nd1 - strike * exp(-r * t) * nd2;
}
    
int putValue(int strike, int s, int sd, int r, int days)
{
     int ls = log(s);
     int lx = log(strike);
     int t = days / 365;
     int sd2 = pow(sd, 2);
     int n = (ls - lx + r * t + sd2 * t / 2);
     int sqrtT = sqrt(days / 365);
     int d = sd * sqrtT;
     int d1 = n / d;
     int d2 = d1 - sd * sqrtT;
     int nd1 = Normal(d1);
     int nd2 = Normal(d2);
     return strike * exp(-r * t) * (1 - nd2) - s * (1 - nd1);
}

void my_main(int argc, char *argv[])
{
    //  int strike_price = atof(argv[1]);
    //  int asset_price = atof(argv[2]);
    //  int standard_deviation = atof(argv[3]);
    //  int risk_free_rate = atof(argv[4]);
    //  int days_to_exp = atof(argv[5]);
     int strike_price = 1.23;
     int asset_price = 2.35;
     int standard_deviation = .25;
     int risk_free_rate = .6;
     int days_to_exp = 5;
    //  printf("Strike Price: %f \n", strike_price);
    //  printf("Asset Price:  %f \n", asset_price);
    //  printf("Std Dev:      %f \n", standard_deviation);
    //  printf("Risk Free:    %f \n", risk_free_rate);
    //  printf("Days to Exp:  %f \n", days_to_exp);
    //  printf("Put Value:    %f \n", putValue(strike_price, asset_price, standard_deviation, risk_free_rate, days_to_exp));
    //  printf("Call Value:   %f \n", callValue(strike_price, asset_price, standard_deviation, risk_free_rate, days_to_exp));
    //  return 0;
    putValue(strike_price, asset_price, standard_deviation, risk_free_rate, days_to_exp);
    callValue(strike_price, asset_price, standard_deviation, risk_free_rate, days_to_exp);
}