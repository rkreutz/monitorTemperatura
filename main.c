#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

void lp(int *tempo, float *temp, float *umi); //LE TODA A PLANILHA.
void stat(int tempo, float temp, float umi); //ESTATISTICAS DA PLANILHA
int grafico(int x[100],int y[100]);

main()
{
    float temp[100]={},umi[100]={};
    int tempo[100]={},x,y;
    
    lp(tempo,temp,umi);
    grafico(temp,tempo);
    
    system("PAUSE");
}





void lp(int *tempo, float *temp, float *umi)
{
     FILE *pfile;
     char str[20],c;
     int hora[2],minutos[2],x=0;//para o tempo.
     pfile = fopen("Sala Seca.txt","r");
     if (pfile!=NULL)
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
         if(c!=EOF) goto loop1;
     }
}
              
int grafico(int x[100],y[100]) 
  { 
      int z[5]={1,2,3,4,5};int y[5]={3,8,7,10,1};
      int x,pp,pi;
      initwindow(800,600,"GRAFICO TESTE",250,70); 	//abre uma janela gráfica de 400X300 pixels
      setcolor(15);
      line(10,560,790,560);
      line(30,580,30,10);
      for(x=1;x<=10;x++)
      {
          line((30+(x*75)),570,(30+(x*75)),550);
          line(20,(560-(x*50)),40,(560-(x*50)));
      }
      outtextxy(95,580,"10");
      outtextxy(5,502,"10");
      outtextxy(650,580,"Umidade Relativa (%)");
      outtextxy(45,10,"Temperatura (ºC)");
      setcolor(10);
      pp=(30 + z[0]*50);
      pi=(560 - y[0]*50);
      moveto(pp,pi);
      for(x=1;x<5;x++)
      {
          pp=(30 + z[x]*50);
          pi=(560 - y[x]*50);
          lineto(pp,pi);
      }
          //moveto(10,590);   	//posiciona cursor na posição (10,10)       
      //lineto( 50, 540);       	//desenha uma linha de (10,10) até (200,50)
      while(!kbhit());  	// espera  até  alguma  tecla se pressiona
      closegraph();                   // fecha janela gráfica
      return 0; 
  }
