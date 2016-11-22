/**
@file StringHelpers.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once

 #include <sstream>

 // Since std::to_string doesn't work on MinGW we have to implement
 // our own to support all platforms.
 template <typename T>
 std::string toString(const T& value);

 #include "StringHelpers.inl"