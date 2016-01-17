/* 5 channel temperature controlled fan controller version 1.0
 * David Ramirez
 * 12/30/2015
 */


/* References/credit: https://www.arduino.cc/en/Reference/Millis
 * http://www.learningaboutelectronics.com/Articles/LM35-temperature-sensor-circuit.php 
 * https://www.youtube.com/watch?v=b3uF3aANszw "electrodacus" from youtube "ADC noise reduction with software filter"
 */

// input sensors.
// assigned pins for the temperature sensors.
short analog1 = 4,
      analog2 = 5,
      analog3 = 6,
      analog4 = 2,
      analog5 = 3;
// Place to store average sensor value.
short avgReading1 = 0,
      avgReading2 = 0,
      avgReading3 = 0,
      avgReading4 = 0,
      avgReading5 = 0;
// assigned fans.
// Assigned the pwm pins from the Uno/Pro Mini.
short fan1 = 10,
      fan2 = 9,
      fan3 = 6,
      fan4 = 5,
      fan5 = 3;
//value to get mapped
float fValue1 = 0,
      fValue2 = 0,
      fValue3 = 0,
      fValue4 = 0,
      fValue5 = 0;
// fan speed.      
float fanspeed1 = 0,
      fanspeed2 = 0,
      fanspeed3 = 0,
      fanspeed4 = 0,
      fanspeed5 = 0;
// timed interupts to run multiple fans.
// milliseconds in time.
unsigned short cpuTime = 830,
               ambientTime = 970,
               hdbayTemp = 1070,
               auxTemp1 = 1300,
               auxTemp2 = 1400;
long previous1 = 0,
     previous2 = 0,
     previous3 = 0,
     previous4 = 0,
     previous5 = 0;
//Hold values to calculate temperature.
float millivolts1 = 0,
      millivolts2 = 0,
      millivolts3 = 0,
      millivolts4 = 0,
      millivolts5 = 0,
      celsius1 = 0,
      celsius2 = 0,
      celsius3 = 0,
      celsius4 = 0,
      celsius5 = 0;
void setup()
{
  Serial.begin(9600); // initialize serial communication at 9600 bits per second: for debugging.
  pinMode(fan1, OUTPUT); // Tells the Uno/Pro Mini what kind of pins we are going to use for output. Connect these wires to the base pin of the npn transistor.
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);
  pinMode(fan4, OUTPUT);
  pinMode(fan5, OUTPUT);
}
void loop()
/* Warning adjust temps when computer is idle first.
 * Change the 1st number(idle temp)this is slowest you want the fan to be ,and set the second number (max temp)this will be your fans max speed. example:  fanspeed1 = map(fValue,[idle temp],[max temp],0,255) 
 * If you want to be somewhat close to your motherboards sensor temperature. Add what ever you need to the end of the celsius equation like this example: celsius1 = (millivolts1 / 10)+5;
*/

