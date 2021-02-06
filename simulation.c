//İsmailcan Tosun 365239 1.öğretim A grubu struct
// Uğur Şatır 314027 2. Öğretim C grubu Dosya

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//ayarlar[0]=takım sayısı,ayarlar[1]=galibiyet puanı,ayarlar[2]=beraberlik puanı,ayarlar[3]=maglubiyet puanı
int ayarlar[4],ev[200],dep[200],sayac=0;//ev ve dep dizileri maçların skorlarını tutuyor. sayac klavyeden veya dosyadan çekildiğinde artması için global tanımladık.
char evAd[200],depAd[200];//maç yapan takımların kısa adlarını tutuyor.

struct Takimlar{//takımların bilgilerini tutan yapı

    char uzunad[13];//takım isimlerini tutuyor.
    char kisa;//takımların kısa adlarını tutuyorç
    int sonuclar[8];//puanları averajları maç sayılarını dizi şeklinde tutuyoruz.
    //sonucların 0.sı mac sayısı,1.si galibiyet sayısı,2.si beraberlik sayısı,3.sü mağlubiyet sayısı,4.sü atılan gol
    //5.si yenilen gol, 6.sı averaj,7.si puan.

};

void ayarokuma();
void takimbuyukad(struct Takimlar x[]);
void takimkucukad(struct Takimlar x[]);
void PuanTablosu(struct Takimlar x[]);
void PuanTabSifir(struct Takimlar x[]);
void PuanTabBuyukAdDosya(struct Takimlar x[]);
void takimokuma(struct Takimlar x[]);
void kucukad(struct Takimlar x[]);
void karsilastirma();
void dosyasonuc(struct Takimlar x[]);
void takimyazma(struct Takimlar x[]);
void klavyeokuma(struct Takimlar x[]);
void PuanTabPuan(struct Takimlar x[]);
void PuanTabisim(struct Takimlar x[]);
void Menu1(struct Takimlar x[]);




void ayarokuma(){//ayarları dosyadan okuyup kaydediyoruz.

    FILE *dosya;
    dosya=fopen("ayarlar.txt","r");

    if(dosya==NULL){//dosya bulunamazsa hata veriyor.
        printf("Dosya bulunamadi.");
}
    else{
        for(int i=0;i<4;i++ ){//döngü yardımıyla diziye kaydediyor.
            fscanf(dosya,"%d",&ayarlar[i]);
    }


    }
    fclose(dosya);//dosyayı kapatıyor.
}



void takimbuyukad(struct Takimlar x[]){//takımları büyük harfe çeviriyor.
    for(int i=0;i<ayarlar[0];i++){
        for(int j=0;j<12;j++){
            if(x[i].uzunad[j]!='\0'){
                if(x[i].uzunad[j]>96){//değişik karakterler basmaması için sınırlandırıyoruz
                x[i].uzunad[j]-=32;//küçük harf ve büyük harf arasındaki fark 32 olduğu için 32 çıkarıyoruz.
                        }
                }
            }
        }
}

void takimkucukad(struct Takimlar x[]){//takımları küçük harfe çeviriyor.
    for(int i=0;i<ayarlar[0];i++){
        for(int j=0;j<12;j++){
            if(x[i].uzunad[j]!='\0'){
                if(x[i].uzunad[j]>64){
                x[i].uzunad[j]+=32;
                        }
                }
            }
        }
}




void PuanTablosu(struct Takimlar x[]){//puan tablosunu ekrana basıyor.

    printf("  %12s%12s%2s%2s%2s%3s%3s%5s%7s\n","TAKIMLAR",       "MAC", "G", "B", "M", "A", "Y",  "Av.",  "Puan");


    for(int i=0;i<ayarlar[0];i++){

        printf("%2d. %c %-14s    %d%3d%2d%2d%3d%3d%4d%6d\n",i+1, x[i].kisa,x[i].uzunad,x[i].sonuclar[0],x[i].sonuclar[1],x[i].sonuclar[2],x[i].sonuclar[3],x[i].sonuclar[4],x[i].sonuclar[5],x[i].sonuclar[6],x[i].sonuclar[7]);


}



}




void PuanTabSifir(struct Takimlar x[]){//puan tablosunu sıfırlıyor yani takımlar yapısındaki değerleri sıfırlıyor.

    for(int k=0;k<ayarlar[0];k++){
        for(int j=0;j<8;j++){
            x[k].sonuclar[j]=0;}}
}




