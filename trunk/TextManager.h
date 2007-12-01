#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include "SingletonObj.h"
#include <NiTMap.h>
#include <Ni2DString.h>
#include <NiRenderer.h>

// Singleton class, TO_BE_REFACTORED
class TextManager : public SingletonObj<TextManager>
{
	friend SingletonObj<TextManager>;
public:

	// string types
	enum StringType
	{
		STRING_SELECTEDSOLDIERS = 0,
		STRING_KILLINGRATE
	};
	
	// initializes the manager
	bool Init(NiRenderer* renderer);
	// updates the text for a specific string type
	void UpdateText(StringType type, const char* text);
	// renders text
	void DisplayText();

private:
	// private ctor / dtor
	TextManager();
	~TextManager();
	
	// adds a string to the hash table
	bool AddString(const char *text, NiFontPtr font, 
				   unsigned int flags, unsigned int maxLength,
				   const NiColorA& color, short x, short y,
				   StringType type);

	// a hast table that contains all of the strings to be displayed
	NiTMap<StringType, Ni2DStringPtr> m_tStrings;
	// the renderer that is used to render the text
	NiRenderer* m_pRenderer;
};

#endif