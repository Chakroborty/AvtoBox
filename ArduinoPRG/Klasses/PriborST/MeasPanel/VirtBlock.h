//---------------------------------------------------------------------------

#ifndef VirtBlockH
#define VirtBlockH
//---------------------------------------------------------------------------


 class IBLock
{
public:
	//TODO: SETFR @STEND (VirtBlock.h)
	 virtual void SetFreq(double,double,int,int,int,int,int,int) = 0;
	 virtual void SetMFC1(double,int,int,int) = 0;
};

#endif
