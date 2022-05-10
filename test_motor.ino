/*hướng dẫn kết nối:
 *chân D dò line trái trên  : nối với chân A0 của arduino
 *chân D dò line trái dưới  : nối với chân A1 của arduino
 *chân D dò line phải trên  : nối với chân A2 của arduino
 *chân D dò line phải dưới  : nối với chân A3 của arduino
 *INA-INB-INC-IND của module L298 nối với 5-6-9-10 của arduino
 *trig  và echo của SRF-04 nối với 8-7 của arduino
 */
//dong co
const int outA = 5;
const int outB = 6;//banh trai

const int outC = 9;
const int outD = 10;//banh phai
//cai dat cac gioi han toc do
int pulseRight=220;
int pulseLeft=220;
int pulseRightmin=150;
int pulseLeftmin=150;
int pulseRightmax=255;
int pulseLeftmax=255;

//////////////////////////////////////////////////////////Chuong trinh cai dat cac thong so ban dau
void setup() 
{ 
  ////////control motor DC//////////////
  //Cac chan dieu khien motor la cac chan xuat
  pinMode(outA, OUTPUT);pinMode(outB, OUTPUT);pinMode(outC, OUTPUT);pinMode(outD, OUTPUT);
  //dung 2 dong co
  motor_left_run(0,0);motor_right_run(0,0);
  //Khoi dong UART
  Serial.begin(9600);Serial.println("Bat dau chuong trinh test dong co:");
   
}
//////////////////////////////
/////////Chuong trinh chinh
//////////////////////////////
void loop() 
{ Serial.println("Banh trai quay toi, banh phai dung...2 giay");  motor_left_run(200,0);motor_right_run(0,0); delay(2000);
Serial.println("Banh trai dung, banh phai dung...2 giay");        motor_left_run(0,0);motor_right_run(0,0); delay(2000);
Serial.println("Banh trai quay lui, banh phai dung...2 giay");    motor_left_run(200,1);motor_right_run(0,0); delay(2000);
Serial.println("Banh trai dung, banh phai dung...2 giay");        motor_left_run(0,0);motor_right_run(0,0); delay(2000);
Serial.println("Banh trai dung, banh phai quay toi...2 giay");    motor_left_run(0,0);motor_right_run(200,0); delay(2000);
Serial.println("Banh trai dung, banh phai dung...2 giay");        motor_left_run(0,0);motor_right_run(0,0); delay(2000);
Serial.println("Banh trai dung, banh phai quay lui...2 giay");    motor_left_run(0,0);motor_right_run(200,1); delay(2000);
Serial.println("Banh trai dung, banh phai dung...2 giay");        motor_left_run(0,0);motor_right_run(0,0); delay(2000);
Serial.println("Robot chay toi ...2 giay");                 motor_left_run(200,0);motor_right_run(200,0); delay(2000);
Serial.println("Robot dung...2 giay");                      motor_left_run(0,0);motor_right_run(0,0); delay(2000);
Serial.println("robot chay lui...2 giay");                  motor_left_run(200,1);motor_right_run(200,1); delay(2000);
Serial.println("Robot dung ... 2 giay");                    motor_left_run(0,0);motor_right_run(0,0); delay(2000);
Serial.println("Robot quay trai ... 2 giay");               motor_left_run(200,1);motor_right_run(200,0); delay(2000);
Serial.println("Robot dung...2 giay");                      motor_left_run(0,0);motor_right_run(0,0); delay(2000);
Serial.println("Robot quay lui...2 giay");                  motor_left_run(200,0);motor_right_run(200,1); delay(2000);
Serial.println("Robot dung...2 giay");                      motor_left_run(0,0);motor_right_run(0,0); delay(2000);
}
/////////////////////
/*********************************************************************
        SUBROTINES
*********************************************************************/
//******dieu khien banh Trai******
//********************************
void motor_left_run(int speedmotor,boolean dir)
{// speedmotor 0 --> 255 (0=min  /// 255= max)
 // dir: 0 false  --> run head (quay thuan)
 //      1 true   --> run back (quay nghich)    
 if (dir == 0)
 {// quay thuan
   analogWrite (outB, speedmotor);
   digitalWrite(outA, LOW);
 }
 else
 {// quay nghich
   analogWrite (outB, 255 - speedmotor);
   digitalWrite(outA, HIGH);
 } 
}
//******dieu khien banh Phai******
//********************************
void motor_right_run(int speedmotor,boolean dir)
{// speedmotor 0 --> 255 (0=min  /// 255= max)
 // dir: 0 false  --> run head (quay thuan)
 //      1 true   --> run back (quay nghich)    
 if (dir == 0)
 {// quay thuan
   analogWrite (outD, speedmotor);
   digitalWrite(outC, LOW);
 }
 else
 { // quay nghich
   analogWrite (outD, 255 - speedmotor);
   digitalWrite(outC, HIGH);
 } 
}
