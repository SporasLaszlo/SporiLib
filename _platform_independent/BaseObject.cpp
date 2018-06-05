//#include "stdafx.h"
#include "BaseObject.h"

CBaseObject::CBaseObject()
{
	m_init = false;
	m_className = "BaseObject";
	m_classFunction = "";
	m_ID = 0;
}
CBaseObject::~CBaseObject()
{
}

void CBaseObject::EXT_SetID(int ID)
{
	m_ID = ID;
}
int CBaseObject::EXT_GetID()
{
	return m_ID;
}