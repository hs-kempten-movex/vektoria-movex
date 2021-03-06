#pragma once
#include "Vektoria\Root.h"
#include "IPlantGeo.h"

using namespace Vektoria;

namespace ForestNS
{
    class CherryBlossomTree : 
        public IPlantGeo
    {
    public:
        CherryBlossomTree();
        ~CherryBlossomTree();
        void Iterate(float fAge, float frTimeOfYear, float fRootCutHeight, bool isLoD) override;
        void DeIterate() override;

        ///<summary> Erzeugt die Baumgeometrie f�r eine ausgew�hlte Level of Detail-Stufe. <para></para>
          /// Achtung! Vor "Init" muss die Methode "Iterate" aufgerufen werden.  </summary> 
          ///<param name="pzgTemplate"> Pointer zu einer Vorlage-Birke, bei der schon Iterate aufgerufen wurde, <para></para>
          /// um das L-System zu erzeugen. </param>
          ///<param name="uLoD"> Level of Detail-Stufe <para></para>
          /// 0 => h�chstpolygonale Stufe, <para></para>
          /// 1 => zweith�chstpolygonale Stufe, ca. ein Viertel Polys weniger als Stufe 0).,<para></para>
          /// 2 => dritth�chstpolygonale Stufe, ca. ein Sechszehntel Polys weniger als Stufe 0).<para></para>
          /// ALLES > 3 FUNKTIONIERT AKTUELL AUS UNBEKANNTEN GR�NDEN NICHT! </param>
        void Init(IPlantGeo * pzgTemplate, unsigned int uLoD = 0) override;
        float GetOptimalLoDMin(float fAge, unsigned int uLoD);
        float GetOptimalLoDMax(float fAge, unsigned int uLoD);

    private:
        CGeoBio m_zgCherryblossom;
        CMaterial m_zmBlossom;
        bool m_bIsBlossoming = false;
        CGeoLeaf m_zgLeafMain;
        CGeoLeaf m_zgBlossomMain;
        CGeoLeaf m_zgStamenMain;
        CMaterial m_zmFruit;
		bool m_bIsHitbox;
    };
}