#include "fraction.h"

namespace mhle {
	fraction::fraction() :
		m_integer(),
		m_decimal(),
		m_negative()
	{

	}

	fraction::fraction(const fraction& f)
	{
		m_integer = f.m_integer;
		m_decimal = f.m_decimal;
		m_negative = f.m_negative;
	}


	fraction::fraction(unsigned _integer,
					   unsigned _decimal,
					   bool _negative) :
		m_integer(_integer),
		m_decimal(_decimal),
		m_negative(_negative)
	{
		reduce();
	}

	fraction::fraction(const char* str)
	{
		if (str[0] == '-')m_negative = 1, ++str;
		unsigned* pt = &m_integer;
		while (*str != '\0') {
			if (*str == '/')pt = &m_decimal;
			else *pt = (*pt * 10) + (*str - 48);
			++str;
		}
		reduce();
	}

	fraction::fraction(const std::string& str) :
		fraction(str.data())
	{
	}

	const std::string fraction::to_string() const noexcept
	{
		std::string result;
		if (m_negative)result = "-";
		if (!m_decimal)return result + std::to_string(m_integer);
		else
			return (result +
					std::to_string(m_integer) +
					'/' + std::to_string(m_decimal));
	}

	const int fraction::to_int() const noexcept
	{
		int tmp = (m_decimal ? m_integer / m_decimal : m_integer);
		if (m_negative)return -tmp;
		return tmp;
	}

	const double fraction::to_double() const noexcept
	{
		double tmp = (m_decimal ? m_integer * 1.0 / m_decimal : m_integer);
		if (m_negative)return -tmp;
		return tmp;
	}

	fraction& fraction::operator=(const fraction& f)
	{
		m_integer = f.m_integer;
		m_decimal = f.m_decimal;
		m_negative = f.m_negative;
		return *this;
	}

	bool fraction::operator==(const fraction& f)const
	{
		return (m_integer == f.m_integer &&
				m_decimal == f.m_decimal &&
				m_negative == f.m_negative);
	}

	const fraction fraction::operator+(const fraction& f)const
	{
		if (m_negative && f.m_negative)
			return -fraction(-*this + -f);
		if (m_negative)
			return f - *this;
		if (f.m_negative)
			return *this - f;
		else
			return fraction(m_integer * f.m_decimal +
							m_decimal * f.m_integer
							,
							m_decimal * f.m_decimal);
	}

	const fraction fraction::operator-(const fraction& f) const
	{
		if (m_negative && f.m_negative)
			return -f - (-*this);
		if (m_negative)
			return -fraction(-*this + -f);
		if (f.m_negative)
			return *this + f;
		else return fraction(m_integer * f.m_decimal -
							 m_decimal * f.m_integer
							 ,
							 m_decimal * f.m_decimal);
	}

	const fraction fraction::operator*(const fraction& f) const
	{
		return fraction(m_integer * f.m_integer,
						m_decimal * f.m_decimal,
						m_negative ^ f.m_negative);
	}

	const fraction fraction::operator/(const fraction& f) const
	{
		if (f.m_integer == 0) {
			throw std::runtime_error("try to devide by an zero");
			return fraction();
		}
		return *this * fraction(f.m_decimal, f.m_integer, f.m_negative);
	}

	const fraction gcd(const fraction& f1, const fraction& f2)
	{
		return fraction(gcd(f1.m_integer, f2.m_integer),
						gcd(f1.m_decimal, f2.m_decimal),
						f2.m_negative);
	}

	const fraction lcm(const fraction& f1, const fraction& f2)
	{
		return fraction(f1 * f2 / gcd(f1, f2));
	}

	const fraction abs(fraction f)
	{
		f.m_negative = 0;
		return f;
	}

	void fraction::reduce()
	{
		if (m_integer == 0 || m_decimal == 0) {
			m_integer = m_decimal = 0;
			return;
		}
		int tmp = gcd(m_integer, m_decimal);
		m_integer /= tmp, m_decimal /= tmp;
	}

	std::istream& fraction::operator>>(std::istream& in)
	{
		std::string str;
		in >> str;
		int i = 0;
		if (str[0] == '-')m_negative = 1,++i;
		unsigned* pt = &m_integer;
		while (i<str.length()) {
			if (str[i] == '/')pt = &m_decimal;
			else *pt = (*pt * 10) + (str[i] - 48);
			++i;
		}
		reduce();
		return in;
	}

	std::ostream& fraction::operator<<(std::ostream& out) const
	{
		out << to_string();
		return out;
	}

	const fraction fraction::operator-() const
	{
		return fraction(m_integer, m_decimal, !m_negative);
	}

}