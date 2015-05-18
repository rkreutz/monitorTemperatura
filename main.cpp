#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

void lp(int *tempo, float *temp, float *umi,char data[11],int *x); //LE TODA A PLANILHA.

//ESTATISTICAS DA PLANILHA
void stat(int tempo[100], float temp[100], float umi[100]); 
int MAX(int x[100], float y[100], float z[100]);

//GRAFICOS
void graficoI(float z[100],int y[100],char str[80],char str2[80]);
void graficoF(float z[100],float y[100]);

main()
{
    float temp[100]={},umi[100]={};
    int tempo[100]={},x=0,y;
    char data[11];
    printf("Digite a data desejada: (\"dd/mm/aaaa\")\n");
    scanf("%s",data);
    //strcpy(data,"10/08/2012");
    lp(tempo,temp,umi,data,&x);
    
    if(x==1){
    loop4:
    system("cls");
    printf("O que deseja fazer?\n");
    printf("1 - Tabela: temperatura x tempo\n2 - Tabela: umidade x tempo\n3 - Tabela: umidade x temperatura\n");
    printf("4 - Estatisticas\n0 - encerrar programa\n");
    fflush(stdin);
    scanf("%d",&y);
    //y=4;
    if(y==1) graficoI(temp,tempo,"Temperatura x Tempo","Temperatura (ºC)");
    if(y==2) graficoI(umi,tempo,"Umidade Relativa x Tempo","Umidade Relativa (%)");
    if(y==3) graficoF(umi,temp);
    if(y==4) stat(tempo,temp,umi);  
    
    if(y!=0) goto loop4;
    }
    else {
       printf("\nData nao encontrada!");
       _sleep(4000);}
    
}





void lp(int *tempo, float *temp, float *umi,char data[11],int *z)
{
     FILE *pfile;
     char str[20],c='0';
     int hora[2],minutos[2],x=0;//para o tempo.
     pfile = fopen("Sala Seca.txt","r");
     if (pfile!=NULL)
     {
         loop5:
         fscanf(pfile,"%s",str);
         if(strcmp(str,data)==0)
         {
             loop1:
                 fscanf(pfile,"%s",str);
         
                 //TEMPO
                 if(strcmp(str,"Hora:")==0)
                 {
                     if(x==0)
                     {
                          *tempo=0;
                          fscanf(pfile,"%d:%d",&hora[x],&minutos[x]);
                          x++;
                     }
                     else
                     {
                         fscanf(pfile,"%d:%d",&hora[1],&minutos[1]);
                         *tempo = (hora[1] - hora[0])*60 + minutos[1] - minutos[0];
                     }
                     *tempo++;                          
                 }
         
                 //UMIDADE
                 if(strcmp(str,"Relativa:")==0)
                 {
                     fscanf(pfile,"%f",umi);
                     *umi++;
                 }
         
                 //TEMPERATURA
                 if(strcmp(str,"Temperatura:")==0)
                 {
                     fscanf(pfile,"%f",temp);
                     *temp++;
                 }
                 c = fgetc(pfile);
                 if(strcmp(str,"@")!=0){
                 if(c!=EOF) goto loop1;}
             *z=1;
         }
         c = fgetc(pfile);
         if(c!=EOF) goto loop5;
     }
}
              
void graficoI(float z[100],int y[100],char str[80],char str2[80]) 
  { 
      int x,pp,pi,escala=160,escala2=10,maiorT=0;
      float maiorY=0;
      char string[8];
      initwindow(800,600,str,250,70); 	//abre uma janela gráfica de 800X600 pixels
      setcolor(15);
      line(10,560,790,560);
      line(30,580,30,10);
      for(x=1;x<=10;x++)
      {
          line((30+(x*80)),570,(30+(x*80)),550);//x se move 10 unidades em 80 espacos
          line(20,(560-(x*50)),40,(560-(x*50)));//y se move 10 unidades em 50 espacos
      }
      for(x=0;x<100;x++)
      {
          if(maiorT<y[x]) maiorT=y[x];
          if(maiorY<z[x]) maiorY=z[x];
      }
      while(escala*5>maiorT)
      {
          escala=escala/2;
      }
      while(escala2*5>maiorY)
      {
          escala2=escala2/2;
      }
      if(escala==0) escala=1;
      if(escala2==0) escala2=1;
      for(x=1;x<=10;x++)
      {
          sprintf(string,"%d",x*escala);
          outtextxy(18+(x*80),580,string);
      }
      for(x=1;x<=10;x++)
      {
          sprintf(string,"%d",x*escala2);
          outtextxy(5,552-(50*x),string);
      }
      outtextxy(680,530,"Tempo (minutos)");
      outtextxy(45,10,str2);
      setcolor(10);
      pp=30 + (80.0/escala)*y[0];
      pi=560 - (50.0/escala2)*z[0];      
      moveto(pp,pi);
      circle(pp,pi,4);
      sprintf(string,"%d",1);
      outtextxy(pp-4,pi-20,string);
      x=1;
      loop2:
            if(y[x]>0||z[x]>0)
            {
                 pp=(30 + (80.0/escala)*y[x]);
                 pi=(560 - (50.0/escala2)*z[x]);
                 lineto(pp,pi);
                 circle(pp,pi,4);
                 sprintf(string,"%d",x+1);
                 outtextxy(pp-4,pi-20,string);
                 x++;
                 goto loop2;
            }      
      while(!kbhit());  	// espera  até  alguma  tecla se pressiona
      closegraph();                   // fecha janela gráfica
  }

