#pragma once
#include "Vektoria\Root.h"
#include "Geos/IPlantGeo.h"
#include "../ThreadPool.h"
#include <array>

using namespace Vektoria;

namespace ForestNS
{
    template<typename T, size_t LoDCount, bool = std::is_base_of<IPlantGeo, T>::value>
    class PlantPlacement
    {
    };

    struct LoDRange
    {
        float max;
        unsigned int lodIndex;
    };

    template<typename T, size_t LoDCount>
    class PlantPlacement <T, LoDCount, true> :
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

        void InitLoDs(std::array<LoDRange, LoDCount> lodRanges, ThreadPool* threadPool)
        {
            for (int i = 0; i < LoDCount; i++)
            {
                InitGeo(m_zpLoDs[i], m_lodGeos[i], m_timeOfYear, lodRanges[i].lodIndex, threadPool);
                m_zpLoDs[i].SetLoD((i > 0) ? lodRanges[i - 1].max : 0.0f, lodRanges[i].max);
            }
        }

        void InitCollisionGeo(ThreadPool* threadPool)
        {
            InitGeo(m_zpCollisionGeo, m_collisionGeo, 0.8f, 9, threadPool);
            m_zpCollisionGeo.SetDrawingOff();
        }

        T& GetCollisionGeo()
        {
            return m_collisionGeo;
        }

    private:
        unsigned int m_seed;
        float m_age;
        float m_timeOfYear;
        float m_rootCutHeight;

        std::array<T, LoDCount> m_lodGeos;
        std::array<CPlacement, LoDCount> m_zpLoDs;

        T m_collisionGeo;
        CPlacement m_zpCollisionGeo;

        void InitGeo(CPlacement& placement, T& geo, float timeOfYear, unsigned int lodIndex, ThreadPool* threadPool)
        {
            IPlantGeo& cast = dynamic_cast<IPlantGeo&>(geo);

            placement.AddGeo(&cast);
            AddPlacement(&placement);

            threadPool->EnqueueTask([](IPlantGeo* geo, unsigned int seed, float age, float timeOfYear, float rootCutHeight, unsigned int lodIndex)
                {
                    geo->SetRandomSeed(seed);
                    geo->Iterate(age, timeOfYear, rootCutHeight);
                    geo->Init(geo, lodIndex);
                    geo->DeIterate();
                }, &cast, m_seed, m_age, timeOfYear, m_rootCutHeight, lodIndex
            );
        }

    };
}