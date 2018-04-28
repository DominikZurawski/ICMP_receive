/*
 ============================================================================
 Name        : ICMP.c
 Author      : Domino
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

#include<netinet/ip_icmp.h>   //Provides declarations for icmp header
#include "naglowki.h"



void print_icmp_packet(unsigned char* , int );
void PrintData (unsigned char* data , int Size);

int main(void) {

	//void print_packet (struct eth_ipv4_icmp pakiet_icmp);
	//definicja zmiennych
	//int s;				//deskryptor gniazda
	int i = 0;			//ile pakietow
		struct nagl_icmp *first = NULL;
		struct nagl_icmp *previous;
		struct nagl_icmp *item;
	int length = 0;		//recvfrom

	printf("Uruchamiam odbieranie ramek Ethernet.\n"); /* prints */
//Utworzenie bufora dla odbieranych ramek Ethernet
char* buffer = (void*) malloc(ETH_FRAME_LEN);
//lub !!!!!!!!!!!!!!!!!! dla drugiej opcji
//buffer = (void*) malloc(ETH_p_IP);

//Otwarcie gniazda pozwalającego na odbiór wszystkich ramek Ethernet
int iEthSockHandl = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
//Kontrola czy gniazdo zostało otwarte poprawnie, w przypadku bledu wyświetlenie komunikatu.
if (iEthSockHandl<0)
printf("Problem z otwarciem gniazda : %s!\n", strerror(errno));
//Zmienna do przechowywania rozmiaru odebranych danych
int iDataLen = 0;
//wskaznik do naglowka Eth
//unsigned char* etherhead = buffer;

//Pętla nieskończona do odbierania ramek Ethernet
//--------Opcja pierwsza---------------
	while (1){
		//odbierz ramke Eth
		iDataLen = recvfrom(iEthSockHandl, buffer, ETH_FRAME_LEN, 0, NULL, NULL);
		length = iDataLen;

		struct nagl_ipv4 *iph = (struct nagl_ipv4 *)(buffer + sizeof(struct nagl_eth));
		if (length == -1)
		printf("Nie moge odebrac ramki: %s! \n", strerror(errno));


		else if(iph->protocol == 1) 	//spr czy jest to ICMP
						{

							printf("========================================================\n");
							printf (" Ramka: %d, dlugosc: %d [B]\n", i, length);
							print_icmp_packet(buffer , length);

						}
	}
//-------------Opcja druga LISTA -----------------------
/*
while (1){
		//odbierz ramke Eth
		iDataLen = recvfrom(iEthSockHandl, buffer, ETH_FRAME_LEN, 0, NULL, NULL);
		length = iDataLen;

		struct nagl_icmp *icmp= (struct nagl_icmp *)(buffer = sizeof(struct nagl_eth));
		struct nagl_ipv4 *iph = (struct nagl_ipv4 *)(buffer + sizeof(struct nagl_eth));
		if (length == -1)
		printf("Nie moge odebrac ramki: %s! \n", strerror(errno));


		else if(iph->protocol == 1) 	//spr czy jest to ICMP
						{
							while(i<20)
							{
								item = (struct nagl_icmp*) malloc(sizeof(struct nagl_icmp));
					if (first == NULL)
						first = item;
					else
						previous->nowy_element = item;

					item->nowy_element = NULL;
					item->Type = icmp->Type;
					item->Code = icmp->Code;
					item->Checksum = icmp->Checksum;

					previous = item;
					i++;
					break;
							}
							item = first;


				if (i == 20) {
					while (i > 0 && item != NULL) {
						printf("\n");
						printf("\n#ICMP \n");
						printf("\t Type %d\n", item->Type);
						printf("\t Code: %d\n",item->Code);
						printf("\t Checksum: %d\n", item->Checksum);

						i--;
						item = item->nowy_element;
					}

					printf("\n");
					i = 0;

					while (item != NULL) {
						item = item;
						previous = item;
						item = item->nowy_element;
						free(previous);
					}
				}

						}*/
	return EXIT_SUCCESS;

}


void print_icmp_packet(unsigned char* Buffer , int Size)
{
	unsigned short iphdrlen;
	struct nagl_ipv4 *iph = (struct nagl_ipv4 *)(Buffer + sizeof(struct nagl_eth));

	iphdrlen = iph->ihl * 4;
	struct nagl_icmp *icmp = (struct nagl_icmp *)(Buffer + iphdrlen + sizeof(struct nagl_eth));
	int header_size =  sizeof(struct nagl_eth) + iphdrlen + sizeof icmp;

       printf("   |-Type : %d",(unsigned int)(icmp->Type));
       printf("   |-Code : %d",(unsigned int)(icmp->Code));
       printf("   |-Checksum : %d\n",ntohs(icmp->Checksum));
       printf("Rest of header\n");

         //Move the pointer ahead and reduce the size of string
         PrintData(Buffer + header_size , (Size - header_size) );

}

void PrintData (unsigned char* data , int Size)
{
    int i , j;
    for(i=0 ; i < Size ; i++)
    {
        if( i!=0 && i%16==0)   //if one line of hex printing is complete...
        {
            printf("         ");
            for(j=i-16 ; j<i ; j++)
            {
                if(data[j]>=32 && data[j]<=128)
                    printf("%c",(unsigned char)data[j]); //if its a number or alphabet

                else printf("."); //otherwise print a dot
            }
            printf("\n");
        }

        if(i%16==0) printf("   ");
            printf(" %02X",(unsigned int)data[i]);

        if( i==Size-1)  //print the last spaces
        {
            for(j=0;j<15-i%16;j++)
            {
              printf("   "); //extra spaces
            }

            printf("         ");

            for(j=i-i%16 ; j<=i ; j++)
            {
                if(data[j]>=32 && data[j]<=128)
                {
                  printf("%c",(unsigned char)data[j]);
                }
                else
                {
                  printf(".");
                }
            }

            printf("\n" );
        }
    }
}



