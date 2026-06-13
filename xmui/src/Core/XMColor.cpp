#include "Core/XMColor.h"

XMColor::XMColor()
	: m_r(255)
	, m_g(255)
	, m_b(255)
	, m_a(255)
{
}

XMColor::XMColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	: m_r(r)
	, m_g(g)
	, m_b(b)
	, m_a(a)
{

}

XMColor::~XMColor()
{
}
