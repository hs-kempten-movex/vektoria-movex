#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;

namespace ForestNS
{
    class CherryBlossomTree : public CGeoBio
    {
    public:
        CherryBlossomTree();
        ~CherryBlossomTree();
        void Iterate(float fAge, float frTimeOfYear = 0.25f, float fRootCutHeight = 0.0f);
        void DeIterate();

        ///<summary> Erzeugt die Baumgeometrie für eine ausgewählte Level of Detail-Stufe. <para></para>
          /// Achtung! Vor "Init" muss die Methode "Iterate" aufgerufen werden.  </summary> 
          ///<param name="pzgTemplate"> Pointer zu einer Vorlage-Birke, bei der schon Iterate aufgerufen wurde, <para></para>
          /// um das L-System zu erzeugen. </param>
          ///<param name="uLoD"> Level of Detail-Stufe <para></para>
          /// 0 => höchstpolygonale Stufe, <para></para>
          /// 1 => zweithöchstpolygonale Stufe, ca. ein Viertel Polys weniger als Stufe 0).,<para></para>
          /// 2 => dritthöchstpolygonale Stufe, ca. ein Sechszehntel Polys weniger als Stufe 0).<para></para>
          /// ALLES > 3 FUNKTIONIERT AKTUELL AUS UNBEKANNTEN GRÜNDEN NICHT! </param>
        void Init(CherryBlossomTree * pzgTemplate, unsigned int uLoD = 0);
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
    };
}