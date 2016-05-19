/*

*/ 


#ifndef X10MESSAGE_H_
#define X10MESSAGE_H_

struct  X10Message
{
	int unit_;			// 0-31 (31 = all)
	int mode_;			// 0 = inactive, 1 = active
	int brightness_;	// 0-100%
};

#endif /* X10MESSAGE_H_ */