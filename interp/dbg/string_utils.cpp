#include "string_utils.h"
#include <cstdio>

vector<string> string_utils::string_split( const string& s, const char delimiter )
{
    size_t start = 0;
    size_t end = s.find_first_of( delimiter );

    vector<string> output;

    while( end <= string::npos )
    {
	output.emplace_back( s.substr( start, end - start ) );

        if( end == string::npos )
	    break;

	    start = end + 1;
	    end = s.find_first_of( delimiter, start );
    }

    return output;
}

//http://stackoverflow.com/a/217605
void string_utils::ltrim( string &s ) 
{
    s.erase( s.begin(), std::find_if( s.begin(), s.end(), std::not1( std::ptr_fun<int, int>( std::isspace ) ) ) );
}

bool string_utils::is_number( const string& num_text, int base, int* res )
{
    char* p;
    if( res != nullptr )
	*res = strtol( num_text.c_str(), &p, base );
    else
	strtol( num_text.c_str(), &p, base );
    return *p == 0;
}

bool string_utils::begins_with( const string & input, const string & begin )
{
    return input.length() >= begin.length() && input.substr( 0, begin.length() ) == begin;
}

bool string_utils::ends_with( const string & input, const string & end )
{
    return input.length() >= end.length() && input.substr( input.length() - end.length() ) == end;
}

string string_utils::to_hex( int32_t num )
{
    char buf[32];
    sprintf( buf, "%x", num );
    return string( "0x" ) + buf;
}