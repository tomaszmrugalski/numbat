//

#ifndef __FACTSDEFS_H__
#define __FACTSDEFS_H__

#include <string>

//
// General FACTS related definitions.
//

// switches used when parsing input files
// constants define the output format
#define	OUTPUT_GEORSS	1
#define	OUTPUT_JAVA		2
#define	OUTPUT_STL		3


static void _readModuleParameters(cModule *mod)
{
    int n = mod->params();
    for (int k=0; k<n; k++)
        if (mod->par(k).isInput())
            mod->par(k).read();
}


/**
 * Trim whitespace from string.
 */
static std::string& trim(std::string& str)
{
	std::string::size_type pos = str.find_last_not_of(' ');
	if (pos != std::string::npos)
	{
		str.erase(pos + 1);
		pos = str.find_first_not_of(' ');
		if (pos != std::string::npos)
			str.erase(0, pos);
	}
	else
		str.erase( str.begin(), str.end() );
	
	return str;
}


#endif
