/*hướng dẫn kết nối:
 *chân D dò line trái trên  : nối với chân A0 của arduino
 *chân D dò line trái dưới  : nối với chân A1 của arduino
 *chân D dò line phải trên  : nối với chân A2 của arduino
 *chân D dò line phải dưới  : nối với chân A3 của arduino
 *INA-INB-INC-IND của module L298 nối với 5-6-9-10 của arduino
 *trig  và echo của SRF-04 nối với 8-7 của arduino
 */
#include <NewPing.h>

//dong co
const int outA = 5;
const int outB = 6;//banh trai

const int outC = 9;
const int outD = 10;//banh phai
//do line
#define traitren  A0
#define traiduoi  A1
#define phaitren  A2
#define phaiduoi  A3
//SRF-04
#define TRIGGER_PIN  8
#define ECHO_PIN     7
#define MAX_DISTANCE 50
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//cai dat cac gioi han toc do
int pulseRight=220;
int pulseLeft=220;
int pulseRightmin=150;
int pulseLeftmin=150;
int pulseRightmax=255;
int pulseLeftmax=255;

int temp,kc,kctruoc;  //temp: doc line; kc: doc khoang cach; kctruoc: kc truoc do
boolean tp=1; // cờ hiệu để chạy hay thoát khỏi vòng lập while
// cac che do chay
int mode=0;
//////////////////////////////////////////////////////////Chuong trinh cai dat cac thong so ban dau
void setup() 
{ 
  ////////control motor DC//////////////
  //Cac chan dieu khien motor la cac chan xuat
  pinMode(outA, OUTPUT);pinMode(outB, OUTPUT);pinMode(outC, OUTPUT);pinMode(outD, OUTPUT);
  //cac chan doc cam bien do line la cac chan doc voi dien tro noi keo len
  pinMode(traitren, INPUT_PULLUP);pinMode(phaiduoi, INPUT_PULLUP);pinMode(traiduoi, INPUT_PULLUP);pinMode(phaitren, INPUT_PULLUP);
  //dung 2 dong co
  motor_left_run(0,0);motor_right_run(0,0);
  //Khoi dong UART
  Serial.begin(9600);
  //Tao tre 2 giay; day la thoi gian quy dinh de nguoi dieu khien roi khoi khu vuc robot thi dau
  delay(2000);
  //doc lai gia tri khoang cach va do line
 dockc();
 temp=digitalRead(traitren)*8+digitalRead(phaitren)*4+digitalRead(traiduoi)*2+digitalRead(phaiduoi); //bình thường 1111b =15d
   
}
///// Chuong trinh con doc khoang cach va luu vao bien kc
void dockc()
{ //doc 2 lan de chong nhieu
  kctruoc=sonar.ping_cm();delay(10);
  kc=sonar.ping_cm();delay(10);
  while (((kc==0)&&(kctruoc!=0))||((kc!=0)&&(kctruoc==0))) {kctruoc=kc;kc=sonar.ping_cm();delay(10);}
//Serial.print("Ping: ");Serial.print(kc); Serial.println("cm");
}
//////////////////////////////
/////////Chuong trinh chinh
//////////////////////////////
void loop() 
{ Serial.println(mode);
  if (mode==0) {tp=1;timrobot();}       //che do tim doi phuong; thuc hien neu khong cham line va khong thay doi thu
  else if (mode==1) {tp=1;tancong();}   //Che do tan cong; thuc hien thi phat hien doi thu vaf khong cham line
  else if (mode==2) {tp=1;phongthu();   //Che do phong thu; thuc hien khi cac cam bien cham line trang
}
}
////////////////////
void timrobot()
{//chuong trinh xoay vong tim doi thu nhung khong duoc cham vach
  while (tp)
  {
  dockc();
  motor_left_run(pulseLeft,1);motor_right_run(pulseRight,0);//xoay vong de tim doi thu
  if (kc) {tp=0;mode=1;}  //neu phat hien doi thu thi chuyen che do tan cong
  //doc cac cam bien do line va ghi vao bien temp theo gia tri nhi phan
  temp=digitalRead(traitren)*8+digitalRead(phaitren)*4+digitalRead(traiduoi)*2+digitalRead(phaiduoi);
  if (temp!=15) {tp=0;mode=2;}  //Neu cham line thi chuyen che do phong thu
  }
}
//////////////////////
void tancong()
{
  while (tp)
  {motor_left_run(pulseLeftmax,0);motor_right_run(pulseRightmax,0); //robot chay toi voi toc do toi da
  dockc();
  if (kc==0) {tp=0;mode=0;}   //neu khong thay doi thu nua thi chuyen che do tim robot doi phuong
  temp=digitalRead(traitren)*8+digitalRead(phaitren)*4+digitalRead(traiduoi)*2+digitalRead(phaiduoi);
  if (temp!=15) {tp=0;mode=2;}//dang tan cong gap vach ngang thi chuyen che do phong thu  
  }
}
///////////////////////
void phongthu()
{ 
  while(tp){  
            //doc cac cam bien do line theo 4 bit nhi phan luu vao bien temp; neu temp =1111 (so 15) tuc la khong con cham line
            temp=digitalRead(traitren)*8+digitalRead(phaitren)*4+digitalRead(traiduoi)*2+digitalRead(phaiduoi);
              //no line
              if (temp==15) {motor_left_run(pulseLeft,1);motor_right_run(pulseRight,0);tp=0;mode=0;}//xoay và thoát
            //line trai tren//line phai 2; dang bi tan cong tu ben trai
              else if ((temp==7)||(temp==10)) {motor_left_run(100,1);motor_right_run(250,1);}
            //line phai tren //line trai 2; dang bi tan cong tu ben phai
              else if ((temp==11)||(temp==5)) {motor_left_run(250,1);motor_right_run(100,1);}
            //line trai duoi//line phai duoi
              else if ((temp==13)||(temp==14)) {motor_left_run(pulseLeft,0);motor_right_run(pulseRight,0);}
            //line tren 2
              else if (temp==3) {motor_left_run(pulseLeft,1);motor_right_run(pulseRight,1);}
            //2 led tren, 1 phai duoi hoac 1 trai duoi
              else if ((temp==1)||(temp==2)) {motor_left_run(255,1);motor_right_run(255,1);}
            //2 led duoi, 1 phai tren hoac 1 trai tren//line duoi 2
            else if ((temp==8)||(temp==4)||(temp==12)) {motor_left_run(255,0);motor_right_run(255,0);}
            else {motor_left_run(pulseLeft,1);motor_right_run(pulseRight,0);}  //cac truong hop khac thi xoay robot
    }
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