void PuanTabBuyukAdDosya(struct Takimlar x[]){//puan tablosunu dosyaya yazıyor

    FILE *dosya;
    dosya=fopen("puantablosu.txt","w");

    if(dosya==NULL){
        printf("Dosya olusturulamadi.");}
    else{
        fprintf(dosya,"TAKIMLAR       MAC G B M A Y  Av  Puan\n");
        for(int i=0;i<ayarlar[0];i++){
            fprintf(dosya,"%c %s \b\t%d  %d %d %d %d %d  %d   %d\n",x[i].kisa,x[i].uzunad,x[i].sonuclar[0],x[i].sonuclar[1],x[i].sonuclar[2],x[i].sonuclar[3],x[i].sonuclar[4],x[i].sonuclar[5],x[i].sonuclar[6],x[i].sonuclar[7]);
        }
    }
    fclose(dosya);
}




void takimokuma(struct Takimlar x[]){//dosyadan takımları okuyor.
    FILE *dosya;
    dosya=fopen("takimlar.txt","r");


    if(dosya==NULL){
        printf("Dosya bulunamadi.");
            }

    else{

        for(int i=0;i<ayarlar[0];i++){
            fscanf(dosya,"%s",&*x[i].uzunad);

}
    fclose(dosya);
}

}



void kucukad(struct Takimlar x[]){//takımlara takma isim atıyor.
    int sonuc=65;//ascii tablosunda 65 a harfine denk geliyor. a dan başlayarak küçük atıyor.
    for(int i=0;i<ayarlar[0];i++){
        x[i].kisa=(sonuc);
        sonuc++;
        }
}



void karsilastirma(struct Takimlar x[],int deger){//skor işlemleri burada yapılıyor.deger değişkeni fonksiyonun nereden çağrıldığını belirtiyor.1 klavye,0 dosya.

    for(int c=0;c < sayac;c++){
        int macyapildimi=0;//her döngü başında sıfırlıyoruz bu değeri.



        for(int q=0;q<c;q++){//maçların daha önce yapılıp yapılmadığını karşılaştırıyor.
            if(evAd[c]==evAd[q] && depAd[c]==depAd[q]){//dizi olarak bakıyor
             if(deger==0){//dosyadakilere hata verdirmek için
                printf("%c ve %c daha önce maç yapmistir.\n",evAd[q],depAd[q]);}
                macyapildimi=1;

                        if(deger==1){
                            if(c==sayac-1){
                                printf("%c ile %c daha önce maç yapmıştır.\n",evAd[sayac-1],depAd[sayac-1]);


                                    macyapildimi=1;
                                    break;}
                                        }}
                

                 if(deger==1){
                            if(c==sayac-1){
                                    if(evAd[sayac-1]==depAd[sayac-1])
                                        printf("Hazırlık maçları dahil değildir.\n");}}
                if(evAd[c]==depAd[c]){
                    if(deger==0){//dosyadan aynı takımlar girilse
                        printf("Hazırlık maçları dahil değildir.\n");}
                        macyapildimi=1;
                        break;
                            }
                        }


        if(evAd[c]-64 > ayarlar[0]){//kayıtlı olmayan takımları kontrol ediyor.
            printf("%c takimi bulunamadi. (%c - %c) (Ev sahibi)\n", evAd[c],evAd[c],depAd[c]);
            macyapildimi=1;
        }

        if(depAd[c]-64 > ayarlar[0]){//kayıtlı olmayan takımları kontrol ediyor.
            printf("%c takimi bulunamadi. (%c - %c) (Deplasman)\n", depAd[c],evAd[c],depAd[c]);
            macyapildimi=1;
        }

        for(int i=0;i<ayarlar[0];i++){//skor işlemlerini yapıyor. karşılaştırıp gerekli puanları ekliyor.
             if(ev[c]>dep[c] && macyapildimi==0){
                if(evAd[c]==x[i].kisa){
                    x[i].sonuclar[0]+=1;
                    x[i].sonuclar[1]+=1;
                    x[i].sonuclar[4]+=ev[c];
                    x[i].sonuclar[5]+=dep[c];
                    x[i].sonuclar[6]+=ev[c]-dep[c];
                    x[i].sonuclar[7]+=ayarlar[1];
}
                if(depAd[c]==x[i].kisa){
                    x[i].sonuclar[0]+=1;
                    x[i].sonuclar[3]+=1;
                    x[i].sonuclar[4]+=dep[c];
                    x[i].sonuclar[5]+=ev[c];
                    x[i].sonuclar[6]+=dep[c]-ev[c];
                    x[i].sonuclar[7]+=ayarlar[3];
}

}


            if(ev[c]<dep[c] && macyapildimi==0){
                if(depAd[c]==x[i].kisa){
                    x[i].sonuclar[0]+=1;
                    x[i].sonuclar[1]+=1;
                    x[i].sonuclar[4]+=dep[c];
                    x[i].sonuclar[5]+=ev[c];
                    x[i].sonuclar[6]+=dep[c]-ev[c];
                    x[i].sonuclar[7]+=ayarlar[1];
                    }
                if(evAd[c]==x[i].kisa){
                    x[i].sonuclar[0]+=1;
                    x[i].sonuclar[3]+=1;
                    x[i].sonuclar[4]+=ev[c];
                    x[i].sonuclar[5]+=dep[c];
                    x[i].sonuclar[6]+=ev[c]-dep[c];
                    x[i].sonuclar[7]+=ayarlar[3];
                    }


            }

            if(ev[c]==dep[c] && macyapildimi==0){
                if(depAd[c]==x[i].kisa){
                    x[i].sonuclar[0]+=1;
                    x[i].sonuclar[2]+=1;
                    x[i].sonuclar[4]+=dep[c];
                    x[i].sonuclar[5]+=ev[c];
                    x[i].sonuclar[6]+=0;
                    x[i].sonuclar[7]+=ayarlar[2];
                        }
                if(evAd[c]==x[i].kisa){
                    x[i].sonuclar[0]+=1;
                    x[i].sonuclar[2]+=1;
                    x[i].sonuclar[4]+=ev[c];
                    x[i].sonuclar[5]+=dep[c];
                    x[i].sonuclar[6]+=0;
                    x[i].sonuclar[7]+=ayarlar[2];
                        }


                }
        }

    }

}


