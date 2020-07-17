#include <iostream>
#include <limits>
#include <cmath>
#include <locale.h>

double get_time(double v, double w){

  double l = 10 + 10*int(w);
  double p = 0;
  double t = w;
  double dt = int(t+1) - t;
  
  int ticks = 0;
  
  while(p<l && ticks<1e7){
    ticks++;
    if(l-p <= v*dt){
      t += (l-p) / v;
      p = l;
    }
    else{
      t += dt;
      p = (p + v*dt) * (l + 10) / l;
      l += 10;
      dt = 1;
    }
  }
 
  return t;

}

void print_time(double t, std::string prefix=""){

  std::string suffix = "%.2f\n";

  double sec = 60*(t - int(t));
  if(t<1){
    suffix = prefix + suffix;
    printf(suffix.c_str(), sec);
    return;
  }
  
  suffix = "%dm " + suffix;
  int min = int(t)%60;
  if(t<60){
    suffix = prefix + suffix;
    printf(suffix.c_str(), min, sec);
    return;
  }

  t /= 60;
  suffix = "%dh " + suffix;
  int hrs = int(t)%24;
  if(t<24){
    suffix = prefix + suffix;
    printf(suffix.c_str(), hrs, min, sec);
    return;
  }

  t /= 24;
  suffix = "%dd " + suffix;
  int days = t;
  suffix = prefix + suffix;
  printf(suffix.c_str(), days, hrs, min, sec);

}


int main(int argc, char* argv[]){

  double vh = 1.25;
  if(argc>1) vh = std::stoi(argv[1])/60.;

  printf("%d\n", argc);
  printf("%f\n", vh);

  double ttl = get_time(1,0);
  
  double w0 = 0;
  double dw = 0.01;
  double hr = get_time(vh, w0);
  
  double eps = 1e-10;
  int steps = 0;
  while(fabs(ttl-hr)>eps*ttl && steps<20){
    steps++;
    double f1 = get_time(vh, w0 + dw);
    w0 += dw * (ttl - hr) / (f1 - hr);
    hr = get_time(vh, w0);
  }
  
  printf("Solution found in %d steps with error = %.1g\n", steps, 1-hr/ttl);
  
  setlocale(LC_NUMERIC, "");
  printf("Total distance: %'d miles\n", 10*int(ttl+1));

  print_time(ttl, "Total time: ");
  print_time(w0, "Hare waiting time: ");
         
  return 0;

}
