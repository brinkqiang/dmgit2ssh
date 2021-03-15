
#include "execute.h"
#include "dmscan.h"

int https2ssh(std::string strGit, Iexecute* execute)
{
	std::string strGitUrl;
	fmt::scan(strGit, "https://{0}", strGitUrl);
	strGitUrl = strGitUrl.substr(0, strGitUrl.find('/'));

	if (strGitUrl.empty())
	{
		return -1;
	}

	std::string strName;
	std::string strProject;


	std::string strNameTmp = "https://" + strGitUrl + "/" + "{}";

	fmt::scan(strGit, strNameTmp, strName);
	strName = strName.substr(0, strName.find('/'));

	std::string strCmd = "https://" + strGitUrl + "/" + strName + "/{}";
	fmt::scan(strGit, strCmd, strProject);
	strProject = strProject.substr(0, strProject.find_last_of('.'));


	std::string strUrl = fmt::format("git remote set-url origin git@{}:{}/{}.git", strGitUrl, strName, strProject);

	std::string strSSH = execute->exec(strUrl);

	std::cout << fmt::format("https://{}/{}/{}.git", strGitUrl, strName, strProject) << std::endl;
	std::cout << fmt::format("git@{}:{}/{}.git", strGitUrl, strName, strProject) << std::endl;

	return 0;
}

int ssh2https(std::string strGit, Iexecute* execute)
{
	std::string strGitUrl;
	fmt::scan(strGit, "git@{0}", strGitUrl);
	strGitUrl = strGitUrl.substr(0, strGitUrl.find(':'));

	if (strGitUrl.empty())
	{
		return -1;
	}

	std::string strName;
	std::string strProject;

	std::string strNameTmp = "git@" + strGitUrl + ":" + "{}";

	fmt::scan(strGit, strNameTmp, strName);
	strName = strName.substr(0, strName.find('/'));

	std::string strCmd = "git@" + strGitUrl + ":" + strName + "/{}";
	fmt::scan(strGit, strCmd, strProject);
	strProject = strProject.substr(0, strProject.find_last_of('.'));

	std::string strUrl = fmt::format("git remote set-url origin https://{}/{}/{}.git", strGitUrl, strName, strProject);

	std::string strHTTPS = execute->exec(strUrl);

	std::cout << fmt::format("https://{}/{}/{}.git", strGitUrl, strName, strProject) << std::endl;
	std::cout << fmt::format("git@{}:{}/{}.git", strGitUrl, strName, strProject) << std::endl;

	return 0;
}

int main(int argc, char* argv[])
{
    Iexecute* execute = executeGetModule();

    if (NULL != execute)
    {
        std::string strGit = execute->exec("git remote -v | awk \"{ print $2 }\"");

#ifdef WIN32
		strGit = strGit.substr(0, strGit.find('\n'));
#else
		strGit = strGit.substr(0, strGit.find('\n')); 
		strGit = strGit.substr(strGit.find('\t')+1, strGit.size());
#endif
        std::string strCompare = strGit.substr(0, strlen("https"));
        if (strCompare.compare("https") != 0)
        {
			ssh2https(strGit, execute);
            return -1;
        }

        return https2ssh(strGit, execute);
    }

    return 0;
}
