#include "GeoBioAsianTree.h"

namespace Vektoria
{
	CGeoBioAsianTree::CGeoBioAsianTree()
	{
	}

	CGeoBioAsianTree::~CGeoBioAsianTree()
	{
	}

	void CGeoBioAsianTree::Iterate(float fAge, float fRootCutHeight)
		{
			m_fAge = fAge;
			m_fAgeStopped = fAge;
			m_fRootCutHeight = fRootCutHeight;

			if (m_fAgeStopped > 200.0f)
				m_fAgeStopped = 200.0f;
			if (m_fAgeStopped < 1.0f)
				m_fAgeStopped = 1.0f;

			if (m_fAgeStopped > 50.0f)
			{
				m_iIterations = 14;
				m_iTurtleStartLongitude = 26;
				m_iTurtleStartLattitude = 26;
				m_fTurtleStartLength = 2.0f + (m_fAge - 50.0f) / 150.0f * 0.5f;
				m_fTurtleStartRadius = 0.4f + (m_fAge - 50.0f) / 150.0f * 0.4f;
				m_fSwakeRandom = 0.01f;
			}
			else if (m_fAgeStopped > 20.0f)
			{
				m_iIterations = 13;
				m_iTurtleStartLongitude = 22;
				m_iTurtleStartLattitude = 22;
				m_fTurtleStartLength = 1.5f + (m_fAge - 20.0f) / 30.0f * 0.5f;
				m_fTurtleStartRadius = 0.2f + (m_fAge - 20.0f) / 30.0f * 0.2f;
				m_fSwakeRandom = 0.005f;
			}
			else if (m_fAgeStopped > 10.0f)
			{
				m_iIterations = 12;
				m_iTurtleStartLongitude = 18;
				m_iTurtleStartLattitude = 18;
				m_fTurtleStartLength = 1.0f + (m_fAge - 10.0f) / 10.0f * 0.5f;
				m_fTurtleStartRadius = 0.1f + (m_fAge - 10.0f) / 10.0f * 0.1f;
				m_fSwakeRandom = 0.005f;
			}
			else if (m_fAgeStopped > 5.0f)
			{
				m_iIterations = 11;
				m_iTurtleStartLongitude = 12;
				m_iTurtleStartLattitude = 10;
				m_fTurtleStartLength = 0.8f + (m_fAge - 5.0f) / 5.0f * 0.2f;
				m_fTurtleStartRadius = 0.05f + (m_fAge - 5.0f) / 5.0f * 0.05f;
				m_fSwakeRandom = 0.002f;
			}
			else if (m_fAgeStopped > 2.0f)
			{
				m_iIterations = 10;
				m_iTurtleStartLongitude = 12;
				m_iTurtleStartLattitude = 10;
				m_fTurtleStartLength = 0.5f + (m_fAge - 2.0f) / 3.0f * 0.3f;
				m_fTurtleStartRadius = 0.02f + (m_fAge - 2.0f) / 3.0f * 0.03f;
				m_fSwakeRandom = 0.001f;
			}
			else if (m_fAgeStopped > 1.0f)
			{
				m_iIterations = 9;
				m_iTurtleStartLongitude = 12;
				m_iTurtleStartLattitude = 6;
				m_fTurtleStartLength = 0.3f + (m_fAge - 1.0f) / 1.0f * 0.2f;
				m_fTurtleStartRadius = 0.01f + (m_fAge - 1.0f) / 1.0f * 0.01f;
				m_fSwakeRandom = 0.0005f;
			}
			else
			{
				m_iIterations = 8;
				m_iTurtleStartLongitude = 12;
				m_iTurtleStartLattitude = 5;
				m_fTurtleStartLength = m_fAge * 0.3f;
				m_fTurtleStartRadius = m_fAge * 0.01f;
				m_fSwakeRandom = 0.0005f;
			}

			SetSwakeRandomFactor(m_fSwakeRandom);
			SetTurtleStartHeight(m_fTurtleStartLength);
			SetTurtleStartRadius(m_fTurtleStartRadius);

			// Stamm und �ste
			SetAxiom("X");
			AddRule("20:X={r>0.005,+(r0.90)_(>35)f[(l0.85)(<10)(r0.87)X][(l0.55)(r0.7)(>50)X]}{r<0.0051,Y}");
			AddRule("20:X={r>0.005,+(r0.9)_(<33)f[(l0.93)(>15)(r0.94)X][(l0.65)(r0.7)(<45)X]}{r<0.0051,Y}");
			AddRule("20:X={r>0.005,+(r0.84)_(<27)f[(l0.90)(>15)(r0.91)X][(l0.55)(r0.7)(>60)X]}{r<0.0051,Y}");
			AddRule("20:X={r>0.005,�+(r0.93)_(v23)f[(l0.96)(^15)(r0.85)X]}{r<0.0051,Y}");
			AddRule("20:X={r>0.005,+(r0.95)_(^30)f[(l0.82)(v15)(r0.94)X][(l0.60)(r0.7)(<77)X]}{r<0.0051,Y}");
			AddRule("50:Y=!(l0.95)f[^l]!!(l0.95)f[vl]!!(l0.95)f[^l]!!(l0.95)f[vl]!!(l0.95)f[^l]!!(l0.95)f[vh]!!(l0.95)f[^l]!!(l0.90)f[vl]!!(l0.95)f[^l]!!(l0.90)f[vl]l");
			AddRule("50:Y=!(l0.95)f[^l]!!(l0.95)f[vl]!!(l0.70)f[^l]!!(l0.95)f[vh]!!(l0.95)f[^l]!!(l0.90)f[vl]!!(l0.95)f[^l]!!(l0.90)f[vl]l");

			m_iIterations += 23;
			CGeoLSystem::Iterate(m_iIterations, m_acAxiom);
			m_iIterations -= 23;

			if (fRootCutHeight < 0.0f)
			{

				m_pzgRoot = new CGeoLSystem();
				m_pzgRoot->m_random.m_uRand = m_random.m_uRand;

				m_pzgRoot->SetAxiom("'Z");
				m_pzgRoot->AddRule("50:Z=(l0.8)[(+0)(>90)X][(+123)(>92)X][(+239)(>88)X]�(r0.80)f[X]");
				m_pzgRoot->AddRule("50:Z=(l0.8)[(+10)(>85)X][(+113)(>82)X][(+219)(>98)X]�(r0.80)(>9)f[X]");
				m_pzgRoot->AddRule("5:X=#+(r0.80)_f[(l0.90)(>10)X]");
				m_pzgRoot->AddRule("45:X=#+(r0.80)_f[(l0.79)<(r0.80)X][(l0.87)(>15)X]");
				m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.79)(<45)(r0.80)X][(l0.86)(>9)X]");
				m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.79)(<35)(r0.80)X][(l0.85)(>25)X]");


				m_pzgRoot->Iterate(m_iIterations, m_pzgRoot->m_acAxiom);

			}
	}
	

	void CGeoBioAsianTree::Init(CGeoBioAsianTree * pzgTemplate, unsigned int uLoD)
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

		char* acTurtleOrdersMain = pzgTemplate->m_pacToKill[pzgTemplate->m_iToKill - 1];

		if (!acTurtleOrdersMain)
		{
			return;
		}
		
		m_zgLeafMain.SetMiddle(Vektoria::CHVector(0.0f, 0.03f, 0.5f, 1.0f));
		if (uLoD == 0)
		{
			CHVector avOuter[28];

			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.020f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.015f, 0.0f, 0.90f, 1.0f);

			//Ausbuchtung Z1:
			avOuter[3] = CHVector(0.04f, 0.0f, 0.90f, 1.0f);
			avOuter[4] = CHVector(0.03f, 0.0f, 0.90f, 1.0f);
			avOuter[5] = CHVector(0.08f, 0.0f, 0.83f, 1.0f);

			// Z2:
			avOuter[6] = CHVector(0.15f, 0.0f, 0.85f, 1.0f);
			avOuter[7] = CHVector(0.13f, 0.0f, 0.85f, 1.0f);


			// Z3:
			avOuter[8] = CHVector(0.2f, 0.0f, 0.82f, 1.0f);
			avOuter[9] = CHVector(0.18f, 0.0f, 0.82f, 1.0f);

			// Z4:
			avOuter[10] = CHVector(0.3f, 0.0f, 0.8f, 1.0f);
			avOuter[11] = CHVector(0.28f, 0.0f, 0.8f, 1.0f);

			// Z5:
			avOuter[12] = CHVector(0.4f, 0.0f, 0.7f, 1.0f);
			avOuter[13] = CHVector(0.38f, 0.0f, 0.7f, 1.0f);

			// Z6:
			avOuter[14] = CHVector(0.45f, 0.0f, 0.6f, 1.0f);
			avOuter[15] = CHVector(0.43f, 0.0f, 0.6f, 1.0f);

			// Z7:
			avOuter[16] = CHVector(0.48f, 0.0f, 0.5f, 1.0f);
			avOuter[17] = CHVector(0.46f, 0.0f, 0.49f, 1.0f);

			// Z8:
			avOuter[18] = CHVector(0.45f, 0.0f, 0.4f, 1.0f);
			avOuter[19] = CHVector(0.43f, 0.0f, 0.41f, 1.0f);

			// Z9:
			avOuter[20] = CHVector(0.38f, 0.0f, 0.3f, 1.0f);
			avOuter[21] = CHVector(0.36f, 0.0f, 0.31f, 1.0f);

			// Z10:
			avOuter[22] = CHVector(0.27f, 0.0f, 0.2f, 1.0f);
			avOuter[23] = CHVector(0.25f, 0.0f, 0.22f, 1.0f);

			// Z11:
			avOuter[24] = CHVector(0.12f, 0.0f, 0.12f, 1.0f);
			avOuter[25] = CHVector(0.10f, 0.0f, 0.14f, 1.0f);

			avOuter[26] = CHVector(0.02f, 0.0f, 0.05f, 1.0f);
			avOuter[27] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);

			for (int i = 0; i < 28; i++)
				m_zgLeafMain.AddOuter(&avOuter[i]);

			m_zgLeafMain.Init(&m_zmLeaf, true, true);
			SetGeoLeaf(&m_zgLeafMain);
		}
		else if (uLoD <= 2)
		{
			CHVector avOuter[13];

			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.020f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.015f, 0.0f, 0.90f, 1.0f);

			//Ausbuchtung:
			avOuter[3] = CHVector(0.15f, 0.0f, 0.90f, 1.0f);
			avOuter[4] = CHVector(0.2f, 0.0f, 0.88f, 1.0f);
			avOuter[5] = CHVector(0.25f, 0.0f, 0.85f, 1.0f);
			avOuter[6] = CHVector(0.35f, 0.0f, 0.8f, 1.0f);
			avOuter[7] = CHVector(0.3f, 0.0f, 0.7f, 1.0f);
			avOuter[8] = CHVector(0.2f, 0.0f, 0.65f, 1.0f);
			avOuter[9] = CHVector(0.15f, 0.0f, 0.65f, 1.0f);
			avOuter[10] = CHVector(0.1f, 0.0f, 0.6f, 1.0f);
			avOuter[11] = CHVector(0.05f, 0.0f, 0.6f, 1.0f);
			avOuter[12] = CHVector(0.0f, 0.0f, 0.6f, 1.0f);


			for (int i = 0; i < 13; i++)
				m_zgLeafMain.AddOuter(&avOuter[i]);

			m_zgLeafMain.Init(&m_zmLeaf, true, true);
			SetGeoLeaf(&m_zgLeafMain);
		}
		else
		{
			
			CHVector avOuter[5];
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.5f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.5f, 0.0f, 0.5f, 1.0f);
			avOuter[3] = CHVector(0.5f, 0.0f, 0.0f, 1.0f);
			avOuter[4] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);
			for (int i = 0; i < 5; i++)
				m_zgLeafMain.AddOuter(&avOuter[i]);


			m_zgLeafMain.Init(&m_zmLeaf, true, true);
			SetGeoLeaf(&m_zgLeafMain);
			
		}

		CHMat mScale;
		mScale.Scale(2.0f);
		m_zgLeafMain.Transform(mScale);
		m_zmLeaf.LoadPreset("LeafBirch");

		SetMaterialLeaf(&m_zmLeaf);

		m_zmBark.LoadPreset("BarkBirch");
		SetMaterial(&m_zmBark);

		SetSwakeRandomFactor(m_fSwakeRandom);
		SetTurtleStartHeight(m_fTurtleStartLength);
		SetTurtleStartRadius(m_fTurtleStartRadius);

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

			CHMat mLoD;
			if (uLoD == 4)
			{
				mLoD.Scale(3);
				m_zgLeafMain.Transform(mLoD);
				SetLeafSkipFactor(20);
			}
			else if (uLoD == 5)
			{
				mLoD.Scale(7.5f);
				m_zgLeafMain.Transform(mLoD);
				SetLeafSkipFactor(200);
			}
			else if (uLoD >= 6)
			{
				mLoD.Scale(20);
				m_zgLeafMain.Transform(mLoD);
				SetLeafSkipFactor(2000);
			}


		}
		if (m_iTurtleStartLattitude == 1)
			m_iTurtleStartLattitude = 2;
		if (m_iTurtleStartLattitude == 0 && m_iTurtleStartLongitude > 0)
			m_iTurtleStartLattitude = 2;
		SetTurtleStartLongitude(m_iTurtleStartLongitude);
		SetTurtleStartLattitude(m_iTurtleStartLattitude);

		Interprete(acTurtleOrdersMain);

		if (pzgTemplate->m_pzgRoot && uLoD < 2)
		{
			if (!m_pzgRoot)
				m_pzgRoot = new CGeoLSystem();

			char* acTurtleOrdersRoot = pzgTemplate->m_pzgRoot->m_pacToKill[pzgTemplate->m_pzgRoot->m_iToKill - 1];
			m_pzgRoot->m_random.m_uRand = pzgTemplate->m_pzgRoot->m_random.m_uRand;

			m_pzgRoot->SetDefaultAngles(80.0f, 80.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
			m_pzgRoot->SetDefaultFactorGravitation(0.1f);

			m_pzgRoot->SetMaterial(&m_zmBark);		// Schrittweise Reduzierung der Segmentl�nge (Default: 1.0)
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

	}
	void CGeoBioAsianTree::DeIterate()
	{
		((CGeoLSystem*)this)->DeIterate();
	}
}