#ifndef UTILS_H
#define UTILS_H

#include <iostream>

namespace stl {

// 提取类型的 traits，原始定义
template<typename T>
struct remove_reference {
	typedef T type;
};

// 提取类型的 traits，偏特化左值引用
template<typename T>
struct remove_reference<T&> {
	typedef T type;
};

// 提取类型的 traits，偏特化右值引用
template<typename T>
struct remove_reference<T&&> {
	typedef T type;
};

// move
template<typename T>
typename remove_reference<T>::type&& move(T&& args) {
	return static_cast<typename remove_reference<T>::type&&>(args);
}

// forward
template<typename T>
T&& forward(typename std::remove_reference<T>::type& arg) {
	return static_cast<T&&>(arg);
}

template<typename T>
T&& forward(typename std::remove_reference<T>::type&& arg) {
	return static_cast<T&&>(arg);
}

// pair
template<typename T1, typename T2>
struct pair
{
	using first_type = T1;
	using second_type = T2;

	// 内部数值
	first_type first_val;
	second_type second_val;

	pair(const pair& rhs) = default;
	pair(pair&& rhs) = default;

	// 默认构造函数
	template<typename U1 = T1, typename U2 = T2,
		typename _type = typename std::enable_if<
		std::is_default_constructible<U1>::value&&
		std::is_default_constructible<U2>::value>::type>
	pair() : first_val(), second_val() {};

	// 带参数的默认构造函数
	template<typename U1 = T1, typename U2 = T2,
		typename _type = typename std::enable_if<
		std::is_default_constructible<U1>::value&&
		std::is_default_constructible<U2>::value&&
		std::is_convertible<const U1&, T1>::value&&
		std::is_convertible<const U2&, T2>::value>::type>
	pair(const U1& _first_val, const U2& _second_val) :
		first_val(_first_val), second_val(_second_val) {};

	friend std::ostream& operator << (std::ostream& os, pair _pair) {
		os << _pair.first_val << ", " << _pair.second_val << std::endl;
		return os;
	}
};

template<typename T1, typename T2>
bool operator<(const pair<T1, T2>& lpair, const pair<T1, T2>& rpair) {
	return lpair.first_val < rpair.first_val ||
		(lpair.first_val == rpair.first_val &&
			lpair.second_val < rpair.second_val);
}

template<typename T1, typename T2>
bool operator>(const pair<T1, T2>& lpair, const pair<T1, T2>& rpair) {
	return lpair.first_val > rpair.first_val ||
		(lpair.first_val == rpair.first_val &&
			lpair.second_val > rpair.second_val);
}

template<typename T1, typename T2>
bool operator<=(const pair<T1, T2>& lpair, const pair<T1, T2>& rpair) {
	return lpair < rpair || lpair == rpair;
}

template<typename T1, typename T2>
bool operator>=(const pair<T1, T2>& lpair, const pair<T1, T2>& rpair) {
	return lpair > rpair || lpair == rpair;
}

template<typename T1, typename T2>
bool operator==(const pair<T1, T2>& lpair, const pair<T1, T2>& rpair) {
	return lpair.first_val == rpair.first_val &&
		lpair.second_val == rpair.second_val;
}

template<typename T1, typename T2>
bool operator!=(const pair<T1, T2>& lpair, const pair<T1, T2>& rpair) {
	return !(lpair == rpair);
}
}
#endif