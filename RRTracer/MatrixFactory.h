#ifndef MATRIX_FACTORY_H
#define MATRIX_FACTORY_H

#include "Matrix.h"

namespace RRT
{
	class MatrixFactory
	{
	public:
		Matrix IdentityMatrix() const;
	};
}


#endif // !MATRIX_FACTORY_H