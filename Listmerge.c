#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LISTE1BOYUT 5		//Liste boyutu degistirilebilir
#define LISTE2BOYUT 5

//Kendine referans verebilen yapi
struct listeElemani {
	int deger;					//	Her listeElemani bir deger icermektedir.
	struct listeElemani *sonrakiPtr;	//	Her listeElemani listeyi olu�turmak i�in
};								//	sonraki elemani g�sterecek pointer icerir

typedef struct listeElemani ListeElemani; 		//	listeEleman yapisi ile es anlamli
typedef ListeElemani *ListeElemaniPtr;	//	ListeElemani tip pointer tanimi

void  listeyeYaz (ListeElemaniPtr *ptr, int sayi); //S�ral� bir liste olusturma fonksiyonu
int   bosKontrolu (ListeElemaniPtr ptr);		   //Listelerin bos oldugunu kontrol edecek fonksiyon
void  listeGoruntule (ListeElemaniPtr simdikiPtr); //Olusan listeleri ekrana yazdiracak fonksiyon
ListeElemaniPtr  listeleriBirlestir(ListeElemaniPtr ListePtr1, ListeElemaniPtr ListePtr2); //iki listeyi birlestiren fonksiyon

//ana fonksiyon cagriliyor
int main(void) {
	/* Listeleri i�aret edecek pointerlar tan�mlan�yor
	 * 1.liste-2.liste ve birlesik liste icin */
	ListeElemaniPtr liste1Ptr=NULL;
	ListeElemaniPtr liste2Ptr=NULL;
	ListeElemaniPtr PtrbirlesikListe=NULL;
	int girdi;	// olusturulan liste elemanlar�na deger atamak icin tanimlandi
	size_t i;	//for dongu sayac�

	srand(time(0));							//rasgele sayi olusturma icin kullanildi
	for(i=1; i<=LISTE1BOYUT; i++){
	girdi=rand()%51; 					//0-50 arasinda bir deger rasgele belirlenir
	listeyeYaz(&liste1Ptr,girdi);
	}
	printf("1.liste: ");
	listeGoruntule(liste1Ptr);					//ilk bagli liste yazdirilir

srand(time(0));
	for(i=1; i<=LISTE2BOYUT; i++){
	girdi=rand()%101; 					//0-100 arasinda bir deger rasgele belirlenir
	listeyeYaz(&liste2Ptr,girdi);
	}
	printf("2.liste: ");
	listeGoruntule(liste2Ptr);					//ilk bagli liste yazdirilir

	printf("1 ve 2. listenin sirali birlesimi:\n ");
	PtrbirlesikListe=listeleriBirlestir(liste1Ptr, liste2Ptr);		//listeler birlestirilir ve ekrana yazdirilir
	listeGoruntule(PtrbirlesikListe);
    scanf("%d",&i);			//konsolun acik kalmasi icin eklendi

    return EXIT_SUCCESS;

    //ana fonksiyon sonlan�r
}
//ana fonksiyonda kullan�lan fonksiyonlar
ListeElemaniPtr listeleriBirlestir(ListeElemaniPtr ListePtr1, ListeElemaniPtr ListePtr2){
	ListeElemaniPtr simdikiPtr1; //Liste1 icin kullan�lacak isaretci
	ListeElemaniPtr simdikiPtr2; //Liste2 icin kullan�lacak isaretci
	ListeElemaniPtr birlesiklistePtr=NULL;//Birlestirilmis liste icin kullan�lacak isaretci
	simdikiPtr1=ListePtr1; //simdikiPtr1 ilk bagl� listeye baglan�r
	simdikiPtr2=ListePtr2; //simdikiPtr2 ikinci bagl� listeye baglan�r

	while(simdikiPtr1!=NULL){//ilk listenin son elemani bitene kadar
		if (simdikiPtr2==NULL || simdikiPtr1->deger < simdikiPtr2->deger){//liste 2 bossa veya liste1 eleman� kucukse
			listeyeYaz(&birlesiklistePtr,simdikiPtr1->deger);//birlesik listeye 1 liste elemani yazilir
			simdikiPtr1 = simdikiPtr1->sonrakiPtr;
		}
		else{
			listeyeYaz(&birlesiklistePtr,simdikiPtr2->deger); //liste2 eleman� birlesik listeye yazilir
			simdikiPtr2=simdikiPtr2->sonrakiPtr;
		}

	}//while dongu sonu
	while ( simdikiPtr2 != NULL ) {//Liste2 de eleman kald�ysa onlar birlestirilmis listeye yaz�l�r
		listeyeYaz( &birlesiklistePtr, simdikiPtr2->deger );
	 simdikiPtr2 = simdikiPtr2->sonrakiPtr;
	 }
	return birlesiklistePtr;//Birlestirilmis yeni listenin isaretcisi dondurulur


}
void  listeyeYaz (ListeElemaniPtr *ptr, int sayi){ //Listeye yazma fonksiyonu
	ListeElemaniPtr yeniPtr; //yeni eleman isaretcisi
	ListeElemaniPtr oncekiPtr;//onceki eleman isaretcisi
	ListeElemaniPtr simdikiPtr;//simdiki eleman�n isaretcisi

	yeniPtr=malloc(sizeof(ListeElemani)); //listeEleman� boyutunda bellekte bir adres ac�l�r ve yeni eleman�n adresine at�l�r

	if (yeniPtr!=NULL){ //bellekte yer ac�lm�ssa
		yeniPtr->deger=sayi; //sayi degeri yeni elemana at�l�r
		yeniPtr->sonrakiPtr=NULL;//Yeni eleman�n sonrakiPtr degeri Null yapilir
		oncekiPtr=NULL;
		simdikiPtr=*ptr;
		while(simdikiPtr!=NULL && sayi>simdikiPtr->deger){ // listede uygun yer aran�r
			oncekiPtr = simdikiPtr;
			simdikiPtr= simdikiPtr->sonrakiPtr;
		}//While sonu
		if(oncekiPtr==NULL){//Listenin bas�na eleman ekleniyorsa
			yeniPtr->sonrakiPtr= *ptr;
			*ptr= yeniPtr;
		}
		else {// onceki ve simdiki seklinde iki eleman�n aras�na eleman ekleme
			oncekiPtr->sonrakiPtr=yeniPtr;
			yeniPtr->sonrakiPtr=simdikiPtr;
		}
	}//I sonu
	else{//malloc fonksiyonundan NULL donerse alan olusturmada ve eleman eklemede hata olur
		printf("Alan olusturulamad� hata!");
	}
}
int   bosKontrolu (ListeElemaniPtr ptr){
	return ptr==NULL; //Liste dolu mu bos mu kontrolu yap�l�r
}

void  listeGoruntule (ListeElemaniPtr simdikiPtr){//isaretcisi girilien liste goruntulenir
	if (bosKontrolu(simdikiPtr)){
		printf("Liste bo�. \n");
	}
	else{
		while(simdikiPtr!=NULL){ //tum liste elemanlar� sira ile yazdirilir
			printf("%d, ", simdikiPtr->deger);
			simdikiPtr=simdikiPtr->sonrakiPtr;
		}
		printf("NULL\n");
	}
}


