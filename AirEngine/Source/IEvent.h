#pragma once
#include "Macros.h"

#define MAKE_TRIVIAL_EVENT(eventName)	\
struct eventName : public IEvent		\
{										\
public:									\
	eventName()							\
		: IEvent(#eventName)			\
	{}									\
};

struct IEvent
{
private:
	const char* m_pName;

public:
	IEvent(const char* pName)
		: m_pName(pName)
	{}

	const char* GetName() const { return m_pName; }
};