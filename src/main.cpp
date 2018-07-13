#include <Arduino.h>
#include <Wire.h>
#include <QMC5883L.h>
#include <Average.h>


QMC5883L sens_1;

Average<float> ave_x(10);
Average<float> ave_y(10);
Average<float> ave_z(10);

float x_offset; int x;
float y_offset; int y;
float z_offset; int z;
float  mT = 1.00; 


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  sens_1.init();


 sens_1.read(&x, &y, &z);
 
   x_offset = x/mT;
   y_offset = y/mT;
   z_offset = z/mT;
 
  
  
}

void loop()
{
  sens_1.read(&x, &y, &z);
  x = x/mT-x_offset;
  y = y/mT-y_offset;
  z = z/mT-z_offset;

    ave_x.push((float)x);
    ave_y.push((float)y);
    ave_z.push((float)z);

  Serial.print(ave_x.mean());
  Serial.print(" ");
  Serial.print(ave_y.mean());
  Serial.print(" ");
  Serial.println(ave_z.mean());
}