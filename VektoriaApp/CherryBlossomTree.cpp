#include "CherryBlossomTree.h"

CherryBlossomTree::CherryBlossomTree()
{
	// Startdurchmesser Stamm
	SetTurtleStartRadius(0.9f);

	// Default Winkel (für <>v^)
	SetDefaultAngles(PHI / 2.0f, PHI / 2.0f, PHI);

	// Regeln
	SetAxiom("K");
	AddRule("33:K={r>0.7,(r0.95)(^34)f(r0.95)fK}{r<0.7,X}");
	AddRule("33:K={r>0.7,(r0.95)(>35)f(r0.95)fK}{r<0.7,X}");
	AddRule("34:K={r>0.7,(r0.95)(<32)f(r0.95)fK}{r<0.7,X}");
	AddRule("35:X={b<12,°+(l0.93)(r0.95)(_0.8)(>9)f(r0.95)(>9)f[(l0.9)(<4)(r0.9)X][°(l0.95)(r0.5)(>80)X]}{b=12,Y}");
	AddRule("15:X={b<12,+(l0.93)(r0.95)(_0.8)(<15)f(r0.95)(<3)f[(l0.85)(r0.8)(^25)f(^27)X][°(l0.89)(^32)f(r0.8)f(v20)(r0.8)XY]}{b=12,Y}");
	AddRule("15:X={b<12,°+(l0.93)(r0.95)(_0.8)(v8)f(r0.95)(v12)f[(l0.97)(r0.8)(<5)(^5)(v8)fXY]}{b=12,Y}");
	AddRule("15:X={b<12,°+(r0.95)(_0.8)(>51)f(r0.95)f[(l0.97)(^10)(r0.92)fXY][(l0.52)(r0.5)(<57)X]}{b=12,Y}");
	AddRule("10:X={b<12,°+(r0.95)(_0.8)(^35)f(r0.95)fXY}{b=12,Y}");
	AddRule("10:X={b<12,°+(r0.95)(_0.8)(<31)f(r0.95)f[(l0.97)(<10)(r0.92)fXY][(l0.52)(r0.5)(^27)X]}{b=12,Y}");
	AddRule("Y={r<0.00751,°(l0.05)(^22)f[^l][<l]f[>l][vl]f[^l][<l]f[>l][vl]f[^l][<l]f[>l][vl]f[^l][<l]f[>l][vl]f[^l][<l]f[>l][vl]f[^l][<l]f[>l][vl]f[^l][<l]f[>l][vl]l}{r>0.0075,Z}");

	// Blüten
	m_zgLeafMain.SetMiddle(CHVector(0.0f, 0.03f, 0.64f, 1.0f));

	CHVector avOuter[30];

	avOuter[0] = CHVector(0.0f, 0.0f, 1.2f, 1.0f);
	avOuter[1] = CHVector(0.02f, 0.0f, 1.2f, 1.0f);
	avOuter[2] = CHVector(0.0f, 0.0f, 0.8f, 1.0f);
	avOuter[3] = CHVector(0.02f, 0.0f, 0.9f, 1.0f);
	avOuter[4] = CHVector(0.07f, 0.0f, 0.99f, 1.0f);
	avOuter[5] = CHVector(0.135f, 0.0f, 1.06f, 1.0f);
	avOuter[6] = CHVector(0.22f, 0.0f, 1.1f, 1.0f);
	avOuter[7] = CHVector(0.32f, 0.0f, 1.15f, 1.0f);
	avOuter[8] = CHVector(0.4f, 0.0f, 1.06f, 1.0f);
	avOuter[9] = CHVector(0.44f, 0.0f, 0.98f, 1.0f);
	avOuter[10] = CHVector(0.46f, 0.0f, 0.9f, 1.0f);
	avOuter[11] = CHVector(0.44f, 0.0f, 0.82f, 1.0f);
	avOuter[12] = CHVector(0.4f, 0.0f, 0.75f, 1.0f);
	avOuter[13] = CHVector(0.35f, 0.0f, 0.705f, 1.0f);
	avOuter[14] = CHVector(0.28f, 0.0f, 0.675f, 1.0f);
	avOuter[15] = CHVector(0.38f, 0.0f, 0.66f, 1.0f);
	avOuter[16] = CHVector(0.46f, 0.0f, 0.62f, 1.0f);
	avOuter[17] = CHVector(0.53f, 0.0f, 0.57f, 1.0f);
	avOuter[18] = CHVector(0.565f, 0.0f, 0.485f, 1.0f);
	avOuter[19] = CHVector(0.57f, 0.0f, 0.4f, 1.0f);
	avOuter[20] = CHVector(0.53f, 0.0f, 0.32f, 1.0f);
	avOuter[21] = CHVector(0.45f, 0.0f, 0.285f, 1.0f);
	avOuter[22] = CHVector(0.36f, 0.0f, 0.28f, 1.0f);
	avOuter[23] = CHVector(0.28f, 0.0f, 0.3f, 1.0f);
	avOuter[24] = CHVector(0.2f, 0.0f, 0.35f, 1.0f);
	avOuter[25] = CHVector(0.215f, 0.0f, 0.25f, 1.0f);
	avOuter[26] = CHVector(0.215f, 0.0f, 0.155f, 1.0f);
	avOuter[27] = CHVector(0.18f, 0.0f, 0.08f, 1.0f);
	avOuter[28] = CHVector(0.11f, 0.0f, 0.03f, 1.0f);
	avOuter[29] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < 28; i++)
		m_zgLeafMain.AddOuter(&avOuter[i]);

	m_zgLeafMain.Init(&m_zmLeaf, true, true, -1.0f);
	SetGeoLeaf(&m_zgLeafMain);
	CHMat mScale;
	mScale.Scale(2.0);
	m_zgLeafMain.Transform(mScale);

	m_zmLeaf.MakeTextureDiffuse("textures\\red_image.jpg");
	SetMaterialLeaf(&m_zmLeaf);

	SetDefaultFactorGravitation(0.2f);
	Create(40);

	m_zmBark.LoadPreset("BarkBirch");
	SetMaterial(&m_zmBark);
}

CherryBlossomTree::~CherryBlossomTree()
{

}

