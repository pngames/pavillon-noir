#include "Logger.h"
#include <fstream>

namespace opal
{
	namespace loggerImpl
	{
		Logger::Logger()
		{
			//static std::ofstream debugOut, warningOut, errorOut;
			//debugOut.open("opal_debug.log");
			//warningOut.open("opal_warning.log");
			//errorOut.open("opal_error.log");

			//setStream("debug", &debugOut, "[OPAL debug] ");
			//setStream("warning", &warningOut, "[OPAL warning] ");
			//setStream("error", &errorOut, "[OPAL error] ");
			//setStream("performance", &std::cout);

			setStream("debug", &std::cout, "[OPAL debug] ");
			setStream("warning", &std::cout, "[OPAL warning] ");
			setStream("error", &std::cout, "[OPAL error] ");
		}

		Logger::~Logger()
		{
		}

		void Logger::setStream(const std::string &name, std::ostream *stream, 
			const std::string& prefix, char mark)
		{
			Logger::Stream s;
			s.mark = mark;
			s.silent = false;
			s.stream = stream;
			s.prefix = prefix;
	//		s.nullStream = new std::ostream( s.nullBuffer );
			mStreams[name] = s;
		}

		//void Logger::silenceStream(const std::string &name)
		//{
		//	std::map<std::string, Logger::Stream>::iterator itr = 
		//		mStreams.find(name);
		//	if(itr != mStreams.end())
		//	{
		//		itr->second.silent = true;
		//	}
		//}

		//void Logger::unsilenceStream(const std::string &name)
		//{
		//	std::map<std::string, Logger::Stream>::iterator itr = 
		//		mStreams.find(name);		
		//	if(itr != mStreams.end())
		//	{
		//		itr->second.silent = false;
		//	}
		//}

		std::ostream &Logger::stream(const std::string &name)
		{
			Logger::Stream s = mStreams[name];

			if(s.mark != '\0')
			{
				std::cout << s.mark;
				std::cout.flush();
			}

			if (!s.prefix.empty())
			{
				*s.stream << s.prefix;
			}

			return *(s.stream);
		}
	}
}
