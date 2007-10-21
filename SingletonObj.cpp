#include "SingletonObj.h"

SingletonObj* SingletonObj::m_spInstance = 0;

SingletonObj::SingletonObj()
{
}

SingletonObj::~SingletonObj()
{
}

SingletonObj* SingletonObj::Get()
{
	if ( !m_spInstance )
	{
		m_spInstance = new SingletonObj;
	}

	return m_spInstance;
}

void SingletonObj::Destroy()
{
	if (m_spInstance)
	{
		delete m_spInstance;
	}
}