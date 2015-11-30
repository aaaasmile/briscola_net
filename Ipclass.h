// Ipclass.h: interface for the _IP_ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPCLASS_H__5D2DCF19_FD04_4678_B3FB_403D03784744__INCLUDED_)
#define AFX_IPCLASS_H__5D2DCF19_FD04_4678_B3FB_403D03784744__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IP
{
private:
public:
	unsigned char seg1;
	unsigned char seg2;
	unsigned char seg3;
	unsigned char seg4;
	CString Get();
	void Set(char *);
	bool operator == (IP &);
	IP(IP &);
	IP(char *);
	IP(CString);
	IP::IP(unsigned char, unsigned char, unsigned char, unsigned char);
	IP();
	virtual ~IP();
};


#endif // !defined(AFX_IPCLASS_H__5D2DCF19_FD04_4678_B3FB_403D03784744__INCLUDED_)
