#include "GeoBioPoppy.h"

using namespace ForestNS;

GeoBioPoppy::GeoBioPoppy()
{
}


GeoBioPoppy::~GeoBioPoppy()
{
}

void GeoBioPoppy::Iterate(float fAge, float frTimeOfYear, float fRootCutHeight)
{
    fColorscaling = m_random.RandFr();
    m_fAge = fAge;
    m_frTimeOfYear = frTimeOfYear;
    m_fRootCutHeight = fRootCutHeight;

    float frTimeShifted = m_frTimeOfYear + 0.25f;
    if (frTimeShifted > 1.0f)
        frTimeShifted -= 1.0f;

    m_fAgeStopped = fAge;

    // Das Schˆllkraut wird ca. 3 Jahre alt:
    if (m_fAgeStopped > 3.0f)
        m_fAgeStopped = 3.0f;
    if (m_fAgeStopped < 0.01f)
        m_fAgeStopped = 0.01f;

    // Das Schˆllkraut kann bis zu 60 cm groﬂ werden
    // St‰ngel hat ca. 6cm -10cm Hˆhe bis zur ersten Verzweigung, wenn erwachsen:
    // St‰ngel hat ca. 2mm - 3mm Radius an der Basis, wenn erwachsen:
    if (m_fAgeStopped > 0.1f)
    {
        m_iIterations = 30; // war 19
        m_iTurtleStartLongitude = 20;
        m_iTurtleStartLattitude = 28;
        //		m_fTurtleStartLength = 0.06f + (m_fAgeStopped - 0.01f) *0.01f;
        //		m_fTurtleStartRadius = 0.002f + (m_fAgeStopped - 0.1f) *0.00033f; 

        m_fTurtleStartLength = 1.6f;
        m_fTurtleStartRadius = 0.2f;
        m_fTurtleStartLength = 0.6f + (m_fAgeStopped - 0.01f) *0.01f;
        m_fTurtleStartRadius = 0.02f + (m_fAgeStopped - 0.1f) *0.00033f;
    }
    else
    {
        m_iIterations = 30; // war 18
        m_iTurtleStartLongitude = 15;
        m_iTurtleStartLattitude = 23;
        m_fTurtleStartLength = 0.06f * (m_fAgeStopped*10.0f);
        m_fTurtleStartRadius = 0.002f * (m_fAgeStopped*10.0f);
    }

    //SetDefaultAngles(HALFPI, HALFPI, HALFPI);
    SetDefaultAngles(QUARTERPI, QUARTERPI, QUARTERPI);
    SetDefaultFactorGravitation(0.5f);
    SetTurtleStartHeight(m_fTurtleStartLength);
    SetTurtleStartRadius(m_fTurtleStartRadius);
    //------------------------
    // Erzeuge Stamm und Ge‰st:
    //------------------------

    // Soll Bl¸ten (Y) ausbilden, wenn St‰gelradius unter einem mm:
    SetAxiom("A");

    // anf‰ngliche Verzweigungen
    AddRule("20:A=(l0.1)f[U](l10)[(^24)fX][(v19)fX]");
    AddRule("20:A=(l0.1)f[U](l10)[(<20)fX][(>23)fX][∞∞(^43)fX]");
    AddRule("30:A=(l0.1)f[U](l10)[(<23)fX](+10)[∞∞(>43)fX][fX]");
    AddRule("30:A=(l0.1)f[U](l10)[(<20)fX][(>23)fX][∞∞(v43)fX]");

    // Blumenstiel bis er 0.01 Durchmesser erreicht 
    AddRule("20:X={r>0.01,(^2)+(r0.8)(l0.9)fX}{r<0.0101,fY}");
    AddRule("20:X={r>0.01,(<5)+(r0.9)(l0.85)fX}{r<0.0101,fY}");
    AddRule("30:X={r>0.01,(v12)+(^30)(r0.8)(l0.9)fX}{r<0.0101,fY}");
    AddRule("30:X={r>0.01,(>22)+(r0.9)(l0.9)fX}{r<0.0101,Y}");

    // Bl‰tter in unterschiedlicher Anzahl
    AddRule("10:U=+(R1.5)(L1.5)[<0l][>0l][^0l][v0l]");
    AddRule("10:U=+(R1.5)(L1.5)[<0l][>0l][^0l][v0l](+40)[<0l][>0l][^0l][v0l]");
    AddRule("10:U=+(R1.5)(L1.5)[<0l][>0l]");
    AddRule("10:U=+(R1.5)(L1.5)[>0l][^0l][v0l]");
    AddRule("10:U=+(R1.5)(L1.5)[<0l][v0l]");
    AddRule("10:U=+(R1.5)(L1.5)[<0l]");
    AddRule("10:U=+(R1.5)(L1.5)[v0l]");
    AddRule("10:U=+(R1.5)(L1.5)[>0l]");
    AddRule("10:U=+(R1.5)(L1.5)[^0l]");
    AddRule("10:U=+(R1.5)(L1.5)[<0l][>0l][^0l][v0l]");



    // Die Bl¸te mit Staubbl‰ttern:

    // mit 4 Bl‰ttern
    AddRule("50:Y=&(R1.0)(L1.5)[(<78)0b][(^75)0b][(>71)0b][(v69)0b](R0.3)(L0.3)[(<20.2)c][(^18.4)c][(>20.4)c][(v22.4)c](+40.0)[(<10.2)c][(^11.4)c][(>14.4)c][(v12.4)c]");
    // oder mit 8
    AddRule("50:Y=&(R1.0)(L1.5)[(<78)0b][(^75)0b][(>71)0b][(v69)0b]+[(<63)0b][(^60)0b][(>57)0b][(v54)0b](R0.3)(L0.3)[(<20.2)c][(^18.4)c][(>20.4)c][(v22.4)c](+40.0)[(<10.2)c][(^11.4)c][(>14.4)c][(v12.4)c]");



    CGeoLSystem::Iterate(m_iIterations, m_acAxiom);


    // ---------------
    // Erzeuge Wurzel:
    // ---------------


    /*
    if (fRootCutHeight < 0.0f)
    {

      m_pzgRoot = new CGeoLSystem();
      m_pzgRoot->m_random.m_uRand = m_random.m_uRand;

      m_pzgRoot->SetAxiom("'Z");
      m_pzgRoot->AddRule("50:Z=(l0.8)[(+0)(>90)X][(+123)(>92)X][(+239)(>88)X]∞(r0.80)f[X]");
      m_pzgRoot->AddRule("50:Z=(l0.8)[(+10)(>85)X][(+113)(>82)X][(+219)(>98)X]∞(r0.80)(>9)f[X]");
      m_pzgRoot->AddRule("5:X=#+(r0.80)_f[(l0.90)(>10)X]");
      m_pzgRoot->AddRule("45:X=#+(r0.80)_f[(l0.79)<(r0.80)X][(l0.87)(>15)X]");
      m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.79)(<45)(r0.80)X][(l0.86)(>9)X]");
      m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.79)(<35)(r0.80)X][(l0.85)(>25)X]");


      m_pzgRoot->Iterate(m_iIterations, m_pzgRoot->m_acAxiom);

    }
    */
}

