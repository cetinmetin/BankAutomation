#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

typedef struct{
int toplamhesap;
int toplampara;
}banka;
typedef struct{
int hesapno[10];
float bakiye[10];
}hesap;
typedef struct{
int musterino;
char tc[12];
int musterituru;
int hesapsayisi;
int sira;
hesap hsp;
}musteri;

int main()
{
    menu:menu();
    goto menu;
    return 0;
}
void menu(){
    int tercih;
    printf( "-------------HOSGELDINIZ-------------\n"
            "Bireysel Musterileri Gormek Icin 0, Ticari Musterileri Gormek Icin 9\n"
            "Yeni Musteri Icin 1,\nPara Cekmek Icin 2,\nPara Yatirmak Icin 3,\n"
            "Havale Icin 4,\nBanka Gelir-Gider Raporu Icin 5,\n"
            "Cikis Icin 6' yi Tuslayin\nTercih: ");
    scanf("%d",&tercih);

    if(tercih==0){
        bireyselmusteriler();
    }
    else if(tercih==1){
        yenimusteri();
        printf("\nIsleminiz Basariyla Tamamlandi\n");
    }
    else if(tercih==2){
        paracek();
        printf("\nIsleminiz Basariyla Tamamlandi\n");
        menu();
    }
    else if(tercih==3){
        parayatir();
        printf("\nIsleminiz Basariyla Tamamlandi\n");
    }
    else if(tercih==4){
        havaleyap();
        printf("\nIsleminiz Basariyla Tamamlandi\n");
    }
    else if(tercih==5){
        bankaraporu();
        printf("\nIsleminiz Basariyla Tamamlandi\n");
    }
    else if(tercih==6){
        printf("\nIyi Gunler\n");
        exit(1);
    }
    if(tercih==9){
        ticarimusteriler();
    }
}
void bireyselmusteriler(){
        musteri m;
        FILE *fp;
        int i;
        if((fp=fopen("bireysel.txt","rb+"))==NULL){
        printf("Dosya Acilamadi");
        exit(1);
        }
        while(fread(&m,sizeof(musteri),1,fp)==1){
            printf("Sira No:%d\n",m.sira);
            printf("Tc no:%s\n",m.tc);
            printf("Musteri turu:%d\n",m.musterituru);
            printf("Musteri no:%d\n",m.musterino);
            for(i=0;i<m.hesapsayisi;i++){
                printf("Hesap No:%d\n",m.hsp.hesapno[i]);
                printf("Bakiye:%.2f\n",m.hsp.bakiye[i]);
            }
            printf("\n");
        }
}
void ticarimusteriler(){
        musteri m;
        FILE *fp;
        int i;
        if((fp=fopen("ticari.txt","rb+"))==NULL){
        printf("Dosya Acilamadi");
        exit(1);
        }
        while(fread(&m,sizeof(musteri),1,fp)==1){
            printf("Tc no:%s\n",m.tc);
            printf("Musteri turu:%d\n",m.musterituru);
            printf("Musteri no:%d\n",m.musterino);
            for(i=0;i<m.hesapsayisi;i++){
                printf("Hesap No:%d\n",m.hsp.hesapno[i]);
                printf("Bakiye:%.2f\n",m.hsp.bakiye[i]);
            }
            printf("\n");
        }
}
void yenimusteri(){
    FILE *fp;
    int secim,i;
    printf("Bireysel Musteri Olmak Icin 1, Ticari Musteri Olmak Icin 2' yi Tuslayin\nTercih: ");
    scanf("%d",&secim);
    if(secim==1){
        musteri mu;
        if((fp=fopen("bireysel.txt","ab+"))==NULL){
        printf("Dosya Acilamadi");
        exit(1);
        }
        printf("TC Kimlik Numaranizi Girin:");
        scanf("%s",mu.tc);
        mu.musterino=musterinouret();
        mu.sira=siranouret();
        mu.musterituru=1;
        printf("Kac Adet Hesap Olusturmak Istiyorsunuz?\nTercih:");
        scanf("%d",&mu.hesapsayisi);
        for(i=0;i<mu.hesapsayisi;i++){
            mu.hsp.hesapno[i]=hesapnouret();
            mu.hsp.bakiye[i]=0;
        }
        if(fwrite(&mu,sizeof(mu),1,fp) !=1){
            printf("Yazma Hatasi!");
            exit(1);
        }
        printf("\n");
        rewind(fp);
        musteri m;
        while(fread(&m,sizeof(musteri),1,fp)==1){
            printf("Sira No:%d\n",m.sira);
            printf("Tc no:%s\n",m.tc);
            printf("Musteri turu:%d\n",m.musterituru);
            printf("Musteri no:%d\n",m.musterino);
            for(i=0;i<m.hesapsayisi;i++){
                printf("Hesap No:%d\n",m.hsp.hesapno[i]);
                printf("Bakiye:%.2f\n",m.hsp.bakiye[i]);
            }
            printf("\n");
        }
        fclose(fp);
    }
    else{
        musteri mi;
        if((fp=fopen("ticari.txt","ab+"))==NULL){
        printf("Dosya Acilamadi");
        exit(1);
        }
        printf("TC Kimlik Numaranizi Girin:");
        scanf("%s",mi.tc);
        mi.musterino=musterinouret();
        mi.musterituru=2;
        printf("Kac Adet Hesap Olusturmak Istiyorsunuz?\nTercih:");
        scanf("%d",&mi.hesapsayisi);
        for(i=0;i<mi.hesapsayisi;i++){
            mi.hsp.hesapno[i]=hesapnouret();
            mi.hsp.bakiye[i]=0;
        }
        if(fwrite(&mi,sizeof(mi),1,fp) !=1){
            printf("Yazma Hatasi!");
            exit(1);
        }
        printf("\n");
        rewind(fp);
        musteri mus;
        while(fread(&mus,sizeof(musteri),1,fp)==1){
            printf("Tc no:%s\n",mus.tc);
            printf("Musteri turu:%d\n",mus.musterituru);
            printf("Musteri no:%d\n",mus.musterino);
            for(i=0;i<mus.hesapsayisi;i++){
                printf("Hesap No:%d\n",mus.hsp.hesapno[i]);
                printf("Bakiye:%.2f\n",mus.hsp.bakiye[i]);
            }
            printf("\n");
        }
    }
}
int siranouret(){
    musteri mu;
    FILE *fp;
    int i=0,gecici=1;
    if((fp=fopen("bireysel.txt","rb+"))==NULL){
        printf("Dosya Acilamadi");
        exit(1);
    }
    while(fread(&mu,sizeof(musteri),1,fp)==1){
            if(gecici==mu.sira){
                gecici++;
            }
    }
            return gecici;
}
 int musterinouret(){
    musteri m;
    FILE *fp;
    int gecici,i;
   if((fp=fopen("bireysel.txt","rb+"))==NULL){
        printf("Dosya Acilamadi");
        exit(1);
    }
    gecici=(10000+rand()%99999);
    while(fread(&m,sizeof(musteri),1,fp)==1){
            if(gecici==m.musterino){
                srand(time(NULL));
                gecici=(10000+rand()%99999);
            }
        }
        return gecici;
}
int hesapnouret(){
    musteri m;
    FILE *fp;
    int hesapno,i=0;
    if((fp=fopen("bireysel.txt","rb+"))==NULL){
        printf("Dosya Acilamadi");
        exit(1);
    }
    hesapno=(10000+rand()%99999);
    while(fread(&m,sizeof(musteri),1,fp)==1){
            if(hesapno==m.hsp.hesapno){
                srand(time(NULL));
                hesapno=(10000+rand()%99999);
            }
           }
        return hesapno;
}
void parayatir(){
    FILE *fp;
    musteri mu;
    int girilenhesapno;
    int i,yatirilantutar;
    fp=fopen("bireysel.txt","rb+");
    printf("Para Yatirmak Istediginiz Hesap Numaranizi Girin:");
    scanf("%d",&girilenhesapno);
    printf("Yatirmak Istediginiz Tutari Girin:");
    scanf("%d",&yatirilantutar);
    while(fread(&mu,sizeof(musteri),1,fp)==1){
        for(i=0;i<mu.hesapsayisi;i++){
            if(mu.hsp.hesapno[i]==girilenhesapno){
                mu.hsp.bakiye[i]+=yatirilantutar;
                rewind(fp);
                fseek(fp,sizeof(musteri)*(mu.sira-1),SEEK_CUR);
                if(fwrite(&mu,sizeof(mu),1,fp) !=1){
                    printf("Yazma Hatasi!");
                    exit(1);
                }
                rewind(fp);
                musteri m;
                fseek(fp,sizeof(musteri)*m.sira,SEEK_CUR);
                while(fread(&m,sizeof(m),1,fp)==1){
                }
            }
        }
        printf("\n");
    }
}
void paracek(){
    FILE *fp;
    musteri mu;
    int girilenhesapno,i,cekilentutar;
    fp=fopen("bireysel.txt","rb+");
    printf("Para Cekmek Istediginiz Hesap Numaranizi Girin:");
    scanf("%d",&girilenhesapno);
    printf("Cekmek Istediginiz Tutari Girin:");
    scanf("%d",&cekilentutar);
    while(fread(&mu,sizeof(musteri),1,fp)==1){
        for(i=0;i<mu.hesapsayisi;i++){
            if(mu.hsp.hesapno[i]==girilenhesapno){
                    mu.hsp.bakiye[i]-=cekilentutar;
                    rewind(fp);
                fseek(fp,sizeof(musteri)*(mu.sira-1),SEEK_CUR);
                if(fwrite(&mu,sizeof(mu),1,fp) !=1){
                    printf("Yazma Hatasi!");
                    exit(1);
                }
                rewind(fp);
                musteri m;
                fseek(fp,sizeof(musteri)*m.sira,SEEK_CUR);
                while(fread(&m,sizeof(m),1,fp)==1){
                }
            }
        }
        printf("\n");
    }
}
void havaleyap(){
    FILE *fp;
    musteri mu;
    int kendihesapno,gonderilecekhesapno,i,gonderilecektutar;
    fp=fopen("bireysel.txt","rb+");
    printf("Hesap Numaranizi Girin:");
    scanf("%d",&kendihesapno);
    printf("Gondermek Istediginiz Kisinin Hesap Numarasini Girin:");
    scanf("%d",&gonderilecekhesapno);
    printf("Gonderilecek Tutari Girin:");
    scanf("%d",&gonderilecektutar);
    while(fread(&mu,sizeof(musteri),1,fp)==1){
        for(i=0;i<mu.hesapsayisi;i++){
            if(mu.hsp.hesapno[i]==kendihesapno){
                    mu.hsp.bakiye[i]-=gonderilecektutar;
                    rewind(fp);
                fseek(fp,sizeof(musteri)*(mu.sira-1),SEEK_CUR);
                if(fwrite(&mu,sizeof(mu),1,fp) !=1){
                    printf("Yazma Hatasi!");
                    exit(1);
                }
                rewind(fp);
                musteri m;
                fseek(fp,sizeof(musteri)*m.sira,SEEK_CUR);
                while(fread(&m,sizeof(m),1,fp)==1){
                }
            }
        }
        printf("\n");
    }
    fclose(fp);
    fp=fopen("bireysel.txt","rb+");
    while(fread(&mu,sizeof(musteri),1,fp)==1){
        for(i=0;i<mu.hesapsayisi;i++){
            if(mu.hsp.hesapno[i]==gonderilecekhesapno){
                    mu.hsp.bakiye[i]+=gonderilecektutar;
                    rewind(fp);
                fseek(fp,sizeof(musteri)*(mu.sira-1),SEEK_CUR);
                if(fwrite(&mu,sizeof(mu),1,fp) !=1){
                    printf("Yazma Hatasi!");
                    exit(1);
                }
                rewind(fp);
                musteri m;
                fseek(fp,sizeof(musteri)*m.sira,SEEK_CUR);
                while(fread(&m,sizeof(m),1,fp)==1){
                }
            }
        }
        printf("\n");
    }
    fclose(fp);
}
void bankaraporu(){
        musteri m;
        banka bank;
        FILE *fp;
        int i,toplampara=0;
        if((fp=fopen("bireysel.txt","rb+"))==NULL){
        printf("Dosya Acilamadi");
        exit(1);
        }
        while(fread(&m,sizeof(musteri),1,fp)==1){
            for(i=0;i<m.hesapsayisi;i++)
                bank.toplampara+=m.hsp.bakiye[i];
            printf("\n");
            bank.toplamhesap=m.sira;
        }

        fclose(fp);
        if((fp=fopen("rapor.txt","wb+"))==NULL){
            printf("Dosya Acilamadi");
            exit(1);
        }
        fwrite(&bank,sizeof(bank),1,fp);
        rewind(fp);
        banka bnk;
        while(fread(&bnk,sizeof(banka),1,fp)==1){
            printf("Bankadaki Toplam Musteri Sayisi:%d\n",bnk.toplamhesap);
            printf("Bankadaki Toplam Para Miktari:%d\n",bnk.toplampara);
        }
}
