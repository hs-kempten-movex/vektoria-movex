#pragma once
#include "Vektoria\Root.h"

//--------------------------------------------------------------------------
// CGeoBioChelidoniumMajus 
// 
// Erklärung: Klasse, um prozedural realistische Geometrien für das Schöllkraut (Chelidonium Majus) zu erzeugen
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt
// Zeit     : seit April. 2020 (mit seitdem ständigen Verbesserungs-Updates) 
// Copyright: Tobias Breiner und die panokratischen U-Topienauten
//--------------------------------------------------------------------------

namespace Vektoria
{
	class GeoBioPoppy : public CGeoBio
	{
	public:
		///<summary> Konstruktor </summary> 
		GeoBioPoppy();

		///<summary> Destruktor </summary> 
		~GeoBioPoppy();

		///<summary> Erzeugt das L-System. <para></para>
		/// Achtung Nr. 1! Nach "Iterate" müssen eine oder mehere "Init"-Methoden verschiedener Objektinstanzen aufgerufen werden, um die Geometrie zu erzeugen. 
		/// Achtung Nr. 2! Nach allen "Init"-Methodenaufrufen sollte "Deiterate" aufgerufen werden, um das L-System wieder zu zerstören und den Speicher freizugeben. </summary> 
		///<param name="fAge"> Alter in Jahren (Je älter, desto größer und komplexer). </param>
		///<param name="frTimeOfYear"> Fraktionale Jahreszeit (Frühlingstagundnachtgleiche = 0.0f .. Sommersonnenwende  = 0.25f ... Herbsttagundnachtgleiche = 0.5f ... Wintersonnenwende = 0.75f) <para></para>
		/// Wichtig für Farbe und Aussehen der Blätter. </param>
		///<param name="fRootCutHeight"> Unter dieser Höhe werden die Wurzeln nicht mehr erzeugt. <para></para>
		/// Bei "0.0f" wird die Erzeugung der Wurzel ganz ausgelassen (default). </param>
		void Iterate(float fAge, float frTimeOfYear = 0.25f, float fRootCutHeight = 0.0f);

		///<summary> Sollte nach "Iterate"- und allen "Init"-Methodenaufrufen final aufgerufen werden, <para></para>
		/// um das L-System wieder zu zerstören und den Speicher freizugeben. </summary> 
		void DeIterate();

		///<summary> Erzeugt die Baumgeometrie für eine ausgewählte Level of Detail-Stufe. <para></para>
		/// Achtung! Vor "Init" muss die Methode "Iterate" aufgerufen werden.  </summary> 
		///<param name="pzgTemplate"> Pointer zu einer Vorlage-Birke, bei der schon Iterate aufgerufen wurde, <para></para>
		/// um das L-System zu erzeugen. </param>
		///<param name="uLoD"> Level of Detail-Stufe <para></para>
		/// 0 => höchstpolygonale Stufe, <para></para>
		/// 1 => zweithöchstpolygonale Stufe, ca. ein Viertel Polys weniger als Stufe 0).,<para></para>
		/// 2 => dritthöchstpolygonale Stufe, ca. ein Sechszehntel Polys weniger als Stufe 0).<para></para>
		/// 3 => etc.</param>
		void Init(GeoBioPoppy * pzgTemplate, unsigned int uLoD = 0);

		///<summary> Gibt den Entfernungswert in Units (=Metern) für die optimale Distanz der minimalen LoD-Stufe aus. <para></para>
		/// Optimal, heißt hier, dass bei einem 4K-Monitor das Switchen optisch nicht mehr wahrgenommen wird, da es weniger als 4 Pixel betrift.<para></para>
		/// Will man eine höhere Frame-Rate, auf Kosten des LoD-Poppings, kann z.B. durch einen Faktor > 1 geteilt werden. </summary> 
		///<param name="fAge"> Alter des Graßes in Jahren (Je älter, desto größer und komplexer). </param>
		///<param name="uLoD"> Level of Detail-Stufe <para></para>
		/// 0 => höchstpolygonale Stufe, <para></para>
		/// 1 => zweithöchstpolygonale Stufe, ca. ein Viertel Polys weniger als Stufe 0).,<para></para>
		/// 2 => dritthöchstpolygonale Stufe, ca. ein Sechszehntel Polys weniger als Stufe 0).<para></para>
		/// 3 => etc.</param>
		float GetOptimalLoDMin(float fAge, unsigned int uLoD);

		///<summary> Gibt den Entfernungswert in Units (=Metern) für die optimale Distanz der minimalen LoD-Stufe aus. <para></para>
		/// Optimal, heißt hier, dass bei einem 4K-Monitor das Switchen optisch nicht mehr wahrgenommen wird, da es weniger als 4 Pixel betrift.<para></para>
		/// Will man eine höhere Frame-Rate, auf Kosten des LoD-Poppings, kann z.B. durch einen Faktor > 1 geteilt werden. </summary> 
		///<param name="fAge"> Alter des Graßes in Jahren (Je älter, desto größer und komplexer). </param>
		///<param name="uLoD"> Level of Detail-Stufe <para></para>
		/// 0 => höchstpolygonale Stufe, <para></para>
		/// 1 => zweithöchstpolygonale Stufe, ca. ein Viertel Polys weniger als Stufe 0).,<para></para>
		/// 2 => dritthöchstpolygonale Stufe, ca. ein Sechszehntel Polys weniger als Stufe 0).<para></para>
		/// 3 => etc.</param>
		float GetOptimalLoDMax(float fAge, unsigned int uLoD);

		///<summary> Haupt-Blütenblatt-Geometrie </summary>
		CGeoLeaf m_zgStamenMain;

		///<summary> Haupt-Blütenblatt-Geometrie </summary>
		CGeoLeaf m_zgBlossomMain;

		///<summary> Haupt-Blatt-Geometrie </summary>
		CGeoLeaf m_zgLeafMain;

		///<summary> Haupt-Frucht-Geometrie </summary>
		CGeoTriangleTable m_zgFruitMain;

		///<summary> Material des Staubblattes </summary>
		CMaterial m_zmStamen;


		// rand float
		CRandom Colorscaling;

		float fColorscaling;
	};
}