void graficoF(float z[100],float y[100])
{
      int x,pp,pi,escala=10,escala2=10;
      float maiorT=0,maiorY=0;
      char string[8];
      initwindow(800,600,"Temperatura x Umidade Relativa",250,70); 	//abre uma janela gráfica de 800X600 pixels
      setcolor(15);
      line(10,560,790,560);
      line(30,580,30,10);
      for(x=1;x<=10;x++)
      {
          line((30+(x*80)),570,(30+(x*80)),550);//x se move 10 unidades em 80 espacos
          line(20,(560-(x*50)),40,(560-(x*50)));//y se move 10 unidades em 50 espacos
      }
      for(x=0;x<100;x++)
      {
          if(maiorT<y[x]) maiorT=y[x];
          if(maiorY<z[x]) maiorY=z[x];
      }
      while(escala*5>maiorT)
      {
          escala=escala/2;
      }
      while(escala2*5>maiorY)
      {
          escala2=escala2/2;
      }
      if(escala==0) escala=1;
      if(escala2==0) escala2=1;
      for(x=1;x<=10;x++)
      {
          sprintf(string,"%d",escala*x);
          outtextxy(18+(x*80),580,string);
      }
      for(x=1;x<=10;x++)
      {
          sprintf(string,"%d",x*escala2);
          outtextxy(5,552-(50*x),string);
      }
      outtextxy(680,530,"Temperatura (ºC)");
      outtextxy(45,10,"Umidade Relativa (%)");
      setcolor(10);
      pp=30 + (80.0/escala)*y[0];
      pi=560 - (50.0/escala2)*z[0];      
      moveto(pp,pi);
      circle(pp,pi,4);
      sprintf(string,"%d",1);
      outtextxy(pp-4,pi-20,string);
      x=1;
      loop3:
            if(y[x]>0||z[x]>0)
            {
                 pp=(30 + (80.0/escala)*y[x]);
                 pi=(560 - (50.0/escala2)*z[x]);
                 lineto(pp,pi);
                 circle(pp,pi,4);
                 sprintf(string,"%d",x+1);
                 outtextxy(pp-4,pi-20,string);
                 x++;
                 goto loop3;
            }      
      while(!kbhit());  	// espera  até  alguma  tecla se pressiona
      closegraph();                   // fecha janela gráfica
  }

