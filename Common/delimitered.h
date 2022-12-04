#include <iostream>
#include <string>

#include <stream_required.h>

template<typename T, char sep = ','>
struct delimitered_value
{
	T value;

	operator const T& () const { return value; }
	operator T && ()&& { return std::move(value); }
};

template<typename T, char sep>
std::istream& operator>>(std::istream& in, delimitered_value<T, sep>& t)
{
	if (!(in >> t.value)) //if we failed to read the int
		return in;          //return failure state
	if (in.peek() == sep) //if next character is a comma
		in.ignore();        //extract it from the stream and we're done
	else                  //if the next character is anything else
		in.clear();         //clear the EOF state, read was successful
	return in;
}

template<char sep>
std::istream& operator>>(std::istream& in, delimitered_value<std::string, sep>& t)
{
	std::getline(in, t.value, sep);
	return in;
}

template<typename T>
using comma_separated = delimitered_value<T, ','>;



template<typename T, char sep = ','>
struct delimitered_container;

template<typename T>
struct remove_delimitered
{
	using type = T;
};

template<typename T, char sep>
struct remove_delimitered<delimitered_container<T, sep>>
{
	using type = T;
};

template<typename T, typename U>
struct remove_delimitered<std::pair<T, U>>
{
	using type = std::pair<typename remove_delimitered<T>::type, typename remove_delimitered<U>::type>;
};

template<typename T, char sep>
struct delimitered_container
{
	T value;

	operator const T& () const { return value; }
	operator T&& () && { return std::move(value); }
	operator remove_delimitered<T>::type() const& requires !std::same_as<T, remove_delimitered<T>::type> { return value; }
	operator remove_delimitered<T>::type() && requires !std::same_as<T, remove_delimitered<T>::type> { return std::move(value); }
};

template<typename T, typename U, char sep>
std::istream& operator>>(std::istream& in, delimitered_container<std::pair<T,U>, sep>& t)
{
	in >> t.value.first >> required{ sep } >> t.value.second;

	return in;
}

template<typename T, typename U, char sep=','>
using delimitered_pair = delimitered_container<std::pair<T, U>, sep>;
