/**
 * Displays text on screen. Singleton Class.
 */
#include "TextManager.h"
#include "ResourceManager.h"

//--------------------------------------------------------------------------- 
/** 
 * Ctor
 * 
 */
TextManager::TextManager() : m_pRenderer(0)
{
}
//--------------------------------------------------------------------------- 
/** 
 * Dtor
 * 
 */
TextManager::~TextManager()
{
	m_tStrings.RemoveAll();
}
//--------------------------------------------------------------------------- 
/** 
 * Adds a string to the list of strings to be displayed
 * 
 * @param text: The text
 * @param font: The font
 * @param flags: String flags 
 * @param maxLength: Maximum text length 
 * @param color: Color of text 
 * @param x: x position 
 * @param y: y position: 
 * @param type: TOBEREMOVED
 * 
 * @return bool
 */
bool TextManager::AddString(const char *text, NiFontPtr font, 
							unsigned int flags, unsigned int maxLength,
							const NiColorA& color, short x, short y,
							StringType type)
{
	Ni2DStringPtr str = NiNew Ni2DString((NiFont*)font, flags, maxLength, text, 
										 color, x, y);
	if (str)
	{
		m_tStrings.SetAt(type, str);
		return true;
	}
	else 
		return false;
}
//--------------------------------------------------------------------------- 
/** 
 * Initializes the manager
 * 
 * @param renderer
 * 
 * @return bool
 */
bool TextManager::Init(NiRenderer* renderer)
{
	// create default strings
	m_pRenderer = renderer;
	NiFontPtr font = ResourceManager::Get()->GetFont
		(ResourceManager::RES_FONT_SELECTEDSOLDIERS);
	if (!font) return false;

	bool bSuccess = AddString("", font , NiFontString::COLORED |
		NiFontString::CENTERED, 10, NiColorA(1.0, 1.0, 0.0, 1.0), 50, 20, STRING_SELECTEDSOLDIERS);

	return bSuccess;
}
//--------------------------------------------------------------------------- 
/** 
 * Updates the text of a string
 * 
 * @param type
 * @param text
 */
void TextManager::UpdateText(StringType type, const char* text)
{	
	Ni2DStringPtr str = 0;
	m_tStrings.GetAt(type, str);
	if (str) str->SetText(text);
}
//--------------------------------------------------------------------------- 
/** 
 * Renders text
 * 
 */
void TextManager::DisplayText()
{
	if (m_tStrings.IsEmpty() || !m_pRenderer) return;

	NiTMapIterator it = m_tStrings.GetFirstPos();
	StringType type;
	Ni2DStringPtr str = 0;
	for (int i=0; i<m_tStrings.GetCount(); i++)
	{
		m_tStrings.GetNext(it, type, str);
		if (str) str->Draw(m_pRenderer);
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