void GeoBioPoppy::DeIterate()
{
    ((CGeoLSystem*)this)->DeIterate();
    if (m_pzgRoot)
        m_pzgRoot->DeIterate();
}


void GeoBioPoppy::Init(IPlantGeo * pzgTemplate, unsigned int uLoD)
{
    if (!pzgTemplate)
    {
        return;
    }
    CopyThis(*pzgTemplate);

    if (pzgTemplate->m_iToKill <= 0)
    {
        return;
    }

    char * acTurtleOrdersMain = pzgTemplate->m_pacToKill[pzgTemplate->m_iToKill - 1];

    if (!acTurtleOrdersMain)
    {
        return;
    }

    float frTimeShifted = m_frTimeOfYear + 0.25f;
    if (frTimeShifted > 1.0f)
        frTimeShifted -= 1.0f;
    // 0= 22.Dez. 0.5=22.Juni 0.75 = 22 Sep.

    // --------------
    // Erzeuge Blatt: 
    // --------------


    m_zgLeafMain.SetMiddle(CHVector(0.0f, 0.07f, 0.5f, 1.0f));

    CHVector avOuter[87];

    // "Stiel"
    avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
    avOuter[1] = CHVector(0.03f, 0.0f, 0.99f, 1.0f);
    avOuter[2] = CHVector(0.035f, 0.0f, 0.975f, 1.0f);

    // 1. mal nach auﬂen
    avOuter[3] = CHVector(0.085f, 0.0f, 0.955f, 1.0f);
    avOuter[4] = CHVector(0.11f, 0.0f, 0.9f, 1.0f);
    avOuter[5] = CHVector(0.16f, 0.0f, 0.87f, 1.0f);
    avOuter[6] = CHVector(0.185f, 0.0f, 0.815f, 1.0f);
    avOuter[7] = CHVector(0.19f, 0.0f, 0.768f, 1.0f);

    // 1. mal nach innen
    avOuter[8] = CHVector(0.16f, 0.0f, 0.773f, 1.0f);
    avOuter[9] = CHVector(0.14f, 0.0f, 0.79f, 1.0f);
    avOuter[10] = CHVector(0.11f, 0.0f, 0.81f, 1.0f);
    avOuter[11] = CHVector(0.07f, 0.0f, 0.875f, 1.0f);
    avOuter[12] = CHVector(0.02f, 0.0f, 0.92f, 1.0f);

    // 2. mal nach auﬂen
    avOuter[13] = CHVector(0.03f, 0.0f, 0.85f, 1.0f);
    avOuter[14] = CHVector(0.045f, 0.0f, 0.82f, 1.0f);
    avOuter[15] = CHVector(0.06f, 0.0f, 0.785f, 1.0f);
    avOuter[16] = CHVector(0.08f, 0.0f, 0.765f, 1.0f);
    avOuter[17] = CHVector(0.1f, 0.0f, 0.765f, 1.0f);
    avOuter[18] = CHVector(0.15f, 0.0f, 0.67f, 1.0f);
    avOuter[19] = CHVector(0.18f, 0.0f, 0.64f, 1.0f);
    avOuter[20] = CHVector(0.185f, 0.0f, 0.57f, 1.0f);

    // 2. mal nach innen
    avOuter[21] = CHVector(0.155f, 0.0f, 0.59f, 1.0f);
    avOuter[22] = CHVector(0.13f, 0.0f, 0.63f, 1.0f);
    avOuter[23] = CHVector(0.11f, 0.0f, 0.645f, 1.0f);
    avOuter[24] = CHVector(0.1f, 0.0f, 0.665f, 1.0f);
    avOuter[25] = CHVector(0.085f, 0.0f, 0.67f, 1.0f);
    avOuter[26] = CHVector(0.07f, 0.0f, 0.69f, 1.0f);
    avOuter[27] = CHVector(0.03f, 0.0f, 0.71f, 1.0f);
    avOuter[28] = CHVector(0.02f, 0.0f, 0.73f, 1.0f);

    // 3. mal nach auﬂen
    avOuter[29] = CHVector(0.03f, 0.0f, 0.685f, 1.0f);
    avOuter[30] = CHVector(0.045f, 0.0f, 0.675f, 1.0f);
    avOuter[31] = CHVector(0.07f, 0.0f, 0.645f, 1.0f);
    avOuter[32] = CHVector(0.09f, 0.0f, 0.635f, 1.0f);
    avOuter[33] = CHVector(0.095f, 0.0f, 0.62f, 1.0f);
    avOuter[34] = CHVector(0.14f, 0.0f, 0.575f, 1.0f);
    avOuter[35] = CHVector(0.16f, 0.0f, 0.54f, 1.0f);
    avOuter[36] = CHVector(0.19f, 0.0f, 0.525f, 1.0f);
    avOuter[37] = CHVector(0.19f, 0.0f, 0.515f, 1.0f);
    avOuter[38] = CHVector(0.21f, 0.0f, 0.485f, 1.0f);
    avOuter[39] = CHVector(0.21f, 0.0f, 0.465f, 1.0f);

    // 3. mal nach innen
    avOuter[40] = CHVector(0.18f, 0.0f, 0.46f, 1.0f);
    avOuter[41] = CHVector(0.165f, 0.0f, 0.475f, 1.0f);
    avOuter[42] = CHVector(0.148f, 0.0f, 0.48f, 1.0f);
    avOuter[43] = CHVector(0.105f, 0.0f, 0.525f, 1.0f);
    avOuter[44] = CHVector(0.058f, 0.0f, 0.55f, 1.0f);
    avOuter[45] = CHVector(0.04f, 0.0f, 0.57f, 1.0f);
    avOuter[46] = CHVector(0.035f, 0.0f, 0.59f, 1.0f);

    // 4. mal nach auﬂen
    avOuter[47] = CHVector(0.04f, 0.0f, 0.55f, 1.0f);
    avOuter[48] = CHVector(0.065f, 0.0f, 0.52f, 1.0f);
    avOuter[49] = CHVector(0.085f, 0.0f, 0.51f, 1.0f);
    avOuter[50] = CHVector(0.085f, 0.0f, 0.5f, 1.0f);
    avOuter[51] = CHVector(0.135f, 0.0f, 0.46f, 1.0f);
    avOuter[52] = CHVector(0.16f, 0.0f, 0.43f, 1.0f);
    avOuter[53] = CHVector(0.165f, 0.0f, 0.38f, 1.0f);

    // 4. mal nach innen
    avOuter[54] = CHVector(0.145f, 0.0f, 0.38f, 1.0f);
    avOuter[55] = CHVector(0.11f, 0.0f, 0.41f, 1.0f);
    avOuter[56] = CHVector(0.07f, 0.0f, 0.42f, 1.0f);
    avOuter[57] = CHVector(0.045f, 0.0f, 0.45f, 1.0f);
    avOuter[58] = CHVector(0.025f, 0.0f, 0.48f, 1.0f);

    // 5. mal nach auﬂen
    avOuter[59] = CHVector(0.025f, 0.0f, 0.44f, 1.0f);
    avOuter[60] = CHVector(0.045f, 0.0f, 0.42f, 1.0f);
    avOuter[61] = CHVector(0.08f, 0.0f, 0.395f, 1.0f);
    avOuter[62] = CHVector(0.15f, 0.0f, 0.335f, 1.0f);
    avOuter[63] = CHVector(0.15f, 0.0f, 0.31f, 1.0f);

    // 5. mal nach innen
    avOuter[64] = CHVector(0.11f, 0.0f, 0.325f, 1.0f);
    avOuter[65] = CHVector(0.03f, 0.0f, 0.365f, 1.0f);

    // 6. mal nach auﬂen
    avOuter[66] = CHVector(0.03f, 0.0f, 0.34f, 1.0f);
    avOuter[67] = CHVector(0.07f, 0.0f, 0.29f, 1.0f);
    avOuter[68] = CHVector(0.095f, 0.0f, 0.255f, 1.0f);
    avOuter[69] = CHVector(0.1f, 0.0f, 0.235f, 1.0f);

    // 6. mal nach innen
    avOuter[70] = CHVector(0.075f, 0.0f, 0.24f, 1.0f);
    avOuter[71] = CHVector(0.05f, 0.0f, 0.265f, 1.0f);
    avOuter[72] = CHVector(0.04f, 0.0f, 0.255f, 1.0f);

    // 7. mal nach auﬂen
    avOuter[73] = CHVector(0.045f, 0.0f, 0.22f, 1.0f);
    avOuter[74] = CHVector(0.07f, 0.0f, 0.2f, 1.0f);
    avOuter[75] = CHVector(0.075f, 0.0f, 0.18f, 1.0f);

    // 7. mal nach innen
    avOuter[76] = CHVector(0.045f, 0.0f, 0.195f, 1.0f);

    // Spitze!
    avOuter[77] = CHVector(0.05f, 0.0f, 0.17f, 1.0f);
    avOuter[78] = CHVector(0.045f, 0.0f, 0.16f, 1.0f);
    avOuter[79] = CHVector(0.051f, 0.0f, 0.14f, 1.0f);
    avOuter[80] = CHVector(0.053f, 0.0f, 0.12f, 1.0f);
    avOuter[81] = CHVector(0.03f, 0.0f, 0.125f, 1.0f);
    avOuter[82] = CHVector(0.045f, 0.0f, 0.085f, 1.0f);
    avOuter[83] = CHVector(0.03f, 0.0f, 0.08f, 1.0f);
    avOuter[84] = CHVector(0.015f, 0.0f, 0.04f, 1.0f);
    avOuter[85] = CHVector(0.015f, 0.0f, 0.02f, 1.0f);
    avOuter[86] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);

    /*for (int i = 0; i < 87; i++)
      m_zgLeafMain.AddOuter(&avOuter[i]);*/

    if (uLoD == 0)
    {
        for (int i = 0; i < 87; i++)
            m_zgLeafMain.AddOuter(&avOuter[i]);
    }
    else if (uLoD == 1)
    {
        for (int i = 0; i < 87; i += 4)
            m_zgLeafMain.AddOuter(&avOuter[i]);
    }
    else if (uLoD == 2)
    {
        for (int i = 0; i < 87; i += 6)
            m_zgLeafMain.AddOuter(&avOuter[i]);
    }
    else if (uLoD == 3)
    {
        for (int i = 0; i < 87; i += 8)
            m_zgLeafMain.AddOuter(&avOuter[i]);
    }

    else if (uLoD > 3)
    {
        m_zgLeafMain.AddOuter(&avOuter[0]);
        m_zgLeafMain.AddOuter(&avOuter[7]);
        m_zgLeafMain.AddOuter(&avOuter[39]);
        m_zgLeafMain.AddOuter(&avOuter[86]);
    }

    SetMaxLeafBending(0.1f);
    SetMaxLeafFolding(0.5f);
    m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.001f);
    SetGeoLeaf(&m_zgLeafMain);

    /*CHMat mScale;
    mScale.Scale(1.5f);
    m_zgLeafMain.Transform(mScale);*/


    m_zmLeaf.MakeTextureDiffuse("textures\\poppyleaf.png");
    m_zmLeaf.MakeTextureBump("textures\\poppyleaf_n.png");
    m_zmLeaf.MakeTextureHeight("textures\\poppyleaf_h.png");
    m_zmLeaf.MakeTextureSpecular("textures\\poppyleaf_o.png");
    m_zmLeaf.SetChromaKeyingOn();



    // --------------------
    // Erzeuge Staubblatt: 
    // --------------------
    m_zmStamen.LoadPreset("LeafBlossom");

    m_zgStamenMain.SetMiddle(CHVector(0.0f, 0.0f, 0.9f, 1.0f));
    if (uLoD == 0)
    {
        CHVector avOuter[7];
        //Stiel:
        avOuter[0] = CHVector(0.00f, 0.0f, 1.0f, 1.0f);
        avOuter[1] = CHVector(0.03f, 0.0f, 1.0f, 1.0f);
        avOuter[2] = CHVector(0.03f, 0.0f, 0.2f, 1.0f);

        //Staubstempel:
        avOuter[3] = CHVector(0.20f, 0.0f, 0.18f, 1.0f);
        avOuter[4] = CHVector(0.20f, 0.0f, 0.02f, 1.0f);
        avOuter[5] = CHVector(0.07f, 0.0f, 0.00f, 1.0f);
        avOuter[6] = CHVector(0.00f, 0.0f, 0.00f, 1.0f);

        for (int i = 0; i < 7; i++)
            m_zgStamenMain.AddOuter(&avOuter[i]);

        m_zgStamenMain.Init(&m_zmStamen, true, true, -0.0f, 0.0f, 0.0f);
        // m_zgBlossomMain.SetAngleUp(0.4f);
        SetGeoStamen(&m_zgStamenMain);
    }


    // --------------------
    // Erzeuge Bl¸tenblatt: 
    // --------------------


    m_zgBlossomMain.SetMiddle(CHVector(0.0f, 0.03f, 0.5f, 1.0f));
    if (uLoD == 0)
    {
        CHVector avOuter[16];

        avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
        avOuter[1] = CHVector(0.02f, 0.0f, 1.0f, 1.0f);
        avOuter[2] = CHVector(0.065f, 0.0f, 0.935f, 1.0f);
        avOuter[3] = CHVector(0.1f, 0.0f, 0.92f, 1.0f);
        avOuter[4] = CHVector(0.2f, 0.0f, 0.92f, 1.0f);
        avOuter[5] = CHVector(0.295f, 0.0f, 0.89f, 1.0f);
        avOuter[6] = CHVector(0.35f, 0.0f, 0.82f, 1.0f);
        avOuter[7] = CHVector(0.38f, 0.0f, 0.8f, 1.0f);
        avOuter[8] = CHVector(0.405f, 0.0f, 0.74f, 1.0f);
        avOuter[9] = CHVector(0.365f, 0.0f, 0.62f, 1.0f);
        avOuter[10] = CHVector(0.31f, 0.0f, 0.55f, 1.0f);
        avOuter[11] = CHVector(0.29f, 0.0f, 0.51f, 1.0f);
        avOuter[12] = CHVector(0.26f, 0.0f, 0.515f, 1.0f);
        avOuter[13] = CHVector(0.145f, 0.0f, 0.48f, 1.0f);
        avOuter[14] = CHVector(0.02f, 0.0f, 0.46f, 1.0f);
        avOuter[15] = CHVector(0.0f, 0.0f, 0.46f, 1.0f);


        for (int i = 0; i < 16; i++)
            m_zgBlossomMain.AddOuter(&avOuter[i]);
        SetMaxBlossomBending(-0.25f);
        SetMaxBlossomFolding(0.15f);
        m_zgBlossomMain.Init(&m_zmBlossom, true, true, 0.0f, 0.0f, 0.001f);
        SetGeoBlossom(&m_zgBlossomMain);

        /*CHMat mScalebluete;
        mScalebluete.Scale(6.0f);
        m_zgBlossomMain.Transform(mScalebluete);*/

    }
    else
    {
        CHVector avOuter[7];

        avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
        avOuter[1] = CHVector(0.02f, 0.0f, 1.0f, 1.0f);
        avOuter[2] = CHVector(0.2f, 0.0f, 0.92f, 1.0f);
        avOuter[3] = CHVector(0.35f, 0.0f, 0.82f, 1.0f);
        avOuter[4] = CHVector(0.365f, 0.0f, 0.62f, 1.0f);
        avOuter[5] = CHVector(0.29f, 0.0f, 0.51f, 1.0f);
        avOuter[6] = CHVector(0.0f, 0.0f, 0.46f, 1.0f);


        for (int i = 0; i < 7; i++)
            m_zgBlossomMain.AddOuter(&avOuter[i]);


        SetMaxBlossomBending(-0.25f);
        SetMaxBlossomFolding(0.15f);
        m_zgBlossomMain.Init(&m_zmBlossom, true, true, 0.0f, 0.0f, 0.001f);
        SetGeoBlossom(&m_zgBlossomMain);

        CHMat mScalebluete;
        mScalebluete.Scale((float)uLoD);
        m_zgBlossomMain.Transform(mScalebluete);

        SetLeafSkipFactor(uLoD);
    }

    //m_zmBlossom.MakeTextureDiffuse("textures\\poppyblossomred.png");
    m_zmBlossom.MakeTextureBump("textures\\PoppyBlossom_n.png");
    m_zmBlossom.MakeTextureHeight("textures\\PoppyBlossom_h.png");
    m_zmBlossom.MakeTextureSpecular("textures\\PoppyBlossom_o.png");
    //m_zmBlossom.SetSpecularStrength(0.0f);
    //m_zmBlossom.SetChromaKeyingOn();


    //Zuf‰llige Farbe der Bl¸tenbl‰tter -> Weiﬂ (selten), Lavendel (selten), gelb, orange-rot, rot (am h‰ufigsten)
    // funktioniert nicht ganz, Donnerstag fragen

    if (fColorscaling < 0.101)
    {
        // Setze Farbe auf Lavendel (selten)(221.0f, 160.0f, 221.0f)
        m_zmBlossom.MakeTextureDiffuse("textures\\poppyblossomrose.png");
    }
    else if (fColorscaling < 0.201)
    {
        // Setze Farbe auf Weiﬂ (selten)
        m_zmBlossom.MakeTextureDiffuse("textures\\poppyblossomwhite.png");
    }
    else if (fColorscaling < 0.401)
    {
        // Setze Farbe auf gelb
        m_zmBlossom.MakeTextureDiffuse("textures\\poppyblossomyellow.png");
    }
    else if (fColorscaling < 0.801)
    {
        m_zmBlossom.MakeTextureDiffuse("textures\\poppyblossomred.png");
    }
    else {
        // Setze Farbe auf Orange-rot
        m_zmBlossom.MakeTextureDiffuse("textures\\poppyblossomorange.png");
    }



    m_zgBlossomMain.SetMaterial(&m_zmBlossom);



    /*CHMat mScaleleaf;
    mScaleleaf.ScaleX(0.05f);
    m_zgLeafMain.Transform(mScaleleaf);*/

    SetMaterialLeaf(&m_zmLeaf);




    //m_zmBark.LoadPreset("BarkChelidoniumMajus");
    m_zmBark.MakeTextureDiffuse("textures\\PoppyBark.png");
    SetMaterial(&m_zmBark);


    SetSwakeRandomFactor(m_fSwakeRandom);
    SetTurtleStartHeight(m_fTurtleStartLength);
    SetTurtleStartRadius(m_fTurtleStartRadius);
    SetDefaultFactorGravitation(0.5f);

    if (uLoD == 1)
    {
        m_iTurtleStartLongitude /= 2;
        m_iTurtleStartLattitude /= 2;
    }
    if (uLoD == 2)
    {
        m_iTurtleStartLongitude /= 4;
        m_iTurtleStartLattitude /= 4;
        if (m_iTurtleStartLongitude < 4)
            m_iTurtleStartLongitude = 4;
    }
    if (uLoD >= 3)
    {
        m_iTurtleStartLongitude /= 6;
        m_iTurtleStartLattitude /= 6;
        if (m_iTurtleStartLongitude < 4)
            m_iTurtleStartLongitude = 4;

        if (uLoD >= 5)
        {
            m_iTurtleStartLongitude = 0;
            m_iTurtleStartLattitude = 0;
        }
        SetTurtleEndLongitude(0);
        SetTurtleEndLattitude(0);

    }
    if (m_iTurtleStartLattitude == 1)
        m_iTurtleStartLattitude = 2;
    if (m_iTurtleStartLattitude == 0 && m_iTurtleStartLongitude > 0)
        m_iTurtleStartLattitude = 2;
    SetTurtleStartLongitude(m_iTurtleStartLongitude);
    SetTurtleStartLattitude(m_iTurtleStartLattitude);

    Interprete(acTurtleOrdersMain);

    // ---------------
    // Erzeuge Wurzel:
    // ---------------

  /*
    if (pzgTemplate->m_pzgRoot && uLoD < 2)
    {
      if (!m_pzgRoot)
        m_pzgRoot = new CGeoLSystem();

      char * acTurtleOrdersRoot = pzgTemplate->m_pzgRoot->m_pacToKill[pzgTemplate->m_pzgRoot->m_iToKill - 1];
      m_pzgRoot->m_random.m_uRand = pzgTemplate->m_pzgRoot->m_random.m_uRand;

      m_pzgRoot->SetDefaultAngles(80.0f, 80.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
      m_pzgRoot->SetDefaultFactorGravitation(0.1f);

      m_pzgRoot->SetMaterial(&m_zmBark);		// Schrittweise Reduzierung der Segmentl‰nge (Default: 1.0)
      m_pzgRoot->SetTurtleStartDir(CHVector(0.0f, -1.0f, 0.0f, 0.0f));
      //		m_pzgRoot->SetTurtleStartPos(CHVector(0.0f, 2.5f, 0.0f, 1.0f));

      m_pzgRoot->SetRootCutHeight(m_fRootCutHeight);
      m_pzgRoot->SetTextureRepeat(-1.0f, 1.0f);
      m_pzgRoot->SetSwakeRandomFactor(m_fSwakeRandom);
      m_pzgRoot->SetTurtleStartHeight(m_fTurtleStartLength);
      m_pzgRoot->SetTurtleStartRadius(m_fTurtleStartRadius);
      m_pzgRoot->SetTurtleStartLongitude(m_iTurtleStartLongitude);
      m_pzgRoot->SetTurtleStartLattitude(m_iTurtleStartLattitude);
      m_pzgRoot->SetDefaultAngles(80.0f, 80.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
      m_pzgRoot->SetDefaultFactorGravitation(0.1f);

      m_pzgRoot->Interprete(acTurtleOrdersRoot);

      AddGeo(m_pzgRoot);
    }
    */
}

float GeoBioPoppy::GetOptimalLoDMin(float fAge, unsigned int uLoD)
{
    float m_fAgeStopped = fAge;
    if (m_fAgeStopped > 1.0f)
        m_fAgeStopped = 1.0f;
    if (m_fAgeStopped < 0.01f)
        m_fAgeStopped = 0.01f;
    if (uLoD == 0)
        return 0.0F;
    return (5.f + m_fAgeStopped * 0.5f) * powf(4.0f, uLoD - 1);
}

float GeoBioPoppy::GetOptimalLoDMax(float fAge, unsigned int uLoD)
{
    float m_fAgeStopped = fAge;
    if (m_fAgeStopped > 1.0f)
        m_fAgeStopped = 1.0f;
    if (m_fAgeStopped < 0.01f)
        m_fAgeStopped = 0.01f;
    return (5.f + m_fAgeStopped * 0.5f) * powf(4.0f, uLoD);
}