void dosyasonuc(struct Takimlar x[]){//dosyadaki maçları okuyor.

    FILE *dosya;
    dosya=fopen("maclar1.txt","r");

    if(dosya==NULL){
            printf("Dosya bulunamadi.");
    }

    else{

        while(!feof(dosya)){
            fscanf(dosya,"%s %d %s %d",&evAd[sayac],&ev[sayac],&depAd[sayac],&dep[sayac]);

            sayac++;
}
    PuanTabSifir(x);
    karsilastirma(x,0);//skor işlemleri için fonksiyona yolluyor
}
    fclose(dosya);
}


void takimyazma(struct Takimlar x[]){//takım isimlerini ekrana yazıyor
    for(int i=0;i<ayarlar[0];i++){
        printf("%s\n",x[i].uzunad);
    }
}



void klavyeokuma(struct Takimlar x[])//klavyeden girilen maçları okuyor.
{

   printf("Sonuclari giriniz:\n");


    scanf("%s %d %s %d",&evAd[sayac],&ev[sayac],&depAd[sayac],&dep[sayac]);


    sayac++;

    PuanTabSifir(x);

    karsilastirma(x,1);


}



void PuanTabPuan(struct Takimlar x[]){//puan tablosunu puana göre sıralıyor.


    struct Takimlar temp2;

    for(int j=0;j<ayarlar[0];j++){//sıralama algoritması(bubble sort)
        for(int i=0;i<(ayarlar[0]-1);i++){
            if(x[i+1].sonuclar[7]>x[i].sonuclar[7]){
                temp2=x[i+1];
                x[i+1]=x[i];
                x[i]=temp2;

    for(int i=0;i<ayarlar[0];i++){//puanlar aynıysa averaja bakıyor.
        for(int j=0;j<(ayarlar[0]);j++){
            if(x[i].sonuclar[7]==x[j].sonuclar[7]){
                if(x[i].sonuclar[6]>x[j].sonuclar[6]){
                    temp2=x[i];
                    x[i]=x[j];
                    x[j]=temp2;
                                }
                if(x[i].sonuclar[6]==x[j].sonuclar[6]){//averajlar aynıysa atılan gollere bakıyor.
                    if(x[i].sonuclar[4]>x[j].sonuclar[4]){
                        temp2=x[i];
                        x[i]=x[j];
                        x[j]=temp2;
                                    }

                            }
                        }
                    }
                }

            }
        }

    }
PuanTablosu(x);
}


