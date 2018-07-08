#pragma once
namespace Helpers {
	template<typename t>
	bool ArrayComparer(t *left, size_t leftSize, t *right, size_t rightSize) {
		if (leftSize != rightSize) { return false; }
		for (size_t ite = 0; ite < leftSize; ++ite) {
			if (*(left + ite) != *(right + ite)) { return false; }
		}
		return true;
	}
}