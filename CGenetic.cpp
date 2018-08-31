#include "CGenetic.h"

template <typename T>
CGenetic<T>::CGenetic(std::list<CIndividu> population) {
	_population = population;
}

template <typename T>
CGenetic<T>::~CGenetic(void) {
}