void PuanTabisim(struct Takimlar x[]){//puan tablosunu isime göre sıralıyor.
    struct Takimlar temp;
        for(int j=0;j<ayarlar[0];j++){
            for(int i=0;i<(ayarlar[0]-1);i++){
                if(x[i+1].uzunad[0]<x[i].uzunad[0]){
                    temp=x[i+1];
                    x[i+1]=x[i];
                    x[i]=temp;
                }
                if(x[i+1].uzunad[0]==x[i].uzunad[0]){//ilk harfler aynıysa diğerlerine bakıyor.
                    for(int k=1;k<13;k++){
                        if(x[i+1].uzunad[k]<x[i].uzunad[k]){
                            temp=x[i+1];
                            x[i+1]=x[i];
                            x[i]=temp;

                            break;
                        }
                    }

                }

        }
    }
    PuanTablosu(x);
}


void puantabtakmaad(struct Takimlar x[]){//puan tablosunu takma isme göre sıralıyorç
    struct Takimlar temp;
        for(int i=0;i<ayarlar[0];i++){//sıralama algoritması
            for(int j=0;j<(ayarlar[0]-1);j++){
                if(x[j+1].kisa<x[j].kisa){
                    temp=x[j+1];
                    x[j+1]=x[j];
                    x[j]=temp; }
        }
    }
    PuanTablosu(x);
}


void Menu1(struct Takimlar x[]){//menü içerisinde gerekli girişler yapıldığında istenilen fonksiyonlar çağırılıyor.
    takimokuma(x);
    kucukad(x);
    int sayi,sayi2;
    int sayac1=0;
    int sayac2=0;
    do{
        printf("** Takimlari görmek için -> 1\n");
        printf("** Bos puan tablosu için -> 2\n");
        printf("** Klavyeden maç girmek için -> 3\n");
        printf("** Dosyadan maç girmek için -> 4\n");
        printf("** Puan tablosu için -> 5\n");
        printf("** Çıkmak için -> 0\n");
        scanf("%d",&sayi);
            if(sayi==1){
                takimokuma(x);
                takimyazma(x);
}
            else if(sayi==2){
            PuanTabSifir(x);
            PuanTablosu(x);
            }

            else if(sayi==3){

                klavyeokuma(x);

}
            else if(sayi==4){
                    dosyasonuc(x);


}
            else if(sayi==5){
                do{
                    printf("** Puana göre sıralamak için -> 1\n");
                    printf("** İsime göre sıralamak için -> 2\n");
                    printf("** Takma ada göre sıralamak için -> 3\n");
                    printf("** İsimler arasında büyük/kücük harf geçisi yapmak için -> 4\n");
                    printf("** Puan tablosunu dosyaya yazdirmak için -> 5\n");
                   // printf("** Sıfırlamak için -> 6\n");
                    printf("** Üst menü için -> 0\n");
                    scanf("%d",&sayi2);
                    if(sayi2==1){
                        PuanTabPuan(x);
        }
                    else if(sayi2==2){
                        PuanTabisim(x);
        }
                    else if(sayi2==3){

                        puantabtakmaad(x);
        }
                    else if(sayi2==4 ){
                        if(sayac1==0){
                            takimbuyukad(x);
                            PuanTablosu(x);
                            sayac1=1;
                        }
                        else{
                            takimkucukad(x);
                            PuanTablosu(x);
                            sayac1=0;
                        }
                    }

                    else if(sayi2==5){
                        PuanTabBuyukAdDosya(x);

                        printf("Tablo puantablosu.txt þeklinde yazdırılmıştır.\n");
        }
                  //  else if(sayi2==6){
                  //      PuanTabSifir(x);
                   //     PuanTablosu(x);
                   //     sayac2=0;
                   //     }
                    else{
                        if(sayi2!=0){
                        printf("Yanlis deger girdiniz...\n");
                        }
                    }
                }while(sayi2!=0);
}
        else if(sayi==0){
            printf("Çıkış yapıldı...");
        }
        else {
            printf("Yanlış deger girdiniz...\n");
        }
    }while(sayi!=0);

}

int main()
{
    setlocale(LC_ALL,"Turkish");//türkçe karakter kullanmak için ekleniyor.
    ayarokuma();//önce ayarları okuyor.

    struct Takimlar takim[ayarlar[0]];// takim adında dizi şeklinde struct tanımlayıp dizini eleman sayısını da ayarlardan alıyoruz.
    PuanTabSifir(takim);

    Menu1(takim);
}
