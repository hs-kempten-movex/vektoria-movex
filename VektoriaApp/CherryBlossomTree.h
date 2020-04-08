#include "Vektoria\Root.h"
using namespace Vektoria;

class CherryBlossomTree : public CGeoBio
{
public:
	CherryBlossomTree();
	~CherryBlossomTree();
private:
	CGeoBio m_zgCherryblossom;
	CMaterial m_zmBlatt;
	CMaterial m_zmStamm;
};