void stat(int tempo[100], float temp[100], float umi[100])
{
     int max,x,y;
     float somaT=0,somaU=0,medT=0,medU=0,maiorT=0,maiorU=0,menorU=100,menorT=200;
     float cor=0,somaT2=0,somaU2=0,somaTU=0;
     char nd;
     max = MAX(tempo,temp,umi);
     for(x=1;x<max;x++)
     {
         somaT+=((temp[x]+temp[x-1])/2.0)*(tempo[x]-tempo[x-1]);
         somaU+=((umi[x]+umi[x-1])/2.0)*(tempo[x]-tempo[x-1]);
     }
     medT=somaT/tempo[max-1];
     medU=somaU/tempo[max-1];
     for(x=0;x<max;x++)
     {
         if(maiorT<temp[x]) maiorT=temp[x];
         if(maiorU<umi[x]) maiorU=umi[x];
         if(menorT>temp[x]) menorT=temp[x];
         if(menorU>umi[x]) menorU=umi[x];
     }
     system("cls");
     if(max==1) printf("Existe apenas %d medicao nessa data. O programa nao ira funcionar de forma\nadequada por falta de medicoes (no minimo duas).\n\n",max);
     else printf("Existem %d medicoes feitas nessa data.\n\n",max);
     
     printf("Media de temperatura: %.1f%cC\n",medT,167);
     printf("Media de umidade: %.1f%%\n\n",medU);
     
     printf("Tempo total das medicoes: %d minutos\n\n",tempo[max-1]);
     
     printf("Primeira medicao de temperatura: %.1f%cC\n",temp[0],167);
     printf("Ultima medicao de temperatura: %.1f%cC\n",temp[max-1],167);
     printf("Primeira medicao de umidade: %.1f%%\n",umi[0]);
     printf("Ultima medicao de umidade: %.1f%%\n\n",umi[max-1]);
     
     printf("Maior medicao de temperatura: %.1f%cC\n",maiorT,167);
     printf("Menor medicao de temperatura: %.1f%cC\n",menorT,167);
     printf("Amplitude maxima da medicao de temperatura: %.1f%cC\n",(maiorT-menorT),167);
     printf("Maior medicao de umidade: %.1f%%\n",maiorU);
     printf("Menor medicao de umidade: %.1f%%\n",menorU);
     printf("Amplitude maxima da medicao de umidade: %.1f%%\n\n",(maiorU-menorU));
     
     //PROBABILIDADE DO SEMESTRE PASSADO!!!!!!
     somaT=0;somaU=0;
     for(x=0;x<max;x++)
     {
         somaT2+=(temp[x]*temp[x]);
         somaU2+=(umi[x]*umi[x]);
         somaTU+=(umi[x]*temp[x]);
         somaT+=temp[x];
         somaU+=umi[x];
     }
     cor=((max*somaTU)-(somaT*somaU))/(sqrt(((max*somaT2)-(somaT*somaT))*((max*somaU2)-(somaU*somaU))));
     printf("A temperatura explica em %.3f%% a umidade de forma linear.\n\n",(cor*cor*100));
     
     
     
     
     
     
     
     
     
     //tabela normal z: 2,58=>99%      1,65=>90%      1,96=>95%             (z*desvio)/sqrt(n)
     float varU=0,varT=0,z1=1.65,z2=1.96,z3=2.58,erroU,erroT;
     somaU=0;
     somaT=0;
     for(x=1;x<max;x++)
     {
         somaT+=((pow((((temp[x]+temp[x-1])/2.0)-medT),2))*(tempo[x]-tempo[x-1]));
         somaU+=((pow((((umi[x]+umi[x-1])/2.0)-medU),2))*(tempo[x]-tempo[x-1]));
     }
     varU=somaU/tempo[max-1];
     varT=somaT/tempo[max-1];
     erroU=(sqrt(varU)/sqrt(max));
     erroT=(sqrt(varT)/sqrt(max));
     printf("Desvio padrao da temperatura: %.3f\n\n",(sqrt(varT)));
     
     printf("Desvio padrao da umidade: %.3f\n\n",(sqrt(varU)));
     
     printf("Erro de media da temperatura a 90%% de confianca: %c%.3f%cC\n",241,z1*erroT,167);
     printf("\t\t\t\tI.C. = [ %.1f%cC , %.1f%cC ]\n\n",(medT-(z1*erroT)),167,(medT+(z1*erroT)),167);
     printf("Erro de media da temperatura a 95%% de confianca: %c%.3f%cC\n",241,z2*erroT,167);
     printf("\t\t\t\tI.C. = [ %.1f%cC , %.1f%cC ]\n\n",(medT-(z2*erroT)),167,(medT+(z2*erroT)),167);
     printf("Erro de media da temperatura a 99%% de confianca: %c%.3f%cC\n",241,z3*erroT,167);
     printf("\t\t\t\tI.C. = [ %.1f%cC , %.1f%cC ]\n\n",(medT-(z3*erroT)),167,(medT+(z3*erroT)),167);
     
     printf("Erro de media da umidade a 90%% de confianca: %c%.3f%%\n",241,z1*erroU);
     printf("\t\t\t\tI.C. = [ %.1f%% , %.1f%% ]\n\n",(medU-(z1*erroU)),(medU+(z1*erroU)));
     printf("Erro de media da umidade a 95%% de confianca: %c%.3f%%\n",241,z2*erroU);
     printf("\t\t\t\tI.C. = [ %.1f%% , %.1f%% ]\n\n",(medU-(z2*erroU)),(medU+(z2*erroU)));
     printf("Erro de media da umidade a 99%% de confianca: %c%.3f%%\n",241,z3*erroU);
     printf("\t\t\t\tI.C. = [ %.1f%% , %.1f%% ]\n\n",(medU-(z3*erroU)),(medU+(z3*erroU)));
     
     float a,b,estLog,est,u,templ[max];
     somaTU=0;somaT=0;somaU=0;medT=0;medU=0;somaT2=0;
     printf("Digite a umidade desejada para estimativa da temperatura necessaria,\ncom base nos testes.\n");
     scanf("%f",&u);
     for(x=0;x<max;x++)
     {
         somaTU+=(temp[x]*umi[x]);
         somaT+=temp[x];
         somaU+=umi[x];
         somaT2+=(temp[x]*temp[x]);
     }
     medT=somaT/max;
     medU=somaU/max;
     b=(somaTU-(medU*somaT))/(somaT2-(medT*somaT));
     a=medU - (b * medT);
     est = (u-a)/b;
     cor=pow(((max*somaTU)-(somaT*somaU))/(sqrt(((max*somaT2)-(somaT*somaT))*((max*somaU2)-(somaU*somaU)))),2);
     
     float corLog;
     for(x=0;x<max;x++) templ[x]=log(temp[x]);
     somaTU=0;somaT=0;somaU=0;medT=0;medU=0;somaT2=0;
     for(x=0;x<max;x++)
     {
         somaTU+=(templ[x]*umi[x]);
         somaT+=templ[x];
         somaU+=umi[x];
         somaT2+=(templ[x]*templ[x]);
     }
     medT=somaT/max;
     medU=somaU/max;
     b=(somaTU-(medU*somaT))/(somaT2-(medT*somaT));
     a=medU - (b * medT);
     estLog = pow(exp(u-a),1/b);
     corLog=pow(((max*somaTU)-(somaT*somaU))/(sqrt(((max*somaT2)-(somaT*somaT))*((max*somaU2)-(somaU*somaU)))),2);
     
     float corExp;
     float umil[max],estExp;
     for(x=0;x<max;x++) umil[x]=log(umi[x]);
     somaTU=0;somaT=0;somaU=0;medT=0;medU=0;somaT2=0;
     for(x=0;x<max;x++)
     {
         somaTU+=(temp[x]*umil[x]);
         somaT+=temp[x];
         somaU+=umil[x];
         somaT2+=(temp[x]*temp[x]);
     }
     medT=somaT/max;
     medU=somaU/max;
     corExp=pow(((max*somaTU)-(somaT*somaU))/(sqrt(((max*somaT2)-(somaT*somaT))*((max*somaU2)-(somaU*somaU)))),2);
     b=(somaTU-(medU*somaT))/(somaT2-(medT*somaT));
     a=exp(medU - (b * medT));
     estExp = log(u/a)/b;
     
     float corPot=0,estPot;
     somaTU=0;somaT=0;somaU=0;medT=0;medU=0;somaT2=0;
     for(x=0;x<max;x++)
     {
         somaTU+=(templ[x]*umil[x]);
         somaT+=templ[x];
         somaU+=umil[x];
         somaT2+=(templ[x]*templ[x]);
     }
     medT=somaT/max;
     medU=somaU/max;
     b=(somaTU-(medU*somaT))/(somaT2-(medT*somaT));
     a=exp(medU - (b * medT));
     corPot=pow(((max*somaTU)-(somaT*somaU))/(sqrt(((max*somaT2)-(somaT*somaT))*((max*somaU2)-(somaU*somaU)))),2);
     estPot = exp(log(u/a)/b);
     
     printf("\n\nEstimativa da temperatura para se chegar a %.1f%% de umidade: %.1f%cC.\n\t\t\t\t\t\t(Regressao Linear)\n\n",u,est,167);
     printf("Estimativa da temperatura para se chegar a %.1f%% de umidade: %.1f%cC.\n\t\t\t\t\t\t(Regressao Logaritmica)\n\n",u,estLog,167);
     printf("Estimativa da temperatura para se chegar a %.1f%% de umidade: %.1f%cC.\n\t\t\t\t\t\t(Regressao Exponencial)\n\n",u,estExp,167);
     printf("Estimativa da temperatura para se chegar a %.1f%% de umidade: %.1f%cC.\n\t\t\t\t\t\t(Regressao Potencial)\n\n\n\n",u,estPot,167);
     
     printf("Media da estimativa: %.1f",(est+estLog+estExp+estPot)/4.0);
     printf("\n\nPressione enter para voltar ao menu.");
     fflush(stdin);
     scanf("%c",&nd);
}

//Determinacao do numero de medicoes totais.
int MAX(int x[100], float y[100], float z[100])
{
     int a,b,max;
     for(a=0;a<100;a++)
     {
         b=0;
         if(x[a]==0) b+=1;
         if(y[a]==0.0) b+=1;
         if(z[a]==0.0) b+=1;
         if(b==3) 
         {
             max=a;
             a=1000;
         }
     }
     return max;
}
