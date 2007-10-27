#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include "SingletonObj.h"
#include <NiTMap.h>
#include <Ni2DString.h>
#include <NiRenderer.h>

class TextManager : public SingletonObj<TextManager>
{
	friend SingletonObj<TextManager>;
public:

	enum StringType
	{
		STRING_SELECTEDSOLDIERS = 0
	};
	
	bool Init(NiRenderer* renderer);
	void UpdateText(StringType type, const char* text);
	void DisplayText();

private:
	TextManager();
	~TextManager();

	bool AddString(const char *text, NiFontPtr font, 
				   unsigned int flags, unsigned int maxLength,
				   const NiColorA& color, short x, short y,
				   StringType type);

	NiTMap<StringType, Ni2DStringPtr> m_tStrings;
	NiRenderer* m_pRenderer;
};

#endif