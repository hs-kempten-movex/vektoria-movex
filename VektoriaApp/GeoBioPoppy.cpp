#include "GeoBioPoppy.h"

GeoBioPoppy::GeoBioPoppy()
{

	SetTurtleStartRadius(0.05f);
	SetDefaultFactorGravitation(0.4f);
	SetDefaultAngles(PHI / 2.0f, PHI / 2.0f, PHI);


	// Grundgerüst
	SetAxiom("A");

	//SetAxiom("X");
	//AddRule("X=fl[(+90)(<1)l]fK");			// X = unterster Teil mit Blättern
	//AddRule("25:K=(<5)f[(>22)fZ]ffZ");		// K = Verzweigung
	//AddRule("25:K=(>8)f[(<23)fZ]ffZ");
	//AddRule("25:K=(^12)f[(v27)fZ]ffZ");
	//AddRule("25:K=(v13)f[(^25)fZ]ffZ");
	//AddRule("Z=(<90)b(^90)b(^90)b(^90)b");	// Z = Blüte
	////AddRule("X=f[>>l][<l]fK");			// Blätter die auch mal funktioniert haben und dann irgendwie nicht mehr
	AddRule("20:A=fX");
	AddRule("20:A=(l0.1)f(l10)[(<20)fX][(>23)fX][°°(^43)fX]");
	AddRule("30:A=(l0.1)f(l10)[(<23)fX](+10)[°°(>43)fX][fX]");
	AddRule("30:A=(l0.1)f(l10)[(<20)fX][(>23)fX][°°(v43)fX]");
	AddRule("20:X={r>0.01,(^2)+(r0.8)(l0.9)fX}{r<0.0101,fY}");
	AddRule("20:X={r>0.01,(<5)+(r0.9)(l0.85)fX}{r<0.0101,fY}");
	AddRule("30:X={r>0.01,(v12)+(^30)(r0.8)(l0.9)fX}{r<0.0101,fY}");
	AddRule("30:X={r>0.01,(>22)+(r0.9)(l0.9)fX}{r<0.0101,Y}");


	// Die Blüte:
	AddRule("Y=(r10.0)(l0.5)[<b][^b][>b][vb][(<20.2)c][(^18.4)c][(>20.4)c][(v22.4)c](+40.0)[(<10.2)c][(^11.4)c][(>14.4)c][(v12.4)c]");

	// Blütenblatt
	m_zgBlossomMain.SetMiddle(CHVector(0.0f, 0.03f, 0.5f, 1.0f));

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
	SetMaxBlossomBending(0.05f);
	SetMaxBlossomFolding(0.03f);
	m_zgBlossomMain.Init(&m_zmBlossom, true, true, 0.0f, 0.0f, 0.02f);
	SetGeoBlossom(&m_zgBlossomMain);

	CHMat mScalebluete;
	mScalebluete.Scale(6.0f);
	m_zgBlossomMain.Transform(mScalebluete);

	m_zmBlossom.MakeTextureDiffuse("textures\\PoppyBlossom.png");
	m_zmBlossom.MakeTextureBump("textures\\PoppyBlossom_n.png");
	m_zmBlossom.MakeTextureHeight("textures\\PoppyBlossom_h.png");
	m_zmBlossom.SetSpecularStrength(0.0f);
	//m_zmBlossom.SetChromaKeyingOn();
	m_zgBlossomMain.SetMaterial(&m_zmBlossom);


	// Mohn Staubblatt


	m_zgStamenMain.SetMiddle(CHVector(0.0f, 0.0f, 0.9f, 1.0f));
	/*if (uLoD == 0)
	{*/
	CHVector avOuters[7];
	//Stiel:
	avOuters[0] = CHVector(0.00f, 0.0f, 1.0f, 1.0f);
	avOuters[1] = CHVector(0.03f, 0.0f, 1.0f, 1.0f);
	avOuters[2] = CHVector(0.03f, 0.0f, 0.2f, 1.0f);

	//Staubstempel:
	avOuters[3] = CHVector(0.20f, 0.0f, 0.18f, 1.0f);
	avOuters[4] = CHVector(0.20f, 0.0f, 0.02f, 1.0f);
	avOuters[5] = CHVector(0.07f, 0.0f, 0.00f, 1.0f);
	avOuters[6] = CHVector(0.00f, 0.0f, 0.00f, 1.0f);

	for (int i = 0; i < 7; i++)
		m_zgStamenMain.AddOuter(&avOuters[i]);

	m_zgStamenMain.Init(&m_zmBlossom, true, true, -0.0f, 0.0f, 0.0f);
	// m_zgBlossomMain.SetAngleUp(0.4f);
	SetGeoStamen(&m_zgStamenMain);
	//}

	// Mohn Blatt

	CHVector blatt[13];

	blatt[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
	blatt[1] = CHVector(0.07f, 0.0f, 0.99f, 1.0f);
	blatt[2] = CHVector(0.06f, 0.0f, 0.84f, 1.0f);
	blatt[3] = CHVector(0.22f, 0.0f, 0.76f, 1.0f);
	blatt[4] = CHVector(0.245f, 0.0f, 0.68f, 1.0f);
	blatt[5] = CHVector(0.28f, 0.0f, 0.565f, 1.0f);
	blatt[6] = CHVector(0.235f, 0.0f, 0.435f, 1.0f);
	blatt[7] = CHVector(0.21f, 0.0f, 0.335f, 1.0f);
	blatt[8] = CHVector(0.13f, 0.0f, 0.23f, 1.0f);
	blatt[9] = CHVector(0.14f, 0.0f, 0.18f, 1.0f);
	blatt[10] = CHVector(0.07f, 0.0f, 0.09f, 1.0f);
	blatt[11] = CHVector(0.06f, 0.0f, 0.002f, 1.0f);
	blatt[12] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);

	m_zgLeafMain.SetMiddle(CHVector(0.0f, 0.03f, 0.5f, 1.0f));

	for (int i = 0; i < 13; i++)
		m_zgLeafMain.AddOuter(&blatt[i]);
	m_zgLeafMain.Init(&m_zmLeaf, true, true, -1.0f);
	SetGeoLeaf(&m_zgLeafMain);
	CHMat mScale;
	mScale.Scale(1.5f);
	m_zgLeafMain.Transform(mScale);
	m_zmLeaf.MakeTextureBillboard("textures\\PoppyLeaf.png");
	m_zmLeaf.SetChromaKeyingOn();


	m_zmBark.MakeTextureDiffuse("textures\\PoppyBark.png");
	SetMaterial(&m_zmBark);
	Create(15);
}

GeoBioPoppy::~GeoBioPoppy()
{

}

