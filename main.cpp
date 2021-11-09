#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <vector>
#include <filesystem>

class file
{
	public:
	std::string name;
	std::vector<std::string> contents;

	file( std::string in_name )
	{
		name = in_name;
	}

	bool exists()
	{
		return std::filesystem::exists( name );
	}

	void setup(std::vector<std::pair<std::string, bool>> settings)
	{
		if( !exists() )
		{
			std::vector<std::string> to_build;

			for( int i = 0; i != settings.size(); i++ )
			{
				std::string temp_string = "[" + std::to_string( i ) + "]" + settings[ i ].first + "=" + std::to_string(settings[i].second);
				to_build.push_back( temp_string );
			}

			std::ofstream myfile( name );
			if( myfile.is_open() )
			{
				for( std::string s : to_build )
				{
					myfile << s + "\n";
				}
				myfile.close();
			}
		}
	}

	std::string get_value( std::string command )
	{
		read();
		std::string command_string;

		for( std::string x : contents )
		{
			int command_find = x.find( command );
			if( command_find > -1 && command_find < 1000 )
			{
				int false_find = x.find( "FALSE" );
				int true_find = x.find( "TRUE" );

				if( false_find > -1 && false_find < 1000 )
					return "FALSE";
				else if( true_find > -1 && true_find < 1000 )
					return "TRUE";
				else
					return "ERROR";
			}
		}

		//print error here
		return "ERROR";
	}

	void write( std::vector<std::string> insert )
	{
		std::ofstream myfile( name );

		if( myfile.is_open() )
		{
			for( std::string s : insert )
			{
				myfile << s + "\n";
			}
			myfile.close();
		}
	}

	void read()
	{
		contents.clear();
		std::string current_line;

		std::ifstream myfile( name );
		if( myfile.is_open() )
		{
			while( std::getline( myfile, current_line ) )
			{
				contents.push_back( current_line );
			}
			myfile.close();
		}
	}
};

void example_load()
{
	file config( "settings.txt" );
	std::cout << config.get_value( "setting_two" );
}

void example_save()
{
	file config( "settings.txt" );
	std::vector<std::pair<std::string, bool>> setts;

	setts.push_back( { "setting_one", false } );
	setts.push_back( { "setting_two", true } );
	setts.push_back( { "setting_three", false } );

	config.setup( setts );

	std::cout << config.get_value( "setting_one" ) << std::endl;
	std::cout << config.get_value( "setting_two" ) << std::endl;
}

int main()
{
	//example_save();
	example_load();
	Sleep( 500000 );
}
