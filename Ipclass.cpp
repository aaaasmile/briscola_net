// Ipclass.cpp: implementation of the __IP__ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Netmsg.h"
#include "Ipclass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//The class I use for transfering IP addresses around

//! constructors:
IP::IP(unsigned char s1, unsigned char s2, unsigned char s3, unsigned char s4)
{
	seg1 = s1;
	seg2 = s2;
	seg3 = s3;
	seg4 = s4;
}

IP::IP(IP &ip)
{
	seg1 = ip.seg1;
	seg2 = ip.seg2;
	seg3 = ip.seg3;
	seg4 = ip.seg4;
}

IP::IP(char *ip)
{
	Set(ip);
}

IP::IP(CString ip)
{
	if (ip.GetLength() > 16) 
        return;

	char Ip[16];
	strcpy(Ip, ip);
	
    Set(Ip);
}

IP::IP()
{
	seg1 = 0;
	seg2 = 0;
	seg3 = 0;
	seg4 = 0;
}

//! destructor
IP::~IP()
{

}

void IP::Set(char *ip)
{
	char ipbuf[16];
	if (  strlen(ip) > 15 ||
	      !strchr(strchr(strchr(ip, '.') + 1, '.') + 1, '.'))
	{
		seg1 = 0;
		seg2 = 0; 
		seg3 = 0; 
		seg4 = 0; 
	}
	else
	{
		strcpy(ipbuf, ip);
		seg1 = atoi(strtok(ipbuf, "."));
		seg2 = atoi(strtok(NULL, "."));
		seg3 = atoi(strtok(NULL, "."));
		seg4 = atoi(strtok(NULL, ""));
	}
	if (seg1 > 0xFF || seg2 > 0xFF || seg3 > 0xFF || seg4 > 0xFF)
	{
		seg1 = 0; 
		seg2 = 0; 
		seg3 = 0; 
		seg4 = 0;
	}
}

CString IP::Get()
{
	CString ret;
	ret.Format("%d.%d.%d.%d", seg1, seg2, seg3, seg4);
	return ret;
}


////////////////////////////////////////
//       operator == 
/*! Compare two IP addresses
// \param IP &ip : 
*/
bool IP:: operator == (IP &ip)
{
    bool bRes = false;

	if (this->seg1 == ip.seg1 && this->seg2 == ip.seg2 &&
		this->seg3 == ip.seg3 && this->seg4 == ip.seg4)
    {
		bRes =  true;
    }
	return bRes;
}

