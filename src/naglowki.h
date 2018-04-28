

/*
 * naglowki.h
 *
 *  Created on: 21 Dec 2017
 *      Author: pi
 */

#ifndef NAGLOWKI_H_
#define NAGLOWKI_H_




	struct nagl_eth {
		unsigned char	destination_mac[6];
		unsigned char	source_mac[6];
		unsigned short	ether_type;
	};

	struct nagl_ipv4 {
		unsigned char	ihl:4,		//inna kolejnosc
						version:4;//
		unsigned char	ecn:2,			//kolejnosc
						dscp:6;//
		unsigned short	total_length;//
		unsigned short	identification;//
		unsigned short	fragment_offset:13,//	//odwrotnie wpisana kolejnosc
						flags:3;//
		unsigned char	time_to_live;//
		unsigned char	protocol;  				//mozna sprawdzic rodzaj protokolu
		unsigned short	header_checksum;//
		unsigned char	source_ip_adress[4];//
		unsigned char	destination_ip_adress[4];//
	};

	struct nagl_icmp{
			unsigned char Type;
			unsigned char Code;
			unsigned short Checksum;		//dlugosc.16
			unsigned char Rest_of_Header:4;
			struct Buf *nowy_element;	//tylko do listy wiazanej
		};

		struct eth_ipv4_icmp {
			struct nagl_eth		naglowek_eth;		//
			struct nagl_ipv4    nagl_ipv4;
			struct nagl_icmp    nagl_icmp;
			int		bufor_danych : 32;
			};



#endif /* NAGLOWKI_H_ */


