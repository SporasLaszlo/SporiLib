//#include "stdafx.h"
#include "ColorGenerator.h"

CColorGenerator::SColorGeneratorData CColorGenerator::m_data;

CColorGenerator::CColorGenerator(void)
{
}
CColorGenerator::~CColorGenerator(void)
{
}

void CColorGenerator::_Init()
{
	//m_colors.push_back(cv::Scalar(0, 0, 0)); //fekete
	m_data.m_colors.clear();
	m_data.m_colors.push_back(cv::Scalar(255, 0, 0)); //kek
	m_data.m_colors.push_back(cv::Scalar(0, 255, 0)); //zold
	m_data.m_colors.push_back(cv::Scalar(0, 0, 255)); //piros
	m_data.m_colors.push_back(cv::Scalar(255, 255, 0)); //cian
	m_data.m_colors.push_back(cv::Scalar(255, 0, 255)); //lila
	m_data.m_colors.push_back(cv::Scalar(0, 255, 255)); //sarga
	m_data.m_colors.push_back(cv::Scalar(255, 255, 255)); //feher
	m_data.m_colors.push_back(cv::Scalar(255, 130, 130));
	m_data.m_colors.push_back(cv::Scalar(130, 255, 130));
	m_data.m_init = true;
}
cv::Scalar CColorGenerator::EXT_GetColor(int ID)
{
	if (m_data.m_init)
	{
		return m_data.m_colors.at(ID % m_data.m_colors.size());
	}
	else
	{
		_Init();
		return m_data.m_colors.at(ID % m_data.m_colors.size());
	}
}
