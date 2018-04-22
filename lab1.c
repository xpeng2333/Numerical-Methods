#include<stdio.h>
#include<math.h>
int main(){
    long top;//满足要求的上界
    double sum;//计算和

    //寻找满足要求的上界top
    //估计最小上界为1000000，然后逐次递增10000找到一个上界，使得省略的级数和小于5x10^-7,另外预留5x10^-7以消除其它因素带来上午误差
    for(top=1000000;;top+=10000){
        sum=0.0;
        long  temp=top+1000; //省略的级数经过裂项相消后大约会剩余300项，这里计算1000项以保证误差更小
        for(double j=top;j<temp;j++){
            sum+=1/j;
            if(sum>0.0000005) 
                break;            
        }
        if(sum<0.0000005) //省略的1000项级数和规定不超过5x10^-7以保证精度
            break;
    }
    
    double xTable[7]={0.0,0.5,1.0,sqrt(2.0),10.0,100.0,300.0};
    for(int i=0;i<7;i++){
        sum=0.0;
        double x=xTable[i];
        for(long k=1;k<top;k++){
            sum+=1/(k*(k+x));
        }
        printf("%6.2lf , %16.12e\n",x,sum);
    }
    return 0;
}