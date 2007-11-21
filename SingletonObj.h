#ifndef SINGLETONOBJ_H
#define SINGLETONOBJ_H

#include "GameObj.h"
#include "NiMemObject.h"

template <typename T>
class SingletonObj : public NiMemObject
{
protected:

	// protected Ctor / Dtor (Singleton Pattern)
	SingletonObj()
	{}

	virtual ~SingletonObj()
	{}

	// static single instance of the class
	static T* m_instance;

public:

	// gets a single instance of the class
	static T* Get()
	{
		if ( !m_instance )
		{
			m_instance = NiNew T();
		}

		return m_instance;
	}

	// destroys the single instance of the class
	static void  Destroy()
	{
        NiDelete m_instance;
        m_instance = 0;
    }
	
};

// initialize single instance to Null
template <typename T> T* SingletonObj<T>::m_instance = 0;

#endif