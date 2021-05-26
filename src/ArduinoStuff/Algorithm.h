//
// Created by PinkySmile on 26/05/2021.
//

#ifndef GBEMULATOR_ALGORITHM_H
#define GBEMULATOR_ALGORITHM_H


namespace standard
{
	template<typename it, typename elemType>
	it find(it begin, it end, elemType elem)
	{
		while (begin < end)
		{
			if (*begin == elem)
				return begin;
			begin++;
		}
		return end;
	}

	template<typename T>
	T clamp(T val, T low, T high)
	{
		if (val < low)
			return low;
		if (val > high)
			return high;
		return val;
	}
}


#endif //GBEMULATOR_ALGORITHM_H
