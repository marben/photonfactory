#ifndef _AUXILIARY_H_
#define _AUXILIARY_H_

namespace ggl {

template<int begin, int end, typename T>	// TODO: put this function to some other header
T clamp(T value)
{
		if (value > static_cast<T>(end))
			return static_cast<T>(end);

		if (value < static_cast<T>(begin))
			return static_cast<T>(begin);

		return value;
}


} // namespace ggl

#endif
