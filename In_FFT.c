/*
// Sample code to perform I/O:
#include <stdio.h>

int main(){
	int num;
	scanf("%d", &num);              			// Reading input from STDIN
	printf("Input number is %d.\n", num);       // Writing output to STDOUT
}

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI acos(-1.0)

void read_arr(double a[],int n){
    for(int i=0;i<n;i++)
        scanf("%lf",(a+i));
}

void null_arr(double a[],int d,int n){
        for(int i=d;i<n;i++){
            a[i]=0;
        }
        
}
void make_arr(double* Wnr,double* Wni,int n){
    for(int i=0;i<n;i++){
        Wnr[i]=cos(2*i*PI/n);
        Wni[i]=sin(2*i*PI/n);
    }
}
void make_arr2(double* Wnr,double* Wni,int n){
    for(int i=0;i<n;i++){
        Wnr[i]=cos(2*i*PI/n);
        Wni[i]=-1*sin(2*i*PI/n);
    }
}
void Rec_FFT(double a[],double b[],double y1[],double y2[],int n){
    if(n==1){
        y1[0]=a[0];
        y2[0]=b[0];
        return ;
    }
    double Wnr[n],Wni[n];
    make_arr(Wnr,Wni,n);
    // Wnr=cos((2*PI)/n);
    // Wni=sin((2*PI)/n);
    double wr=1,wi=1;
    //int ae_len=(int)(ceil((double)(n)/2));
    //int ao_len=(int)(floor((double)(n)/2));
    int ae_len=n/2;
    int ao_len=n/2;
    double ae[ae_len];
    double ao[ao_len];
    double be[ae_len];
    double bo[ao_len];
    
    int x=0;
    for(int i=0;i<ae_len;i=i+1){
        ae[i]=a[x];
        x=x+2;
    }
    x=1;
    for(int i=0;i<ao_len;i=i+1){
        ao[i]=a[x];
        x=x+2;
    }
    x=0;
    for(int i=0;i<ae_len;i=i+1){
        be[i]=b[x];
        x=x+2;
    }
    x=1;
    for(int i=0;i<ao_len;i=i+1){
        bo[i]=b[x];
        x=x+2;
    }
    
    double yo[ao_len];
    double yoi[ao_len];
    //yo=(double*)malloc(ao_len*sizeof(double));
    Rec_FFT(ao,bo,yo,yoi,ao_len);
    //double *ye=Rec_FFT(ae,y,n,real);
    double ye[ae_len];
    double yei[ae_len];
    
    // ye=(double*)malloc(ae_len*sizeof(double));
    Rec_FFT(ae,be,ye,yei,ae_len);
    
    for(int k=0;k<(n/2);k++){
        y1[k]=ye[k]+(Wnr[k]*yo[k])-(Wni[k]*yoi[k]);
        y1[k+n/2]=ye[k]-((Wnr[k]*yo[k])-(Wni[k]*yoi[k]));
        
        //wr=wr*Wnr-wi*Wni;
        
        y2[k]=yei[k]+Wni[k]*yo[k]+Wnr[k]*yoi[k];
        y2[k+n/2]=yei[k]-(Wni[k]*yo[k]+Wnr[k]*yoi[k]);
        //wi=wr*Wni + wi*Wnr;
    }
    
}

void Inverse_DFT(double a[],double b[],double y1[],double y2[],int n){
    if(n==1){
        y1[0]=a[0];
        y2[0]=b[0];
        return ;
    }
    double Wnr[n],Wni[n];
    make_arr2(Wnr,Wni,n);
    // Wnr=cos((2*PI)/n);
    // Wni=sin((2*PI)/n);
    double wr=1,wi=1;
    //int ae_len=(int)(ceil((double)(n)/2));
    //int ao_len=(int)(floor((double)(n)/2));
    int ae_len=n/2;
    int ao_len=n/2;
    double ae[ae_len];
    double ao[ao_len];
    double be[ae_len];
    double bo[ao_len];
    
    int x=0;
    for(int i=0;i<ae_len;i=i+1){
        ae[i]=a[x];
        x=x+2;
    }
    x=1;
    for(int i=0;i<ao_len;i=i+1){
        ao[i]=a[x];
        x=x+2;
    }
    x=0;
    for(int i=0;i<ae_len;i=i+1){
        be[i]=b[x];
        x=x+2;
    }
    x=1;
    for(int i=0;i<ao_len;i=i+1){
        bo[i]=b[x];
        x=x+2;
    }
    
    double yo[ao_len];
    double yoi[ao_len];
    //yo=(double*)malloc(ao_len*sizeof(double));
    Inverse_DFT(ao,bo,yo,yoi,ao_len);
    //double *ye=Rec_FFT(ae,y,n,real);
    double ye[ae_len];
    double yei[ae_len];
    
    // ye=(double*)malloc(ae_len*sizeof(double));
    Inverse_DFT(ae,be,ye,yei,ae_len);
    
    for(int k=0;k<(n/2);k++){
        y1[k]=ye[k]+(Wnr[k]*yo[k])-(Wni[k]*yoi[k]);
        y1[k+n/2]=ye[k]-((Wnr[k]*yo[k])-(Wni[k]*yoi[k]));
        
        //wr=wr*Wnr-wi*Wni;
        
        y2[k]=yei[k]+Wni[k]*yo[k]+Wnr[k]*yoi[k];
        y2[k+n/2]=yei[k]-(Wni[k]*yo[k]+Wnr[k]*yoi[k]);
        //wi=wr*Wni + wi*Wnr;
    }
    
}


int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int old=n+m-1;
    int size=1;
    while(size<old){
        size=size*2;
    }
    double a_real[size],b_real[size];
    double a_im[size],b_im[size];
    int i;
    for(i=0;i<n;i++){
        scanf("%lf",&a_real[i]);
    }
    for(i=0;i<n;i++){
        scanf("%lf",&a_im[i]);
    }
    for(i=0;i<m;i++){
        scanf("%lf",&b_real[i]);
    }
    for(i=0;i<m;i++){
        scanf("%lf",&b_im[i]);
    }
    for(i=n;i<size;i++){
        a_real[i]=0.0;
        a_im[i]=0.0;
    }
     for(i=m;i<size;i++){
        b_real[i]=0.0;
        b_im[i]=0.0;
    }
    double p_real[size];
    double p_im[size];
    double q_im[size];
    double q_real[size];
    Rec_FFT(a_real,a_im,p_real,p_im,size);
    Rec_FFT(b_real,b_im,q_real,q_im,size);

    double r_real[size]; 
    double r_im[size];
    for(i=0;i<size;i++){
        r_real[i]=p_real[i]*q_real[i]-(p_im[i]*q_im[i]);
        r_im[i]=(p_real[i]*q_im[i])+(p_im[i]*q_real[i]);
    }
    double c_real[size];
    double c_im[size];
    Inverse_DFT(r_real,r_im,c_real,c_im,size);
    
    for(int i=0;i<old;i++){
        if(fabs(c_real[i])<10e-5)
            printf("0.00000 ");
        else
            printf("%0.5lf ",c_real[i]/size);
    }
    printf("\n");
    for(int i=0;i<old;i++){
         if(fabs(c_real[i])<10e-5)
            printf("0.00000 ");
        else
            printf("%0.5lf ",c_im[i]/size);
    }
    return 0;
    
}
