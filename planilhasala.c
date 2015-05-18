#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void tempo();

int main()
{
  FILE *pfile;
  int x;
  float temp,umi;
  char info[80];
  system("cls");
  printf("Gostaria de fazer uma anotacao? (1 - sim;2 - nao)\n");
  scanf("%d",&x);
  if(x==1)
  {
     tempo();
     system("cls");
     printf("Temperatura: ");
     scanf("%f",&temp);
     printf("Umidade Relativa: ");
     scanf("%f",&umi);
     printf("Digite informacoes adicionais: ");
     fflush(stdin);
     gets(info);
     pfile = fopen("Sala Seca.txt","a+");
     fprintf(pfile,"\n\t\t\tTemperatura: %.1fºC.",temp);
     fprintf(pfile,"\n\t\t\tUmidade Relativa: %.1f%c.",umi,37);
     fprintf(pfile,"\n\t\t\t%s.",info);
  }	
  return 0;
}

void tempo()
{
   time_t rawtime;
   FILE *pfile;
   struct tm * timeinfo;
   char tempoS[80];
   char mes[3],dia[2],ano[4],hora[8],diaS[15],data[40],c,data1[40];
   int cont=0;
   time(&rawtime);
   timeinfo = localtime(&rawtime);
   strcpy(tempoS,asctime(timeinfo));
   sscanf(tempoS,"%s %s %s %s %s",diaS,mes,dia,hora,ano);
   mes[0]=mes[1];
   mes[1]=mes[2];
   if(strcmp(mes,"ann")==0) strcpy(mes,"01");
   if(strcmp(mes,"ebb")==0) strcpy(mes,"02");
   if(strcmp(mes,"arr")==0) strcpy(mes,"03");
   if(strcmp(mes,"prr")==0) strcpy(mes,"04");
   if(strcmp(mes,"ayy")==0) strcpy(mes,"05");
   if(strcmp(mes,"unn")==0) strcpy(mes,"06");
   if(strcmp(mes,"ull")==0) strcpy(mes,"07");
   if(strcmp(mes,"ugg")==0) strcpy(mes,"08");
   if(strcmp(mes,"epp")==0) strcpy(mes,"09");
   if(strcmp(mes,"ctt")==0) strcpy(mes,"10");
   if(strcmp(mes,"ovv")==0) strcpy(mes,"11");
   if(strcmp(mes,"ecc")==0) strcpy(mes,"12");
   if(strcmp(diaS,"Sun")==0) strcpy(diaS,"Domingo");
   if(strcmp(diaS,"Mon")==0) strcpy(diaS,"Segunda-feira");
   if(strcmp(diaS,"Tue")==0) strcpy(diaS,"Terca-feira");
   if(strcmp(diaS,"Wed")==0) strcpy(diaS,"Quarta-feira");
   if(strcmp(diaS,"Thi")==0) strcpy(diaS,"Quinta-feira");
   if(strcmp(diaS,"Fri")==0) strcpy(diaS,"Sexta-feira");
   if(strcmp(diaS,"Sat")==0) strcpy(diaS,"Sabado");
   sprintf(data,"%.2s/%s/%s",dia,mes,ano,diaS);
   pfile = fopen("Sala Seca.txt","r");
   if(pfile!=NULL)
   {
       while(c!=EOF)
       {
          c = fgetc(pfile);
          if(c=='@') cont+=1;
       }
       rewind(pfile);
       while(cont>0)
       {
          c = fgetc(pfile);
          if(c=='@') cont-=1;
       }
       fscanf(pfile,"%s",data1);
       fclose(pfile);
       pfile = fopen("Sala Seca.txt","a+");
       if(strcmp(data,data1)==0)
       {
           fprintf(pfile,"\n\t\tHora: %.5s",hora);
           fclose(pfile);
       }
       else
       {
           fprintf(pfile,"\n\n@ %s - %s",data,diaS);
           fprintf(pfile,"\n\t\tHora: %.5s",hora);
           fclose(pfile);
       }
   }
   else
   {
       fclose(pfile);
       pfile = fopen("Sala Seca.txt","w");
       fprintf(pfile,"@ %s - %s",data,diaS);
       fprintf(pfile,"\n\t\tHora: %.5s",hora);
       fclose(pfile);
   }
}
