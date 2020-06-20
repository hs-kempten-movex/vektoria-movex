#pragma once
#include "Vektoria\Root.h"
#include "Geos/IPlantGeo.h"
#include "../Utils/ThreadPool.h"
#include <array>

using namespace Vektoria;

namespace ForestNS
{
    template<typename T, size_t C, bool = std::is_base_of<IPlantGeo, T>::value>
    class PlantPlacement
    {
    };

    struct LoDRange
    {
        float max;
        unsigned int lodIndex;
    };

    template<typename T, size_t C>
    class PlantPlacement <T, C, true> :
        public CPlacement
    {
    public:
        PlantPlacement(unsigned int seed, float age, float timeOfYear, float rootCutHeight) :
            m_seed{ seed },
            m_age{ age },
            m_timeOfYear{ timeOfYear },
            m_rootCutHeight{ rootCutHeight }
        {
        }

        void InitLoDs(std::array<LoDRange, C> lodRanges, UtilsNS::ThreadPool* threadPool) {
            for (int i = 0; i < C; i++)
            {
                IPlantGeo& cast = dynamic_cast<IPlantGeo&>(m_lodGeos[i]);
                
                m_lodPlacements[i].AddGeo(&cast);
                m_lodPlacements[i].SetLoD((i > 0) ? lodRanges[i - 1].max : 0.0f, lodRanges[i].max);

                AddPlacement(&m_lodPlacements[i]);

                threadPool->EnqueueTask([](IPlantGeo* geo, unsigned int seed, float age, float timeOfYear, float rootCutHeight, unsigned int lodIndex)
                    {
                        geo->SetRandomSeed(seed);
                        geo->Iterate(age, timeOfYear, rootCutHeight);
                        geo->Init(geo, lodIndex);
                        geo->DeIterate();
                    }, &cast, m_seed, m_age, m_timeOfYear, m_rootCutHeight, lodRanges[i].lodIndex);
            }
        }

    private:
        unsigned int m_seed;
        float m_age;
        float m_timeOfYear;
        float m_rootCutHeight;

        std::array<T, C> m_lodGeos;
        std::array<CPlacement, C> m_lodPlacements;


    };
}