#include "Case.h"

Case::Case()
{
}

Case::Case(vec2 coord) : m_coord(coord), m_status(caseStatus::EMPTY)
{

}

bool Case::isEmpty() const
{
	return (m_status == caseStatus::EMPTY) ? true : false;
}

caseStatus Case::getCaseStatus() const
{
	return m_status;
}

void Case::setCaseStatus(caseStatus status)
{
	m_status = status;
}