{
  unsigned long currentMillis = millis(); // Returns the number of milliseconds since the Arduino board began running the current program.
  //Fan 1 cpuTime.
  const short stime1 = 40; 
  if (currentMillis - previous1 >= cpuTime); {
    int readings1[stime1];
    for (int i = 0; i < stime1; i++) {
      readings1[i] = analogRead(analog1);
      avgReading1 = ((readings1[0] + readings1[1] + readings1[2] + readings1[3] + readings1[4]
                      + readings1[5] + readings1[6] + readings1[7] + readings1[8] + readings1[9] + readings1[10]
                      + readings1[11] + readings1[12] + readings1[13] + readings1[14] + readings1[15] + readings1[16]
                      + readings1[17] + readings1[18] + readings1[19] + readings1[20] + readings1[21] + readings1[22]
                      + readings1[23] + readings1[24] + readings1[25] + readings1[26] + readings1[27] + readings1[28]
                      + readings1[29] + readings1[30] + readings1[31] + readings1[32] + readings1[33] + readings1[34]
                      + readings1[35] + readings1[36] + readings1[37] + readings1[38] + readings1[39]) / stime1);
    }
    if ((readings1[0] + 1 == readings1[1]) || (readings1[0] - 1 ==  readings1[1]) || (readings1[0] + 2 == readings1[1]) || (readings1[0] - 2 ==  readings1[1])); {
      millivolts1 = (avgReading1 / 1024.0) * 5000;
      celsius1 = (millivolts1 / 10);
      fValue1 = celsius1;
      fanspeed1 = map(fValue1, 25, 100, 0, 255); 
      analogWrite(fan1, fanspeed1);
    }
  }

  //Fan 2 ambientTime.
  if (currentMillis - previous2 >= ambientTime) {
    const short stime2 = 40; 
    int readings2[stime2];
    for (int i = 0; i < stime2; i++) {
      readings2[i] = analogRead((analog2+(analog1))/2);
      avgReading2 = ((readings2[0] + readings2[1] + readings2[2] + readings2[3] + readings2[4]
                      + readings2[5] + readings2[6] + readings2[7] + readings2[8] + readings2[9] + readings2[10]
                      + readings2[11] + readings2[12] + readings2[13] + readings2[14] + readings2[15] + readings2[16]
                      + readings2[17] + readings2[18] + readings2[19] + readings2[20] + readings2[21] + readings2[22]
                      + readings2[23] + readings2[24] + readings2[25] + readings2[26] + readings2[27] + readings2[28]
                      + readings2[29] + readings2[30] + readings2[31] + readings2[32] + readings2[33] + readings2[34]
                      + readings2[35] + readings2[36] + readings2[37] + readings2[38] + readings2[39]) / stime2);
    }
    if ((readings2[0] + 1 == readings2[1]) || (readings2[0] - 1 ==  readings2[1]) || (readings2[0] + 2 == readings2[1]) || (readings2[0] - 2 ==  readings2[1])); {
      millivolts2 = (avgReading2 / 1024.0) * 5000;
      celsius2 = (millivolts2 / 10);
      fValue2 = celsius2;
      fanspeed2 = map(fValue2, 25, 100, 0, 255); //(35.13, 69, 0, 255)
      analogWrite(fan2, fanspeed2);
    }
  }
  //Fan 3 hdbayTemp.
  if (currentMillis - previous3 >= hdbayTemp) {
    const short stime3 = 40; 
    int readings3[stime3];
    for (int i = 0; i < stime3; i++) {
      readings3[i] = analogRead((analog3+(analog1+4))/2);
      avgReading3 = ((readings3[0] + readings3[1] + readings3[2] + readings3[3] + readings3[4]
                      + readings3[5] + readings3[6] + readings3[7] + readings3[8] + readings3[9] + readings3[10]
                      + readings3[11] + readings3[12] + readings3[13] + readings3[14] + readings3[15] + readings3[16]
                      + readings3[17] + readings3[18] + readings3[19] + readings3[20] + readings3[21] + readings3[22]
                      + readings3[23] + readings3[24] + readings3[25] + readings3[26] + readings3[27] + readings3[28]
                      + readings3[29] + readings3[30] + readings3[31] + readings3[32] + readings3[33] + readings3[34]
                      + readings3[35] + readings3[36] + readings3[37] + readings3[38] + readings3[39]) / stime3);
    }
    if ((readings3[0] + 1 == readings3[1]) || (readings3[0] - 1 ==  readings3[1]) || (readings3[0] + 2 == readings3[1]) || (readings3[0] - 2 ==  readings3[1])); {
      millivolts3 = (avgReading3 / 1024.0) * 5000;
      celsius3 = (millivolts3 / 10);
      fValue3 = celsius3;
      fanspeed3 = map(fValue3, 25, 100, 0, 255);// it was (29.75, 48, 0, 255) 
      analogWrite(fan3, fanspeed3);
    }
  }
  //Fan 4 auxTemp1.
  if (currentMillis - previous4 >= auxTemp1) {
    const short stime4 = 40; 
    int readings4[stime4];
    for (int i = 0; i < stime4; i++) {
      readings4[i] = analogRead(analog4);
      avgReading4 = ((readings4[0] + readings4[1] + readings4[2] + readings4[3] + readings4[4]
                      + readings4[5] + readings4[6] + readings4[7] + readings4[8] + readings4[9] + readings4[10]
                      + readings4[11] + readings4[12] + readings4[13] + readings4[14] + readings4[15] + readings4[16]
                      + readings4[17] + readings4[18] + readings4[19] + readings4[20] + readings4[21] + readings4[22]
                      + readings4[23] + readings4[24] + readings4[25] + readings4[26] + readings4[27] + readings4[28]
                      + readings4[29] + readings4[30] + readings4[31] + readings4[32] + readings4[33] + readings4[34]
                      + readings4[35] + readings4[36] + readings4[37] + readings4[38] + readings4[39]) / stime4);
    }
    if ((readings4[0] + 1 == readings4[1]) || (readings4[0] - 1 ==  readings4[1]) || (readings4[0] + 2 == readings4[1]) || (readings4[0] - 2 ==  readings4[1])); {
      millivolts4 = (avgReading4 / 1024.0) * 5000;
      celsius4 = (millivolts4 / 10) + 3;
      fValue4 = celsius4;
      fanspeed4 = map(fValue4, 0, 0, 0, 255); //Currently set to off defualt (fValue5, 28, 80, 0, 255). change the 2nd number to adjust the sensitivity. Lower the number the more sensitive to temperature change it becomes.
      analogWrite(fan4, fanspeed4);
    }
  }
//Fan 5 auxTemp2.
  if (currentMillis - previous5 >= auxTemp2) {
    const short stime5 = 40; 
    int readings5[stime5];
    for (int i = 0; i < stime5; i++) {
      readings5[i] = analogRead(analog5);
      avgReading5 = ((readings5[0] + readings5[1] + readings5[2] + readings5[3] + readings5[4]
                      + readings5[5] + readings5[6] + readings5[7] + readings5[8] + readings5[9] + readings5[10]
                      + readings5[11] + readings5[12] + readings5[13] + readings5[14] + readings5[15] + readings5[16]
                      + readings5[17] + readings5[18] + readings5[19] + readings5[20] + readings5[21] + readings5[22]
                      + readings5[23] + readings5[24] + readings5[25] + readings5[26] + readings5[27] + readings5[28]
                      + readings5[29] + readings5[30] + readings5[31] + readings5[32] + readings5[33] + readings5[34]
                      + readings5[35] + readings5[36] + readings5[37] + readings5[38] + readings5[39]) / stime5);
    }
    if ((readings5[0] + 1 == readings5[1]) || (readings5[0] - 1 ==  readings5[1]) || (readings5[0] + 2 == readings5[1]) || (readings5[0] - 2 ==  readings5[1])); {
      millivolts5 = (avgReading5 / 1024.0) * 5000;
      celsius5 = (millivolts5 / 10) + 3;
      fValue5 = celsius5;
      fanspeed5 = map(fValue5, 0, 0, 0, 255); //Currently set to off defualt is (fValue5, 28, 80, 0, 255).
      analogWrite(fan5, fanspeed5);
    }
  }
  /* for debugging
   * comment the ones you don't need with "//"
   * uncomment the ones you want.
   */
  Serial.println("fan1");
  Serial.println(celsius1);
  Serial.println("fan2");
  Serial.println(celsius2);
  Serial.println("fan3");
  Serial.println(celsius3);
//  Serial.println("fan4");
//  Serial.println("fan5");
  
}











